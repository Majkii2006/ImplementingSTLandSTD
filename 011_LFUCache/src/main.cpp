
#include <iostream>
#include <unordered_map>
#include <vector>

struct Node {
	int m_key {};
	int m_value {};
	size_t used_counter {};
	Node* next { nullptr };
	Node* prev { nullptr };

	Node(int key, int value) : m_key(key), m_value(value) {
		std::cout << "Element constructed" << std::endl;
	}
};


class LFUCache {
	private:
		u_int64_t m_capacity {};
		std::unordered_map<int, Node*> map;
		Node* head { nullptr };
		Node* tail { nullptr };

		void insertAfterHead(Node* node) {
			Node* curAfterHead = head->next;	
			head->next = node;
			node->next = curAfterHead;
			curAfterHead->prev = node;
			node->prev = head;
			
		}

		void deleteNode(Node* node) {
			//usuwanie noda'e z DLL
			Node* prevNode = node->prev;
			Node* afterNode = node->next;
			
			prevNode->next = afterNode;
			afterNode->prev = prevNode;
		}		


	public:
		LFUCache(int capacity) {
			map.clear();
			head = new Node(-1, -1);
			tail = new Node(-1, -1);
			head->next = tail;
			tail->prev = head;
			m_capacity = capacity;	
			std::cout << "LFU Cache constructed" << std::endl;
		} 

		~LFUCache() {	
			Node* current = head; 
			while (current != nullptr) {
				Node* nextNode = current->next;	
				delete current;
				current = nextNode;
			}
		}

		void put(int key, int value) {

		}

		int get(int key) {
			if (!(map.contains(key))) {
				std::cout << "Cache Miss!" << std::endl;				
				return -1;
			}

			Node* node = map[key];
			node->used_counter += 1;
			

				

		}
};


int main() {
	

	return 0;
}
