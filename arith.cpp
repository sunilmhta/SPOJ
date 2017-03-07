/* Problem ASSIGN of SPOJ , Simple Arithmetics
 * Author: Sunil Kumar
 * Submitted on: February 2,2017 20:22 status: Accepted
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
/*Removes all the zeroes from the start of a number*/
void removetrailingzero(string &answer)
{
	int index=0;
	while(index < answer.length()-1) //delte all the 0s which are at the beginning
	{
		if (answer[index] == '0')
		{
			answer.erase(0,1);
		}
		else break;
	}
}

// convert two strings first and second of equal length
void equalLength(string &first,string &second)
{
	int firstLength=first.length();
	int secondLength=second.length();
	int differenceinLength = firstLength - secondLength;
	string padding="";
	padding.insert(0,abs(differenceinLength),'0');
	if(differenceinLength > 0)
	{
		second = padding + second;
	}
	else if(differenceinLength < 0)
	{
		first = padding + first;
	}
}

//Subtraction
string sub(string first,string second)
{
	string answer = "";
	equalLength(first,second);
	int length=max(first.length(),second.length());
	int borrow=0;
	// cout << first << " " << second<<endl;
	while(length--)
	{
		int diff=(first[length]-'0')-borrow-(second[length]-'0');
		if(diff < 0) { borrow = 1; diff += 10;}
		else borrow=0;
		char b = diff%10 + '0';
		answer += b;
	}
	reverse(answer.begin(),answer.end());
	if (answer[0] == '0')
	{
		answer.erase(0,1);
	}

	return answer;
}

//Addition
string add(string first,string second)
{
	string answer="";
	equalLength(first,second);
	int length=max(first.length(),second.length());
	int carry = 0;
	while(length--)
	{
		int sum = (first[length] - '0') + (second[length]-'0') + carry;
		carry = sum / 10;
		char b = sum%10 + '0';
		answer += b;
	}
	reverse(answer.begin(),answer.end());
	if (carry != 0)
	{
		answer.insert(0,1,carry+'0');
	}
	// cout << answer << endl;
	return answer;
}

//Multiplication which will use addition
void multiply(string first,string second,std::vector<string> &array)
{
	int secondLength = second.length();
	int index=0;
	int temp=secondLength;
	array[temp] = "0";
	while(secondLength--)
	{
		int digit=second[secondLength]-'0';
		array[index] = "0";
		while(digit--)
		{
			array[index] = add(first,array[index]);
		}
		array[index].insert(array[index].end(),index,'0');
		array[temp] = add(array[index],array[temp]);
		index++;
	}
}

int main(int argc, char const *argv[])
{
	int testcase;
	cin >> testcase;
	std::vector<string> expression(testcase);
	for (int i = 0; i < testcase; ++i)
	{
		cin >> expression[i];
	}

	for (int i = 0; i < testcase; ++i)
	{
		size_t indexOfOperator=expression[i].find_first_of("+-*");
		string first="";
		string second="";
		char operation='+';
		if (indexOfOperator != string::npos)
		{
			first = expression[i].substr(0,indexOfOperator);
			operation = expression[i][indexOfOperator];
			second = expression[i].substr(indexOfOperator+1);
		}

		int firstLength=first.length();
		int secondLength=second.length();
		std::vector<string> products(secondLength+1);
		string answer = "";
		switch(operation)
		{
			case '+' : answer = add(first,second);break;
			case '-' : answer = sub(first,second);break;
			case '*' : multiply(first,second,products);break;
			default : break;
		}

		string padding="";

		if(operation == '+' || operation == '-')
		{
			removetrailingzero(answer);
			int length=answer.length();
			int maxlength = max(length,max(firstLength,secondLength+1));
			int dashlines=max(length,secondLength+1);
			int diff = maxlength-firstLength;
			padding.insert(0,diff,' ');
			cout << padding << first << endl;
			diff=maxlength- secondLength-1;
			padding="";
			padding.insert(0,diff,' ');
			cout << padding << operation << second << endl;
			diff=maxlength-dashlines; //for dashes
			padding="";
			padding.insert(0,diff,' ');
			cout<<padding;
			padding="";
			padding.insert(0,dashlines,'-');
			cout<<padding<<endl;
			diff=maxlength-length; //for dashes
			padding="";
			padding.insert(0,diff,' ');
			cout<<padding<<answer<<"\n\n";

		}
		else if (operation == '*')
		{
			answer = products[secondLength];
			int length = answer.length();
			// cout << "Length of answer: "<<length<<endl;
			int maxlength=max(length,secondLength+1);
			int diff = maxlength-firstLength;
			padding.insert(0,diff,' ');
			cout << padding << first << endl;
			diff=maxlength- secondLength-1;
			padding="";
			padding.insert(0,abs(diff),' ');
			cout << padding << operation << second << endl;
			int p0=products[0].length();
			diff=maxlength-max(secondLength+1,p0);
			padding="";
			padding.insert(0,abs(diff),' ');
			cout << padding;
			int temp = max(secondLength+1,p0);
			while(temp--)cout << "-";
			cout << "\n"; //<< answer<<endl;
			for (int i = 0; i < secondLength; ++i)
			{
				padding ="";
				size_t n = std::count(products[i].begin(), products[i].end(), '0');
				if(n == products[i].length()) products[i].replace(products[i].begin(),products[i].begin()+n-i,1,'0');
				// products[i].replace(products[i].end()-i,products[i].end(),i,' ');
				size_t asf =products[i].length()-i;
				products[i]=products[i].substr(0,asf);
				diff=maxlength-products[i].length()-i;
				padding.insert(0,diff,' ');
				cout << padding << products[i] << endl;
			}
			if(secondLength > 1)
			{
				padding="";
				padding.insert(0,maxlength-length,' ');
				cout << padding;
				string a=padding;
				padding="";
				padding.insert(0,length,'-');
				cout<<padding<< "\n"<< a << answer<<"\n\n";
			}
			else cout<<endl;
		}
	}
	return 0;
}