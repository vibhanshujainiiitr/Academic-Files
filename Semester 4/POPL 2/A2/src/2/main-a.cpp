#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <limits.h>

using namespace std;

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
		//cout << "This is error" << endl;
	};


	double eval() {

		int i;
		vector<double>values;
		vector<char>operation;

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

				while (!operation.empty() && precedence(operation.back()) >= precedence(input[i])) {
					double value_2 = values.back();
					values.pop_back();
					// Check the equivalent of pop

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
			double value_2 = values.back();
			values.pop_back();
			// Check the equivalent of pop

			double value_1 = values.back();
			values.pop_back();

			char op = operation.back();
			operation.pop_back();

			values.push_back(calculation(value_1, value_2, op));
		}

		return values.back();
	};

	void print() {
		cout << eval();
	};
};
int main() {
	char temp[100000];
	cin >> temp;
	Expr A(temp);

	A.print();
}