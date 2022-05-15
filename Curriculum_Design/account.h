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
    class account_info { // �洢��"account_info.txt"��
    public:
        // �����userȨ�޵�account��������Ҫ��ѧ�š������������
        // string account; // ����
        // string password; // ����
        char account_str[17] {}; // ���� -- �˺ţ��16λ��Ĭ��ȫ��
        char password_str[25] {}; // ���� -- ���룬�25λ��Ĭ��ȫ��
        char sp_code[11] {}; //ƾ���룬10λ��Ĭ��ȫ��
        bool if_admin; // Ĭ�ϲ�������ԱȨ��
        account_info()
        {
            if_admin = false;
        }
        ~account_info()
        {
            memset(account_str, 0, sizeof account_str); // ��account_str���
            memset(password_str, 0, sizeof password_str); // ��password_str���
            memset(sp_code, 0, sizeof sp_code); // ��sp_code���
        }
    };
    account_info* login; // ��ʷ��������
    account_info* cache; // ������ account_info_manager �õõ��������ò���
    account_info* cache_base; // �����õõ�����һ������ => ���������У�Ψһ��Ҫ delete �� ����
    // back_function
    // ���������ж� account info �ļ� �ǲ��ǿյģ���Ϊ����Ҫǿ���� ����һ�� ����Ա�˻�
    int check_account(const string&, const string&) const; // У�� [-2=���˻���-1=�������0=��ͨ�˻���1=����Ա]
    void write_account_to_cache(const string&, const string&, bool, const char*); // ���� �˻���Ϣ��д����
    static void change_account_in_cache(account_info*, const string&, const char*); // �޸�������� ���� �и�д���롢ƾ����
    void write_cache_to_file_app() const; // �� �˻���Ϣ���� д���ļ� [ֱ����ӵ�ĩβ]
    void change_account_password_in_file(const account_info*) const; // ֱ���� �ļ��� ���� �û������� // ����������
    static char* generate_sp_code(); // �����˻������ɡ�ƾ���롰
    account_info* if_sp_code_is_correct(const string&, const char*) const; // ����"ƾ����"�Ƿ��롰�û�����ƥ��
    account_info* if_sp_code_exists(const char*) const; // ���顰ƾ���롱�Ƿ���ڣ����ڡ�ʹ��ƾ�����¼��
    bool if_account_exists_new(const string&) const; // ����Ƿ��Ѵ����û� [new]
    static bool if_password_legal(const string&); // ������Ч�Լ���
    static bool if_account_legal(const string&); // �˺���Ч�Լ���
    // front_function
    //��¼ [-2=���˻���-1=�������0=��ͨ�˻���1=����Ա]
    int sign_in_by_account(); // �˺������¼
    int sign_in_by_sp_code(); // �ļ�ƾ�ݵ�¼ [���᷵��-1��ֻ���ܷ���-2��0��1]
    //���˺�
    void create_account();
    //������
    void change_password() const;
    //��½����˻����ʽӿ�
    void give_the_plug_of_account(const string&, const string&); // ��Ҫд�� login ָ�����
    void give_the_plug_of_account(const char*); // ��Ҫд�� login ָ�����
    //�ṩ���ĸ�ʽ
    static bool password_input_judger_with_fmt(const string& judged_str);
    static string password_input_with_fmt_then_return_it();

public:
    auto shell_of_account_login() -> int; // ����¼�������� [���� -> 0=>��ͨ�û���1=>����Ա]
    void first_create_admin_account(); // ��һ��ʹ�ã�Ҫ�󴴽��˺�
    //�����ӿں���
    string return_account_name() const; // ����--�ոյ�¼���˺ŵ��û���
    string return_account_password() const; // ����--�ոյ�¼���˺ŵ�����
    account_manager(); // �չ��캯��
    account_manager(const string&); // �桤���캯��
    ~account_manager(); // ��������
};