// �����¼����󣬡���ʼ��info_cache=>��info=>�ر�info�������˻�����
// Ȼ�󣬴�account_info�ٹرգ�������account��Ϣ���뻺�� [���ڰ�ȫ�Կ��ǣ���account��Ϣ���Բ���ǳ���]
// ���е��޸ģ�������ֻ��� ��account_info list�� ��
// �޸ĺ��Զ���д�ļ�

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
    using account_info = struct account_info { // �洢��"account_info.dat"��
        string account; // userȨ�޵�account��������Ҫ��ѧ�š������������
        string password;
        char sp_code[11] = { '\0' }; //ƾ���룬Ĭ��ȫ��
        bool if_admin = false; // Ĭ�ϲ�������ԱȨ��
        struct account_info* next = nullptr; // Ĭ��ָ�� // �����ò��������
        struct account_info* prev = nullptr; // Ĭ��ָ�� // �����ò��������
    };
    account_info* head = nullptr;
    account_info* tail = nullptr;
    account_info* login; // �ص㣬�ɹ���¼�󣬰������� ��¼���˻� �������Ϣ��ȫ�����Ƶ������棬Ȼ�� �������Ŀռ�ռ�ã�

    account_info* cache; // ������ account_info_manager �õõ������಻Ҫ��
    account_info* cache2; // �����õõ�����һ������

    // ������
    void if_acct_info_file_is_empty();
    auto check_account(const string&, const string&) -> int; // У�� [-2=���˻���-1=�������0=��ͨ�˻���1=����Ա]
    void load_file_to_list(); // ���˻��ļ�д������
    void write_account_to_list(string, string, bool, char*); // ���� �˻���Ϣ����
    void write_account_to_cache(string, string, bool, char*); // ���� �˻���Ϣ��д����
    static void change_account_in_list(account_info*, string, char*); // �޸�������������и�д���롢ƾ����
    void change_account_in_cache(account_info*, string, char*); // �޸�������ڻ�����и�д���롢ƾ����
    void write_list_to_file_trunc(); // �� �˻���Ϣ���� д���ļ�
    void write_list_to_file_app(); // �� �˻���Ϣ���� д���ļ� [ֱ����ӵ�ĩβ]
    void change_account_password_in_file(const string&); // ֱ���� �ļ��� ���� �û������� // ����������
    static auto generate_sp_code() -> char*; // �����˻������ɡ�ƾ���롰
    auto if_sp_code_is_correct(const string&, char*) -> account_info*; // ����"ƾ����"�Ƿ��롰�û�����ƥ��
    auto if_sp_code_exits(char*) -> account_info*; // ���顰ƾ���롱�Ƿ���ڣ����ڡ�ʹ��ƾ�����¼��
    auto if_account_exists(const string&) -> account_info*; // ����Ƿ��Ѵ����û�
    static auto if_password_legal(string) -> bool; // ������Ч�Լ���
    // interface-����
    //��¼ [-2=���˻���-1=�������0=��ͨ�˻���1=����Ա]
    auto sign_in_by_account() -> int; // �˺������¼
    auto sign_in_by_sp_code() -> int; // �ļ�ƾ�ݵ�¼ [���᷵��-1��ֻ���ܷ���-2��0��1]
    //���˺�
    void create_account();
    //������
    void change_password();
    //��½����˻����ʽӿ�
    void give_the_plug_of_account(const string&, const string&); // ��Ҫд�� login ָ�����
    void give_the_plug_of_account(char*); // ��Ҫд�� login ָ�����
    //�������ռ�õĿռ�
    void delete_list();

public:
    auto shell_of_account_login() -> int; // ����¼�������� [���� -> 0=>��ͨ�û���1=>����Ա]
    void first_create_account(); // ��һ��ʹ�ã�Ҫ�󴴽��˺�
    //�����ӿں���
    auto return_account_name() -> string; // ����--�ոյ�¼���˺ŵ��û���
    auto return_account_password() -> string; // ����--�ոյ�¼���˺ŵ�����
    account_manager();
};