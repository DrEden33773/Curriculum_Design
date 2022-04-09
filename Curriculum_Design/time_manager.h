#pragma once

#include <iostream>
using namespace std;

class time_manager {
private:
    using defined_time = struct defined_time {
        int year;
        int month;
        int day;
    };
    defined_time* dtime; // 子封装

protected:
    bool if_leap_year_in_class(const time_manager*); // 判断是否为闰年
    bool if_reach_the_end_of_month(const time_manager*); // if reach the end of month, return true
    bool if_reach_the_end_of_year(const time_manager*); // if reach the end of year, return true
    bool if_reach_the_start_of_month(const time_manager*); // if reach the start of month, return true
    bool if_reach_the_start_of_year(const time_manager*); // if reach the start of year, return true
    time_manager update_date(); // 更新日期--往后加一天
    time_manager update_date_minus(); // 更新日期--往前减一天
    void sync_system_time(); // 同步系统时间

public:
    time_manager(); // 无参情况下 => 同步系统时间
    time_manager(int&, int&, int&); // 日期初始化函数
    friend int operator-(const time_manager&, const time_manager&); // 返回两日期之差 [看看需不需要绝对值]
    time_manager operator+=(const int&); // 日期往后加n天
    time_manager operator-=(const int&); // 日期往前加n天
    time_manager operator++(); // 前置++
    time_manager operator--(); // 前置--
    time_manager operator++(int); // 后置++
    time_manager operator--(int); // 后置--
    friend bool operator==(const time_manager&, const time_manager&); // 比较两日期是否相等
    friend bool operator>(const time_manager&, const time_manager&); // 比较两日期大小(比大)
    friend bool operator<(const time_manager&, const time_manager&); // 比较两日期大小(比小)
    friend ostream& operator<<(ostream&, const time_manager&); // 输出日期
    string time_str(); // 转换成字符格式
};