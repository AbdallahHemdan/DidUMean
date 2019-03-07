/*Author : Abdallah Hemdan */
/* ___  __
* |\  \|\  \
* \ \  \_\  \
*  \ \   ___ \emdan
*   \ \  \\ \ \
*    \ \__\\ \_\
*     \|__| \|__|
*/

#include <bits\stdc++.h>
#include "SpellingCorrector.h"


using namespace std;

SpellingCorrector Spell;

int main()
{
	while (true)
	{
		string CheckedWord, CheckExit;

		cout << "- Enter a String To be Checked :  ";
		cin >> CheckedWord;

		CheckExit = CheckedWord;
		transform(CheckExit.begin(), CheckExit.end(), CheckExit.begin(), ::tolower);
		
		if (CheckExit == "exit")
		{
			break;
		}
		Spell.Correct(CheckedWord);
	}
	return 0;
}