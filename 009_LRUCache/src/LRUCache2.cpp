#include <iostream>
#include <new>
#include <unordered_map>

struct Node {
	int m_key;
	int m_value;
	Node* next { nullptr };
	Node* prev { nullptr };

	Node(int key, int value) {
		m_key = key;
		m_value = value;
		std::cout << "Node Constructed" << std::endl;
	}
};

class LRUCache {
	private:
		int m_capacity { };
		Node* head { nullptr };
		Node* tail { nullptr };
		std::unordered_map<int, Node*> map { };

		void deleteNode(Node* node) {
			Node* node_after = node->next;
			Node* node_before = node->prev;
			node_after->prev = node_before;
			node_before->next = node_after;
			std::cout << "Deleting node: " << node << std::endl;
		}

		void insertNode(Node* node) {
			Node* currentAfterHead = head->next;	
			head->next = node;
			node->next = currentAfterHead;
			currentAfterHead->prev = node;
			node->prev = head;
			std::cout << "Inserting node: " << node << std::endl;
		}


	public:
		LRUCache(int capacity) : m_capacity(capacity) {
			map.clear();
			head = new Node(-1 , -1);	
			tail = new Node(-1 , -1);	
			head->next = tail;
			tail->prev = head;

		}


		int get(int key) {
			if ( map.contains(key) ) {
				Node* node = map[key];
				deleteNode(node); //helpers
				insertNode(node); //helpers
				
				return node->m_value;	

			} else {
				return -1;
			}
		}

		void put(int key, int value) {
			if ( map.contains(key) ) {
				Node* node = map[key];
				node->m_value = value;	
				deleteNode(node);
				insertNode(node);
			}
			else {
				if (static_cast<int>(map.size()) >= m_capacity) {
					std::cout << "Capacity overflow!" << std::endl;
					Node* nodeToErase = tail->prev;
					map.erase(nodeToErase->m_key);
					deleteNode(nodeToErase);

				}
				Node* node = new Node(key, value); 	
				map[key] = node;
				insertNode(node);
			}

						
		}


};

int main() {
	
	LRUCache instance(4);
	std::cout << instance.get(2) <<std::endl;
	instance.put(2, 6);
	instance.put(3, 8);
	instance.put(4, 10);
	instance.put(6, 12);
	std::cout << instance.get(2) << std::endl;
	instance.put(8, 25);
	std::cout << instance.get(4) << std::endl;
	std::cout << instance.get(6) << std::endl;


	return 0;
}
