#pragma once

#include <cstring>
#include <string>

using namespace std;

class account_manager {
protected:
    // path
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    // var
    bool if_acct_info_file_have_admin;
    class account_info { // 存储在"account_info.txt"中
    public:
        // 如果是user权限的account，后期需要绑定学号、姓名、宿舍号
        // string account; // 弃用
        // string password; // 弃用
        char account_str[17] {}; // 启用 -- 账号，最长16位，默认全空
        char password_str[25] {}; // 启用 -- 密码，最长25位，默认全空
        char sp_code[11] {}; //凭据码，10位，默认全空
        bool if_admin; // 默认不给管理员权限
        account_info()
        {
            if_admin = false;
        }
        ~account_info()
        {
            memset(account_str, 0, sizeof account_str); // 将account_str清空
            memset(password_str, 0, sizeof password_str); // 将password_str清空
            memset(sp_code, 0, sizeof sp_code); // 将sp_code清空
        }
    };
    account_info* login; // 历史遗留冗余
    account_info* cache; // 派生类 account_info_manager 用得到，本类用不到
    account_info* cache_base; // 本类用得到，另一个缓存 => 析构函数中，唯一需要 delete 的 对象
    // back_function
    // 我们无需判断 account info 文件 是不是空的，因为至少要强制你 创建一个 管理员账户
    int check_account(const string&, const string&) const; // 校验 [-2=无账户，-1=密码错误，0=普通账户，1=管理员]
    void write_account_to_cache(const string&, const string&, bool, const char*); // 更新 账户信息待写缓存
    static void change_account_in_cache(account_info*, const string&, const char*); // 修改密码后，在 缓存 中改写密码、凭据码
    void write_cache_to_file_app() const; // 将 账户信息缓存 写入文件 [直接添加到末尾]
    void change_account_password_in_file(const account_info*) const; // 直接在 文件内 更改 用户的密码 // 可以用上了
    static char* generate_sp_code(); // 给”账户“生成”凭据码“
    account_info* if_sp_code_is_correct(const string&, const char*) const; // 检验"凭据码"是否与“用户名”匹配
    account_info* if_sp_code_exists(const char*) const; // 检验“凭据码”是否存在，用于“使用凭据码登录”
    bool if_account_exists_new(const string&) const; // 检查是否已存在用户 [new]
    static bool if_password_legal(const string&); // 密码有效性检验
    static bool if_account_legal(const string&); // 账号有效性检验
    // front_function
    //登录 [-2=无账户，-1=密码错误，0=普通账户，1=管理员]
    int sign_in_by_account(); // 账号密码登录
    int sign_in_by_sp_code(); // 文件凭据登录 [不会返回-1，只可能返回-2，0，1]
    //新账号
    void create_account();
    //改密码
    void change_password() const;
    //登陆后的账户访问接口
    void give_the_plug_of_account(const string&, const string&); // 将要写入 login 指针变量
    void give_the_plug_of_account(const char*); // 将要写入 login 指针变量
    //提供密文格式
    static bool password_input_judger_with_fmt(const string& judged_str);
    static string password_input_with_fmt_then_return_it();

public:
    auto shell_of_account_login() -> int; // ”登录“主界面 [返回 -> 0=>普通用户，1=>管理员]
    void first_create_admin_account(); // 第一次使用，要求创建账号
    //解析接口函数
    string return_account_name() const; // 解析--刚刚登录的账号的用户名
    string return_account_password() const; // 解析--刚刚登录的账号的密码
    account_manager(); // 空构造函数
    account_manager(const string&); // 真·构造函数
    ~account_manager(); // 析构函数
};