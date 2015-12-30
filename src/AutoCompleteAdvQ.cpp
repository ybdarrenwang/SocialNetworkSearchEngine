#include "AutoCompleteAdvQ.h"
#include "myGetch.h"
#include "User.h"

void AutoCompleteAdvQ::GetAutoCompleteList(string& keyword, vector<Query*>& history, vector<string>& list)
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

void AutoCompleteAdvQ::GetAutoCompleteList(string& person, vector<string>& friends, vector<string>& list)
{
	list.clear();
	string _friend;

	for (vector<string>::iterator f=friends.begin(); f!=friends.end(); f++)
	{
		if (f->find(person, 0) == 0)
			list.push_back(*f);
	}
}

void AutoCompleteAdvQ::InitQuery(User* user)
{
	string keyword="";
	string person="";
	const char BACKSPACE=127;
	const char RETURN=10;
	const char TAB=9;
	const char UPARROW=72;
	const char DOWNARROW=80;
	char c;
	vector<string> autoList_kw;
	vector<string> autoList_friend;
	vector<string>::iterator autoListIterator;
	
	// auto-complete keyword
	cout<<"Enter the keyword you wanna search for: "<<endl<<"(Leave empty if unlimited; Press Tab to auto-complete)"<<endl<<"> ";
	cout.flush();

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
			GetAutoCompleteList(keyword, user->GetQueryHistory(), autoList_kw);
			autoList_kw.insert(autoList_kw.begin(), keyword);
			autoListIterator = autoList_kw.begin();
		}
		else if (c==TAB)
		{
			if (autoList_kw.size() > 0)
			{
				// clear previous auto-complete
				for (int i=0 ; i<keyword.length(); i++)
				{
					cout <<"\b \b";
					cout.flush();
				}

				// go to next auto-complete
				autoListIterator++;
				if (autoListIterator == autoList_kw.end())
					autoListIterator = autoList_kw.begin();

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
			GetAutoCompleteList(keyword, user->GetQueryHistory(), autoList_kw);
			autoList_kw.insert(autoList_kw.begin(), keyword);
			autoListIterator = autoList_kw.begin();
		}
	}
	cout<<endl;
	cooked();

	SetKeyword(keyword);

	// auto-complete person
	cout<<"Enter the person you wanna search for: "<<endl<<"(Leave empty if unlimited; Press Tab to auto-complete)"<<endl<<"> ";
	cout.flush();

	raw();
	while ((c=getch()) != RETURN)
	{
		if(c==BACKSPACE)
		{
			if(person.length()!=0)
			{
				cout <<"\b \b";
				cout.flush();
				person.resize(person.length()-1);
			}
			GetAutoCompleteList(person, user->GetFriends(), autoList_friend);
			autoList_friend.insert(autoList_friend.begin(), person);
			autoListIterator = autoList_friend.begin();
		}
		else if (c==TAB)
		{
			if (autoList_friend.size() > 0)
			{
				// clear previous auto-complete
				for (int i=0 ; i<person.length(); i++)
				{
					cout <<"\b \b";
					cout.flush();
				}

				// go to next auto-complete
				autoListIterator++;
				if (autoListIterator == autoList_friend.end())
					autoListIterator = autoList_friend.begin();

				// show this auto-complete
				person = (*autoListIterator);
				cout<<person;
				cout.flush();
			}
		}
		else
		{
			person+=c;
			cout<<c;
			cout.flush();
			GetAutoCompleteList(person, user->GetFriends(), autoList_friend);
			autoList_friend.insert(autoList_friend.begin(), person);
			autoListIterator = autoList_friend.begin();
		}
	}
	cout<<endl;
	cooked();

	SetPerson(person);
}
