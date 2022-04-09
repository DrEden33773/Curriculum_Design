#pragma once

#include "daily_health_check.h"
#include "province_information_manager.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// 需要维护的文件 => daily_health_check_file_location [这个是变量名]
class daily_health_check_user : public daily_health_check { // inherited from user_info_receiver
protected:
    void try_to_load_from_file(const string&); // 导入 健康打卡 文件 [弃用]
    void try_to_load_from_file_new(const string& input_sno); // 导入 健康打卡 文件 [启用]
    void write_to_file(const string&); // 写入 健康打卡 文件 [弃用]
    void write_to_file_new(); // 写入 健康打卡 文件 [启用]
    void show_province_info_direct(); // 显示 中高风险区 信息
    auto if_have_medium_and_high_risk_region_direct() -> bool; // 是否存在中高风险区

public:
    daily_health_check_user();
    void do_the_check(); // 进行 打卡
    inline void pre_push_lable()
    {
        cout << "您被强制要求进行健康打卡，但您还未打卡，系统即将自动跳转至打卡页面 >>> " << endl
             << endl;
        Sleep(350);
    }
    void show_check_status(); // 展示 打卡状态 [只在已经完成打卡后展示]
};
