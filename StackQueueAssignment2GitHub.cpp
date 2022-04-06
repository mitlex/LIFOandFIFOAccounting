// AUTHOR: mitlex
// TITLE: Assignment 1 - Stacks & Queues
// DATE: 1st February 2022
// VERSION: v1
// DESCRIPTION: 
// 
// Allows a user to input stock purchases made up of a stock name, price and number of shares purchased
// The purchases are stored in a Queue for FIFO accounting and a Stack for LIFO accounting
// The user can query a stock to see its cost according to the LIFO and FIFO accounting methods
// The user can also sell shares they have purchased that are stored on the Stack and Queue (i.e. remove them from the Stack and Queue)

#include <iostream>
#include <string> 
#include "Purchase.h"
#include "Stacktemplate.h"
#include "Queuetemplate.h"
using namespace std;

string user_input()
{
    string input;
    getline(cin, input);
    while (input == "")
        getline(cin, input);
    return input;
}

//prevent menu output to allow user to see results
//credit: https://stackoverflow.com/questions/37234253/why-is-this-press-enter-to-continue-code-in-c-not-working
void press_enter_to_continue()
{
    cout << "Press enter to continue to the menu" << endl;
    cin.ignore();
}

// validates that a string input contains only digits
bool validate_whole_number_input(string input)
{
    for (int i = 0; i < input.length(); i++) // iterate over string
    {
        if (!isdigit(input[i])) return false; // if any char is not digit, return false
    }
    return true;
}

// prompts user to input a whole number
int get_whole_number()
{
    int whole_number;

    string input = user_input();
    while (!validate_whole_number_input(input))
    {
        cout << "invalid input, only positive whole numbers accepted, try again: ";
        input = user_input();
    }
    whole_number = stoi(input);
    return whole_number;
}

