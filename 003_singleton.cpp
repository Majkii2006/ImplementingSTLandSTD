#include <iostream>

class Singleton {
	private:
		
		int* m_data;
		size_t m_size;
		
		Singleton(size_t size){
			m_data = new int[m_size];
			
		}	

	public:
		static Singleton& getInstance(size_t m_size) {
			static Singleton instance(m_size);
			return instance;
		}

		~Singleton() {
			delete[] m_data;
		}
		
		//Need to disable copy constructor and copy assignment 
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		
		int* get_data() const {
			return m_data;
		}
};



int main() {
	
	Singleton& s1 = Singleton::getInstance(5);
	std::cout << s1.get_data() << std::endl;

	Singleton& s2 = Singleton::getInstance(4);
	std::cout << s2.get_data() << std::endl;

	//To samo miejsce w pamięci


	return 0;
}
