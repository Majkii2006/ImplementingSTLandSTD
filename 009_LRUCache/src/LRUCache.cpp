#include <iostream>
#include <unordered_map>

struct Node {
	int key { };
	int value { };
	Node* next { nullptr };
	Node* prev { nullptr };
	
	Node(int key, int value) : key(key), value(value) {
			
		std::cout << "Node Constructed" << std::endl;
	}; 
};

class LRUCache {
	private:
		std::unordered_map<int, Node*> map { };	
		int m_capacity { };
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
		LRUCache(int capacity) : m_capacity(capacity) {
			map.clear();
			head = new Node(-1, -1);
			tail = new Node(-1, -1);
			head->next = tail;
			tail->prev = head;
			std::cout << "Created instance of of LRU Cache of capacity: " << m_capacity << std::endl;
		} 

		~LRUCache() {
			Node* current = head;
			while (current != nullptr) {
				Node* nextNode = current->next;
				delete current;
				current = nextNode;
			}
		}

		int get(int key) {
			if (!(map.contains(key))) { 
				std::cout << "Cache Miss!" << std::endl;
				return -1; 
			} 
			
			Node* node = map[key];

			deleteNode(node);
			insertAfterHead(node);
			

			std::cout << "Value: " << node->value << std::endl;
			return node->value;
		}

		void put(int key, int value) {
			if (map.contains(key)) {
				Node* node = map[key];
				node->value = value;

				deleteNode(node);
				insertAfterHead(node);
			}
			else {
				if (map.size() == m_capacity) {
					Node* nodeToErase = tail->prev;
					map.erase(nodeToErase->key);
					deleteNode(nodeToErase);
					delete nodeToErase;
				}

				Node* node = new Node(key, value); 
				map[key] = node;		  
				insertAfterHead(node);


			}

		} 
};


int main() {

	LRUCache instance(4);
	instance.put(2, 6);
	instance.put(4, 7);
	instance.put(9, 2);
	instance.put(7, 4);
	instance.get(2);

	return 0;
}
