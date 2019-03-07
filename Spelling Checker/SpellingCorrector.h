#pragma once
#include <bits\stdc++.h>
#include "Trie.h"

#define ll long long int

using namespace std;

class SpellingCorrector
{
private:
    ll TotalWords;
    Trie* Root;
    set<pair<ll, string>> PossibleWords;

public:
	string TransformIt(string);
	void Intro();
	void EditDistance(string, ll);
	void AddWord(Trie*, string);
	ll Search(Trie*, string);
    SpellingCorrector();
    void Correct(string);
};