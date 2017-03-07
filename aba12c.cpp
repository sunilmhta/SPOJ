/* Problem: Buying Apples!
 * Online Judge: SPOJ
 * Author: Sunil Kumar
 * Technique Used: DP
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

enum cons
{
	AVAILABLE=0,NOT_AVAILABLE=INT_MAX,OUT=200,
};

typedef struct node
{
	int answer;
	int packet;
public:
	node()
	{
		answer=0;
		packet=0;
	}

}node;


void Solve()
{
	node DP[101];
	int friends,totalweight;
	std::cin>>friends>>totalweight;
	int* Price = new int[totalweight+1];
	Price[0]=0;
	for (int i = 1; i <= totalweight; ++i)
	{
		std::cin>>Price[i];
		Price[i] == -1? Price[i] = NOT_AVAILABLE:Price[i];
	}
	//solving DP
	DP[0].answer=AVAILABLE;
	DP[0].packet=0;
	for (int i = 1; i <= totalweight; ++i)
	{
		int minPriceIndex = 0;
		int maxPriceIndex=i;
		DP[i].answer = Price[i];
		DP[i].answer != NOT_AVAILABLE ? DP[i].packet = 1:DP[i].packet=OUT;
		while(minPriceIndex <= maxPriceIndex)
		{
			int totalPackets=DP[minPriceIndex].packet+DP[maxPriceIndex].packet;
			if (DP[minPriceIndex].answer != NOT_AVAILABLE && DP[maxPriceIndex].answer != NOT_AVAILABLE && totalPackets < OUT)
			{
				DP[i].answer = std::min(DP[minPriceIndex].answer+DP[maxPriceIndex].answer,DP[i].answer);
			}

			minPriceIndex++;
			maxPriceIndex--;
		}
	}
	DP[totalweight].answer==NOT_AVAILABLE? DP[totalweight].answer=-1:DP[totalweight].answer;
	std::cout<<DP[totalweight].answer<<"\n";
}

int main(int argc, char const *argv[])
{
	int testCases;
	std::cin >> testCases;
	while(testCases--)
		Solve();
	return 0;
}