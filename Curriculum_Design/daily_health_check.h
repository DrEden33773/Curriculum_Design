#pragma once

#include "user_AccountInfoReceiver.h"
#include "time_manager.h"

// 健康打卡 的 用户端/管理员端 共同维护 同一个 二进制文件
class daily_health_check : public user_info_receiver {
public: // 这里是为了方便以后 “修改文件” 才设置成的 public
    const string daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\daily_health_check_list.dat)";
    const string temp_daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_daily_health_check_list.dat)";
    const string name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\unchecked_list_)";
    const string temp_name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_unchecked_list_)"; // 冗余
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    string today_unchecked_file_location = name_base; // 未打卡名单地址，根据当天日期动态变化 // 用到name_base
    string temp_today_unchecked_file_location = temp_name_base; // 未打卡名单地址，根据当天日期动态变化 // 用到temp_name_base
    const string time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\time_dictionary.dat)";
    const string temp_time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_time_dictionary.dat)";

protected:
    time_manager current_time; // 当前时间，栈变量即可，这样方便运算符重载
    time_manager time_dict_tail_checker; // 时间索引最后一项的检测器，栈变量即可，这样方便运算符重载
    bool if_daily_check_file_is_empty;
    bool if_time_dictionary_file_is_empty;
    using dict_checker = struct dict_checker { // 检查 时间索引 是否为空 的结构体
        int year;
        int month;
        int day;
    };
    dict_checker* time_dict_checker = nullptr; // 检查 时间索引 是否为空 的 变量
    using health_check_info = struct health_check_info { // 这里借用 C++11现代特性：类/结构体 内部初始化
        bool if_check_is_necessary = false; // 默认不需要强制打卡
        bool if_checked = false; // 默认未进行打卡
        //
        string account_id; // 用户名
        string student_id; // 学号
        string student_name; // 姓名
        //
        bool if_returned_school = true; // 是否返校
        bool if_is_accomodated = true; // 是否住校
        bool if_passed_by_high_risk_regions = false; // 有无经过高风险区
        bool if_passed_by_midium_risk_regions = false; // 有无经过中风险区
        bool if_temperature_higher_than_37 = false; // 体温是否高于37℃
        bool if_go_abroad = false; // 是否有出国旅居史
    };
    health_check_info* current_health_check_info = nullptr; // 被使用的存储信息
    health_check_info* cached_health_check_info = nullptr; // 缓存 => 遍历的时候用
    health_check_info* checker = nullptr;
    daily_health_check();
    /// function
    inline void make_sure_file_exists();
    auto check_if_file_is_empty() -> bool;
    void make_sure_dictionary_exists();
    auto check_if_dictionary_is_empty() -> bool;
};
