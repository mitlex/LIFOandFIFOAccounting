#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

template <class Type>
class Queue
{
private:
	Type* Contents;
	int Queue_size;
	int Front, Back;
public:
	Queue(int queue_size = 10);
	~Queue();
	bool Empty() const;
	bool Full() const;
	bool Remove(Type& front_element);
	bool Add(const Type& new_element);

	//Stack class above this line provided as part of course content, as are the implementations of methods above
	//Functions below this line have been declared and implemented by me

	// Functions to manipulate Purchase Objects in Queue
	bool Accumulate_Numerator_Decrement_Num_Shares(const string& stock_name, double& numerator, int& num_shares, int& i);
	bool Avg_FIFO(const string& stock_name, int& num_shares, double& fifo_result);
	bool Delete(string stock_name);
	bool Normal_Queue_Delete(const string& stock_name, int& num_shares);
	bool Get_Stock_Total_Shares(const string& stock_name, int& stock_total_shares);
	bool Sell(const string& stock_name, int& num_shares);

	// Functions to get front and back (for testing purposes)
	int Get_Front();
	int Get_Back();

	//overload << to allow Queue objects to be output with cout
	template <class Type>
	friend ostream& operator<<(ostream& outs, const Queue<Type>& q);
};
#endif
