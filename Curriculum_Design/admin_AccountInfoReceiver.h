#pragma once

#include <iostream>
#include <string>
using namespace std;

class admin_info_receiver{
protected:
    bool if_admin_list_file_is_empty;

    const string admin_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\admin_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_admin_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_admin_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    class current_admin_info {
    public:
        string c_account;
        // char admin_type;  //a = 辅导员  b = 班主任  //本功能暂时不予开发
        // int profession_code; // 分管学院类别  //本功能暂时不予开发，现阶段为了方便，直接管理员获得全部用户的管理权
        bool if_first_use = true;
    };
    current_admin_info* ca_info {};
    current_admin_info* ca_cache {};
    current_admin_info* checker {};
    static auto if_profession_type_valid(int) -> bool; // 学院标识 是否有效 -> true为有效 [冗余]
    inline void make_sure_admin_list_file_exists() const; // 以 ios::app 预加载 admin_list.dat
    auto if_admin_list_file_empty() -> bool; // 检查 admin_list.dat 是否为空

public:
    //构造函数
    admin_info_receiver(); // 空构造函数
    admin_info_receiver(const string&); // 真·构造函数
    //最优先执行的函数
    void admin_import_from_login_interface(const string&); // 从 登陆界面 导入 用户名 对应的信息
    //之后执行的函数
    void try_to_load_admin_file(const string&); // 试图读取“管理员文件”，读入cache
    void write_to_admin_file(); // 改写管理员文件
    void ask_to_set_profession_type(); // 设置 分管专业代码 [冗余]
    //接口函数
    auto return_c_account() const -> string; // 返回 用户名
};
