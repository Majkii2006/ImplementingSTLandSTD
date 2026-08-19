#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

struct Node {
	
	int m_key {};
	int m_value {};
	int node_freq {};
	Node(int key, int value) : m_key(key), m_value(value) {
		node_freq = 1;
		std::cout << "Node Constructed" << std::endl;
	}
	
	~Node() {
		std::cout << "Node Destructed" << std::endl;
	}

};

// LFU Policy dziala nastepujaco:
// zaczynamy z frequency 1 dla kazdego node'a
// gdy mamy get ->> czestotliwosc wzrasta o jeden
// gdy potrzeba wymienic bo mamy full capacity to usuwamy ten z najmniejszym freq
// aktualizacja danego klucza to kontunuacja 

class LFUCache {

	public:
		LFUCache(int capacity) : m_capacity(capacity) {
			std::cout << "LFUCache instance Constructed" << std::endl;	
		}

		~LFUCache() {
			std::cout << "LFUCache instance Destructed" << std::endl;
		}

		int get(int key) {
			if (key_to_node.contains(key)) {
				Node* takenNode = key_to_node[key];
				takenNode->node_freq++;
				//std::cout << "Node Frequency was increased" << std::endl;
				return takenNode->m_value;
			}
			return -1;
		}
	
 		void put(int key, int value) {
 			if (key_to_node.contains(key)) {
 				Node* node = key_to_node[key];
				node->m_value = value;	
				return;
 			}
			if (key_to_node.size() < m_capacity) {
				Node* createdNode = new Node(key, value);	
				key_to_node.insert(std::make_pair(key, createdNode)); // potencjalnie wolne 
				//std::cout << key_to_node.size();
				freq_to_pointers[createdNode->node_freq].insert(createdNode); //operator [] automatycznie utworzy ten klucz 
											      //jesli go nie ma 
				
				
			}			
		}



	private:
		std::unordered_map<int, Node*> key_to_node { };
		std::unordered_map<int, std::unordered_set<Node*>> freq_to_pointers { };
		std::size_t m_capacity {};
		int min_freq {};

};




int main() {
	LFUCache instance(10);	
	instance.put(2, 3);
	std::cout << instance.get(2) << std::endl;



	return 0;
}
