This assignment was created as part of the coursework for the following module:
https://www.dundee.ac.uk/module/ac52002

Developed a C++ program using the Stack and Queue data structures with the following features:

	• Allows a user to input a number of share purchases made up of a stock name, share price and number of shares purchased
	• The user can query a certain number of shares of a stock they have purchased to determine its cost according to the LIFO and FIFO accounting methods
	• The user can also sell shares they have purchased

These options are faciliated to the user through a menu during program runtime. 

The Queue is used for implementation of the FIFO accounting method, whilst the Stack is used for implementation of the LIFO accounting method. Both the Stack and Queue are templated to allow for storage of all data types (although only "Purchase" objects are stored in this program).

The following example shows the program in action, where three purchases have been entered. I have entered the following purchases of "HJBNX" shares:

	• 150 shares at 50.67
	• 225 shares at 55.31
	• 300 shares at 49.22

To determine how much 450 shares of "HJBNX" cost based on LIFO accounting, the following calculation is done:

((300*49.22)+(150*55.31))/450 = 51.25

To determine how much 450 shares of "HJBNX" cost based on FIFO accounting, the following calculation is done:

((150*50.67)+(225*55.31)+(75*49.22))/450 = 52.75

![image](https://user-images.githubusercontent.com/94235400/162039587-35e15d18-c1c5-41e2-a890-f5f4204024db.png)

I can print the current Stack and Queue contents, sell 450 shares of "HJBNX" (remove 450 shares of "HJBNX" from the Stack and Queue), then re-print the Stack and Queue contents, as shown below:![image](https://user-images.githubusercontent.com/94235400/162039609-203fa5e7-076c-4419-bf98-ac7da76c6100.png)

![image](https://user-images.githubusercontent.com/94235400/162039721-e4b403f4-d8cc-46d3-9e89-d275a562e5dc.png)
![image](https://user-images.githubusercontent.com/94235400/162039942-35b3513c-d9ce-4a45-a156-13004453613e.png)


