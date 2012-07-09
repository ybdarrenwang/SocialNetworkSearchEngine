#ifndef PHOTO_H
#define PHOTO_H

#include "Post.h"
#include "Time.h"

class Photo : public Post
{
	public:
		virtual ~Photo(){}
		void PrintContent(ostream&);
		void PrintOption(ostream&);
		Post* ExecuteOption(string&, Post*);
		void SetPrevPost(Post* p){prevPost = p;}
		void SetNextPost(Post* p){nextPost = p;}

	private:
		string author;
		Time createTime;
		Time updateTime;
		string content;
		string link;
};

#endif
