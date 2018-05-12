#include"data_pool.h"

data_pool::data_pool(int _cat):
	cat(_cat),
	size(0),
	pool(_cat)
{
	product_step = 0;
	consumer_step = 0;
	sem_init(&blank,0,cat);
	sem_init(&data,0,0);
}
void getdata(std::string& outstring)//xiao fei 
{
//	int index = 0;
	sem_wait(&data);
	outstring = pool[consumer_step];
	consumer_step++;
	consumer_step %= cap;
	size--;
//	size %= cap;
	sem_post(&blank);
}
void putdata(const std::string& instring)//shangchan 
{	
//	int index = 0;
	sem_wait(&blank);
	pool[product_step] = instring;
	product_step++;
	consumer_step %= cap;
	size++;
//	size %= cap;
	sem_post(&data);
}
~data_pool()
{
	cap = 0;
	size = 0;
	produt_step = 0;
	consumer_step = 0;
	sem_destroy(&blank);
	sem_destroy(&data);
}
