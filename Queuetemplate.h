#pragma once
#ifndef QUEUETEMPLATE_H
#define QUEUETEMPLATE_H
#include "Queue.h"

// Constructor
template <class Type>
Queue<Type>::Queue(int queue_size) :
	Queue_size(queue_size),
	Contents(new Type[queue_size + 1]),
	Front(0), Back(0)
{}

// Destructor
template <class Type>
Queue<Type>::~Queue()
{
	delete[] Contents;
}

// Check if queue is empty
template <class Type>
bool Queue<Type>::Empty() const
{
	return (Front == Back) ? true : false;
}

// Check if queue is full
template <class Type>
bool Queue<Type>::Full() const
{
	return ((1 + Back) % (Queue_size + 1) == Front) ? true : false;
}

// Remove element from front of queue
template <class Type>
bool Queue<Type>::Remove(Type& front_element)
{
	if (Empty())
		return false;
	else
	{
		front_element = Contents[Front];
		Front = (Front + 1) % (Queue_size + 1);
		return true;
	}
}

// Add element to back of queue
template <class Type>
bool Queue<Type>::Add(const Type& new_element)
{
	if (Full())
		return false;
	else
	{
		Contents[Back] = new_element;
		Back = (Back + 1) % (Queue_size + 1);
		return true;
	}
}

// calculates the total number of shares of a certain stock name in the queue
template<class Type>
bool Queue<Type>::Get_Stock_Total_Shares(const string& stock_name, int& stock_total_shares)
{
	if (Front < Back) //normal queue
	{
		for (int i = Front; i < Back; i++)
		{
			if (Contents[i].Stock_name == stock_name)
			{
				stock_total_shares += Contents[i].Num_shares;
			}
		}
	}
	else //flipped queue
	{
		for (int i = Front; i <= Queue_size; i++)
		{
			if (Contents[i].Stock_name == stock_name)
			{
				stock_total_shares += Contents[i].Num_shares;
			}
		} //back is > 0 and < front
		for (int i = 0; i < Back; i++) //never loops if back == 0
		{
			if (Contents[i].Stock_name == stock_name)
			{
				stock_total_shares += Contents[i].Num_shares;
			}
		}
	} return true;
}

