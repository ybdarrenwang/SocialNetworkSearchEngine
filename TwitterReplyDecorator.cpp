#include "TwitterReplyDecorator.h"
#include <stdio.h>
#include <stdlib.h>

void TwitterReplyDecorator::PrintContent(ostream& os)
{
	PostDecorator::PrintContent(os);
}

void TwitterReplyDecorator::PrintOption(ostream& os)
{
	os<<"- Reply this post [r]"<<endl;
	PostDecorator::PrintOption(os);
}

Post* TwitterReplyDecorator::ExecuteOption(string& option, Post* p)
{
	if (option == "r")
	{
		string content;
		cout << "What do you want to reply" << endl;
		getchar();
		getline(cin, content);
		
		ofstream fout("reply");
		fout << content;
		fout.close();

		char sys_call[1024] = {0};
		sprintf(sys_call, "python ./Twitter/Twitter_Query.py reply %s", p->GetID().c_str() );	
        system(sys_call);
        
        cout<<"You replied this post!"<<endl<<"> ";
 
		return p;
	}
	else
		return PostDecorator::ExecuteOption(option, p);
}
