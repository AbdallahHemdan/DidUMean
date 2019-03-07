#pragma once
#define ll long long int
#define	   NoOfEdges     26

struct Trie
{
	ll Words;
	Trie* Edges[NoOfEdges];

	Trie()
	{
		Words = 0;
		for (int index = 0; index < NoOfEdges; index++)
		{
			Edges[index] = nullptr;
		}
	}
};