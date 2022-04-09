#define _CRT_SECURE_NO_WARNINGS
#include "time_manager.h"
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

bool time_manager::if_leap_year_in_class(const time_manager* input)
{
    bool status_1 = input->dtime->year % 4 == 0 && input->dtime->year % 100 != 0;
    bool status_2 = input->dtime->year % 400 == 0;
    return (status_1 || status_2);
}

bool if_leap_year(const int& year)
{
    bool status_1 = year % 4 == 0 && year % 100 != 0;
    bool status_2 = year % 400 == 0;
    return (status_1 || status_2);
}

bool time_manager::if_reach_the_end_of_month(const time_manager* input)
{
    bool result;
    if (input->dtime->month == 1 || input->dtime->month == 3 || input->dtime->month == 5 || input->dtime->month == 7 || input->dtime->month == 8 || input->dtime->month == 10 || input->dtime->month == 12) {
        result = (input->dtime->day == 31) ? true : false;
    } else if (input->dtime->month == 2) {
        if (if_leap_year_in_class(input)) {
            result = (input->dtime->day == 29) ? true : false;
        } else {
            result = (input->dtime->day == 28) ? true : false;
        }
    } else {
        result = (input->dtime->day == 30) ? true : false;
    }
    return result;
}

bool time_manager::if_reach_the_end_of_year(const time_manager* input)
{
    bool result;
    result = (input->dtime->month == 12 && input->dtime->day == 31) ? true : false;
    return result;
}

bool time_manager::if_reach_the_start_of_month(const time_manager* input)
{
    bool result;
    result = (input->dtime->day == 1) ? true : false;
    return result;
}

bool time_manager::if_reach_the_start_of_year(const time_manager* input)
{
    bool result;
    result = (input->dtime->month == 1 && input->dtime->day == 1) ? true : false;
    return result;
}

time_manager time_manager::update_date()
{
    if (if_reach_the_end_of_month(this)) {
        if (if_reach_the_end_of_year(this)) {
            this->dtime->day = 1;
            this->dtime->month = 1;
            ++this->dtime->year;
        } else {
            this->dtime->day = 1;
            ++this->dtime->month;
        }
    } else {
        ++this->dtime->day;
    }
    return *this;
}

time_manager time_manager::update_date_minus()
{
    if (if_reach_the_start_of_month(this)) {
        if (if_reach_the_start_of_year(this)) {
            this->dtime->day = 1;
            this->dtime->month = 1;
            --this->dtime->year;
        } else {
            this->dtime->day = 1;
            --this->dtime->month;
        }
    } else {
        --this->dtime->day;
    }
    return *this;
}

void time_manager::sync_system_time() // 感谢 "菜鸟教程" 网的精品示例，真的特别棒！狠狠地爱住了！
{
    // 同步系统时间
    time_t now = time(0); // 基于当前系统的当前日期/时间
    // cout << "1970 到目前经过秒数:" << now << endl;
    tm* ltm = localtime(&now);
    // 输出 tm 结构的各个组成部分
    // cout << "年: " << 1900 + ltm->tm_year << endl;
    // cout << "月: " << 1 + ltm->tm_mon << endl;
    // cout << "日: " << ltm->tm_mday << endl;
    // cout << "时间: " << ltm->tm_hour << ":";
    // cout << ltm->tm_min << ":";
    // cout << ltm->tm_sec << endl;
    this->dtime->year = 1900 + ltm->tm_year;
    this->dtime->month = 1 + ltm->tm_mon;
    this->dtime->day = ltm->tm_mday;
    // 比较离谱的一个函数，因为ctime这头文件比较离谱
}

