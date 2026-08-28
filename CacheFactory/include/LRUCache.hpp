#pragma once

#include <iostream>
#include <unordered_map>

#include "../include/Cache.hpp"

class LRUCache : public Cache {
	private:
		struct Node {
			int key { };
			int value { };
			Node* next { nullptr };
			Node* prev { nullptr };
			
			Node(int key, int value) : key(key), value(value) {
					
				std::cout << "Node Constructed" << std::endl;
			}; 
		};




		std::unordered_map<int, Node*> map { };	
		std::size_t m_capacity { };
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
			std::cout << "Created instance of LRUCache of capacity: " << m_capacity << std::endl;
			map.clear();
			head = new Node(-1, -1);
			tail = new Node(-1, -1);
			head->next = tail;
			tail->prev = head;
		} 

		~LRUCache() {
			std::cout << "Destructor LRUCache called" << std::endl;
			Node* current = head;
			while (current != nullptr) {
				Node* nextNode = current->next;
				delete current;
				current = nextNode;
			}
		}

		int get(int key) override {
			if (!(map.contains(key))) { 
				std::cout << "Cache Miss!" << std::endl;
				return -1; 
			} 
			
			Node* node = map[key];

			deleteNode(node);
			insertAfterHead(node);
			

			return node->value;
		}

		void put(int key, int value) override {
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


