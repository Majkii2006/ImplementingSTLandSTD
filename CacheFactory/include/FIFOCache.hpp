#pragma once

#include <cstdint>
#include <sys/types.h>

#include <cstddef>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "../include/Cache.hpp"

struct Element {
	int m_key;
	int m_value;

	Element(int key, int value) : m_key(key), m_value(value) {
		std::cout << "Element Constructed" << std::endl;
	}
};


class FIFOCache : public Cache{

	private:
		std::unordered_map<int, Element*> map {};
		std::queue<Element*> queue;
		u_int64_t m_capacity {};

	public:
		FIFOCache(int capacity) : m_capacity(capacity) {
			std::cout << "FIFO Cache has been created" << std::endl;
			if ( queue.empty() ) {
				int8_t m_dummy = -1;
				for (u_int64_t i {}; i < m_capacity; ++i) {
					Element* element = new Element(m_dummy, m_dummy);
					map.insert({m_dummy, element});
					queue.push(element);
					m_dummy--;
				}
			}
		}
		~FIFOCache() {
			std::cout << "Destructor FIFO Cache called" << std::endl;
			
			for (auto it = map.begin(); it != map.end(); ++it) {
				Element* toDelete = it->second;	
				delete toDelete;
			}	

			map.clear();

			for (u_int64_t i {}; i < m_capacity; ++i){
				queue.pop();
			}



		}

		std::size_t get_queue_size() const {
			return queue.size();
		}

		void put(int key, int value) override {
			if (map.contains(key)) {
				Element* element = map[key];	
				element->m_value = value;
				return;
			}
			else {
				if (queue.size() >= m_capacity) {
					Element* newElement = new Element(key, value);		
					Element* toDelete = queue.front();
					int key_to_erase = queue.front()->m_key;
					queue.pop();
					queue.push(newElement);
					delete toDelete;
					map.insert({key, newElement});
					map.erase(key_to_erase);
					std::cout << "New Element was pushed to the queue";
					std::cout << "\nThe overloaded one was deleted!" << std::endl;
					return;
				}
				else {
					Element* newElement = new Element(key, value);
					queue.push(newElement);
					map.insert({key, newElement});
					std::cout << "New Element was pushed to the queue" << std::endl;
					std::cout << "But there was a space so nothing deleted" << "\n";
					return;
				}
			}

		}

		int get(int key) override {
			if (!(map.contains(key))) {
				std::cout << "Cache miss!" << std::endl;
				return -1;	
			}
			else {
				Element* element = map[key];
				return element->m_value;
			}
		}
};


