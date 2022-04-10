#pragma once

#include <string>
using namespace std;

class admin_interface {
protected:
    string c_account;
    // 前往 province_info_manager 模块 (省级行政区疫情风险信息管理模块)
    static inline void goto_province_info_manager(); 
    // 显示 当前用户信息
    inline void show_current_user_info() const;
    // 前往 核算信息管理 模块
    static inline void goto_nat_admin();
    // 前往 每日健康打卡管理 模块
    static inline void goto_daily_health_check_admin();
    // 前往 普通用户信息管理 模块
    static inline void goto_account_info_manager();

public:
    admin_interface() = default; // empty constructor
    admin_interface(const string&); // useful constructor
    void shell_of_admin_interface() const;
    string return_c_account(); // returns the account name
};
