#pragma once 

#include <algorithm>
#include <memory>

#include "Cache.hpp"

#include "../include/FIFOCache.hpp"
#include "../include/LFUCache.hpp"
#include "../include/LRUCache.hpp"

enum class CacheType {
	LRU,
	FIFO,
	LFU,
	RR
};


class CacheCreator {
	
	public:
		CacheCreator() = delete;
		CacheCreator(const CacheCreator& other) = delete;
		void operator=(const CacheCreator& other) = delete;
		static std::unique_ptr<Cache> createCache(CacheType type, int capacity) {
			if (type == CacheType::LRU) {
				return std::make_unique<LRUCache>(capacity);

			}
			else if (type == CacheType::FIFO) {
				return std::make_unique<FIFOCache>(capacity);
			}
			else if (type == CacheType::LFU) {
				return std::make_unique<LFUCache>(capacity);
			}
		}	


};
