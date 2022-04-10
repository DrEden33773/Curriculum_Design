// 重构完成

// ReSharper disable CppClangTidyBugproneReservedIdentifier
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "time_manager.h"
#include "user_AccountInfoReceiver.h"

// 健康打卡 的 用户端/管理员端 共同维护 同一个 二进制文件
class daily_health_check : public user_info_receiver {
public: // 这里是为了方便以后 “修改文件” 才设置成的 public
    const string daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\daily_health_check_list.dat)";
    const string temp_daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_daily_health_check_list.dat)";
    const string name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\unchecked_list_)";
    const string temp_name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_unchecked_list_)"; // 冗余
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    string today_unchecked_file_location; // = name_base // 未打卡名单地址，根据当天日期动态变化 // 用到 name_base
    string temp_today_unchecked_file_location; // = temp_name_base // 未打卡名单地址，根据当天日期动态变化 // 用到 temp_name_base
    const string time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\time_dictionary.dat)";
    const string temp_time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_time_dictionary.dat)";

protected:
    time_manager current_time; // 当前时间，栈变量即可，这样方便运算符重载
    time_manager time_dict_tail_checker; // 时间索引最后一项的检测器，栈变量即可，这样方便运算符重载
    time_manager cached_time; // 子类--管理员端 执行 自动删除 任务的时候 会用到
    bool if_daily_check_file_is_empty {};
    bool if_time_dictionary_file_is_empty {};

    class dict_checker {
        // 检查 时间索引 是否为空 的结构体
    public:
        int year;
        int month;
        int day;
    };
    dict_checker* time_dict_checker {}; // 检查 时间索引 是否为空 的 变量

public:
    class health_check_info_trans;
    class health_check_info {
    public:
        time_manager record_time; // 记录 health_check_info 的时间
        bool if_check_is_necessary {}; // 默认不需要强制打卡
        bool if_checked {}; // 默认未进行打卡
        //
        string account_id; // 用户名
        string student_id; // 学号
        string student_name; // 姓名
        //
        bool if_returned_school {}; // 是否返校
        bool if_is_accommodated {}; // 是否住校
        bool if_passed_by_high_risk_regions {}; // 有无经过高风险区
        bool if_passed_by_medium_risk_regions {}; // 有无经过中风险区
        bool if_temperature_higher_than_37 {}; // 体温是否高于37℃
        bool if_go_abroad {}; // 是否有出国旅居史
        friend bool operator==(const health_check_info& left, const health_check_info& right)
        {
            // 重载这个运算符，是为了能够使用find()/sort()
            // 这里"学号、姓名"都相等，才算做两个类“相等”
            const bool case1 = left.student_id == right.student_id;
            const bool case2 = left.student_name == right.student_name;
            return case1 && case2;
        }
        health_check_info()
        {
            var_initializer();
        }
        health_check_info(const health_check_info_trans& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        health_check_info(const health_check_info_trans* input)
        {
            record_time = input->record_time;
            if_check_is_necessary = input->if_check_is_necessary;
            if_checked = input->if_checked;
            account_id = input->account_id;
            student_id = input->student_id;
            student_name = input->student_name;
            if_returned_school = input->if_returned_school;
            if_is_accommodated = input->if_is_accommodated;
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input->if_temperature_higher_than_37;
            if_go_abroad = input->if_go_abroad;
        }
        void var_initializer()
        {
            if_check_is_necessary = false;
            if_checked = false;
            if_returned_school = true;
            if_is_accommodated = true;
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            if_temperature_higher_than_37 = false;
            if_go_abroad = false;
        }
        void operator=(const health_check_info_trans& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        void operator=(const health_check_info& input) // 浅拷 改 深拷
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
    };
    class health_check_info_trans {
    public:
        time_manager record_time {}; // 记录 health_check_info 的时间
        bool if_check_is_necessary {}; // 默认不需要强制打卡
        bool if_checked {}; // 默认未进行打卡
        //
        char account_id[17] {}; // 用户名
        char student_id[10] {}; // 学号
        char student_name[25] {}; // 姓名
        //
        bool if_returned_school {}; // 是否返校
        bool if_is_accommodated {}; // 是否住校
        bool if_passed_by_high_risk_regions {}; // 有无经过高风险区
        bool if_passed_by_medium_risk_regions {}; // 有无经过中风险区
        bool if_temperature_higher_than_37 {}; // 体温是否高于37℃
        bool if_go_abroad {}; // 是否有出国旅居史
        friend bool operator==(const health_check_info_trans& left, const health_check_info_trans& right)
        {
            const bool case1 = strcmp(left.student_id, right.student_id) == 0;
            const bool case2 = strcmp(left.student_name, right.student_name) == 0;
            return case1 && case2;
        }
        health_check_info_trans()
        {
            var_initializer();
        }
        health_check_info_trans(const health_check_info& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            strcpy_s(account_id, input.account_id.c_str());
            strcpy_s(student_id, input.student_id.c_str());
            strcpy_s(student_name, input.student_name.c_str());
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        health_check_info_trans(const health_check_info* input)
        {
            record_time = input->record_time;
            if_check_is_necessary = input->if_check_is_necessary;
            if_checked = input->if_checked;
            strcpy_s(account_id, input->account_id.c_str());
            strcpy_s(student_id, input->student_id.c_str());
            strcpy_s(student_name, input->student_name.c_str());
            if_returned_school = input->if_returned_school;
            if_is_accommodated = input->if_is_accommodated;
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input->if_temperature_higher_than_37;
            if_go_abroad = input->if_go_abroad;
        }
        void var_initializer()
        {
            if_check_is_necessary = false;
            if_checked = false;
            if_returned_school = true;
            if_is_accommodated = true;
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            if_temperature_higher_than_37 = false;
            if_go_abroad = false;
        }
        void operator=(const health_check_info& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            strcpy_s(account_id, input.account_id.c_str());
            strcpy_s(student_id, input.student_id.c_str());
            strcpy_s(student_name, input.student_name.c_str());
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        ~health_check_info_trans()
        {
            memset(account_id, 0, sizeof account_id);
            memset(student_id, 0, sizeof student_id);
            memset(student_name, 0, sizeof student_name);
        }
    };

protected:
    health_check_info* current_health_check_info {}; // 被使用的存储信息
    health_check_info* cached_health_check_info {}; // 缓存 => 遍历的时候用
    health_check_info_trans* cached_health_check_info_tr {}; // storage_layer
    health_check_info* checker {};
    health_check_info_trans* checker_trans {};
    /// function
    void update_health_check_file(); // 更新 健康打卡 成员列表 以及 是否完成健康打卡
    inline void make_sure_file_exists() const; // 确保 daily_health_check_list.dat 存在 (不存在就生成)
    bool check_if_file_is_empty(); // 检查 daily_health_check_list.dat 是否为空
    void make_sure_dictionary_exists() const; // 确保 time_dictionary.dat 存在 (不存在就生成)
    bool check_if_dictionary_is_empty(); // 检查 time_dictionary.dat 是否为空
    daily_health_check(); // 空构造函数
    daily_health_check(const string&); // 真·构造函数
    ~daily_health_check();
    inline void var_initializer(); // 变量初始化
};