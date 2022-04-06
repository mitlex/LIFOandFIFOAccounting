#ifndef STACKTEMPLATE_H
#define STACKTEMPLATE_H
#include "Stack.h"

// Constructor
template <class Type>
Stack<Type>::Stack(int stack_size) :
    Stack_size(stack_size),
    Contents(new Type[stack_size]),
    Index_of_top(-1)
{}

// Destructor
template <class Type>
Stack<Type>:: ~Stack()
{
    delete[] Contents;
}

// Tests
template <class Type>
bool Stack<Type>::Empty() const
{
    return (Index_of_top == -1) ? true : false;
}

template <class Type>
bool Stack<Type>::Full() const
{
    return (Index_of_top == Stack_size - 1) ? true : false;
}

// Push
template <class Type>
bool Stack<Type>::Push(const Type& new_element)
{
    if (Full()) {
        return false;
    }
    else {
        Index_of_top++;
        Contents[Index_of_top] = new_element;
        return true;
    }
}

// Pop
template <class Type>
bool Stack<Type>::Pop(Type& top_element)
{
    if (Empty()) {
        return false;
    }
    else {
        top_element = Contents[Index_of_top];
        Index_of_top--;
        return true;
    }
}

// calculates the total number of shares of a certain stock name in the stack
template<class Type>
bool Stack<Type>::Get_Stock_Total_Shares(const string& stock_name, int& stock_total_shares)
{
    for (int i = Index_of_top; i >= 0; i--)
    {
        if (Contents[i].Stock_name == stock_name)
        {
            stock_total_shares += Contents[i].Num_shares;
        }
    }
    return true;
}

// Avg_LIFO
// calculate average LIFO price of certain number of shares of given stock name
template <class Type>
bool Stack<Type>::Avg_LIFO(const string& stock_name, int& num_shares, double& lifo_result)
{
    int stock_total_shares = 0;

    //find total shares in stack of stock name passed in
    Get_Stock_Total_Shares(stock_name, stock_total_shares);

    //if stack empty, or user enters number of shares > amount of shares of that stock name on stack
    //or num shares entered is less than 0, or stock name not on stack
    if (Empty() || num_shares > stock_total_shares || num_shares <= 0) //2nd condition covers for stock name not being on stack at all
    {
        return false;
    }
    else //calculate average LIFO price
    {
        double numerator = 0;
        int total_num_shares = num_shares;

        for (int i = Index_of_top; i >= 0; i--)
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
        }
        lifo_result = numerator / total_num_shares;
    }
    return true;
}

// Delete
// removes first element in stack that matches a certain stock name
// maintain order of other elements in stack
template <class Type>
bool Stack<Type>::Delete(string stock_name)
{
    if (Empty())
    {
        return false;
    }
    else
    {
        Stack temp_stack(Stack_size); //make new stack, same size as original stack
        Type temp; //stores popped element from temp stack to then push back to original stack
        int counter = 0; //as soon as this > 0, we know we have deleted the element we want from the stack

        for (int i = Index_of_top; i >= 0; i--)
        {
            Pop(Contents[i]); //pop element from original stack
            if (Contents[i].Stock_name != stock_name || counter > 0) //counter > 0 allows us to keep remaining purchases of that stock name
            {
                temp_stack.Push(Contents[i]); //push element to temp stack
            }
            else if (Contents[i].Stock_name == stock_name)
            {
                counter++;
            }
        }
        for (int i = temp_stack.Index_of_top; i >= 0; i--)
        {
            temp_stack.Pop(temp); //pop element from temp stack
            Push(temp); //push element popped from temp_stack back to original stack
        }
    }
    return true;
}

template<class Type>
bool Stack<Type>::Sell(const string& stock_name, int& num_shares)
{
    int stock_total_shares = 0;

    //find total shares in stack of stock name passed in
    Get_Stock_Total_Shares(stock_name, stock_total_shares);

    //if stack empty, or user enters number of shares > amount of shares of that stock name on stack
    //or num shares entered is less than 0, or stock name not on stack
    if (Empty() || num_shares > stock_total_shares || num_shares <= 0) //2nd condition covers for stock name not being on stack at all
    {
        return false;
    }
    else //remove shares from stack working from the top
    {
        for (int i = Index_of_top; i >= 0; i--)
        {
            if (num_shares >= Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
            {
                num_shares -= Contents[i].Num_shares;
                Delete(stock_name);
            }
            else if (num_shares < Contents[i].Num_shares && Contents[i].Stock_name == stock_name)
            {
                Contents[i].Num_shares -= num_shares;
                break; //shares deleted, stop iterating through stack contents
            }
        }
    }
    return true;
}

// Overloaded << to allow for terminal output of Stack objects
// Prints all stack elements without alteration of stack
template <class Type>
ostream& operator<<(ostream& outs, const Stack<Type>& s)
{
    for (int i = s.Index_of_top; i >= 0; i--)
    {
        outs << s.Contents[i];
        if (i == s.Index_of_top) outs << " TOP";
        if (i == 0 && s.Index_of_top != 0) outs << " BOTTOM" << endl;
        outs << endl;
    }
    return outs;
}
#endif

