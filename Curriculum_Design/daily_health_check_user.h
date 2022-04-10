#pragma once

#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// 需要维护的文件 => daily_health_check_file_location [这个是变量名]
class daily_health_check_user : public daily_health_check {
    // inherited from user_info_receiver
protected:
    void try_to_load_from_file(const string&); // 导入 健康打卡 文件 [弃用]
    void try_to_load_from_file_new(const string& input_sno); // 导入 健康打卡 文件 [启用]
    void write_to_file(const string&) const; // 写入 健康打卡 文件 [弃用]
    void write_to_file_new(); // 写入 健康打卡 文件 [启用]
    static void show_province_info_direct(); // 显示 中高风险区 信息
    static bool if_have_medium_and_high_risk_region_direct(); // 是否存在中高风险区

public:
    bool plug_of_if_should_alert;
    daily_health_check_user(); // 空构造函数
    daily_health_check_user(const string&, const string&, const string&); // 真构造函数
    daily_health_check_user(const string&, const string&, const string&, const string&); // 接口构造函数
    ~daily_health_check_user();
    void do_the_check(); // 进行 打卡
    static void pre_push_label()
    {
        cout << "您被强制要求进行健康打卡，但您还未打卡，系统即将自动跳转至打卡页面 >>> " << endl
            << endl;
        Sleep(350);
    }

    static string trans_bool(const bool& in)
    {
        return in ? "是" : "否";
    }

    void show_check_status() const; // 展示 打卡状态 [只在已经完成打卡后展示]
};
