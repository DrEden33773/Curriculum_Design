// 重构完成

// 目前暂时只支持“本校(NUAA)”使用，将会自动分析学号 (例如 16-22-1-02-32)
// 这部分信息，需要被允许 “增删查改” => 最麻烦的在于 “删” ，不过已经有很好的方法！

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class user_info_receiver {
    // 进行继承，避免主函数中传递参数
protected:
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_user_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    //
    bool if_user_list_empty;
    //
    class current_user_info_tr; // pre-define
    class current_user_info;

    class current_user_info_tr {
        // 交换层，处理文件的时候，用这个
    public:
        char c_account[17] {};
        char real_name[17] {};
        char student_number[10] {}; // 学号的长度限制！
        char dorm_number[5] {};
        bool if_first_use;
        current_user_info_tr()
        {
            if_first_use = true;
        }
        current_user_info_tr(const current_user_info& input)
        {
            strcpy_s(c_account, input.c_account.c_str());
            strcpy_s(real_name, input.real_name.c_str());
            strcpy_s(student_number, input.student_number.c_str());
            strcpy_s(dorm_number, input.dorm_number.c_str());
            if_first_use = input.if_first_use;
        }
        current_user_info_tr(const current_user_info* input)
        {
            strcpy_s(c_account, input->c_account.c_str());
            strcpy_s(real_name, input->real_name.c_str());
            strcpy_s(student_number, input->student_number.c_str());
            // bug fixed => 原来 会 拷贝两次 student_number
            strcpy_s(dorm_number, input->dorm_number.c_str());
            if_first_use = input->if_first_use;
        }
        void operator=(const current_user_info& input)
        {
            strcpy_s(c_account, input.c_account.c_str());
            strcpy_s(real_name, input.real_name.c_str());
            strcpy_s(student_number, input.student_number.c_str());
            strcpy_s(dorm_number, input.dorm_number.c_str());
            if_first_use = input.if_first_use;
        }
        ~current_user_info_tr()
        {
            memset(c_account, 0, sizeof c_account);
            memset(real_name, 0, sizeof real_name);
            memset(student_number, 0, sizeof student_number);
            memset(dorm_number, 0, sizeof dorm_number);
        }
    };

    class current_user_info {
        // 表面层，没有处理文件的时候，用这个
    public:
        string c_account;
        string real_name; // 真名 => 首次登录时候，要求设置
        string student_number; // 学号 => 首次登录时候，要求设置
        string dorm_number; // 宿舍号 => 首次登录时候，要求设置
        bool if_first_use; // 是否第一次使用
        current_user_info()
        {
            if_first_use = true;
        }
        current_user_info(const current_user_info_tr& input)
        {
            c_account = input.c_account;
            real_name = input.real_name;
            student_number = input.student_number;
            dorm_number = input.dorm_number;
            if_first_use = input.if_first_use;
        }
        current_user_info(const current_user_info_tr* input)
        {
            c_account = input->c_account;
            real_name = input->real_name;
            student_number = input->student_number;
            dorm_number = input->dorm_number;
            if_first_use = input->if_first_use;
        }
        void operator=(const current_user_info_tr& input)
        {
            c_account = input.c_account;
            real_name = input.real_name;
            student_number = input.student_number;
            dorm_number = input.dorm_number;
            if_first_use = input.if_first_use;
        }
    };

    //
    current_user_info* cu_info {}; // 类内全局性的接口，信息容器
    current_user_info* cu_cache {}; // 类内全局性的接口，但是充当缓存
    current_user_info_tr* cu_cache_tr {}; // 仅用于存储、读取
    // functions
    bool if_sno_already_exists(const string& input_sno); // 输入学号是否存在
    inline void initialize_user_list_file() const; // 以ios::app模式 预加载 user_list.dat
    void user_list_file_empty_check(); // 检查 user_list.dat 是否为空
    void try_to_load_user_file(const string&); // 试图读取“用户文件”，读入cache
    void write_to_user_file(); // 写入“用户文件” // “用户文件”中，存放了连续的几个 结构体块，顺序寻址找到即可 //打开模式一定加一个 app
public:
    // 构造函数
    user_info_receiver(); // 空构造函数
    user_info_receiver(const string&); // 真构造函数
    // 最优先执行的函数
    void user_import_from_login_interface(const string&); // 从 登录模块中的account.dat 导入与用户名对应的 数据
    // 之后执行的函数
    void ask_to_set_user_info(); // 设置 “姓名”,“学号”,“是否住校”,“宿舍号”
    // 接口函数
    string return_c_account() const; // 返回“账号”
    string return_real_name() const; // 返回“真名”
    string return_student_number() const; // 返回“学号”
    string return_dorm_number() const; // 返回”宿舍号“
    // 析构函数
    ~user_info_receiver(); // 析构函数
};
