// �ع����

// ReSharper disable CppClangTidyBugproneReservedIdentifier
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "time_manager.h"
#include "user_AccountInfoReceiver.h"

// ������ �� �û���/����Ա�� ��ͬά�� ͬһ�� �������ļ�
class daily_health_check : public user_info_receiver {
public: // ������Ϊ�˷����Ժ� ���޸��ļ��� �����óɵ� public
    const string daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\daily_health_check_list.dat)";
    const string temp_daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_daily_health_check_list.dat)";
    const string name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\unchecked_list_)";
    const string temp_name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_unchecked_list_)"; // ����
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    string today_unchecked_file_location; // = name_base // δ��������ַ�����ݵ������ڶ�̬�仯 // �õ� name_base
    string temp_today_unchecked_file_location; // = temp_name_base // δ��������ַ�����ݵ������ڶ�̬�仯 // �õ� temp_name_base
    const string time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\time_dictionary.dat)";
    const string temp_time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_time_dictionary.dat)";

protected:
    time_manager current_time; // ��ǰʱ�䣬ջ�������ɣ������������������
    time_manager time_dict_tail_checker; // ʱ���������һ��ļ������ջ�������ɣ������������������
    time_manager cached_time; // ����--����Ա�� ִ�� �Զ�ɾ�� �����ʱ�� ���õ�
    bool if_daily_check_file_is_empty {};
    bool if_time_dictionary_file_is_empty {};

    class dict_checker {
        // ��� ʱ������ �Ƿ�Ϊ�� �Ľṹ��
    public:
        int year;
        int month;
        int day;
    };
    dict_checker* time_dict_checker {}; // ��� ʱ������ �Ƿ�Ϊ�� �� ����

