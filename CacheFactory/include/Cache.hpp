#pragma once

class Cache {

	public:
		
		virtual ~Cache() = default;

		virtual int get(int key) = 0;
		virtual void put(int key, int value) = 0;
};
