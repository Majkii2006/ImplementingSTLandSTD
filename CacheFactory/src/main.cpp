#include <iostream>
#include <memory>

#include "../include/LRUCache.hpp"

enum class CacheType {
	LRU,
	FIFO,
	LFU,
	RR
};

class Cache {

	

};



class CacheFactory : public Cache {
	public:
		static std::unique_ptr<Cache> create(CacheType type, int capacity) {

		}				


};


int main() {




}