// validates that a string input is a number with 2 decimal places
bool validate_two_decimal_places(string input)
{
    char decimal_point = '.';

    if (!isdigit(input[0]))
    {
        return false; //first char must be a digit
    }
    else
    {
        for (int i = 1; i < input.length(); i++) // iterate over string from second char
        {
            if (!isdigit(input[i]) && input[i] != decimal_point) //if char is not a digit or decimal point
            {
                return false;
            }
            else if (input[i] == decimal_point) //decimal point found
            {
                int j = i + 1;
                for (; j < input.length(); j++) //iterate over remaining chars
                {
                    if (j > i + 2) //input has more than 2 decimal places
                    {
                        return false;
                    }
                    else if (!isdigit(input[j])) //if char is not a digit
                    {
                        return false;
                    }
                }
                if (j == i + 3) //prevent 1 decimal place inputs
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

// prompts user to enter share price
// returns share price
double get_share_price()
{
    double share_price;
    string input = user_input();
    while (!validate_two_decimal_places(input))
    {
        cout << "invalid input, only positive values with 2 decimal places accepted, try again: ";
        input = user_input();
    }
    share_price = stod(input);
    return share_price;
}

//prompts user to enter attribute values for a Purchase object
//adds the newly created Purchase object to the Stack and Queue
bool enter_purchase(Stack<Purchase>& stack, Queue<Purchase>& queue)
{
    char add_another;

    do
    {
        if (stack.Full() || queue.Full()) //can't add a purchase to full Stack or Queue
        {
            cout << "The Stack or Queue is full, please sell some shares" << endl << endl;
            cout << "Press enter to continue to the menu" << endl;
            cin.ignore();
            cin.ignore();
            return false;
        }
        else
        {
            //prompt user for purchase details
            Purchase temp;
            cout << "Please enter the name of the stock: ";
            cin >> temp.Stock_name;

            cout << "Please enter the number of shares purchased (positive whole numbers only): ";
            temp.Num_shares = get_whole_number();

            cout << "Please enter the share price: ";
            temp.Share_price = get_share_price();
            cout << endl;

            //add Purchase to Stack and Queue
            stack.Push(temp);
            queue.Add(temp);

            //prompt for another purchase
            cout << "Would you like to enter another purchase? Enter 'Y' or 'y' if so: ";
            cin >> add_another;
            cout << endl;
        }
    } while (add_another == 'Y' || add_another == 'y');
    return true;
}

// generic error message for failed FIFO or LIFO calculation or failed sales - str will be "stack" or "queue"
void error_message(string str)
{
    cout << endl << "***" << str << " error has occurred for one of the following reasons:***" << endl << endl;

    cout << "1. stock name entered is not in the " << str << endl;
    cout << "2. " << str << " is empty" << endl;
    cout << "3. number of shares entered is equal to 0" << endl;
    cout << "4. number of shares entered is greater than the total number of shares in the " << str << " of the entered stock name" << endl << endl;

    cout << "you can print the contents of the " << str << " by selecting option 4 from the options menu" << endl;
}

//prompts user for stock name and number of shares in question
//retrieves and displays results of LIFO and FIFO calculations
void show_LIFO_and_FIFO(Stack<Purchase>& stack, Queue<Purchase>& queue)
{
    //get stock name and number of shares
    cout << "Please enter the stock name: ";
    string stock_name = user_input();
    cout << "Please enter the number of shares in question: ";
    int num_shares_lifo = get_whole_number();

    int num_shares_fifo = num_shares_lifo; //need to store this seperately because num_shares_LIFO is being passed by reference to Avg_LIFO and will change

    double lifo_result, fifo_result;
    string stack_str = "stack", queue_str = "queue"; //for error message

    //calculate and output average LIFO price
    if (stack.Avg_LIFO(stock_name, num_shares_lifo, lifo_result))
    {
        cout << endl << "The average LIFO price of share " << stock_name << " is " << lifo_result << endl;
    }
    else
    {
        error_message(stack_str);
    }
    //calculate and output average FIFO price
    if (queue.Avg_FIFO(stock_name, num_shares_fifo, fifo_result))
    {
        cout << "The average FIFO price of share " << stock_name << " is " << fifo_result << endl << endl;
    }
    else
    {
        error_message(queue_str);
        cout << endl;
    }
}

//prompts user for stock name and number of shares in question
//removes entered number of shares of entered stock name from the stack and queue
void sell_shares(Stack<Purchase>& stack, Queue<Purchase>& queue)
{
    //get stock name and number of shares
    cout << "Please enter the stock name: ";
    string stock_name = user_input();
    cout << "Please enter the number of shares in question: ";
    int num_shares_stack = get_whole_number();

    int num_shares = num_shares_stack; //for successful sale print statements

    int num_shares_queue = num_shares_stack; //need to store this seperately because num_shares_stack is being passed by reference to Sell and will change

    string stack_str = "stack", queue_str = "queue"; //for error message

    //remove shares from stack
    if (stack.Sell(stock_name, num_shares_stack))
    {
        cout << endl << num_shares << " shares successfully sold from stack" << endl;
    }
    else
    {
        error_message(stack_str);
    }
    //remove shares from queue
    if (queue.Sell(stock_name, num_shares_queue))
    {
        cout << num_shares << " shares successfully sold from queue" << endl << endl;
    }
    else
    {
        error_message(queue_str);
        cout << endl;
    }
}

void display_menu()
{
    cout << "Here are your options: " << endl << endl;

    cout << "Press 1 to enter a purchase" << endl;
    cout << "Press 2 to find the LIFO & FIFO price" << endl;
    cout << "Press 3 to make a sale" << endl;
    cout << "Press 4 to print your Stack & Queue content" << endl;
    cout << "Press 5 to exit the program" << endl << endl;
}

void run_menu(Stack<Purchase>& stack, Queue<Purchase>& queue)
{
    //display menu
    display_menu();

    //perform queries
    bool anotherQuery = true;
    char answer;
    do
    {
        cout << "Please enter 1, 2, 3, 4 or 5 (the first number you enter will be input): ";
        answer = user_input()[0];
        cout << endl;
        switch (answer)
        {
        case '1':
            enter_purchase(stack, queue);
            display_menu();
            break;
        case '2':
            show_LIFO_and_FIFO(stack, queue);
            press_enter_to_continue();
            display_menu();
            break;
        case '3':
            sell_shares(stack, queue);
            press_enter_to_continue();
            display_menu();
            break;
        case '4':
            cout << "Stack contents: " << endl << stack;
            cout << "Queue contents: " << endl << queue;
            press_enter_to_continue();
            display_menu();
            break;
        case '5':
            cout << "Thank you for using this program! Goodbye!" << endl;
            anotherQuery = false;
            break;
        default:
            cout << "Your choice was invalid, please try again. " << endl << endl;
        }
    } while (anotherQuery);
}

void welcome()
{
    cout << "***************************************" << endl;
    cout << "***WELCOME TO LIFO & FIFO ACCOUNTING***" << endl;
    cout << "***************************************" << endl << endl;
}

int main()
{
    welcome(); //program welcome message.

    //prompt user to input stack and queue size
    cout << "Please enter the size of the queue and stack (maximum number of purchases that can be stored): ";
    int max_num_purchases = get_whole_number();
    cout << endl;

    //create stack and queue
    Stack<Purchase> stack(max_num_purchases);
    Queue<Purchase> queue(max_num_purchases);

    //set output precision to 2dp
    cout.setf(ios::fixed);
    cout.precision(2);

    run_menu(stack, queue); //run options menu

    return 0;
}