#include <iostream>

struct Node {

	int data { 0 };
	Node* next { nullptr };

	Node(int data) {
		this->data = data;
	}

};


class LinkedList {
	private:	
		Node* m_head { nullptr };

	public:
		LinkedList() {
			std::cout << "Linked List constructed\n";
		}

		~LinkedList() {
			std::cout << "LinkedList destructed\n";
		}
		
		void add_node(int data) {
			if (m_head == nullptr) {
				Node* node = new Node(data);
				std::cout << "First node address: " << node << std::endl;
				std::cout << "First node data: " << node->data << std::endl;
				m_head = node;
				std::cout << "m_head: " << m_head << std::endl;

			} else {
				m_head->next = new Node(data);
				std::cout << "Second node address: " << m_head->next << std::endl;
				std::cout << "Second node data: " << m_head->next->data << std::endl;
				std::cout << "m_head: " << m_head << std::endl;
			}
		} 

};


int main() {

	LinkedList ll;
	ll.add_node(10);
	ll.add_node(25);

	return 0;
}
