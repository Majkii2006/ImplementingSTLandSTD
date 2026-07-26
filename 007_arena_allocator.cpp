#include <iostream>

class Arena {
public:
	Arena (std::size_t size) : m_size(size) {
		m_buffer = reinterpret_cast<std::byte*>(::operator new(size));
	}  
	~Arena() {}



private:
	std::byte* m_buffer {};
	std::size_t m_size {};
	std::size_t m_capacity {};

};
int main() {


	return 0;
}
