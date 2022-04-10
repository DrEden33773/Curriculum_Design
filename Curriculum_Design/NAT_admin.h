/*
 * 文件目录结构：
 *      $/root/ -- cpp_final_task [folder]
 *                 |=> NAT_personal_detail_info [folder]
 *                 |=> "student_id" + "student_name" + "_detail_info" [folder]
 *                 |=> "student_id" + "student_name" [.dat]
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
    /* 以 姓名/学号 为索引，返回 被安排的核酸检测 总数 */
    int return_num_of_nat_by_name(const string& input_name);
    int return_num_of_nat_by_sno(const string& input_sno);
    /* 以 姓名/学号 为索引，返回 已完成的核酸检测 总数 */
    int return_finished_num_of_nat_by_name(const string& input_name);
    int return_finished_num_of_nat_by_sno(const string& input_sno);
    /* institute/profession/class 也就是 学院/专业/班级 代号 存在性验证 */
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
    // 为用户/组别 安排 核酸检测
    void arrange_nat_for_input_users(const vector<map<string, time_manager>>& input_users);
    void arrange_nat_for_input_groups(const vector<map<string, time_manager>>& input_groups);
    /* 当前用户(姓名/学号) 当天是否有 集体核酸检测 */
    bool if_person_has_collective_nat_check_by_name(const string& input_real_name, const time_manager& input_time);
    bool if_person_has_collective_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    /* 当前用户(学号) 当天是否有 其他核酸检测 */
    bool if_person_has_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    // => 下面这个函数，对应 重构前的 文件，弃用
    bool search_in_detail_folder_if_person_has_collective_nat_check(
        const string& file_path,
        const int& file_num,
        const time_manager& input_time) const; // abandoned
    // => 下面这个函数，对应 重构后的 文件，启用
    bool search_in_detail_file_if_person_has_collective_nat_check(
        const string& name,
        const string& sno,
        const time_manager& time); // 检查某个用户 有无 未完成的 集体核酸检测
    /* 指定学生有无待进行的核酸检测 */
    static void if_user_has_unfinished_nat_check_by_name(); // 姓名索引
    void if_user_has_unfinished_nat_check_by_sno(); // 学号索引
    // 展示特定用户 未完成的 核酸检测的 细节
    void show_sp_user_unfinished_nat_check_details(
        const string& sno,
        const string& name,
        const bool& if_generate_file = false) const;
    /* 所有/指定 集体有无待进行的核酸检测 */
    void if_sp_group_has_nat_check(); // 核心部分 完成
    void if_any_group_has_nat_check(); // 核心部分 完成
    /* 当前有无待进行的集体核酸检测 */
    static bool if_have_unfinished_group_nat_check(
        const string& institute = "empty",
        const string& profession = "empty",
        const string& political_class = "empty");

    // functions => first_layer
    // 这些函数都没有实际意义，有实际意义的函数都在上面
    void new_nat_arranger(); // 完成
    void personal_nat_arranger(); // 完成
    void collective_nat_arranger(); // 完成
    void show_if_user_has_unfinished_nat_check(); // 完成
    void show_if_we_have_unfinished_group_nat_check(); // 核心部分完成
    static void manual_confirm_finish_nat_of_user(); // 冗余
    static void manual_confirm_finish_nat_of_group(); // 冗余

    // 展示 建议核酸检测用户名单
    void show_nat_check_suggested_user(const bool& if_generate_file); // 完成
    // 生成 建议核酸检测用户名单 文件
    void generate_file_of_suggested_nat_check_user(); // 完成
    // 生成 有截至今天应完成而未完成核酸的用户列表 文件
    void generate_file_of_unfinished_nat_check_user();

    // 生成 用于存储 输入用户的 核酸检测详细信息 的 目录
    void generate_input_personal_detail_folder(const string& input);

public:
    // 界面
    void shell_of_NAT_admin();

    NAT_admin()
        : NAT_manager() {}

    ~NAT_admin();
};
