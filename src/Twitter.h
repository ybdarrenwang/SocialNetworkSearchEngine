#ifndef TWITTER_H
#define TWITTER_H

#include "SocialNet.h"
#include "TwitterTweetDecorator.h"
#include "TwitterReplyDecorator.h"
#include "Message.h"
#include "Photo.h"
#include "BasicQuery.h"
#include "AdvancedQuery.h"
#include <stdio.h>
#include <fstream>

class Twitter : public SocialNet
{
	public:
		SocialNet* Clone() {return new Twitter(*this);}
		int Login(string& id, string& pwd);
		vector<Post*> BasicSearch(BasicQuery*);
		vector<Post*> AdvancedSearch(AdvancedQuery*);

	private:
		Twitter();
		static Twitter dummy;
};

#endif
