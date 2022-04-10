#pragma once

#include <string>
using namespace std;

class user_interface {
protected:
    string c_account; // 用户名
    string real_name; // 真名
    string student_number; // 学号
    string dorm_number; // 宿舍号
    inline void show_current_user_info() const; // 展示当前用户信息
    inline void goto_daily_check() const; // 前往每日打卡
    inline void goto_nat_check() const; // 前往核酸检测
    inline void goto_necessary_affairs_check(const bool&) const; // 前往待办事项管理平台[可指定是否催促完成]

public:
    user_interface() = default; // 空构造函数
    user_interface(const string&, const string&, const string&, const string&); // 真构造函数
    void shell_of_user_interface() const; //
    string return_c_account(); // 返回用户名
    string return_real_name(); // 返回真名
    string return_student_number(); // 返回学号
};
