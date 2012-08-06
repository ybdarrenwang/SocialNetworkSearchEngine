#ifndef TWITTERREPLYDECORATOR_H
#define TWITTERREPLYDECORATOR_H

#include "PostDecorator.h"
#include <stdio.h>
#include <fstream>

class TwitterReplyDecorator : public PostDecorator
{
	public:
		TwitterReplyDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
