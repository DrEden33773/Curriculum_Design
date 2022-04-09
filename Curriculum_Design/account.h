// 进入登录界面后，“初始化info_cache=>打开info=>关闭info”更新账户个数
// 然后，打开account_info再关闭，把所有account信息读入缓存 [出于安全性考虑，且account信息绝对不会非常大]
// 所有的修改，都是先只针对 “account_info list” 的
// 修改后，自动覆写文件

#pragma once

#include "software_information.h"
#include <string>

using namespace std;

class account_manager : public info {
protected:
    bool if_acct_info_file_empty;

    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    //
    using account_info = struct account_info { // 存储在"account_info.dat"中
        string account; // user权限的account，后期需要绑定学号、姓名、宿舍号
        string password;
        char sp_code[11] = { '\0' }; //凭据码，默认全空
        bool if_admin = false; // 默认不给管理员权限
        struct account_info* next = nullptr; // 默认指空 // 现在用不着这个了
        struct account_info* prev = nullptr; // 默认指空 // 现在用不着这个了
    };
    account_info* head = nullptr;
    account_info* tail = nullptr;
    account_info* login; // 重点，成功登录后，把链表中 登录的账户 的相关信息，全部复制到这里面，然后 解除链表的空间占用！

    account_info* cache; // 派生类 account_info_manager 用得到，本类不要用
    account_info* cache2; // 本类用得到，另一个缓存

    // 后处理函数
    void if_acct_info_file_is_empty();
    auto check_account(const string&, const string&) -> int; // 校验 [-2=无账户，-1=密码错误，0=普通账户，1=管理员]
    void load_file_to_list(); // 将账户文件写入链表
    void write_account_to_list(string, string, bool, char*); // 更新 账户信息链表
    void write_account_to_cache(string, string, bool, char*); // 更新 账户信息待写缓存
    static void change_account_in_list(account_info*, string, char*); // 修改密码后，在链表中改写密码、凭据码
    void change_account_in_cache(account_info*, string, char*); // 修改密码后，在缓存块中改写密码、凭据码
    void write_list_to_file_trunc(); // 将 账户信息链表 写入文件
    void write_list_to_file_app(); // 将 账户信息缓存 写入文件 [直接添加到末尾]
    void change_account_password_in_file(const string&); // 直接在 文件内 更改 用户的密码 // 可以用上了
    static auto generate_sp_code() -> char*; // 给”账户“生成”凭据码“
    auto if_sp_code_is_correct(const string&, char*) -> account_info*; // 检验"凭据码"是否与“用户名”匹配
    auto if_sp_code_exits(char*) -> account_info*; // 检验“凭据码”是否存在，用于“使用凭据码登录”
    auto if_account_exists(const string&) -> account_info*; // 检查是否已存在用户
    static auto if_password_legal(string) -> bool; // 密码有效性检验
    // interface-函数
    //登录 [-2=无账户，-1=密码错误，0=普通账户，1=管理员]
    auto sign_in_by_account() -> int; // 账号密码登录
    auto sign_in_by_sp_code() -> int; // 文件凭据登录 [不会返回-1，只可能返回-2，0，1]
    //新账号
    void create_account();
    //改密码
    void change_password();
    //登陆后的账户访问接口
    void give_the_plug_of_account(const string&, const string&); // 将要写入 login 指针变量
    void give_the_plug_of_account(char*); // 将要写入 login 指针变量
    //解除链表占用的空间
    void delete_list();

public:
    auto shell_of_account_login() -> int; // ”登录“主界面 [返回 -> 0=>普通用户，1=>管理员]
    void first_create_account(); // 第一次使用，要求创建账号
    //解析接口函数
    auto return_account_name() -> string; // 解析--刚刚登录的账号的用户名
    auto return_account_password() -> string; // 解析--刚刚登录的账号的密码
    account_manager();
};