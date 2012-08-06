#ifndef TWITTERTEDECORATOR_H
#define TWITTERTEDECORATOR_H

#include "PostDecorator.h"

class TwitterTeDecorator : public PostDecorator
{
	public:
		TwitterTeDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