public:
    class health_check_info_trans;
    class health_check_info {
    public:
        time_manager record_time; // ��¼ health_check_info ��ʱ��
        bool if_check_is_necessary {}; // Ĭ�ϲ���Ҫǿ�ƴ�
        bool if_checked {}; // Ĭ��δ���д�
        //
        string account_id; // �û���
        string student_id; // ѧ��
        string student_name; // ����
        //
        bool if_returned_school {}; // �Ƿ�У
        bool if_is_accommodated {}; // �Ƿ�סУ
        bool if_passed_by_high_risk_regions {}; // ���޾����߷�����
        bool if_passed_by_medium_risk_regions {}; // ���޾����з�����
        bool if_temperature_higher_than_37 {}; // �����Ƿ����37��
        bool if_go_abroad {}; // �Ƿ��г����þ�ʷ
        friend bool operator==(const health_check_info& left, const health_check_info& right)
        {
            // ����������������Ϊ���ܹ�ʹ��find()/sort()
            // ����"ѧ�š�����"����ȣ������������ࡰ��ȡ�
            const bool case1 = left.student_id == right.student_id;
            const bool case2 = left.student_name == right.student_name;
            return case1 && case2;
        }
        health_check_info()
        {
            var_initializer();
        }
        health_check_info(const health_check_info_trans& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        health_check_info(const health_check_info_trans* input)
        {
            record_time = input->record_time;
            if_check_is_necessary = input->if_check_is_necessary;
            if_checked = input->if_checked;
            account_id = input->account_id;
            student_id = input->student_id;
            student_name = input->student_name;
            if_returned_school = input->if_returned_school;
            if_is_accommodated = input->if_is_accommodated;
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input->if_temperature_higher_than_37;
            if_go_abroad = input->if_go_abroad;
        }
        void var_initializer()
        {
            if_check_is_necessary = false;
            if_checked = false;
            if_returned_school = true;
            if_is_accommodated = true;
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            if_temperature_higher_than_37 = false;
            if_go_abroad = false;
        }
        void operator=(const health_check_info_trans& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        void operator=(const health_check_info& input) // ǳ�� �� �
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            account_id = input.account_id;
            student_id = input.student_id;
            student_name = input.student_name;
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
    };
    class health_check_info_trans {
    public:
        time_manager record_time {}; // ��¼ health_check_info ��ʱ��
        bool if_check_is_necessary {}; // Ĭ�ϲ���Ҫǿ�ƴ�
        bool if_checked {}; // Ĭ��δ���д�
        //
        char account_id[17] {}; // �û���
        char student_id[10] {}; // ѧ��
        char student_name[25] {}; // ����
        //
        bool if_returned_school {}; // �Ƿ�У
        bool if_is_accommodated {}; // �Ƿ�סУ
        bool if_passed_by_high_risk_regions {}; // ���޾����߷�����
        bool if_passed_by_medium_risk_regions {}; // ���޾����з�����
        bool if_temperature_higher_than_37 {}; // �����Ƿ����37��
        bool if_go_abroad {}; // �Ƿ��г����þ�ʷ
        friend bool operator==(const health_check_info_trans& left, const health_check_info_trans& right)
        {
            const bool case1 = strcmp(left.student_id, right.student_id) == 0;
            const bool case2 = strcmp(left.student_name, right.student_name) == 0;
            return case1 && case2;
        }
        health_check_info_trans()
        {
            var_initializer();
        }
        health_check_info_trans(const health_check_info& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            strcpy_s(account_id, input.account_id.c_str());
            strcpy_s(student_id, input.student_id.c_str());
            strcpy_s(student_name, input.student_name.c_str());
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        health_check_info_trans(const health_check_info* input)
        {
            record_time = input->record_time;
            if_check_is_necessary = input->if_check_is_necessary;
            if_checked = input->if_checked;
            strcpy_s(account_id, input->account_id.c_str());
            strcpy_s(student_id, input->student_id.c_str());
            strcpy_s(student_name, input->student_name.c_str());
            if_returned_school = input->if_returned_school;
            if_is_accommodated = input->if_is_accommodated;
            if_passed_by_high_risk_regions = input->if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input->if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input->if_temperature_higher_than_37;
            if_go_abroad = input->if_go_abroad;
        }
        void var_initializer()
        {
            if_check_is_necessary = false;
            if_checked = false;
            if_returned_school = true;
            if_is_accommodated = true;
            if_passed_by_high_risk_regions = false;
            if_passed_by_medium_risk_regions = false;
            if_temperature_higher_than_37 = false;
            if_go_abroad = false;
        }
        void operator=(const health_check_info& input)
        {
            record_time = input.record_time;
            if_check_is_necessary = input.if_check_is_necessary;
            if_checked = input.if_checked;
            strcpy_s(account_id, input.account_id.c_str());
            strcpy_s(student_id, input.student_id.c_str());
            strcpy_s(student_name, input.student_name.c_str());
            if_returned_school = input.if_returned_school;
            if_is_accommodated = input.if_is_accommodated;
            if_passed_by_high_risk_regions = input.if_passed_by_high_risk_regions;
            if_passed_by_medium_risk_regions = input.if_passed_by_medium_risk_regions;
            if_temperature_higher_than_37 = input.if_temperature_higher_than_37;
            if_go_abroad = input.if_go_abroad;
        }
        ~health_check_info_trans()
        {
            memset(account_id, 0, sizeof account_id);
            memset(student_id, 0, sizeof student_id);
            memset(student_name, 0, sizeof student_name);
        }
    };

protected:
    health_check_info* current_health_check_info {}; // ��ʹ�õĴ洢��Ϣ
    health_check_info* cached_health_check_info {}; // ���� => ������ʱ����
    health_check_info_trans* cached_health_check_info_tr {}; // storage_layer
    health_check_info* checker {};
    health_check_info_trans* checker_trans {};
    /// function
    void update_health_check_file(); // ���� ������ ��Ա�б� �Լ� �Ƿ���ɽ�����
    inline void make_sure_file_exists() const; // ȷ�� daily_health_check_list.dat ���� (�����ھ�����)
    bool check_if_file_is_empty(); // ��� daily_health_check_list.dat �Ƿ�Ϊ��
    void make_sure_dictionary_exists() const; // ȷ�� time_dictionary.dat ���� (�����ھ�����)
    bool check_if_dictionary_is_empty(); // ��� time_dictionary.dat �Ƿ�Ϊ��
    daily_health_check(); // �չ��캯��
    daily_health_check(const string&); // �桤���캯��
    ~daily_health_check();
    inline void var_initializer(); // ������ʼ��
};