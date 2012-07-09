#include "TwitterTeDecorator.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

void TwitterTeDecorator::PrintContent(ostream& os)
{
	PostDecorator::PrintContent(os);
}

void TwitterTeDecorator::PrintOption(ostream& os)
{
	os<<"- like this post [l]"<<endl;
	PostDecorator::PrintOption(os);
}

Post* TwitterTeDecorator::ExecuteOption(string& option, Post* p)
{
	if (option == "l")
	{
		char sys_call[1024] = {0};
		sprintf(sys_call, "python ./Twitter/Twitter_Query.py like %s",p->GetID().c_str());
		system(sys_call);

		cout<<"You like this post!"<<endl<<"> ";
		return p;

	}
	else
		return PostDecorator::ExecuteOption(option, p);
}
