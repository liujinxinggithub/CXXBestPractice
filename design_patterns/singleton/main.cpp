#include <iostream>
#include <dirent.h> //linux下使用头文件 <unistd.h>
#include <zconf.h>
#include <memory>
#include <cstring>
#include <vector>
#include "lazy.h"
#include "hunger.h"
#include <algorithm>

using namespace std;

int DayOfWeek() {
    return -1;
}

typedef struct XSTRUCT {
    int a;
} X;

// 判断瑞年
bool IsLeap(const int &year) {
    return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
}


//
bool StringToDate(const std::string &date, int &year, int &month, int &day) {
    year = atoi((date.substr(0, 4)).c_str());
    month = atoi((date.substr(5, 2)).c_str());
    day = atoi((date.substr(8, 2)).c_str());

    int Day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (IsLeap(year)) {
        Day[1] = 29;
    }

    return (year >= 0 && month <= 12 && month > 0 && day <= Day[month - 1] && day > 0);
}

// 给定日期是周几
int DayOfWeek(const std::string &date) {
    int day, month, year, week_day;
    if (!StringToDate(date, year, month, day)) {
        cout << "输入的日期格式有误" << endl;
        return -1;
    }
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    week_day = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;

    return week_day;
}

std::string DateAfterDays(const std::string &date, int days) {
    struct tm in;
    struct tm *time_in = &in;
    struct tm out;
    struct tm *time_out = &out;

    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
    time_in->tm_year = year - 1900;
    time_in->tm_mon = month - 1;
    time_in->tm_mday = day;
    time_in->tm_hour = 0;
    time_in->tm_min = 0;
    time_in->tm_sec = 0;
    time_in->tm_isdst = -1;

    time_t seconds = mktime(time_in);
    seconds += days * 60 * 60 * 24;
    time_out = localtime(&seconds);

    char date_after_days[32];
    memset(date_after_days, 0, sizeof(date_after_days));
    strftime(date_after_days, sizeof(date_after_days), "%Y-%m-%d", time_out);

    return date_after_days;
}

// 给定日期的周一日期
std::string DateOfMonday(const std::string &date) {
    int days = -DayOfWeek(date);
    std::string date_of_monday = DateAfterDays(date, days + 1);

    return date_of_monday;
}

int MonthsBetween2Date(const std::string &date1, const std::string &date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    if (!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2, month2, day2)) {
        std::cout << "输入的日期格式有误" << std::endl;
        return -1;
    }
    int result = 0;
    if (year1 == year2) {
        result = month1 > month2 ? month1 - month2 : month2 - month1;
        return result +1;
    } else {
        if (year1 > year2) {
            std::swap(year1, year2);
            std::swap(month1, month2);
        }

        int months1 = 12 - month1;
        int months2 = (year2 - year1 - 1) * 12;

        return months1 + months2 + month2 + 1;
    }
}

int DayOfMonth(const std::string &date) {
    int day, month, year, week_day;
    if (!StringToDate(date, year, month, day)) {
        std::cout << "输入的日期格式有误" << std::endl;
        return -1;
    }
    return month;
}

int Day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int DayInYear(const int &year, const int &month, const int &day) {
    int Day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = day;
    if (IsLeap(year)) {
        Day[1] = 29;
    }
    for (int i = 0; i < month - 1; ++i) {
        days += Day[i];
    }

    return days;
}

int DaysBetween2Date(const std::string &date1, const std::string &date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    if (!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2, month2, day2)) {
        cerr << "输入的日期格式有误";
        return -1;
    }
    if (year1 == year2 && month1 == month2) {
        return day1 > day2 ? day1 - day2 : day2 - day1;
    } else if (year1 == year2) {
        int day_in_year1, day_in_year2;
        day_in_year1 = DayInYear(year1, month1, day1);
        day_in_year2 = DayInYear(year2, month2, day2);
        return day_in_year1 > day_in_year2 ? day_in_year1 - day_in_year2 : day_in_year2 - day_in_year1;
    } else {
        if (year1 > year2) {
            std::swap(year1, year2);
            std::swap(month1, month2);
            std::swap(day1, day2);
        }
        int days1, days2, days3;
        if (IsLeap(year1)) {
            days1 = 366 - DayInYear(year1, month1, day1);
        } else {
            days1 = 365 - DayInYear(year1, month1, day1);
        }

        days2 = DayInYear(year2, month2, day2);

        days3 = 0;

        for (int year = year1 + 1; year < year2; year++) {
            if (IsLeap(year)) {
                days3 += 366;
            } else {
                days3 += 365;
            }
        }
        return days1 + days2 + days3;
    }
}

int main() {
    cout << "开始" << endl;
    {
        cout << DayOfWeek() << endl;
        auto hunger_instance1 = CSingletonHunger::GetInstance();
        CSingletonHunger::ReleaseInstance();
    }
    cout << "结束" << endl;
    int Day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    std::string start_time = "2020-01-01 00:00:00";
    std::string end_time = "2022-03-05 11:06:39";
    string x = DateAfterDays(start_time, 7000);
    cout << x << endl;
    cout << Day[30] << endl;

    return 0;
}



