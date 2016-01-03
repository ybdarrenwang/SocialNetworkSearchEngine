#ifndef FACEBOOKREPLYDECORATOR_H
#define FACEBOOKREPLYDECORATOR_H

#include "PostDecorator.h"
#include <stdio.h>
#include <fstream>

class FacebookReplyDecorator : public PostDecorator
{
	public:
		FacebookReplyDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
