// (增) 删 查 改 => 学生信息

#pragma once

#include "user_AccountInfoReceiver.h" // 多级继承

class account_info_manager : public user_info_receiver {
protected:
    const string user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_user_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    // 后处理函数 -- done
    auto if_input_user_exists(const string&, const int& mode, const bool& if_print) -> bool; // 检验 输入用户[精确匹配] 是否存在 (可以指定是否打印存在的用户)
    auto if_input_user_exists_sub(const string&, const int& mode, const bool& if_print) -> bool; // 功能类似上述，但是，是[模糊匹配]
    inline void print_detail_info();
    inline void print_partial_matched_info();
    inline void open_all_files(fstream& account_info_file, fstream& user_list_file);
    /* [mode => 1.学号精确搜索 2.姓名精确搜索 3.用户名精确搜索] */
    // 展示信息 -- done
    void precisely_show_specific_user_info(); // 精确搜索 用户 [可以是用户名，也可以是学号，还可以是姓名]
    void show_all_user_info(); // 展示所有 用户 信息
    void search_then_show_specific_user(); // 模糊搜索 用户 [可以是用户名，也可以是学号，还可以是姓名]
    static inline void not_found(); // 不存在用户
    // 修改信息 -- done
    void change_specific_user_information(); // 更改 特定用户 的 信息 [选择下面四个中的一个]
    void change_specific_user_password(const string&); // 更改 特定用户 的 密码
    void change_specific_user_realname(const string&); // 更改 特定用户 的 姓名
    void change_specific_user_student_number(const string&); // 更改 特定用户 的 学号
    void change_specific_user_student_dorm_number(const string&); // 更改 特定用户 的 宿舍号
    // 增加用户 [冗余]
    static void add_a_user(); // 增加一个用户 [冗余]
    // 删除用户 -- done
    void delete_input_user_in_account_info(const string&);
    void delete_input_user_in_user_list(const string&);
    void delete_a_user(); // 删除一个用户

public:
    account_info_manager();
    void shell_of_account_info_manager(); // 操作界面
};
