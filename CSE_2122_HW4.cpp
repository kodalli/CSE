/*
File name: CSE_2122_HW04.cpp
Created by: Surya Kodali
Created on: 3/3/2020
Synopsis: This program prompts user input of a postfix notation math operation
that would like to be solved and then returns the solution. Only single digit 
positive integer operations with +,-,*,/ are allowed.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

const char SENTINEL = ';';

struct Node
{
	int data;
	Node *link;
};

// precondition: c is initialized
// postcondition: returns true if c is '+', '-', '*' or '/'
bool isOperator(char c);

// precondition: o1 and o2 are initialized and op is an operator
// postcondition: returns op(o1, o2), e.g. if op is '-' then returns o1-o2
int calculate(int o1, int o2, char op);

// precondition: c is a digit
// postcondition: returns the integer value of c
int charToInt(char c);

class Stack
{

public:
	// default constructor
	// initializes the stack to an empty stack
	Stack();

	// default destructor
	// frees the memory used by dynamic node objects in the stack
	~Stack();

	// this is a const function, meaning it cannot change any of the member variables
	// returns true if the stack is empty, false otherwise
	bool isEmpty() const;

	// this is a const function, meaning it cannot change any of the member variables
	// returns the value at the top of stack, does not modify the stack, does not check if the stack is empty or not
	int top() const;

	// adds data to the top of stack
	void push(int data);

	// removes the top value of stack, does not return it, does nothing if the stack is empty
	void pop();

private:
	Node *listHead; // pointer to the head of a linked list
};

int main()
{
	char in;
	Stack operandStack;

	cout << "Enter a postfix expression (ending with " << SENTINEL << " and press Enter):" << endl;
	cin >> in;
	while (in != SENTINEL)
	{
		if (isOperator(in))
		{
			// pop two numbers from stack
			int n1, n2;
			if (operandStack.isEmpty())
			{
				// print error message
				cout << "Not enough operands entered for operator: " << in << endl;
				exit(1); // end the program
			}
			n2 = operandStack.top();
			operandStack.pop();
			if (operandStack.isEmpty())
			{
				// print error message
				cout << "Not enough operands entered for operator: " << in << endl;
				exit(1);
			}
			n1 = operandStack.top();
			operandStack.pop();

			// push the calculation result to the top of operandStack
			operandStack.push(calculate(n1, n2, in));
		}
		else
		{
			// push the number to the top of opernadStack
			// (pay attention to the data type)
			operandStack.push(charToInt(in));
		}
		cin >> in;
	}

	// pop a number from the top of stack
	int result;
	result = operandStack.top();
	operandStack.pop();

	if (operandStack.isEmpty())
	{ // nothing left in the stack
		cout << "\nThe result is: " << result << endl;
	}
	else
	{ // if there are still numbers in the stack, print an error message
		cout << "Not enough operators entered!" << endl;
	}

	return 0;
}

// default constructor for stack, stack is empty
Stack::Stack()
{
	listHead = NULL;
}

// stack destructor
Stack::~Stack()
{
	while (!isEmpty())
	{ // remove the top node until the stack is empty
		pop();
	}
}

// stack is empty if the top node is empty
bool Stack::isEmpty() const
{
	return listHead == NULL;
}

// returns data stored in the top node
int Stack::top() const
{
	return listHead->data;
}

// remove the top node
void Stack::pop()
{
	if (isEmpty())
	{
		return;
	}
	Node *temp = listHead;	 //store the top node
	listHead = listHead->link; // set the top node to the next node
	delete temp;			   // delete the temp node that had the previous top node
}

// add a new node on top
void Stack::push(int data)
{
	Node *temp = new Node; // create a new node
	temp->data = data;	 // the data is stored in the new node
	temp->link = listHead; // the new node is linked to the old head node
	listHead = temp;	   // the head node is now equal to the new node
}

// returns result of operation between two integers
int calculate(int o1, int o2, char op)
{
	switch (op)
	{
	case '+':
		return o1 + o2;
	case '-':
		return o1 - o2;
	case '*':
		return o1 * o2;
	case '/':
		return o1 / o2;
	}
}

bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int charToInt(char c)
{
	return (static_cast<int>(c) - static_cast<int>('0'));
}
