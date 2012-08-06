#ifndef MESSAGE_H
#define MESSAGE_H

#include "Post.h"
#include "Time.h"

class Message : public Post
{
	public:
		virtual ~Message(){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
		void SetPrevPost(Post* p){prevPost = p;}
		void SetNextPost(Post* p){nextPost = p;}

		void SetMessage(Json::Value &root);

	private:
		string author;
		Time createTime;
		Time updateTime;
		string content;
		string link;
};

#endif
