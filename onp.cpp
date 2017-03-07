//Dijkstra's shunting yard algorithm

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

int Priority(char Operator) //returns the priority of the operators according to the given priorities
{
	int answer=0;
	switch(Operator)
	{
		case '+' : answer=1;break;
		case '-' : answer=2;break;
		case '*' : answer=3;break;
		case '/' : answer=4;break;
		case '^' : answer=5;break;
		default  : break;
	}
	return answer;
}

void clear(std::stack<char> &q) //clears the stack
{
	std::stack<char> a;
	std::swap(a,q);
}

int main(int argc, char const *argv[])
{
	int testcases;
	std::cin >> testcases;
	for (int i = 0; i < testcases; ++i)
	{
		std::string expresssion; //input
		std::cin>>expresssion;
		std::stack<char> Operator; //stack
		std::string output=""; //output

		int index = 0;
		int length=expresssion.length();

		while(index < length)
		{
			if (isalpha(expresssion[index])) //if operand output it
			{
				output += expresssion[index];	
			}
			else if (expresssion[index] == '(') // if left bracket push it to the stack
			{
					Operator.push(expresssion[index]);
			}
			else if (expresssion[index] == ')') //if right bracket then pop the stack until it is left bracket
			{
				while(!Operator.empty() && Operator.top() != '(')
				{
					output += Operator.top();
					Operator.pop();
				}
				if (!Operator.empty()) //pop the left bracket too
				{
					Operator.pop();
				}

			}
			else
			{
				char currentOperator = expresssion[index];
				while(!Operator.empty() && Priority(currentOperator) <= Priority(Operator.top())) //until priority of current operator is not greater
				{
					output += Operator.top();
					Operator.pop();
				}
				Operator.push(currentOperator); //Now push the current operator
			}
			index++;
		}
		while(!Operator.empty()) //if the stack is still not empty then pop it
		{
			output += Operator.top();
			Operator.pop();
		}
		std::cout<<output<<std::endl;
		clear(Operator);
	}
	return 0;
}

