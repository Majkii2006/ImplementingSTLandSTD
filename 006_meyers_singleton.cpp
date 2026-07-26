#include <iostream>

class Singleton {

	public:
		static Singleton& getInstance() {
			static Singleton instance;
			return instance;
		}
		
		~Singleton() {
			std::cout << "Singleton Destroyed" << std::endl;
		}
	
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;


	private:
		Singleton() {
			std::cout << "Singleton Created" << std::endl;	
		}
			




};


int main() {
	
	Singleton::getInstance();

	return 0;
}
