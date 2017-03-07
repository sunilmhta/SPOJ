#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <cstdlib>

enum operators
{
	NOTHING=0,
	MULTIPLICATION=1,
	DIVISION=2,
	SUBTRACTION=3,
	ADDITION=4
};

operators GetOperator(char operation) //will give the operators
{
	switch(operation)
	{
		case '+' : return ADDITION;break;
		case '-' : return SUBTRACTION;break;
		case '*' : return MULTIPLICATION;break;
		case '/' : return DIVISION;break;
		default  : return  NOTHING; break;
	}

}

void clear(std::stack<char> &q) //empty a stack
{
	std::stack<char> empty;
	std::swap(q,empty);
}

int main(int argc, char const *argv[])
{
	int testcases;
	std::cin >> testcases;
	std::vector<std::string> input(testcases);

	for (int i = 0; i < testcases; ++i)
	{
		std::cin >> input[i];
	}

	for (int i = 0; i < testcases; ++i)
	{
		std::string expression = input[i];
		std::stack<char> primary;
		primary.push('!');
		std::stack<char> secondary;
		int length = expression.length();
		int index=0; //index of the string expression

		while(index < length)
		{
			operators MainSecondaryOperator = NOTHING;
			char currentCharacter = expression[index];
			if (currentCharacter != ')')
			{
				primary.push(currentCharacter);
			}
			else
			{
				while(!primary.empty() && primary.top() != '(')
				{
					if (!isalpha(primary.top()))
					{
						int temp=MainSecondaryOperator;
						int a = GetOperator(primary.top());
						MainSecondaryOperator = (operators)std::max(temp,a);
					}
					secondary.push(primary.top());
					primary.pop();
				}
				if(primary.empty()) std::exit(EXIT_FAILURE);

				primary.pop(); //removing left bracket too

				operators PrimaryLeft = NOTHING;
				operators PrimaryRight = NOTHING;
				PrimaryLeft = GetOperator(primary.top());
				if(index+1 < length && !isalpha(expression[index+1]))
				{
					PrimaryRight = GetOperator(expression[index+1]);
				}

				bool removeBrackets = false; //give whether to remove the brackets or not
				if (MainSecondaryOperator >= SUBTRACTION) // operatore is '+' or '-'
				{
					if ((PrimaryLeft == NOTHING || PrimaryLeft == ADDITION) && (PrimaryRight >= SUBTRACTION || PrimaryRight == NOTHING))
					{
						removeBrackets = true;
					}
				}
				else if (MainSecondaryOperator >= MULTIPLICATION) // operator is either '*' or '/'
				{
					if (PrimaryLeft != DIVISION)
					{
						removeBrackets = true;
					}
				}
				else if (MainSecondaryOperator == NOTHING) //no operators inside the brackets
				{
					removeBrackets = true;
				}

				if(!removeBrackets)
				{
					primary.push('L');
				}
				while(!secondary.empty())
				{
					primary.push(secondary.top());
					secondary.pop();
				}
				if(!removeBrackets)
				{
					primary.push('R');
				}
			}

			index++;
		}

		std::string answer="";
		while(primary.size() > 1)
		{
			char currentCharacter = primary.top();
			if(currentCharacter == 'L') currentCharacter = '(';
			if(currentCharacter == 'R') currentCharacter = ')';
			answer = currentCharacter + answer;
			primary.pop();
		}

		std::cout<<answer <<"\n";
		clear(primary);
		clear(secondary);
	}
	return 0;
}
