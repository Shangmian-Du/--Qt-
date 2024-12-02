#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

class Calculator{
	private:
	bool isOperator(char c){
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	}
	int getPriority(char op){
		if (op == '^') return 3;
		if (op == '*' || op == '/') return 2;
		if (op == '+' || op == '-') return 1;
		return 0;
	}
	double operate(double b , double a , char op){
		switch(op){
			case '+' : return a + b;
			case '-' : return a - b;
			case '*' : return a * b;
			case '/' : return a / b;
			case '^' : return std::pow(a , b);
			default : return 0;
		}
	}
	public:
	double calculate(string expression){
		stack<double> numbers;
		stack<char> operators;
		stringstream ss(expression);
		double number;
		char op;
		while (ss >> number){
			numbers.push(number);
			if (ss >> op){
				while (!operators.empty() && getPriority(operators.top()) >= getPriority(op)){
					double b = numbers.top(); numbers.pop();
					double a = numbers.top(); numbers.pop();
					char topOp = operators.top(); operators.pop();
					numbers.push(operate(b , a , topOp));
				}
				operators.push(op);
			}
		}
		while (!operators.empty()){
		double b = numbers.top(); numbers.pop();
		double a = numbers.top(); numbers.pop();
		char topOp = operators.top(); operators.pop();
		numbers.push(operate(b , a ,topOp));
		}
		return numbers.top();
	}	
};

int main(){
	Calculator calc;
	string expression;
	
	cout << "输入一个计算表达式(不含括号)：" << endl;
	getline(cin , expression);
	
	double result = calc.calculate(expression);
	cout << "计算结果" << result <<endl;
	
	return 0;
}