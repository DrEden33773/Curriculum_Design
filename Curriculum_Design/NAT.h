// NAT <=> 核酸检测

/*
 * 文件目录结构：
 *      $/root/ = cpp_final_task [folder]
 *                => NAT_personal_detail_info [folder]
 *                => "student_id" + "student_name" + "_detail_info" [folder]
 *                => (这个学生产生的所有 核酸检测 记录) [binary files] "名字就是 1.dat 2.dat 这种，取决于这是第几次的事件"
 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "time_manager.h"
#include "user_AccountInfoReceiver.h" // 这个绝对用得上
#include <iostream>
#include <string>
using namespace std;

class NAT_manager : public user_info_receiver {
protected:
    // binary file
    const string NAT_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\NAT_list.dat)";
    const string temp_NAT_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_NAT_list.dat)";
    const string NAT_file_root = R"(C:\Users\edwar\Desktop\cpp_final_task)";
    const string NAT_detail_file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\NAT_personal_detail_info)";
    const string status_of_folder_file_location = NAT_detail_file_root + R"(\status_of_folder.dat)";
    string current_NAT_detail_file_folder_location;
    // status
    bool if_generate_all_personal_nat_detail_info_folder;
    bool if_NAT_list_file_empty;
    // NAT_list_tree
    class NAT_template_translator;

    class NAT_template {
        // while copying data from NAT_template_translator, auto_filled_vars_initializer() will be called
    public:
        /* personal_info */
        string student_name;
        string student_number; // EG => 16 21 103 35
        string dorm_number;
        bool if_passed_by_high_risk_regions; // 是否经过高风险区 => 默认 false
        bool if_passed_by_medium_risk_regions; // 是否经过中风险区 => 默认 false
        /* auto-filled vars */
        string department_num; // EG => 16
        string year_of_approaching_college; // EG => 21 <=> 2021
        string profession_num; // EG => 1
        string class_num; // EG => 03
        string personal_num; // EG => 35
        int total_num_of_NAT; // 总共 预定 进行过多少次NAT => 默认 0
        int total_num_of_finished_NAT; // 总共 完成过 多少次NAT => 默认 0
        void auto_filled_vars_initializer() // deal with auto_filled vars
        {
            department_num = student_number.substr(0, 2);
            year_of_approaching_college = student_number.substr(2, 2);
            profession_num = student_number.substr(4, 1);
            class_num = student_number.substr(5, 2);
            personal_num = student_number.substr(7, 2);
        }

        NAT_template()
        {
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            total_num_of_NAT = 0;
            total_num_of_finished_NAT = 0;
        }

        void operator=(const NAT_template_translator& input)
        {
            student_name = input.student_name;
            student_number = input.student_number;
            dorm_number = input.dorm_number;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            total_num_of_NAT = input.total_num_of_NAT;
            total_num_of_finished_NAT = input.total_num_of_finished_NAT;
            auto_filled_vars_initializer();
        }

        void operator=(const NAT_template& input)
        {
            student_name = input.student_name;
            student_number = input.student_number;
            dorm_number = input.dorm_number;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            total_num_of_NAT = input.total_num_of_NAT;
            total_num_of_finished_NAT = input.total_num_of_finished_NAT;
            auto_filled_vars_initializer();
        }

        NAT_template(const NAT_template_translator& input)
        {
            student_name = input.student_name;
            student_number = input.student_number;
            dorm_number = input.dorm_number;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            total_num_of_NAT = input.total_num_of_NAT;
            total_num_of_finished_NAT = input.total_num_of_finished_NAT;
            auto_filled_vars_initializer();
        }

        NAT_template(const NAT_template_translator* input)
        {
            student_name = input->student_name;
            student_number = input->student_number;
            dorm_number = input->dorm_number;
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            total_num_of_NAT = input->total_num_of_NAT;
            total_num_of_finished_NAT = input->total_num_of_finished_NAT;
            auto_filled_vars_initializer();
        }
    };

    class NAT_template_translator {
    public:
        /* personal_info */
        char student_name[17] {};
        char student_number[10] {}; // EG => 16 21 103 35
        char dorm_number[4] {};
        bool if_passed_by_high_risk_regions; // 是否经过高风险区 => 默认 false
        bool if_passed_by_medium_risk_regions; // 是否经过中风险区 => 默认 false
        /* auto-filled vars */
        char department_num[3] {}; // EG => 16
        char year_of_approaching_college[3] {}; // EG => 21 <=> 2021
        char profession_num[2] {}; // EG => 1
        char class_num[3] {}; // EG => 03
        char personal_num[3] {}; // EG => 35
        int total_num_of_NAT; // 总共 预定 进行过多少次NAT => 默认 0
        int total_num_of_finished_NAT; // 总共 完成过 多少次NAT => 默认 0
        NAT_template_translator()
        {
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            total_num_of_NAT = 0;
            total_num_of_finished_NAT = 0;
        }

        ~NAT_template_translator()
        {
            memset(student_name, 0, sizeof student_name);
            memset(student_number, 0, sizeof student_number);
            memset(dorm_number, 0, sizeof dorm_number);
            memset(department_num, 0, sizeof department_num);
            memset(year_of_approaching_college, 0, sizeof year_of_approaching_college);
            memset(profession_num, 0, sizeof profession_num);
            memset(class_num, 0, sizeof class_num);
            memset(personal_num, 0, sizeof personal_num);
        }

        void operator=(const NAT_template& input)
        {
            strcpy_s(student_name, input.student_name.c_str());
            strcpy_s(student_number, input.student_number.c_str());
            strcpy_s(dorm_number, input.dorm_number.c_str());
            strcpy_s(department_num, input.department_num.c_str());
            strcpy_s(year_of_approaching_college, input.year_of_approaching_college.c_str());
            strcpy_s(profession_num, input.profession_num.c_str());
            strcpy_s(class_num, input.class_num.c_str());
            strcpy_s(personal_num, input.personal_num.c_str());
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            total_num_of_NAT = input.total_num_of_NAT;
            total_num_of_finished_NAT = input.total_num_of_finished_NAT;
        }

        NAT_template_translator(const NAT_template& input)
        {
            strcpy_s(student_name, input.student_name.c_str());
            strcpy_s(student_number, input.student_number.c_str());
            strcpy_s(dorm_number, input.dorm_number.c_str());
            strcpy_s(department_num, input.department_num.c_str());
            strcpy_s(year_of_approaching_college, input.year_of_approaching_college.c_str());
            strcpy_s(profession_num, input.profession_num.c_str());
            strcpy_s(class_num, input.class_num.c_str());
            strcpy_s(personal_num, input.personal_num.c_str());
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            total_num_of_NAT = input.total_num_of_NAT;
            total_num_of_finished_NAT = input.total_num_of_finished_NAT;
        }

        NAT_template_translator(const NAT_template* input)
        {
            strcpy_s(student_name, input->student_name.c_str());
            strcpy_s(student_number, input->student_number.c_str());
            strcpy_s(dorm_number, input->dorm_number.c_str());
            strcpy_s(department_num, input->department_num.c_str());
            strcpy_s(year_of_approaching_college, input->year_of_approaching_college.c_str());
            strcpy_s(profession_num, input->profession_num.c_str());
            strcpy_s(class_num, input->class_num.c_str());
            strcpy_s(personal_num, input->personal_num.c_str());
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            total_num_of_NAT = input->total_num_of_NAT;
            total_num_of_finished_NAT = input->total_num_of_finished_NAT;
        }
    };

    NAT_template* c_NAT_template {}; // nullptr // 当前用户使用的 NAT_template => 用户端用得到
    NAT_template* cache_NAT_template {}; // nullptr // 缓存用的 NAT_template => 管理员端和自动化处理用得到
    NAT_template_translator* cache_NAT_template_tr {}; // nullptr

    // personal_NAT_list => don't need translator (because there's no string var in this class)
    class personal_NAT_list {
    public:
        int no_; // 用于统计 这个用户 完成了 几次核酸 [这个也是一个顺序索引] // => 目前暂时冗余
        time_manager time_should_do_this_NAT;
        bool if_have_done_this_NAT;
        int type_of_this_NAT; // 0::全员普查、以 某个集体 为单位 && 1::常态化抽查，以个人为单位
        char code_of_group_check_if_have[10] {}; // 如果有 集体普查， 这里填写代号 // EG => 16/161/16103 [学号，忽略入学年份]
        time_manager time_of_finishing_this_NAT;
        personal_NAT_list* next {}; // nullptr
        personal_NAT_list* prev {}; // nullptr
        personal_NAT_list()
        {
            no_ = 1; // => 目前暂时冗余
            if_have_done_this_NAT = false;
            type_of_this_NAT = 1;
        }
    };

    personal_NAT_list* head {}; // nullptr
    personal_NAT_list* tail {}; // nullptr
    // functions
    void generate_main_folder_for_nat_detail_info() const;
    void generate_all_personal_nat_detail_info_folder(); // abandoned
    void load_status_of_folder(); // abandoned
    void write_status_of_folder(); // abandoned
    void write_status_of_all_personal_folder(const bool&); // abandoned
    void update_NAT_list_file(); // 更新 NAT_list.dat
    void fetch_region_information() const; // 获取 遍历到的/当前的 用户 当天健康打卡中 经过的区域 信息
    // 将输入姓名 对应的 安排的核酸总次数 更新一次
    void update_num_of_nat_of_input_name(const string& input_real_name); // assume that input_real_name already exists
    // 将输入学号 对应的 安排的核酸总次数 更新一次
    void update_num_of_nat_of_input_sno(const string& input_sno); // assume that input_sno already exists
    // 将输入姓名 对应的 已完成的核酸次数 更新一次
    void update_num_of_finished_nat_of_input_sno(const string& input_sno); // assume that input_sno already exists
    // 将输入学号 对应的 已完成的核酸次数 更新一次
    void update_num_of_finished_nat_of_input_name(const string& input_real_name); // assume that input_real_name already exists
    // 将输入学号 对应的 已完成的核酸次数 更新 times 次
    void multi_update_num_of_finished_nat_of_input_sno(const string& input_sno, const int& times);
    bool check_user_existence_by_real_name(const string& input_real_name); // 输入姓名 是否存在
    bool check_user_existence_by_sno(const string& input_student_number); // 输入学号 是否存在
    string return_real_name_by_sno(const string& input_student_number); // 返回 输入学号 对应的 姓名
    string return_sno_by_real_name(const string& input_real_name); // 返回 输入姓名 对应的 学号
    // pre_load
    void pre_generate_nat_file_location() const; // 以 ios::app 预加载 NAT_list.dat

public:
    NAT_manager();
    NAT_manager(
        const string& student_name,
        const string& student_number,
        const string& dorm_number,
        const bool& if_passed_by_high_risk_regions = false,
        const bool& if_passed_by_medium_risk_regions = false);
};
