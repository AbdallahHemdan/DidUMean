#include "SpellingCorrector.h"
#define  ALPHASIZE   26


SpellingCorrector::SpellingCorrector()
{
	TotalWords = 0;
	Root = new Trie();

	ifstream BigFile;
	BigFile.open("Dic.txt");

	string Word;

	// eof() is an Indecator of The End of The File 
	// If at The end of the file return (true)
	// Else return (false)
	while (!BigFile.eof())
	{
		BigFile >> Word;
		Word = TransformIt(Word);
		if (Word != "")
		{
			AddWord(Root, Word);
			TotalWords++;
		}
	}

	BigFile.close();
	Intro();
}

string SpellingCorrector::TransformIt(string ToTransform)
{
	transform(ToTransform.begin(), ToTransform.end(), ToTransform.begin(), ::tolower);
	return ToTransform;
}


void SpellingCorrector::AddWord(Trie* Vertex, string Word)
{
	if (Word == "")
	{
		Vertex->Words++;
	}
	else
	{
		ll Index = Word[0] - 'a';
			if (Vertex->Edges[Index] == nullptr)
			{
				Vertex->Edges[Index] = new Trie();
			}
		Word.erase(0, 1);
		return AddWord(Vertex->Edges[Index], Word);
	}
}




void SpellingCorrector::Intro()
{
	cout << endl << "========================================== Welcome To Our Spell Corrector "
		"======================================= "
		<< endl << endl ;
	cout << "- We Check Your Word You Entered " << endl << endl;
	cout << "\t\t => If It Valid, No Problem" << endl;
	cout << "\t\t => If Not We Recommend Some Similar Words for you..." << endl << endl;
	cout <<"- Enter 'exit' OR 'EXIT' To Quit " << endl;
	cout << "=================================================== Lets's Go "
		"==================================================="
		<< endl;
	cout << endl << endl;
}


ll SpellingCorrector::Search(Trie* Vertex, string Word)
{
	if (Word == "")
	{
		return Vertex->Words;
	}
	else
	{
		ll Index = Word[0] - 'a';
			if (Vertex->Edges[Index] == nullptr)
			{
				return 0;
			}

		// Delete The First Char
		Word.erase(0, 1);
		return Search(Vertex->Edges[Index], Word);
	}
}



void SpellingCorrector::EditDistance(string Word, ll Current)
{
	ll Counter = 0;
	ll Length = Word.length();

	ll i, j;

	for (i = -1; i < Length; i++)
	{
		for (j = 0; j < ALPHASIZE; j++)
		{
			char C = 'a' + j;
			string NewWord = Word.substr(0, i + 1) + C + Word.substr(i + 1, Length - i - 1);

			ll NoOfEqual = Search(Root, NewWord);
			NoOfEqual *= -1;

			if (NoOfEqual != 0)
			{
				PossibleWords.insert(make_pair(NoOfEqual, NewWord));
			}
			if (Current == 0)
			{
				EditDistance(NewWord, 1);
			}
		}
	}

	for (i = 0; i < Length; i++)
	{
		for (j = 0; j < ALPHASIZE; j++)
		{
			char C = 'a' + j;
			string NewWord = Word.substr(0, i) + C + Word.substr(i + 1, Length - i - 1);

			ll NoOfEqual = Search(Root, NewWord);
			NoOfEqual *= -1;

			if (NoOfEqual != 0)
			{
				PossibleWords.insert(make_pair(NoOfEqual, NewWord));
			}
			if (Current == 0)
			{
				EditDistance(NewWord, 1);
			}
		}
	}
	for (i = 0; i < Length; i++)
	{
		string NewWord = Word.substr(0, i) + Word.substr(i + 1, Length - i - 1);
		ll NoOfEqual = Search(Root, NewWord);

		NoOfEqual *= -1;

		if (NoOfEqual != 0)
		{
			PossibleWords.insert(make_pair(NoOfEqual, NewWord));
		}
		if (Current == 0)
		{
			EditDistance(NewWord, 1);
		}
	}

	for (i = 0; i < Length - 1; i++)
	{
		char A = Word[i], B = Word[i + 1];
		string NewWord = Word.substr(0, i) + B + A + Word.substr(i + 2, Length - i - 2);

		ll NoOfEqual = Search(Root, NewWord);

		NoOfEqual *= -1;
		if (NoOfEqual != 0)
		{
			PossibleWords.insert(make_pair(NoOfEqual, NewWord));
		}
		if (Current == 0)
		{
			EditDistance(NewWord, 1);
		}
	}
}


void SpellingCorrector::Correct(string Word)
{
	// Clear the Set of The Possible Words...
	PossibleWords.clear();
	Word = TransformIt(Word);

	// Number of Equal Words...
	ll NoOfEqualWords = Search(Root, Word);

	if (NoOfEqualWords == 0)
	{
		EditDistance(Word, 1);
		if (PossibleWords.size() == 0)
		{
			EditDistance(Word, 0);
		}
		if (PossibleWords.size() == 0)
		{
			cout << "\t\tSorry...!!, No Recommendation." << endl;
		}
		else
		{
			cout << "\t\t" << "Possible Correct Words :" << endl;
			for (auto it : PossibleWords)
			{
				cout << it.second << endl;
			}
		}
	}
	else
	{
		cout << endl << "Good..!!, You Entered Correct Word." << endl;
	}
}