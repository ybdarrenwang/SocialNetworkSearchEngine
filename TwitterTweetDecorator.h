#ifndef TWITTERTWEETDECORATOR_H
#define TWITTERTWEETDECORATOR_H

#include "PostDecorator.h"

class TwitterTweetDecorator : public PostDecorator
{
	public:
		TwitterTweetDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
