#include <algorithm>
#include <iostream>
#include <map>
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
	private:
		//funkcja pomocnicza do podgladniecia setu
		void printSetContents() const {
			for (auto& [freq, pointer] : freq_to_pointers) { 	//feature C++17
				std::cout << "Frequency of node: " << freq << std::endl;	
				std::cout << "Number of nodes with this frequency: "<< pointer.size() << std::endl;
			}	
			std::cout << "-------" << std::endl;
		}	


	public:
		LFUCache(int capacity) : m_capacity(capacity) {
			std::cout << "LFUCache instance Constructed" << std::endl;	
		}

		~LFUCache() {
			for ( auto it { key_to_node.begin() }; it != key_to_node.end(); ++it) {
				if (!(it->second == nullptr)) {
					delete it->second;
				}
			}
			std::cout << "LFUCache instance Destructed" << std::endl;
		}

		int get(int key) {
			if (key_to_node.contains(key)) {
				Node* takenNode = key_to_node[key];
				freq_to_pointers[takenNode->node_freq].erase(takenNode);
				takenNode->node_freq++;
				freq_to_pointers[takenNode->node_freq].insert(takenNode);	

				//std::cout << "Node Frequency was increased" << std::endl;
				printSetContents();
				return takenNode->m_value;
			}
			else {
				return -1;			
			}
			printSetContents();
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
				
				for (auto it { freq_to_pointers.begin() }; it != freq_to_pointers.end(); ) {
					if ( it->second.empty() ) {
						it = freq_to_pointers.erase(it);	
					} else {
						++it;
					}	
				}

			//std::cout << freq_to_pointers.size() << std::endl;	
						
			}			
			else {
				Node* createdNode = new Node(key, value);

				auto first_element_map = freq_to_pointers.begin();
						
				Node* toDelete = *first_element_map->second.begin();
				freq_to_pointers[toDelete->node_freq].erase(toDelete);
				key_to_node.erase(toDelete->m_key);
				delete toDelete;
				
				key_to_node.insert(std::make_pair(key, createdNode)); // potencjalnie wolne 
				freq_to_pointers[createdNode->node_freq].insert(createdNode); //operator [] automatycznie utworzy ten klucz 
				
				for (auto it { freq_to_pointers.begin() }; it != freq_to_pointers.end();) {
					if ( it->second.empty() ) {
						it = freq_to_pointers.erase(it);	
					} else {
						++it;
					}	
				}							      

			}

			printSetContents();
		}



	private:
		std::unordered_map<int, Node*> key_to_node { };
		std::map<int, std::unordered_set<Node*>> freq_to_pointers { };
		std::size_t m_capacity {};
		int min_freq {};

};




int main() {
	LFUCache instance(2);	
	instance.put(2, 3);
	instance.get(2);
	instance.put(1,4);
	instance.get(2);
	instance.put(3,10);
	



	return 0;
}
