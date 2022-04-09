// 目前暂时只支持“本校(NUAA)”使用，将会自动分析学号 (例如 16-22-1-04-32)

// 这部分信息，需要被允许 “增删查改” => 最麻烦的在于 “删” ，不过已经有很好的方法！

#pragma once

#include "account.h"
#include <iostream>
#include <string>

using namespace std;

class user_info_receiver : public account_manager { // 进行继承，避免主函数中传递参数
protected:
    const string user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_user_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    //
    using current_user_info = struct current_user_info {
        string c_account;
        string real_name; // 真名 => 首次登录时候，要求设置
        string student_number; // 学号 => 首次登录时候，要求设置
        int dorm_number; // 宿舍号 => 首次登录时候，要求设置
        bool if_first_use; // 是否第一次使用
    };
    current_user_info* cu_info; // 类内全局性的接口，信息容器
    current_user_info* cu_cache; // 类内全局性的接口，但是充当缓存
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    inline void try_to_load_user_file(const string&); // 试图读取“用户文件”，读入cache
    void write_to_user_file(); // 写入“用户文件” // “用户文件”中，存放了连续的几个 结构体块，顺序寻址找到即可 //打开模式一定加一个 app

public:
    //构造函数
    user_info_receiver();
    user_info_receiver(const string&, const string&);
    //最优先执行的函数
    void user_import_from_login_interface(const string&);
    //之后执行的函数
    void ask_to_set_name_and_sno(); // 设置“姓名”/“学号”
    //接口函数
    auto return_c_account() -> string;
    auto return_real_name() -> string;
    auto return_student_number() -> string;
};
