#ifndef PLURK_H
#define PLURK_H

#include "SocialNet.h"
#include "PlurkPuDecorator.h"
#include "PlurkReplyDecorator.h"
#include "Message.h"
#include "Photo.h"
#include "BasicQuery.h"
#include "AdvancedQuery.h"
#include <fstream>

class Plurk : public SocialNet
{
	public:
		SocialNet* Clone() {return new Plurk(*this);}
		int Login(string& id, string& pwd);
		vector<Post*> BasicSearch(BasicQuery*);
		vector<Post*> AdvancedSearch(AdvancedQuery*);

	private:
		Plurk();
		static Plurk dummy;
};

#endif
