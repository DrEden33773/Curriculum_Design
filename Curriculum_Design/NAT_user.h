#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "NAT.h"
#include "time_manager.h"
#include <string>
#include <vector>
using namespace std;

class NAT_user : public NAT_manager {
protected:
    /* __file_path__ */
    const string main_file_root_ = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    const string nat_detail_file_main_root_ = R"(C:\Users\edwar\Desktop\cpp_final_task\NAT_personal_detail_info\)";
    string current_detail_file_name_;
    string temp_current_detail_file_name_;
    /* plug_in_var */
    bool if_have_unfinished_task_no_later_than_today_ = false;
    /* __user_info__ */
    time_manager today_;
    string sno_;
    string name_;
    string dorm_num_;
    bool if_passed_by_high_risk_regions_ = false;
    bool if_passed_by_medium_risk_regions_ = false;
    /* other_var */
    class cache_of_unfinished_nat_check {
    public:
        time_manager time_should_do_this_NAT;
        int type_of_this_NAT;
        string group_code_if_have = R"(NA)";
        cache_of_unfinished_nat_check() = default;
        cache_of_unfinished_nat_check(
            const time_manager& time_should_do_this_NAT,
            const int& type_of_this_NAT,
            const char* group_code_if_have)
        {
            this->time_should_do_this_NAT = time_should_do_this_NAT;
            this->type_of_this_NAT = type_of_this_NAT;
            this->group_code_if_have = group_code_if_have;
        }
        cache_of_unfinished_nat_check(const time_manager& time_should_do_this_NAT)
        {
            this->time_should_do_this_NAT = time_should_do_this_NAT;
            this->type_of_this_NAT = 1; // 个人
        }
        // 去重的时候，sort、unique都会用得到
        friend bool operator<(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return left.time_should_do_this_NAT < right.time_should_do_this_NAT;
        }
        friend bool operator<=(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return !(left.time_should_do_this_NAT > right.time_should_do_this_NAT);
        }
        friend bool operator>(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return left.time_should_do_this_NAT > right.time_should_do_this_NAT;
        }
        friend bool operator>=(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return !(left.time_should_do_this_NAT < right.time_should_do_this_NAT);
        }
        friend bool operator==(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return left.time_should_do_this_NAT == right.time_should_do_this_NAT;
        }
        friend bool operator!=(const cache_of_unfinished_nat_check& left, const cache_of_unfinished_nat_check& right)
        {
            return !(left.time_should_do_this_NAT == right.time_should_do_this_NAT);
        }
    };
    vector<cache_of_unfinished_nat_check> list_of_unfinished_nat_checks_former_than_today {};
    vector<cache_of_unfinished_nat_check> list_of_all_unfinished_nat_checks {};
    /* auto_fill functions */

    // 标记 截至今天 应完成而未完成的所有核酸检测 数据
    void fill_list_of_unfinished_nat_checks_former_than_today();
    // 标记 所有 应完成而未完成的所有核酸检测 数据
    void fill_list_of_all_unfinished_nat_checks();

    /* background_functions */

    // 返回 有无 截至今天 应完成而未完成的所有核酸检测
    bool return_if_have_unfinished_task_no_later_than_today() const;
    // 为 输入用户 生成 存储 个人详细核算信息 的 目录
    inline string generate_detail_file_path(const string& sno, const string& name) const;
    inline string generate_temp_detail_file_path(const string& sno, const string& name) const;
    inline void set_detail_file_path();
    inline void set_temp_detail_file_path();
    // 检查 有无 截至今天 应完成而未完成的所有核酸检测
    void check_if_have_unfinished_task_no_later_than_today();
    // 催促 确认 截至今天 应完成而未完成的所有核酸检测
    void urge_to_finish_unfinished();
    // 移除已被确认的 截至今天 应完成而未完成的所有核酸检测
    void auto_remove_in_list_of_unfinished_nat_checks_former_than_today(const vector<time_manager>& remove_index_list);
    static void auto_remove_in_list_of_all_unfinished_nat_checks(const vector<time_manager>& remove_index_list);
    void confirm_unfinished_tasks_in_detail_file(const vector<time_manager>& confirm_index_list) const;
    
    /* front functions */

    // 展示 所有截至今天 应完成而未完成的所有核酸检测
    void show_unfinished_tasks_former_than_today() const;
    // 确认 所有截至今天 应完成而未完成的所有核酸检测 完成状态
    void confirm_unfinished_tasks_former_than_today(const bool& if_multi_confirm = false);
    static void confirm_all_unfinished_tasks(const bool& if_multi_confirm = false);
    

public:
    /* plug function */
    bool return_if_have_unfinished_nat_no_later_than_today() const;
    NAT_user() = default;
    NAT_user(const string& student_name,
        const string& student_number,
        const string& dorm_number,
        const bool& if_use_as_plug_only,
        const bool& if_passed_by_high_risk_regions = false,
        const bool& if_passed_by_medium_risk_regions = false);
    void shell_of_user_NAT_check();
};
