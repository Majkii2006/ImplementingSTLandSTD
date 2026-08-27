#include <array>
#include <cstddef>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>
#include <utility>

struct Element {

	Element(int key, int value) : m_key(key), m_value(value) {
		std::cout << "Element created" << std::endl;
	}

	~Element() {
		std::cout << "Element deleted" << std::endl;
	}

	int m_key { };
	int m_value { };
	
};

class RRCache {
	private:
		int pickRandomly() {
			//wylosowac randomowo indeks wzakresie od  elementu do m_capacity	
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distribution(0, static_cast<int>(m_capacity) - 1);
			return distribution(gen);
		}

	public:
		RRCache(int capacity) : m_capacity(capacity) {
			std::cout << "RRCache instance created" << std::endl;
		}
		
		~RRCache() {
			for (auto it { map.begin() }; it != map.end(); ++it) {
				if (it->second != nullptr) {
					delete it->second;
				}	
			}	
			std::cout << "RRCache instance deleted" << std::endl;
		}


		int get(int key) const {
			if (map.contains(key)) {
				Element* element = map.at(key);
				return element->m_value;
			}			
			return -1;
		}

		void put(int key, int value) {
			if (!(map.contains(key))) {
				if (map.size() < m_capacity) {
					Element* newElement = new Element(key, value);	
					map.emplace(key, newElement);
				} 
				else {
				
					int index_to_delete = pickRandomly();
					for ( auto it { map.begin() }; it != map.end(); ++it) {
						allKeys.push_back(it->first);
					}
					int picked_key = allKeys[index_to_delete];	
					allKeys.erase(allKeys.begin() + index_to_delete);		
				
					Element* toDelete = map.at(picked_key);
					std::cout << "Deleted element with key:" << toDelete->m_key << std::endl;
					delete toDelete;
					map.erase(picked_key);
					Element* newElement = new Element(key, value);
					map.emplace(key, newElement);
				}

			} else {
				Element* toModify = map.at(key);						
				toModify->m_value = value;
			} 
		}

	private:
		std::size_t m_capacity { };
		std::unordered_map<int, Element*> map { };
		std::random_device rd;
		std::vector<int> allKeys { };
};




int main() {
	RRCache instance(4);
	instance.put(1, 1);
	instance.put(2, 2);
	instance.put(3, 3);
	instance.put(4, 4);
	instance.put(5, 5);
	instance.put(6, 6);
	instance.put(7, 7);
	instance.put(8, 8);
	instance.put(8, 8);
	


	return 0;
}
