#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring> //for memset

#define NUM 2000
int bugs;
int adjacencyMatrix[NUM+1][NUM+1];
int colourOfVertex[NUM+1];

enum COLOUR
{
	RED=1,BLACK=2
};


bool graphColour(int source)
{
	colourOfVertex[source]=RED;
	std::queue<int> BFS;
	BFS.push(source);//source vertex
	while(!BFS.empty())
	{
		int poppedVertex=BFS.front();
		BFS.pop();
		int currentVertex=1;
		while(currentVertex <= bugs)
		{
			if (adjacencyMatrix[poppedVertex][currentVertex] && !colourOfVertex[currentVertex])
			{
				colourOfVertex[currentVertex] = 3 - colourOfVertex[poppedVertex];
				BFS.push(currentVertex);
			}
			else if (adjacencyMatrix[poppedVertex][currentVertex] && colourOfVertex[currentVertex] == colourOfVertex[poppedVertex])
			{
				return false;
			}
			currentVertex++;
		}
	}
	return true;
}

int allVertexVisited()
{
	for (int i = 1; i <= bugs; ++i)
	{
		if(!colourOfVertex[i]) return i;
	}

	return 0;
}

//Bipartite graph means whether the graph is 2 colourable or not
bool Solve() //returns true if graph is bipartite otherwise false
{
	std::memset(adjacencyMatrix,0,sizeof(adjacencyMatrix));
	std::memset(colourOfVertex,0,sizeof(colourOfVertex));
	int interactions;
	std::cin>>bugs>>interactions;
	for (int i = 1; i <= interactions; ++i)
	{
		int first,second;
		std::cin>>first>>second;
		adjacencyMatrix[first][second] = 1;
		adjacencyMatrix[second][first] = 1;
	}

	//check whether it is bipartite or not
	//means whether the graph is two colorable or not

	while(allVertexVisited())
	{
		bool answer = graphColour(allVertexVisited());
		if(!answer) return false;
	}
	
	return true;
}

int main(int argc, char const *argv[])
{
	int testCases;
	std::cin>>testCases;
	int count = testCases;
	while(testCases--)
	{
		std::cout<<"Scenario #"<< count- testCases << ":"<<std::endl;
		Solve() ? std::cout<<"No suspicious bugs found!\n":std::cout<<"Suspicious bugs found!\n";
	}
	return 0;
}