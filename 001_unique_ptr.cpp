#include <iostream>

template <typename T>
class UniquePtr {

	private:
		T* m_ptr = nullptr;	
	public:
		UniquePtr(T* ptr) { 
			m_ptr = ptr;
		}
		UniquePtr() = default;

		~UniquePtr() {
			delete m_ptr;
		}
		
		UniquePtr(const UniquePtr& other) = delete;

		UniquePtr(UniquePtr&& other) {
			if (&other == this) {
				return;
			}
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}

		UniquePtr& operator=(const UniquePtr& other) = delete;
	
		UniquePtr& operator=(UniquePtr&& other) {
			if (&other == this) {
				return *this;
			}
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
			return *this;
		}
	
		T* get() const {
			return m_ptr;
		}

		void release() {
			delete m_ptr;
			m_ptr = nullptr;
		}

		void reset(T* ptr) {
			release();
			m_ptr = ptr;
		}



};


int main () {

	int number { 25 };

	int* raw_ptr2 = &number;
	UniquePtr<int> ptr1;
	UniquePtr<int> ptr2(raw_ptr2);

	return 0;
}

