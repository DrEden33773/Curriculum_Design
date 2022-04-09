// Ŀǰ��ʱֻ֧�֡���У(NUAA)��ʹ�ã������Զ�����ѧ�� (���� 16-22-1-04-32)

// �ⲿ����Ϣ����Ҫ������ ����ɾ��ġ� => ���鷳������ ��ɾ�� �������Ѿ��кܺõķ�����

#pragma once

#include "account.h"
#include <iostream>
#include <string>

using namespace std;

class user_info_receiver : public account_manager { // ���м̳У������������д��ݲ���
protected:
    const string user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_user_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    //
    using current_user_info = struct current_user_info {
        string c_account;
        string real_name; // ���� => �״ε�¼ʱ��Ҫ������
        string student_number; // ѧ�� => �״ε�¼ʱ��Ҫ������
        int dorm_number; // ����� => �״ε�¼ʱ��Ҫ������
        bool if_first_use; // �Ƿ��һ��ʹ��
    };
    current_user_info* cu_info; // ����ȫ���ԵĽӿڣ���Ϣ����
    current_user_info* cu_cache; // ����ȫ���ԵĽӿڣ����ǳ䵱����
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    inline void try_to_load_user_file(const string&); // ��ͼ��ȡ���û��ļ���������cache
    void write_to_user_file(); // д�롰�û��ļ��� // ���û��ļ����У�����������ļ��� �ṹ��飬˳��Ѱַ�ҵ����� //��ģʽһ����һ�� app

public:
    //���캯��
    user_info_receiver();
    user_info_receiver(const string&, const string&);
    //������ִ�еĺ���
    void user_import_from_login_interface(const string&);
    //֮��ִ�еĺ���
    void ask_to_set_name_and_sno(); // ���á�������/��ѧ�š�
    //�ӿں���
    auto return_c_account() -> string;
    auto return_real_name() -> string;
    auto return_student_number() -> string;
};
