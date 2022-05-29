// �ع����

// Ŀǰ��ʱֻ֧�֡���У(NUAA)��ʹ�ã������Զ�����ѧ�� (���� 16-22-1-02-32)
// �ⲿ����Ϣ����Ҫ������ ����ɾ��ġ� => ���鷳������ ��ɾ�� �������Ѿ��кܺõķ�����

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class user_info_receiver {
    // ���м̳У������������д��ݲ���
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
        // �����㣬�����ļ���ʱ�������
    public:
        char c_account[17] {};
        char real_name[17] {};
        char student_number[10] {}; // ѧ�ŵĳ������ƣ�
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
            // bug fixed => ԭ�� �� �������� student_number
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
        // ����㣬û�д����ļ���ʱ�������
    public:
        string c_account;
        string real_name; // ���� => �״ε�¼ʱ��Ҫ������
        string student_number; // ѧ�� => �״ε�¼ʱ��Ҫ������
        string dorm_number; // ����� => �״ε�¼ʱ��Ҫ������
        bool if_first_use; // �Ƿ��һ��ʹ��
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
    current_user_info* cu_info {}; // ����ȫ���ԵĽӿڣ���Ϣ����
    current_user_info* cu_cache {}; // ����ȫ���ԵĽӿڣ����ǳ䵱����
    current_user_info_tr* cu_cache_tr {}; // �����ڴ洢����ȡ
    // functions
    bool if_sno_already_exists(const string& input_sno); // ����ѧ���Ƿ����
    inline void initialize_user_list_file() const; // ��ios::appģʽ Ԥ���� user_list.dat
    void user_list_file_empty_check(); // ��� user_list.dat �Ƿ�Ϊ��
    void try_to_load_user_file(const string&); // ��ͼ��ȡ���û��ļ���������cache
    void write_to_user_file(); // д�롰�û��ļ��� // ���û��ļ����У�����������ļ��� �ṹ��飬˳��Ѱַ�ҵ����� //��ģʽһ����һ�� app
public:
    // ���캯��
    user_info_receiver(); // �չ��캯��
    user_info_receiver(const string&); // �湹�캯��
    // ������ִ�еĺ���
    void user_import_from_login_interface(const string&); // �� ��¼ģ���е�account.dat �������û�����Ӧ�� ����
    // ֮��ִ�еĺ���
    void ask_to_set_user_info(); // ���� ��������,��ѧ�š�,���Ƿ�סУ��,������š�
    // �ӿں���
    string return_c_account() const; // ���ء��˺š�
    string return_real_name() const; // ���ء�������
    string return_student_number() const; // ���ء�ѧ�š�
    string return_dorm_number() const; // ���ء�����š�
    // ��������
    ~user_info_receiver(); // ��������
};
