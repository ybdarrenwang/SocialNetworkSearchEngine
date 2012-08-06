#ifndef	BASICQUERY_H
#define	BASICQUERY_H

#include "Query.h"

class Post;

class BasicQuery : public Query
{
	public:
		BasicQuery(SocialNet* n):Query(n){}
		virtual vector<Post*> Execute() {return receiver->BasicSearch(this);}
		virtual void InitQuery(User*)
		{
			cout<<"Enter the keyword you wanna search for: "<<endl<<"> ";
			cin>>keyword;
		}
};

#endif
