#include "AutoCompleteBasicQ.h"
#include "myGetch.h"
#include "User.h"

void AutoCompleteBasicQ::GetAutoCompleteList(string& keyword, vector<Query*>& history, vector<string>& list)
{
	list.clear();
	string historyKW;

	for (vector<Query*>::iterator q=history.begin(); q!=history.end(); q++)
	{
		historyKW = (*q)->GetKeyword();
		if (historyKW.find(keyword, 0) == 0)
			list.push_back(historyKW);
	}
}

void AutoCompleteBasicQ::InitQuery(User* user)
{
	string keyword="";

	cout<<"Enter the keyword you wanna search for (press Tab to auto-complete): "<<endl<<"> ";
	cout.flush();

	const char BACKSPACE=127;
	const char RETURN=10;
	const char TAB=9;
	const char UPARROW=72;
	const char DOWNARROW=80;
	char c;
	vector<string> autoList;
	vector<string>::iterator autoListIterator;

	raw();
	while ((c=getch()) != RETURN)
	{
		if(c==BACKSPACE)
		{
			if(keyword.length()!=0)
			{
				cout <<"\b \b";
				cout.flush();
				keyword.resize(keyword.length()-1);
			}
			GetAutoCompleteList(keyword, user->GetQueryHistory(), autoList);
			autoList.insert(autoList.begin(), keyword);
			autoListIterator = autoList.begin();
		}
		else if (c==TAB)
		{
			if (autoList.size() > 0)
			{
				// clear previous auto-complete
				for (int i=0 ; i<keyword.length(); i++)
				{
					cout <<"\b \b";
					cout.flush();
				}

				// go to next auto-complete
				autoListIterator++;
				if (autoListIterator == autoList.end())
					autoListIterator = autoList.begin();

				// show this auto-complete
				keyword = (*autoListIterator);
				cout<<keyword;
				cout.flush();
			}
		}
		else
		{
			keyword+=c;
			cout<<c;
			cout.flush();
			GetAutoCompleteList(keyword, user->GetQueryHistory(), autoList);
			autoList.insert(autoList.begin(), keyword);
			autoListIterator = autoList.begin();
		}
	}
	cout<<endl;
	cooked();

	SetKeyword(keyword);
//	if (autoListIterator == autoList.begin()) // unseen query, add to history
//		user->AddQueryHistory(this);
}
