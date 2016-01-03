#ifndef FACEBOOK_H
#define FACEBOOK_H

#include "SocialNet.h"
#include "FacebookLikeDecorator.h"
#include "FacebookReplyDecorator.h"
#include "Message.h"
#include "Photo.h"
#include "BasicQuery.h"
#include "AdvancedQuery.h"
#include <stdio.h>
#include <fstream>

class Facebook : public SocialNet
{
	public:
		SocialNet* Clone() {return new Facebook(*this);}
		int Login(string& id, string& pwd);
		vector<Post*> BasicSearch(BasicQuery*);
		vector<Post*> AdvancedSearch(AdvancedQuery*);

	private:
		Facebook();
		static Facebook dummy;
};

#endif
