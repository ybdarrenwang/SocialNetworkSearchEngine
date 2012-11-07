#include "SocialNet.h"

SocialNet* SocialNet::instance = 0;

SocialNet* SocialNet::newSocialNet(string& net)
{
	map<string, SocialNet*>::iterator i = socialNetManager.find(net);

	if (i==socialNetManager.end())
	{
		cerr<<"Unrecognizable social network name ("<<net<<")"<<endl;
		return 0;
	}
	else
	{
		return i->second->Clone();
	}
}

SocialNet::SocialNet(string net)
{
	cout<<"Initializing "<<net<<endl;
	socialNetManager.insert(make_pair(net, this));
}

SocialNet* SocialNet::Instance(string& net)
{
	instance = newSocialNet(net);
	return instance;
}
