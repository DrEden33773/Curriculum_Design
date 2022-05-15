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
        // char admin_type;  //a = ����Ա  b = ������  //��������ʱ���迪��
        // int profession_code; // �ֹ�ѧԺ���  //��������ʱ���迪�����ֽ׶�Ϊ�˷��㣬ֱ�ӹ���Ա���ȫ���û��Ĺ���Ȩ
        bool if_first_use = true;
    };
    current_admin_info* ca_info {};
    current_admin_info* ca_cache {};
    current_admin_info* checker {};
    static auto if_profession_type_valid(int) -> bool; // ѧԺ��ʶ �Ƿ���Ч -> trueΪ��Ч
    inline void make_sure_admin_list_file_exists() const;
    auto if_admin_list_file_empty() -> bool;

public:
    //���캯��
    admin_info_receiver(); // �չ��캯��
    admin_info_receiver(const string&); // �桤���캯��
    //������ִ�еĺ���
    void admin_import_from_login_interface(const string&);
    //֮��ִ�еĺ���
    void try_to_load_admin_file(const string&); // ��ͼ��ȡ������Ա�ļ���������cache
    void write_to_admin_file(); // ��д����Ա�ļ�
    void ask_to_set_profession_type();
    //�ӿں���
    auto return_c_account() const -> string;
};
