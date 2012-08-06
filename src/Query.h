#ifndef	QUERY_H
#define	QUERY_H

#include "SocialNet.h"

class User;
class Post;

/**
* This class Query is a Command pattern, and the base class
* of different kinds of query involking different kinds of 
* search algorithm.(e.g. basic, advanced etc.).\n
* And also a QueryDecorator can be added to override
* original methods, for example enable auto-complete while
* query initialization.
*/
class Query
{
	public:
		Query(SocialNet* n)
		{
			receiver = n;
			keyword = "";
			person = "";
		}
		virtual ~Query(){}
		virtual void InitQuery(User*) = 0;
		virtual vector<Post*> Execute() = 0;
		virtual void SetKeyword(string& k){keyword = k;}
		virtual string GetKeyword(){return keyword;}
		virtual void SetPerson(string& k){person = k;}
		virtual string GetPerson(){return person;}

	protected:
		SocialNet* receiver;
		string keyword;
		string person;
};

#endif
