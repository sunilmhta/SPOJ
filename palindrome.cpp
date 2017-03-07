#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool isnine=false; //says whether the given number consists only 9 or not

void add_1(string &num) //this function adds 1 to the given number which is passed as a string
{
	int length = num.length();
	int flag=length;
	while(length--)
	{
		char digit=num[length];
		if (digit == '9')
		{
			num[length] = '0';
		}
		else 
		{
			digit = digit+1; //simple addition [char + int ]results in the correct decimal addition as well.
			num[length] = digit;
			break;
		}
		flag--;
	}
	if(!flag) //means the given number consisits of only 9's.
	{
		num.insert(0,1,'1');
		isnine = true;
		// num.erase(num.length()-1);
	}
}

int main(int argc, char const *argv[])
{
	int testcases;
	cin >> testcases;
	std::vector<string> input(testcases);
	for (int i = 0; i < testcases; ++i)
	{
		cin >> input[i];
	}

	for (int i = 0; i < testcases; ++i)
	{
		string number=input[i];
		int length=number.length();
		int middle=length/2;
		string answer="";
		string first=number.substr(0,middle);
		string temp=first;
		reverse(temp.begin(),temp.end()); //reversed first half
		if (length == 1)
		{
			answer = "11";
		}
		else
		{

			if (length%2 == 0)
			{
				answer=first+temp; //first attempt to make a palindrome
				if (answer <= number) //checking whether it is greater than the given number or not
				{
					/*
					* note that only string comparision between answer and number would 
					* be enough to check which is greater number because
					* the strings answer and number would vary just after the mid position 
					* and the character which is bigger would definitely be the greater string
					* according to the string comparision
					*/
					add_1(first);
					string str=first;
					reverse(str.begin(),str.end());
					answer=first+str;
				}
			}
			else
			{
				answer=first+number[middle]+temp;
				if (answer <= number)
				{
					string num=first+number[middle];
					add_1(num);
					string str=num;
					reverse(str.begin(),str.end());
					answer=num+str.substr(1);
				}
			}
			if(isnine) //if the given number consists of only 9's
			{
				/*
				* in this case there would be an extra 0
				* we are erasing that 0 from the final answer
				*/
				int pos=answer.length();
				pos /=2; //position of 0 to be removed
				answer.erase(answer.begin()+pos); 
				isnine=false;
			}
		}
		cout << answer << endl;
	}

	return 0;
}