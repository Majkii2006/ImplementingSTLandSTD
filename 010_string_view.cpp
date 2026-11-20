#include <cstring>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

class StringView {

public:
	StringView() noexcept = default;
	StringView(const char* str) : m_data(str), m_length(std::strlen(str)) {}
	StringView(const char* str, std::size_t len) noexcept : m_data(str), m_length(len) {}
	StringView(const std::string& str) noexcept : m_data(str.data()), m_length(str.size()) {}

	const char* data() const noexcept { return m_data; }
	std::size_t size() const noexcept { return m_length; }
	bool empty() const noexcept { return m_length == 0; }
	char operator[](std::size_t i) { return m_data[i]; }

	friend std::ostream& operator <<(std::ostream& os, StringView sv) {
		return os.write(sv.m_data, sv.m_length);
	}


private:
	const char* m_data = nullptr;
	std::size_t m_length = 0;
};


int main() {
	std::string my_string = "Hello World!";
	StringView sv(my_string);  

	std::cout << sv << '\n';
	std::cout << sv.empty() << '\n';
	std::cout << sv.size() << '\n';


	return 0;
}
