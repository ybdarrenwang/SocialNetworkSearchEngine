#ifndef POST_H
#define POST_H
#include "json.h"
#include <iostream>

using namespace std;

/**
* This class Post is the base class of all kinds of posts
* (e.g. Message, Photo, etc.). And also a PostDecorator
* can be added to give this Post extra function (e.g. Reply, Like, etc.)
*/
class Post
{
	public:
		Post(){prevPost = 0; nextPost = 0;}
		virtual ~Post(){}
		virtual void PrintContent(ostream&) = 0;
		virtual void PrintOption(ostream&) = 0;
		virtual Post* ExecuteOption(string&, Post*) = 0; ///< return the pointer to the previous or next Post
		virtual void SetPrevPost(Post*) = 0;
		virtual void SetNextPost(Post*) = 0;
		virtual string GetID() {return id;};
		virtual void SetID(string _id) {id = _id;}

	protected:
		Post* prevPost;
		Post* nextPost;
		string id;
};

#endif
