//Task 2
//SIMPLE CALCULATOR
//Develop a calculator program that performs basic arithmetic 
//operations such as addition, subtraction, multiplication, and
//division. Allow the user to input two numbers and choose an
//operation to perform.

#include<iostream>
using namespace std;

int main() {
	cout<< "This is a calculator which can perform arithmetic operations like"<<endl;
	cout<< "Addition, Subtraction, Multiplication and Division."<<endl;
	cout<< "Between two numbers."<<endl;
	
	float num1, num2;
	char operator_used;
	
	cout<<"Enter the first number = ";
	cin>> num1;
	cout<< "Enter the second number = ";
	cin>>num2;
	cout << "Enter the operator you want to use(+,-,*,/) = ";
	cin>> operator_used;
	
	if (operator_used== '+'){
		cout<<"The sum of the two numbers is = ";
		cout<< num1+num2;
	}
	else if (operator_used== '-'){
		cout<<"The difference of the two numbers is = ";
		cout<< num1-num2;
	}
	else if(operator_used== '*'){
		cout<<"The product of the two numbers is = ";
		cout<< num1*num2;
	}
	else if(operator_used== '/'){
		if (num2 != 0) {
			cout << "The division of the two numbers is = " << num1 / num2;
	}
}
	else{
		cout<<"The operator is incorrect or invalid!";
	}	
}