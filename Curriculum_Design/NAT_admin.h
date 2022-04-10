/*
 * 文件目录结构：
 *      $/root/ = cpp_final_task [folder]
 *                => NAT_personal_detail_info [folder]
 *                => "student_id" + "student_name" + "_detail_info" [folder]
 *                => (这个学生产生的所有 核酸检测 记录) [binary files] "名字就是 1.dat 2.dat 这种，取决于这是第几次的事件"
 *                >=> 现在正在考虑 ”重构文件结构“ => 应该重构一下 => 1.dat 2.dat 这样的，全部合到一个文件里
 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "NAT.h"
#include "time_manager.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

// attention: after called constructor of NAT_manager, "c_NAT_template" has been initialized
class NAT_admin : public NAT_manager {
protected:
    // paths:
    // const string NAT_detail_file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\NAT_personal_detail_info)";
    // const string status_of_folder_file_location = NAT_detail_file_root + R"(\status_of_folder.dat)";
    // string current_NAT_detail_file_folder_location;

    // functions => third_layer:
    /* return_num_of_nat */
    int return_num_of_nat_by_name(const string& input_name);
    int return_num_of_nat_by_sno(const string& input_sno);
    /* return_finished_num_of_nat */
    int return_finished_num_of_nat_by_name(const string& input_name);
    int return_finished_num_of_nat_by_sno(const string& input_sno);
    /* if_institute/profession/class_is_valid */
    bool check_if_institute_is_valid(const string& institute_code);
    bool check_if_profession_is_valid(
        const string& institute_code,
        const string& profession_code);
    bool check_if_political_class_is_valid(
        const string& institute_code,
        const string& profession_code,
        const string& political_class_code);
    bool group_existence_checking_manager(
        const string& institute_code = "empty",
        const string& profession_code = "empty",
        const string& political_class_code = "empty");
    /* 指定 组别代号 */
    string set_group_code();
    /* name + sno => 生成 文件最终path */
    inline string generate_detail_file_path(const string& sno, const string& name) const;

    // functions => middle_layer:
    void set_c_nat_template_by_name(const string& input_name);
    void set_c_nat_template_by_sno(const string& input_sno);
    void arrange_nat_for_input_users(const vector<map<string, time_manager>>& input_users);
    void arrange_nat_for_input_groups(const vector<map<string, time_manager>>& input_groups);
    /* arranged_person_occasion_validation_checker */
    bool if_person_has_collective_nat_check_by_name(const string& input_real_name, const time_manager& input_time);
    bool if_person_has_collective_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    bool if_person_has_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    // => 下面这个函数，对应 重构前的 文件，弃用
    bool search_in_detail_folder_if_person_has_collective_nat_check(
        const string& file_path,
        const int& file_num,
        const time_manager& input_time) const;
    // => 下面这个函数，对应 重构后的 文件，启用
    bool search_in_detail_file_if_person_has_collective_nat_check(
        const string& name,
        const string& sno,
        const time_manager& time);
    /* 指定学生有无待进行的核酸检测 */
    static void if_user_has_unfinished_nat_check_by_name(); // 完成
    void if_user_has_unfinished_nat_check_by_sno(); // 完成
    void show_sp_user_unfinished_nat_check_details(
        const string& sno,
        const string& name,
        const bool& if_generate_file = false) const; // 完成
    /* 所有/指定 集体有无待进行的核酸检测 */
    void if_sp_group_has_nat_check(); // 核心部分 完成
    void if_any_group_has_nat_check(); // 核心部分 完成
    /* 当前有无待进行的集体核酸检测 */
    static bool if_have_unfinished_group_nat_check(
        const string& institute = "empty",
        const string& profession = "empty",
        const string& political_class = "empty");

    // functions => first_layer
    void new_nat_arranger(); // 完成
    void personal_nat_arranger(); // 完成
    void collective_nat_arranger(); // 完成
    void show_if_user_has_unfinished_nat_check(); // 完成
    void show_if_we_have_unfinished_group_nat_check(); // 核心部分完成
    static void manual_confirm_finish_nat_of_user(); // 决定冗余
    static void manual_confirm_finish_nat_of_group(); // 决定冗余
    void show_nat_check_suggested_user(const bool& if_generate_file); // 完成
    void generate_file_of_suggested_nat_check_user(); // 完成
    void generate_file_of_unfinished_nat_check_user();

    // personal_file_folder_generator
    void generate_input_personal_detail_folder(const string& input);

public:
    void shell_of_NAT_admin(); // 完成

    NAT_admin()
        : NAT_manager() {}

    ~NAT_admin();
};
