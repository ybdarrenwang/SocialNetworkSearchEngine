#include "FacebookLikeDecorator.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

void FacebookLikeDecorator::PrintContent(ostream& os)
{
	PostDecorator::PrintContent(os);
}

void FacebookLikeDecorator::PrintOption(ostream& os)
{
	os<<"- like this post [l]"<<endl;
	PostDecorator::PrintOption(os);
}

Post* FacebookLikeDecorator::ExecuteOption(string& option, Post* p)
{
	if (option == "l")
	{
		char sys_call[1024] = {0};
		sprintf(sys_call, "python ./Facebook/Facebook_Query.py --like %s",p->GetID().c_str());
		system(sys_call);

		cout<<"You like this post!"<<endl<<"> ";
		return p;

	}
	else
		return PostDecorator::ExecuteOption(option, p);
}
