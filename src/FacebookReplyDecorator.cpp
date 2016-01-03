#include "FacebookReplyDecorator.h"
#include <stdio.h>
#include <stdlib.h>

void FacebookReplyDecorator::PrintContent(ostream& os)
{
	PostDecorator::PrintContent(os);
}

void FacebookReplyDecorator::PrintOption(ostream& os)
{
	os<<"- Reply this post [r]"<<endl;
	PostDecorator::PrintOption(os);
}

Post* FacebookReplyDecorator::ExecuteOption(string& option, Post* p)
{
	if (option == "r")
	{
		string content;
		cout << "What do you want to reply" << endl;
		getchar();
		getline(cin, content);
		
		ofstream fout("log/facebook/reply.txt");
		fout << content;
		fout.close();

		char sys_call[1024] = {0};
		sprintf(sys_call, "python ./Facebook/Facebook_Query.py --reply %s", p->GetID().c_str() );	
        system(sys_call);
        
        cout<<"You replied this post!"<<endl<<"> ";
 
		return p;
	}
	else
		return PostDecorator::ExecuteOption(option, p);
}
