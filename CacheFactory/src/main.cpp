
#include "../include/CacheCreator.hpp"

int main() {

	auto cache1 = CacheCreator::createCache(CacheType::LRU, 3);
	cache1->put(1, 2);
	std::cout << "LRUCache returned: " << cache1->get(1) << std::endl;
	std::cout << "==========" << std::endl;	

	auto cache2 = CacheCreator::createCache(CacheType::FIFO, 2);
	cache2->put(4, 1);
	std::cout << "FIFOCache returned: " << cache2->get(4) << std::endl;
	std::cout << "==========" << std::endl;	

	auto cache3 = CacheCreator::createCache(CacheType::LFU, 4);
	cache3->put(6, 6);
	std::cout << "LFUCache returned: " << cache2->get(4) << std::endl;
	std::cout << "==========" << std::endl;	

	auto cache4 = CacheCreator::createCache(CacheType::RR, 2);
	cache4->put(10, 10);
	std::cout << "RRCache returned: " << cache4->get(10) << std::endl; 
	std::cout << "==========" << std::endl;	

	return 0;

}
