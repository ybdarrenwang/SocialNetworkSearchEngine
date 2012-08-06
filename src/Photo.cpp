#include "Photo.h"
#include <string>

using namespace std;

void Photo::PrintContent(ostream& os)
{
	os<<"Photo printed!"<<endl;
	os<<"Whats next?"<<endl;
}

void Photo::PrintOption(ostream& os)
{
	if (prevPost != 0)
		os<<"- Go to previous post [p]"<<endl;
	if (nextPost != 0)
		os<<"- Go to next post [n]"<<endl;
	os<<"- Quit browsing [q]"<<endl;
}

Post* Photo::ExecuteOption(string& option, Post* p)
{
	if (option == "p" && prevPost != 0) return prevPost;
	else if (option == "n" && nextPost != 0) return nextPost;
	else if (option == "q") return 0;
	else return p;
}
