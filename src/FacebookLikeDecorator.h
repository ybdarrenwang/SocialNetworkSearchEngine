#ifndef FACEBOOKLIKEDECORATOR_H
#define FACEBOOKLIKEDECORATOR_H

#include "PostDecorator.h"

class FacebookLikeDecorator : public PostDecorator
{
	public:
		FacebookLikeDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