// accumulates the numerator for Avg_FIFO calculation and decrements num_shares input by user
// main purpose of this function is to minimise code duplication
template<class Type>
bool Queue<Type>::Accumulate_Numerator_Decrement_Num_Shares(const string& stock_name, double& numerator, int& num_shares, int& i)
{
	if (num_shares > Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
	{
		numerator += (Contents[i].Num_shares * Contents[i].Share_price);
		num_shares -= Contents[i].Num_shares;
	}
	else if (num_shares <= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
	{
		numerator += (Contents[i].Share_price * num_shares); //multiply remaining shares
		num_shares = 0;
	}
	return true;
}

// Avg_FIFO
// calculate average FIFO price of certain number of shares of given stock name
template<class Type>
bool Queue<Type>::Avg_FIFO(const string& stock_name, int& num_shares, double& fifo_result)
{
	if (Empty())
	{
		return false;
	}
	else if (Front < Back) //normal queue (front index < back index)
	{
		//find total shares in queue of stock name passed in
		int stock_total_shares = 0;
		Get_Stock_Total_Shares(stock_name, stock_total_shares);

		//1st condition covers for stock name not being in queue at all
		if (num_shares > stock_total_shares || num_shares <= 0)
		{
			return false;
		}
		else //calculate average FIFO price
		{
			double numerator = 0;
			int total_num_shares = num_shares;

			for (int i = Front; i < Back; i++)
			{
				Accumulate_Numerator_Decrement_Num_Shares(stock_name, numerator, num_shares, i);
			}
			fifo_result = numerator / total_num_shares;
		}
	}
	else //flipped queue (back index < front index)
	{
		//find total shares in queue of stock name passed in
		int stock_total_shares = 0;
		Get_Stock_Total_Shares(stock_name, stock_total_shares);

		//1st condition covers for stock name not being in queue at all
		if (num_shares > stock_total_shares || num_shares <= 0)
		{
			return false;
		}
		else //calculate average FIFO price
		{
			double numerator = 0;
			int total_num_shares = num_shares;

			for (int i = Front; i <= Queue_size; i++)
			{
				Accumulate_Numerator_Decrement_Num_Shares(stock_name, numerator, num_shares, i);
			}
			for (int i = 0; i < Back; i++) //never loops if back == 0
			{
				Accumulate_Numerator_Decrement_Num_Shares(stock_name, numerator, num_shares, i);
			}
			fifo_result = numerator / total_num_shares;
		}
	}
	return true;
}

// Delete
// removes first element in queue that matches a certain stock name
// maintain order of other elements in queue
template<class Type>
bool Queue<Type>::Delete(string stock_name)
{
	if (Empty())
	{
		return false;
	}
	else if (Front < Back) //normal queue (front index < back index)
	{
		Queue temp_queue(Queue_size); //make new queue, same size as original queue
		Type temp; //stores removed element from temp queue to then add back to original queue
		int counter = 0; //as soon as this > 0, we know we have deleted the element we want from the queue

		for (int i = Front; i < Back; i++)
		{
			Remove(Contents[i]); //remove element from original queue
			if (Contents[i].Stock_name != stock_name || counter > 0) //counter > 0 allows us keep remaining purchases of that stock name
			{
				temp_queue.Add(Contents[i]); //add element to temp queue
			}
			else if (Contents[i].Stock_name == stock_name)
			{
				counter++;
			}
		}
		Front = 0, Back = 0; //queue is empty, reset front and back to 0 to avoid flipped queue when adding back elements in loop below
		for (int i = temp_queue.Front; i < temp_queue.Back; i++)
		{
			temp_queue.Remove(temp); //remove element from temp queue
			Add(temp); //Add element removed from temp_queue back to original queue
		}
	}
	else //flipped queue (back index < front index)
	{
		//this could probably be refactored to minimise duplication
		Queue temp_queue(Queue_size); //make new queue, same size as original queue
		Type temp; //stores removed element from temp queue to then add back to original queue
		int counter = 0; //as soon as this > 0, we know we have deleted the element we want from the queue

		for (int i = Front; i <= Queue_size; i++)
		{
			Remove(Contents[i]); //remove element from original queue
			if (Contents[i].Stock_name != stock_name || counter > 0) //counter > 0 allows us keep remaining purchases of that stock name
			{
				temp_queue.Add(Contents[i]); //add element to temp queue
			}
			else if (Contents[i].Stock_name == stock_name)
			{
				counter++;
			}
		}
		for (int i = 0; i < Back; i++) //never loops if back == 0
		{
			Remove(Contents[i]); //remove element from original queue
			if (Contents[i].Stock_name != stock_name || counter > 0) //counter > 0 allows us keep remaining purchases of that stock name
			{
				temp_queue.Add(Contents[i]); //add element to temp queue
			}
			else if (Contents[i].Stock_name == stock_name)
			{
				counter++;
			}
		}
		Front = 0, Back = 0; //queue is empty, reset front and back to 0 to avoid flipped queue when adding back elements in loop below
		for (int i = temp_queue.Front; i < temp_queue.Back; i++)
		{
			temp_queue.Remove(temp); //remove element from temp queue
			Add(temp); //Add element removed from temp_queue back to original queue
		}
	}
	return true;
}

// Delete process for a normal queue i.e. queue Front < queue Back
template<class Type>
bool Queue<Type>::Normal_Queue_Delete(const string& stock_name, int& num_shares)
{
	for (int i = Front; i < Back; i++)
	{
		if (num_shares >= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
		{
			while (num_shares >= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
			{
				num_shares -= Contents[i].Num_shares;
				Delete(stock_name);
			}
			if (num_shares < Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
			{
				Contents[i].Num_shares -= num_shares;
				break; //shares deleted, stop iterating through queue contents
			}
		}
		else if (num_shares < Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
		{
			Contents[i].Num_shares -= num_shares;
			break; //shares deleted, stop iterating through queue contents
		}
	}
	return true;
}

// reduces number of shares of a certain stock name by a number passed as an argument
// deletes elements from the queue where necessary
template<class Type>
bool Queue<Type>::Sell(const string& stock_name, int& num_shares)
{
	if (Empty())
	{
		return false;
	}
	else if (Front < Back) //normal queue (front index < back index)
	{
		//find total shares in queue of stock name passed in
		int stock_total_shares = 0;
		Get_Stock_Total_Shares(stock_name, stock_total_shares);

		//1st condition covers for stock name not being in queue at all
		if (num_shares > stock_total_shares || num_shares <= 0)
		{
			return false;
		}
		else
		{
			Normal_Queue_Delete(stock_name, num_shares);
			return true;
		}
	}
	else //flipped queue (back index < front index)
	{
		//find total shares in queue of stock name passed in
		int stock_total_shares = 0;
		Get_Stock_Total_Shares(stock_name, stock_total_shares);

		//1st condition covers for stock name not being in queue at all
		if (num_shares > stock_total_shares || num_shares <= 0)
		{
			return false;
		}
		else
		{
			int counter = 0;
			for (int i = Front; i <= Queue_size; i++) //find stock name between front and queue size
			{
				if (num_shares >= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
				{
					num_shares -= Contents[i].Num_shares;
					Delete(stock_name);
					Normal_Queue_Delete(stock_name, num_shares); //queue is now normal i.e. front < back
					counter++;
					break; //shares deleted, stop iterating through queue contents
				}
				else if (num_shares < Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
				{
					Contents[i].Num_shares -= num_shares;
					counter++;
					break; //shares deleted, stop iterating through queue contents
				}
			}
			//purchase to be deleted or have num_shares reduced
			//to 0 was not found between front & queue size
			if (counter == 0)
			{
				for (int i = 0; i < Back; i++) //never loops if back == 0
				{
					if (num_shares >= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
					{
						num_shares -= Contents[i].Num_shares;
						Delete(stock_name);
						Normal_Queue_Delete(stock_name, num_shares); //queue is now normal i.e. front < back
						break; //shares deleted, stop iterating through queue contents
					}
					else if (num_shares < Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
					{
						Contents[i].Num_shares -= num_shares;
						break; //shares deleted, stop iterating through queue contents
					}
				}
			}
		}
		return true;
	}
}

template<class Type>
int Queue<Type>::Get_Front()
{
	return Front;
}

template<class Type>
int Queue<Type>::Get_Back()
{
	return Back;
}

// Overloaded << to allow for terminal output of Queue objects
// Prints all Queue elements without alteration of Queue
template <class Type>
ostream& operator<<(ostream& outs, const Queue<Type>& q)
{
	if (q.Front < q.Back) //normal queue (front index < back index)
	{
		for (int i = q.Front; i < q.Back; i++)
		{
			outs << q.Contents[i];
			if (i == q.Front) outs << " FRONT";
			if (i == (q.Back - 1)) outs << " BACK" << endl;
			outs << endl;
		}
	}
	else if (q.Front > q.Back) //flipped queue (front index > back index)
	{
		for (int i = q.Front; i <= q.Queue_size; i++)
		{
			outs << q.Contents[i];
			if (i == q.Front) outs << " FRONT";
			if (i == q.Queue_size && q.Back == 0) outs << " BACK" << endl;
			outs << endl;
		} //back is > 0 and < front
		for (int i = 0; i < q.Back; i++) //never loops if back == 0
		{
			outs << q.Contents[i];
			if (i == (q.Back - 1)) outs << " BACK" << endl;
			outs << endl;
		}
	}
	return outs;
}
#endif

