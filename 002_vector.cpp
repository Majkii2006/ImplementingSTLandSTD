#include <iostream>
#include <vector>

namespace goat {
	template <typename T>
	class Vector {

		public:
			Vector() = default;
			~Vector() {
				delete[] m_data;
			}
			Vector(const Vector& other){
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				m_data = new T[m_capacity];

				for (size_t i {}; i < m_size; ++i){
					m_data[i] = other.m_data[i];
				}

			}
			Vector& operator=(const Vector& other){
				if (&this != other){
					m_capacity = other.m_capacity;		
					m_size = other.m_size;
					m_data = new T[m_capacity];

					for (size_t i {}; i < m_size; ++i){
						m_data[i] = other.m_data[i];
					}
					return m_data;
				}
				return m_data;
			}
			Vector(Vector&& other){
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				m_data = new T[m_capacity];
				
				for(size_t i {}; i < m_size; ++i){
					m_data[i] = other.m_data[i];
				}
			}
			Vector& operator=(Vector&& other) {
				if (&this != other){
					m_capacity = other.m_capacity;
					m_size = other.m_size;
					m_data = new T[m_capacity];

					for(size_t i {}; i < m_size; ++i){
						m_data[i] = other.m_data[i];		
					} 
					return m_data;
				}

				return m_data;
			}
				
			void push_back(const T& element){
				if (m_size >= m_capacity){
					constexpr size_t INITIAL_CAPACITY {2};
					constexpr size_t CAPACITY_FACTOR {2};
					if (m_capacity == 0){
						m_capacity = 2;
					} 
					else {
						m_capacity = m_capacity * CAPACITY_FACTOR;
					}
					realloc();
				}

				m_data[m_size] = element;
				m_size++;
			}

			size_t get_size() const {
				return m_size;
			}

			size_t get_capacity() const {
				return m_capacity;
			}

			void print_vector() const {
				for(size_t i {}; i < m_size; ++i){
					std::cout << m_data[i];
				}	
			}

		private:
			T* m_data { nullptr };
			size_t m_size { 0 }; //for the size of things
			size_t m_capacity { 0 }; // for the maximum amount of bytes of object
			
			void realloc() {
				auto old_data { m_data };
				m_data = new T[m_capacity];

				for(size_t i {}; i < m_size; ++i){
					m_data[i] = std::move(old_data[i]);
				}

				delete[] old_data;
			}


	};

}

int main() {
	int number { 25 };
	int* ptr = &number;
	std::cout << *ptr << std::endl;
	std::cout << ptr << std::endl;
	goat::Vector<int> MineVector;
	MineVector.push_back(1);
	MineVector.push_back(2);
	MineVector.push_back(3);

	MineVector.print_vector();
	std::cout << "\n" << MineVector.get_size() << std::endl;
	std::cout << MineVector.get_capacity() << std::endl;

	std::vector<int> Vector = {1, 2, 3};



	return 0;
}
