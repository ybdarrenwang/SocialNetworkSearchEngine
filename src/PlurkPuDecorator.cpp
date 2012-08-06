#include "PlurkPuDecorator.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

void PlurkPuDecorator::PrintContent(ostream& os)
{
	PostDecorator::PrintContent(os);
}

void PlurkPuDecorator::PrintOption(ostream& os)
{
	os<<"- Pu this post [l]"<<endl;
	PostDecorator::PrintOption(os);
}

Post* PlurkPuDecorator::ExecuteOption(string& option, Post* p)
{
	if (option == "l")
	{
		char sys_call[1024] = {0};
		sprintf(sys_call, "python ./Plurk/Plurk_Query.py like %s",p->GetID().c_str());
		system(sys_call);

		cout<<"You pued this post!"<<endl<<"> ";
		return p;

	}
	else
		return PostDecorator::ExecuteOption(option, p);
}