string time_manager::time_str()
{
    char res[10] = { '\0' }; // 预计的输出格式 => 2022-04-08
    for (char i : res) {
        i = '\0';
    }
    char temp[8] = { '\0' }; // 80402202 need to be reversed
    for (char i : temp) {
        i = '\0';
    }
    char revd[8] = { '\0' }; // reversed to 20220408
    for (char i : revd) {
        i = '\0';
    }
    // tnum
    int tnum = dtime->year * 10000 + dtime->month * 100 + dtime->day;
    // push into temp
    for (char i : temp) {
        i = tnum % 10;
        tnum /= 10;
    }

    int pos, pos_rev, pos_res;

    // push into revd
    for (pos = 9, pos_rev = 0; pos >= 0; --pos, ++pos_rev) {
        revd[pos_rev] = temp[pos];
    }
    // push into res
    for (pos_rev = 0, pos_res = 0; pos_rev < 4; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    res[pos_res++] = '-';
    for (; pos_rev < 6; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    res[pos_res++] = '-';
    for (; pos_rev < 8; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    // end
    string result = res;
    return result;
}

time_manager::time_manager()
{
    dtime = new defined_time;
    //无参 => 直接同步系统时间
    sync_system_time();
}

// 日期初始化
time_manager::time_manager(int& year, int& month, int& day)
{
    dtime = new defined_time;
    this->dtime->year = year;
    this->dtime->month = month;
    this->dtime->day = day;
}

time_manager time_manager::operator+=(const int& n)
{
    for (int i = 0; i < n; ++i) {
        update_date();
    }
    return *this;
}

time_manager time_manager::operator-=(const int& n)
{
    for (int i = 0; i < n; ++i) {
        update_date_minus();
    }
    return *this;
}

time_manager time_manager::operator++() // ++time_manager
{
    return update_date();
}

time_manager time_manager::operator--()
{
    return update_date_minus();
}

time_manager time_manager::operator++(int any) // time_manager++
{
    time_manager result = *this;
    update_date(); // update 最终更改的 只是 this 指向的 [当前对象]
    // 但是这里 result 并不是 *this 的引用，无法被更改，因此返回的是未被更改之前的 [对象]
    // 这个恰好符合 后置++ 的 原来意思
    return result;
}

time_manager time_manager::operator--(int any)
{
    time_manager result = *this;
    update_date_minus();
    return result;
}

int operator-(const time_manager& date1, const time_manager& date2)
{
    // 此时, 无需验证日期有效性 [所有的日期，都是同步系统时间的，必然是有效的]

    // 特殊情况
    if (date1 == date2) {
        return 0;
    }
    bool if_result_smaller_than_zero = false;
    time_manager big, small;
    int result = 0;
    // 映射大小关系
    if (date1 > date2) {
        big = date1;
        small = date2;
        if_result_smaller_than_zero = false;
    } else {
        big = date2;
        small = date1;
        if_result_smaller_than_zero = true;
    }
    /* ------------------------CORE------------------------ */
    // 半遍历年
    for (int i = small.dtime->year; i < big.dtime->year; ++i) {
        if (if_leap_year(i)) {
            result += 366;
        } else {
            result += 365;
        }
    }
    // 半遍历 大年 的月
    for (int i = 1; i < big.dtime->month; ++i) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            result += 31;
        } else if (i == 2) {
            result += (if_leap_year(big.dtime->year)) ? 29 : 28;
        } else {
            result += 30;
        }
    }
    // 半遍历 小年 的月
    for (int i = 1; i < small.dtime->month; ++i) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            result -= 31;
        } else if (i == 2) {
            result -= (if_leap_year(small.dtime->year)) ? 29 : 28;
        } else {
            result -= 30;
        }
    }
    result += big.dtime->day;
    result -= small.dtime->day;
    /* ------------------------END OF CORE------------------------ */
    result = (if_result_smaller_than_zero) ? ((-1) * result) : ((1) * result);
    return result;
}

bool operator==(const time_manager& a, const time_manager& b)
{
    bool result = (a.dtime->year == b.dtime->year) && (a.dtime->month == b.dtime->month) && (a.dtime->day == b.dtime->day);
    return result;
}

bool operator>(const time_manager& a, const time_manager& b)
{
    bool result = false;
    if (a.dtime->year > b.dtime->year) {
        result = true;
    } else if (a.dtime->month > b.dtime->month) {
        result = true;
    } else if (a.dtime->day > b.dtime->day) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

bool operator<(const time_manager& a, const time_manager& b)
{
    bool result = false;
    if (a.dtime->year < b.dtime->year) {
        result = true;
    } else if (a.dtime->month < b.dtime->month) {
        result = true;
    } else if (a.dtime->day < b.dtime->day) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

ostream& operator<<(ostream& out, const time_manager& t)
{
    out << t.dtime->year << "年" << t.dtime->month << "月" << t.dtime->day << "日";
    return out;
}