/* Problem ASSIGN of SPOJ
 * Author: Sunil Kumar
 * Submitted on: February 2,2017 20:22 status:Accepted
 * Techniques used here are bitmasking and DP
 * Explanation of the algorithm here:
 * https://discuss.codechef.com/questions/49559/dynamic-programming-bit-masking
 * and here
 * https://discuss.codechef.com/questions/49669/assign-spoj-redynamic-programming-with-bitmask
 * recursive function here is
 * f(n, s), which calculates the number of combinations of the
 * first n students and if the only available subjects left are in the set s
 * to find the final soultion we must find f(n,{0,1,2,...,n-1})
 */
#include <iostream>
#include <cstring>

#define ll unsigned long long
enum constants
{
	MAX=20
};

int input[MAX][MAX];
ll DP[1 << MAX];

void solve()
{
	int students;
	std::cin>>students;
	std::memset(input,0,sizeof(input));
	for (int i = 0; i < students; ++i)
	{
		for (int j = 0; j < students; ++j)
		{
			std::cin>>input[i][j];
		}
	}

	DP[0] = 1;
	for (ll i = 1; i < (1 << students); ++i)
	{
		DP[i]=0;
		/* number of 1s in i is same as number of students
		 * because those bits represent the available subject
		 * and according to the constraints in the question
		 * total students and total subjects should be same
		*/
		int setBits = __builtin_popcount(i); //total number of students remaining
		for (int mask = 0; mask < students; ++mask)
		{
			//if this (setBits th) student likes the subject and is available in the current set
			if (input[setBits-1][mask] && ( i & (1 << mask)))
			{
				/*
				 * DP[i] += DP[i' where i' has only mask th subject not available]
				 * suppose current set of subject are: i = 1001010 i.e	1st, 3rd, 6th
				 * and currently number of students would be equal to number of
				 * set bits which is 3 (=setbits),and suppose 3rd student likes
				 * 1st and 3rd subjects, so according to recursion the total ways
				 * corresponding to present set that is i would be equal to the
				 * sets 1001000(2nd bit changed to 0,meaning 1st subject made unavailable)
				 * and 1000010 (4th bit made 0 meaning 3rd subject made unavailbale).
				 * Note that last subject was also available but total ways corresponding
				 * to that subject after making it unavailable is not counted because
				 * 3rd student doesn't like this subject(6th subject).
				*/
				DP[i] += DP[i &  ~(1 << mask)] ;
			}
		}
	}
	std::cout<<DP[(1 << students) -1] << "\n";
}


int main()
{
	std::ios::sync_with_stdio(0);
	int testcases;
	std::cin>>testcases;
	while(testcases--)
		solve();

	return 0;
}