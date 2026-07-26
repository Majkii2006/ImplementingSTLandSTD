#include <iostream>

struct Node {
	

	int m_data { 0 };
	Node* m_next{ nullptr };

};

struct LinkedList {

	Node* m_head { nullptr };

	LinkedList() {
		Node* head_first = new Node();	
		std::cout << "Head First Address: " << head_first << std::endl;
		std::cout << "Head First Data: " << head_first->m_data << std::endl;
		m_head = head_first;
		head_first->m_data = 0;
		
	};


		

};

int main() {
	
	LinkedList ll;

	return 0;
}
