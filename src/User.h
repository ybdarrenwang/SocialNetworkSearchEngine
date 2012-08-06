#ifndef USER_H
#define USER_H

#include "SocialNet.h"
#include "Query.h"
#include "Post.h"
#include <vector>

#define MAXHISTORYLOGSIZE 100
using namespace std;

/**
* This class User is a singleton, which is instanciated while program startup.
*/
class User
{
	public:
		~User();
		static User* Instance();
		void InitUser();
		int Login(SocialNet*);
		bool WantContinue();
		void Search(Query*);
		vector<string>& GetFriends(){return friends;}
		vector<Query*>& GetQueryHistory(){return queryHistory;}
		void AddQueryHistory(Query* q){queryHistory.push_back(q);}
		void InteractWithPosts();
		int Logout(SocialNet*);

	protected:
		User();

	private:
		static User instance;
		string id;
		string pwd;
		vector<string> friends;
		vector<Query*> queryHistory;
		vector<Post*> relevantPosts; ///< search results
};

#endif
