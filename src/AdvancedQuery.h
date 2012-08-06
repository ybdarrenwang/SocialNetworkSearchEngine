#ifndef	ADVANCEDQUERY_H
#define	ADVANCEDQUERY_H

#include "Query.h"

class Post;

class AdvancedQuery : public Query
{
	public:
		AdvancedQuery(SocialNet* n):Query(n){}
		virtual vector<Post*> Execute() {return receiver->AdvancedSearch(this);}
		virtual void InitQuery(User*)
		{
			cout<<"Enter the keyword you wanna search for (enter * if unlimited): "<<endl<<"> ";
			cin>>keyword;
			cout<<"Enter the person you wanna search for (enter * if unlimited): "<<endl<<"> ";
			cin>>person;
		}
};

#endif
