#pragma once

#include "user_AccountInfoReceiver.h"
#include "time_manager.h"

// ������ �� �û���/����Ա�� ��ͬά�� ͬһ�� �������ļ�
class daily_health_check : public user_info_receiver {
public: // ������Ϊ�˷����Ժ� ���޸��ļ��� �����óɵ� public
    const string daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\daily_health_check_list.dat)";
    const string temp_daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_daily_health_check_list.dat)";
    const string name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\unchecked_list_)";
    const string temp_name_base = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_unchecked_list_)"; // ����
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    string today_unchecked_file_location = name_base; // δ��������ַ�����ݵ������ڶ�̬�仯 // �õ�name_base
    string temp_today_unchecked_file_location = temp_name_base; // δ��������ַ�����ݵ������ڶ�̬�仯 // �õ�temp_name_base
    const string time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\time_dictionary.dat)";
    const string temp_time_dictionary_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_time_dictionary.dat)";

protected:
    time_manager current_time; // ��ǰʱ�䣬ջ�������ɣ������������������
    time_manager time_dict_tail_checker; // ʱ���������һ��ļ������ջ�������ɣ������������������
    bool if_daily_check_file_is_empty;
    bool if_time_dictionary_file_is_empty;
    using dict_checker = struct dict_checker { // ��� ʱ������ �Ƿ�Ϊ�� �Ľṹ��
        int year;
        int month;
        int day;
    };
    dict_checker* time_dict_checker = nullptr; // ��� ʱ������ �Ƿ�Ϊ�� �� ����
    using health_check_info = struct health_check_info { // ������� C++11�ִ����ԣ���/�ṹ�� �ڲ���ʼ��
        bool if_check_is_necessary = false; // Ĭ�ϲ���Ҫǿ�ƴ�
        bool if_checked = false; // Ĭ��δ���д�
        //
        string account_id; // �û���
        string student_id; // ѧ��
        string student_name; // ����
        //
        bool if_returned_school = true; // �Ƿ�У
        bool if_is_accomodated = true; // �Ƿ�סУ
        bool if_passed_by_high_risk_regions = false; // ���޾����߷�����
        bool if_passed_by_midium_risk_regions = false; // ���޾����з�����
        bool if_temperature_higher_than_37 = false; // �����Ƿ����37��
        bool if_go_abroad = false; // �Ƿ��г����þ�ʷ
    };
    health_check_info* current_health_check_info = nullptr; // ��ʹ�õĴ洢��Ϣ
    health_check_info* cached_health_check_info = nullptr; // ���� => ������ʱ����
    health_check_info* checker = nullptr;
    daily_health_check();
    /// function
    inline void make_sure_file_exists();
    auto check_if_file_is_empty() -> bool;
    void make_sure_dictionary_exists();
    auto check_if_dictionary_is_empty() -> bool;
};
