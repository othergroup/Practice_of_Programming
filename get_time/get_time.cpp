#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<QDate>
#include<QTime>
bool is_leap(int year){return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);}
int trans(string s)
{
    int ret=0;
    for(int i=0;i<s.length();i++)
    {
        ret*=10;
        ret+=(s[i]-'0');    
    }
    return ret;
}
int get_time_difference(string s)
{
    int monthDays[13][2]={{0,0},{31,31},{28,29},{30,30},{31,31},{30,30},{31,31},{30,30},{31,31},{30,30},{31,31},{30,30},{31,31}};
    QDate date(QDate::currentDate());
    QTime time(QTime::currentTime());
    int year=date.year(),month=date.month(),day=date.day();
    int year_t=0,month_t=0,day_t=0;
    for(int i=0;i<3;i++)
    {
        string::size_type pos=s.find("-");
        if(pos==s.npos)
        {
            day_t=trans(s);
            break;
        }
        string sub=s.substr(0,pos);
        s.erase(0,pos+1);
        if(i==0)
            year_t=trans(sub);
        else if(i==1)
            month_t=trans(sub);
    }
    int num=0;
    while(year<year_t||month<month_t||day<day_t)
    {
        day++;
        num++;
        if(day==monthDays[month][is_leap(year)]+1)
        {
            day=1;
            month++;
            num_month++;
            num_day=0;
        }
        if(month==13)
        {
            num_year++;
            num_month=0;
            year++;
            month=1;
        }
    }
    return num;
}
vector<int> query(vector<string> shedule)
{
    /*shedule[i]的格式应是年-月-日，返回距离ddl还有多少天*/
    vector<int> ret(shedule.size());
    for(int i=0;i<shedule.size();i++)
    {
        ret[i]=get_time_difference(shedule[i]);
    }
    return ret;
}