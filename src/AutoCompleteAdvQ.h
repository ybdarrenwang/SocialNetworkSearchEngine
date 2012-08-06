#ifndef AUTOCOMPLETEADVQ
#define AUTOCOMPLETEADVQ

#include "AdvancedQuery.h"

/**
* This class is for overridding AdvancedQuery::InitQuery
*/
class AutoCompleteAdvQ : public AdvancedQuery
{
	public:
		AutoCompleteAdvQ(SocialNet* n):AdvancedQuery(n){}
		void InitQuery(User*);
		void GetAutoCompleteList(string&, vector<Query*>&, vector<string>&);
		void GetAutoCompleteList(string&, vector<string>&, vector<string>&);
};

#endif
