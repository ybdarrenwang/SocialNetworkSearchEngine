#ifndef TIME_H
#define TIME_H

class Time
{
	public:
		virtual ~Time(){}
		void SetYear(int y){year = y;}
		int GetYear(){return year;}
		void SetMonth(int m){month = m;}
		int GetMonth(){return month;}
		void SetDay(int d){day = d;}
		int GetDay(){return day;}
		void SetWeektime(string w){weektime = w;}
		string GetWeektime(){return weektime;}
		void SetHour(int h){hour = h;}
		int GetHour(){return hour;}
		void SetMinute(int m){minute = m;}
		int GetMinute(){return minute;}
		void SetSecond(int s){second = s;}
		int GetSecond(){return second;}
        
    friend std::ostream& operator<<(std::ostream& os, const Time& t){
        os << t.year << "-" << t.month << "-" << t.day << " " <<
            t.hour << ":" << t.minute << ":" << t.second << "  "
        << t.weektime;
        return os;
    }
    
	private:
		int year;
		int month;
		int day;
		string weektime;
		int hour;
		int minute;
		int second;
};

#endif
