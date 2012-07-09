#ifndef AUTOCOMPLETEBASICQ
#define AUTOCOMPLETEBASICQ

#include "BasicQuery.h"

/**
* This class is for overridding BasicQuery::InitQuery
*/
class AutoCompleteBasicQ : public BasicQuery
{
	public:
		AutoCompleteBasicQ(SocialNet* n):BasicQuery(n){}
		void InitQuery(User*);
		void GetAutoCompleteList(string&, vector<Query*>&, vector<string>&);
};

#endif
