#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;

class necessary_affairs_manager {
    // only accessible for __USER__ account
protected:
    string account; // 用户名
    string real_name; // 真名
    string student_number; // 学号
    string dorm_number; // 宿舍号
    bool if_push_to_finish;
    bool if_finished_daily_check;
    bool if_finished_all_nat_check_no_later_than_today;
    /* functions */
    inline void show_unfinished_tasks() const;
    void check_if_finished_daily_check();
    void check_if_finished_all_nat_check();
    void unfinished_tasks_management();

public:
    necessary_affairs_manager(
        const string& account,
        const string& real_name,
        const string& student_number,
        const string& dorm_number,
        const bool& if_push_to_finish);
};
