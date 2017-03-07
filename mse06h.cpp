#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

typedef struct node
{
	int first;
	int second;
}node;


bool accordingto(node left,node right)
{
	if (left.first != right.first)
	{
		return left.first < right.first;
	}
	return left.second <= right.second;
}

long long int Merge(int array[],int left,int mid,int right)
{
	int *leftArray = new int[mid-left];
	int *rightArray = new int[right-mid+1];
	for (int i = left; i < mid; ++i)
	{
		leftArray[i-left]=array[i];
	}
	for (int i = mid; i <= right; ++i)
	{
		rightArray[i-mid]=array[i];
	}

	int overallIndex=left;
	int leftIndex=0;
	int rightIndex=0;
	long long int inversions=0;

	while((leftIndex < mid-left) && (rightIndex <= right-mid))
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[overallIndex++] = leftArray[leftIndex++];
		}
		else
		{
			array[overallIndex++] = rightArray[rightIndex++];
			inversions += mid-left-leftIndex;
			// PrintThePair(array,leftIndex,mid,mid-leftIndex,right);
		}
	}
	while(leftIndex < mid-left)
	{
		array[overallIndex++] = leftArray[leftIndex++];
	}
	while(rightIndex <= right-mid)
	{
		array[overallIndex++] = rightArray[rightIndex++];
	}
	delete[] leftArray;
	delete[] rightArray;
	return inversions;
}

long long int MergeSort(int array[],int left,int right) //left and right are both indices and are inclusive
{
	long long int inversions = 0;
	if (left < right)
	{
		int midIndex=(left+right)/2;
		inversions = MergeSort(array,left,midIndex);
		inversions += MergeSort(array,midIndex+1,right);
		inversions += Merge(array,left,midIndex+1,right);
	}
	return inversions;
}

long long Solve()
{
	int east,west,highways;
	std::cin>>east>>west>>highways;
	node edge[highways];

	for (int i = 0; i < highways; ++i)
	{
		int eastCity,westCity;
		std::cin>>eastCity>>westCity;
		edge[i].first=eastCity;
		edge[i].second=westCity;
	}

	std::sort(edge,edge+highways,accordingto);
	int* rightSide=new int[highways];
	for (int i = 0; i < highways; ++i)
	{
		rightSide[i] = edge[i].second;
	}
	//count the number of inversions in the right index
	long long int inversions = MergeSort(rightSide,0,highways-1);
	delete[] rightSide; //avoiding memory leaks
	return inversions;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	int testCases;
	std::cin>>testCases;
	int num=testCases;
	while(testCases--)
	{
		std::cout<<"Test case "<< num-testCases << ": "<< Solve()<<"\n";
	}
	return 0;
}