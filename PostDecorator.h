#ifndef POSTDECORATOR_H
#define POSTDECORATOR_H

#include "Post.h"

class PostDecorator : public Post
{
	public:
		PostDecorator(Post* p){
			post=p;
			SetID(p->GetID());
		}
		virtual ~PostDecorator()
		{
			delete post;
		}
		virtual void PrintContent(ostream& os){post->PrintContent(os);}
		virtual void PrintOption(ostream& os){post->PrintOption(os);}
		virtual Post* ExecuteOption(string& option, Post* p){return post->ExecuteOption(option, p);}
		void SetPrevPost(Post* p){post->SetPrevPost(p);}
		void SetNextPost(Post* p){post->SetNextPost(p);}

	private:
		Post* post;
};

#endif
