#include "User.h"
#include "SocialNet.h"
#include "Facebook.h"
#include "Twitter.h"
#include "Query.h"
#include "BasicQuery.h"
#include "AutoCompleteBasicQ.h"
#include "AutoCompleteAdvQ.h"
#include "AdvancedQuery.h"
#include "Post.h"
#include "Message.h"
#include "Photo.h"

std::map<string, SocialNet*> SocialNet::socialNetManager;
Twitter Twitter::dummy;
Facebook Facebook::dummy;
User User::instance;

SocialNet* ChooseSocialNet()
{
	string socialNetName;
	cout<<"Enter \"Facebook\" or \"Twitter\" to begin, or \"exit\" to quit: "<<endl<<"> ";
	cin>>socialNetName;
	if (socialNetName == "exit") return 0;
	else return SocialNet::Instance(socialNetName);
}

Query* ChooseQueryMode(SocialNet* n)
{
	int mode = 0;
	while (mode!=1 && mode!=2)
	{
		cout<<"Choose query mode (1.Basic, 2.Advanced): "<<endl<<"> ";
		cin>>mode;
	}
	if (mode == 1)
		return new AutoCompleteBasicQ(n);
//		return new BasicQuery(n);
	else
		return new AutoCompleteAdvQ(n);
//		return new AdvancedQuery(n);
}

int main()
{
	User* user = User::Instance();
	SocialNet* socialNet;
	while(true)
	{
		socialNet = ChooseSocialNet();
		if (socialNet != 0)
		{
			user->InitUser();
			if (user->Login(socialNet))
				cout<<"Login failed"<<endl;
			else
			{
				cout<<"Login succeeded"<<endl;
				while (user->WantContinue())
				{
					Query* query = ChooseQueryMode(socialNet);
					user->Search(query);
					user->InteractWithPosts();
				}
				user->Logout(socialNet);
			}
		}
		else
			break;
	}
	return 0;
}
