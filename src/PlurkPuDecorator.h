#ifndef PLURKPUDECORATOR_H
#define PLURKPUDECORATOR_H

#include "PostDecorator.h"

class PlurkPuDecorator : public PostDecorator
{
	public:
		PlurkPuDecorator(Post* p):PostDecorator(p){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
};

#endif
