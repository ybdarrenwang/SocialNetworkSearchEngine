#include "Message.h"
#include <string>

using namespace std;

void Message::PrintContent(ostream& os)
{
	os<<"------------------------------------------"<<endl;

	os << author << endl << endl;
	os << content << endl << endl;
    os << createTime << endl;
	
    os<<"------------------------------------------"<<endl; 
    os<<"Whats next?"<<endl;
}

void Message::PrintOption(ostream& os)
{
	if (prevPost != 0)
		os<<"- Go to previous post [p]"<<endl;
	if (nextPost != 0)
		os<<"- Go to next post [n]"<<endl;
	os<<"- Quit browsing [q]"<<endl<<"> ";
}

Post* Message::ExecuteOption(string& option, Post* p)
{
	if (option == "p" && prevPost != 0) return prevPost;
	else if (option == "n" && nextPost != 0) return nextPost;
	else if (option == "q") return 0;
	else return p;
}


void Message::SetMessage(Json::Value &root)
{
	author = root["user_name"].asString();
	content = root["content"].asString();
	SetID(root["id"].asString());

	createTime.SetYear(root["time"]["year"].asInt());
	createTime.SetMonth(root["time"]["month"].asInt());
	createTime.SetDay(root["time"]["day"].asInt());
	createTime.SetHour(root["time"]["hour"].asInt());
	createTime.SetMinute(root["time"]["minute"].asInt());
	createTime.SetSecond(root["time"]["second"].asInt());
	createTime.SetWeektime(root["time"]["week_day"].asString());
}
