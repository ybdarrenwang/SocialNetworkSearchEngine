#ifndef	SOCIALNET_H
#define SOCIALNET_H

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "Post.h"
#include "Message.h"

using namespace std;

class BasicQuery;
class AdvancedQuery;

/**
* This class SocialNet is a singleton AND a prototype manager.
* All the possibal concrete instances must be created by client code
* at program startup. The Instance() method is only responsible
* for cloneing existing instance, not creating one. Therefore
* the multi-thread problem can be avoided.
*/
class SocialNet
{
	public:
		virtual ~SocialNet(){}
		static SocialNet* Instance(string&);
		virtual SocialNet* Clone() = 0;
		virtual int Login(std::string&, std::string&) = 0;
		virtual vector<Post*> BasicSearch(BasicQuery*) = 0;
		virtual vector<Post*> AdvancedSearch(AdvancedQuery*) = 0;

	protected:
		SocialNet(string);
		static SocialNet* newSocialNet(string&);

	private:
		static SocialNet* instance;
		static map<string, SocialNet*> socialNetManager;
};

#endif
