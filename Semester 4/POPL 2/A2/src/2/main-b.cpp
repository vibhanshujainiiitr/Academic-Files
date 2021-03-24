#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <limits.h>

using namespace std;

class node{
  public:
    int data;
  	node* next;
  	node* previous;
	node(double value){
		this->data = value;
		this->next = NULL;
		this->previous = NULL;
	}
};

class linkedList
{
public:
	
	node* start;
	node* end;
	
	/* Contructor */
	linkedList(){
		start = NULL;
		// cout<<"Some error here";
	}

	void push_back(double value){
		node temp = node(value);
		temp.data = value;
		temp.next = start;
		*start->previous = temp;
		*start = temp;
		
	};
	void pop_back(){
		if(end == NULL)
			return;

		end->previous->next = NULL;
		node* temp = end->previous;
		end = temp->previous;
		free(temp);
	};
	double back(){
		return end->data;
	};	
};

// Precendence functions
double precedence(char object)
{
	if (object == '+' || object == '-' )
		return 1;

	if (object == '*' || object == '/' )
		return 2;

	return 0;
}

// Actual Calculations
double calculation(double a, double b, char operation)
{
	switch (operation)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}

	return 0;
}

class Expr {
	// input is the string that will be inputed

	string input;

public:

	Expr(char* str) {
		input = str;
		//cout << str << endl;
	};


	double eval() {

		int i;
		linkedList values;
		list <char>operation;
		// Two vectors to store the elements

		for (int i = 0; i < input.size(); i++) {

			// If the token is empty then skip it
			if ( input[i] == ' ' )
				continue;

			else if (isdigit(input[i])) {
				double value = 0;

				// If there are more than one digit in the input
				while ( i < input.size() && isdigit(input[i]))
				{
					value = (value * 10) + (input[i] - '0');
					i++;
				}

				values.push_back(value);
				i--;
			}

			else {
				// Calculating while the precedence of the operator inside is more than the input operator
				while (!operation.empty() && precedence(operation.back()) >= precedence(input[i])) {
					double value_2 = values.back();
					values.pop_back();

					double value_1 = values.back();
					values.pop_back();

					char op = operation.back();
					operation.pop_back();

					values.push_back(calculation(value_1, value_2, op));
				}

				operation.push_back(input[i]);
			}

		}

		while (!operation.empty()) {
			// Calculating while there are opertors in the vector
			double value_2 = values.back();
			values.pop_back();

			double value_1 = values.back();
			values.pop_back();

			char op = operation.back();
			operation.pop_back();

			values.push_back(calculation(value_1, value_2, op));
		}

		// This will be the result of the calculations
		return values.back();
	};

	void print() {
		// Printing the result
		cout << eval();
	};
};
int main() {
	char temp[100000];
	cin >> temp;
	Expr A(temp);

	A.print();
}
