#include "Date.hpp"

Date::Date(): time(0){}
Date::Date(const time_t time): time(time){}
Date::Date(const Date &other){ this -> copy(other); }

Date &Date::operator =(const Date &other){

    if(this != &other) this -> copy(other);
    return *this;

}

bool isLeapYear(const size_t year){ return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0); }

const char *Date::toString() const{

    char *result = new char[20];

    const u_int secondsInDay = 24 * 60 * 60;
    const u_short secondsInHour = 60 * 60;
    u_short daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    size_t daysTillNow = this -> time / secondsInDay;
    size_t extraTime = this -> time % secondsInDay + 3 * secondsInHour;
    size_t currYear = 1970;

    while(daysTillNow >= 365){

        daysTillNow -= isLeapYear(currYear) ? 366 : 365;
        currYear++;

    }

    s_int extraDays = daysTillNow + 1;
    bool flag = isLeapYear(currYear);
    daysOfMonth[1] = flag ? daysOfMonth[1] + 1 : daysOfMonth[1];

    size_t month = 0, index = 0;
    while(extraDays - daysOfMonth[index] >= 0){

        extraDays -= daysOfMonth[index];
        month++;
        index++;

    }

    size_t date;
    if(extraDays > 0){

        month++;
        date = extraDays;

    }
    else if(month == 2 && flag) date = 29;
        else date = daysOfMonth[month - 1];


    size_t hours = extraTime / secondsInHour % 24;
    size_t minutes = (extraTime % secondsInHour) / 60;
    size_t seconds = (extraTime % secondsInHour) % 60;

    result[0] = '0' + date / 10;
    result[1] = '0' + date % 10;
    result[2] = '/';
    result[3] = '0' + month / 10;
    result[4] = '0' + month % 10;
    result[5] = '/';
    result[6] = '0' + currYear / 1000;
    result[7] = '0' + (currYear / 100) % 10;
    result[8] = '0' + (currYear / 10) % 10;
    result[9] = '0' + currYear % 10;
    result[10] = ' ';
    result[11] = '0' + hours / 10;
    result[12] = '0' + hours % 10;
    result[13] = ':';
    result[14] = '0' + minutes / 10;
    result[15] = '0' + minutes % 10;
    result[16] = ':';
    result[17] = '0' + seconds / 10;
    result[18] = '0' + seconds % 10;
    result[19] = '\0';

    return result;

}

void Date::copy(const Date &other){ this -> time = other.time; }