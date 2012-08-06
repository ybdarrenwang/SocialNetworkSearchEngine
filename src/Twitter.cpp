#include "Twitter.h"
#include <stdio.h>
#include <stdlib.h>

Twitter::Twitter():SocialNet("Twitter")
{
}

int Twitter::Login(string& id, string& pwd)
{
	cout<<"Login Twitter with id="<<id<<endl;
    char sys_call[1024] = {0};
	sprintf(sys_call, "python ./Twitter/Twitter_Query.py login %s", id.c_str());
	system( sys_call );	
	return 0;
}

vector<Post*> Twitter::BasicSearch(BasicQuery* q)
{
	vector<Post*> p;
	cout<<"Twitter basic search"<<endl;
	
	char sys_call[1024] = {0};
	sprintf(sys_call, "python ./Twitter/Twitter_Query.py query -r %s", q->GetKeyword().c_str());
	system( sys_call );	

	Json::Value root;
	ifstream fin("POST.json");
	fin >> root;
	fin.close();

	int index = root.size();
	Post* pre = NULL;

	for(int i=0; i< index; ++i){
		Message *_p = new Message();
		_p->SetMessage(root[i]);
	
		Post* p_cur = new TwitterTweetDecorator( new TwitterReplyDecorator (_p)) ;
		if(pre != NULL){
			p_cur->SetPrevPost( pre );
			pre->SetNextPost(p_cur);
		}		
	
		p.push_back( p_cur  );
		pre = p_cur;
	}
	
	return p;
}

vector<Post*> Twitter::AdvancedSearch(AdvancedQuery* q)
{
	vector<Post*> p;
	cout<<"Twitter advanced search"<<endl;
	
	char sys_call[1024] = {0};
	char add_opt[1024] = {0};
	string keyword = q->GetKeyword();
	string person = q->GetPerson();

	if(keyword.compare("*") != 0)
		sprintf(add_opt, "-r %s", keyword.c_str());
	if(person.compare("*") != 0)
		sprintf(add_opt, "%s -u %s", add_opt, person.c_str());
    else
        sprintf(add_opt, "%s -m", add_opt);

	sprintf(sys_call, "python ./Twitter/Twitter_Query.py query %s", add_opt);
	system(sys_call);	

	Json::Value root;
	ifstream fin("POST.json");
	fin >> root;
	fin.close();

	int index = root.size();
	Post* pre = NULL;

	for(int i=0; i< index; ++i){
		Message *_p = new Message();
		_p->SetMessage(root[i]);
	
		Post* p_cur =  new TwitterTweetDecorator( new TwitterReplyDecorator (_p)) ;
		if(pre != NULL){
			p_cur->SetPrevPost( pre );
			pre->SetNextPost(p_cur);
		}		
	
		p.push_back( p_cur  );
		pre = p_cur;
	}


	return p;
}
