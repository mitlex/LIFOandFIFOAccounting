#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class Type>
class Stack
{
private:
    Type* Contents;
    int Stack_size;
    int Index_of_top;
public:
    Stack(int stack_size = 10);
    ~Stack();
    bool Empty() const;
    bool Full() const;
    bool Pop(Type& top_element);
    bool Push(const Type& new_element);

    //Stack class above this line provided as part of course content, as are the implementations of methods above
    //Functions below this line have been declared and implemented by me
    
    // Functions to manipulate Purchase Objects in Stack
    bool Avg_LIFO(const string& stock_name, int& num_shares, double& result);
    bool Delete(string stock_name);
    bool Get_Stock_Total_Shares(const string& stock_name, int& stock_total_shares);
    bool Sell(const string& stock_name, int& num_shares);

    //overload << to allow Stack objects to be output with cout
    template <class Type>
    friend ostream& operator<<(ostream& outs, const Stack<Type>& s);
};
#endif
