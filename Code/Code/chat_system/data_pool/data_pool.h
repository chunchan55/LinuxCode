#define _DATA_POOL_H_
#define _DATA_POOL_H_

#include<iostream>
#include<vector>
#include<string>
class data_pool
{
	private:
		int cap;
		int size;
		std::vector<std::string> pool;
		int consumer_step;
		int product_step;
		sem_t blank;//创建信号量，格子和数据
		sem_t data;
	public:
		data_pool(int _cap);
		void getdata(std::string& outstring);
		void putdata(const std::string& instring);
		~data_pool();
}




