#ifndef PLURKREPLYDECORATOR_H
#define PLURKREPLYDECORATOR_H

#include "PostDecorator.h"
#include <stdio.h>
#include <fstream>

class PlurkReplyDecorator : public PostDecorator
{
	public:
		PlurkReplyDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
