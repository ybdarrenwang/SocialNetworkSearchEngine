#include "User.h"
#include "PlurkPuDecorator.h"
#include "PlurkReplyDecorator.h"
#include "myGetch.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include "AutoCompleteBasicQ.h"
#include "AutoCompleteAdvQ.h"

using namespace std;

User::User()
{
	// load query history
	ifstream ifs;
	ifs.open("queryHistory.log");
	if(!ifs.good())
		cerr<<"Warning: can't load query history log"<<endl;
	else
	{
		string line, keyword, person;
		getline(ifs,line);
		while(!ifs.eof())
		{
			int i;
			while( (i=line.find('\r')) >= 0 ) line.erase( i, i+1 );
			queryHistory.push_back(new BasicQuery(0));
			queryHistory.back()->SetKeyword(line);
			getline(ifs,line);
		}
	}
	ifs.close();
}

User::~User()
{
	// save query history
	ofstream ofs;
	ofs.open("queryHistory.log");
	if(!ofs.good())
		cerr<<"Warning: can't save query history log"<<endl;
	else
	{
		int historySize = 0;
		for (int i=queryHistory.size()-1; i>=0 && historySize<MAXHISTORYLOGSIZE; i--)
		{
			ofs<<queryHistory[i]->GetKeyword()<<endl;
			historySize++;
		}
	}
	ofs.close();

	// clear memory
	for (int i=0; i<relevantPosts.size(); i++)
		delete relevantPosts[i];
	for (int i=0; i<queryHistory.size(); i++)
		delete queryHistory[i];
}

User* User::Instance()
{
	return &instance;
}

void User::InitUser()
{
	cout<<"Enter user name: "<<endl<<"> ";
	cin>>id;
    /*
    // < Password masking >
    // Currently there's no need for password; so this function is just for fun
	cout<<"Enter password: "<<endl<<"> ";
	cout.flush();

	pwd = "";
	const char BACKSPACE=127;
	const char RETURN=10;
	char c;
	raw();
	while ((c=getch()) != RETURN)
	{
		if(c==BACKSPACE)
		{
			if(pwd.length()!=0)
			{
				cout <<"\b \b";
				cout.flush();
				pwd.resize(pwd.length()-1);
			}
		}
		else
		{
			pwd+=c;
			cout<<"*";
			cout.flush();
		}
	}
	cout<<endl;
	cooked();*/
}

int User::Login(SocialNet* n)
{
	int returnedValue =  n->Login(id, pwd);

	// load friend list from file saved by SocialNet
	friends.clear();
	ifstream ifs;
	ifs.open("FriendsList");
	if(!ifs.good())
		cerr<<"Warning: can't load file FriendsList"<<endl;
	else
	{
		int i;
		string line;
		getline(ifs,line);
		while(!ifs.eof())
		{
			while( (i=line.find('\r')) >= 0 ) line.erase( i, i+1 );
			friends.push_back(line);
			getline(ifs,line);
		}
	}
	ifs.close();

	return returnedValue;
}

bool User::WantContinue()
{
	string want = "";
	while (want != "y" && want != "n")
	{
		cout<<"Start the next query? [y/n]: "<<endl<<"> ";
		cin>>want;
	}

	if (want == "y")
		return true;
	else
		return false;
}

void User::Search(Query* q)
{
	q->InitQuery(this);
	queryHistory.push_back(q);
	for (int i=0; i<relevantPosts.size(); i++)
		delete relevantPosts[i];
	relevantPosts.clear();
	relevantPosts = queryHistory.back()->Execute();
}

void User::InteractWithPosts()
{
	if (relevantPosts.empty())
		cout<<"No relevant posts found."<<endl;
	else
	{
		Post* currentPost = *relevantPosts.begin();
		Post* futurePost = currentPost;
		string option;
		while (currentPost != 0)
		{
			currentPost->PrintContent(cout);
			currentPost->PrintOption(cout);

			while(currentPost == futurePost)
			{
				cin>>option;
				futurePost = currentPost->ExecuteOption(option, currentPost);
			}
			currentPost = futurePost;
		}
	}
}

int User::Logout(SocialNet* n)
{
	id = "";
	pwd = "";
	cout<<"Logout"<<endl;

	return 0;
}
