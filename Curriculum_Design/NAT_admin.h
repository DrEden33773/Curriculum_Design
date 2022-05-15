/*
 * �ļ�Ŀ¼�ṹ��
 *      $/root/ = cpp_final_task [folder]
 *                => NAT_personal_detail_info [folder]
 *                => "student_id" + "student_name" + "_detail_info" [folder]
 *                => (���ѧ������������ ������ ��¼) [binary files] "���־��� 1.dat 2.dat ���֣�ȡ�������ǵڼ��ε��¼�"
 *                >=> �������ڿ��� ���ع��ļ��ṹ�� => Ӧ���ع�һ�� => 1.dat 2.dat �����ģ�ȫ���ϵ�һ���ļ���
 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "NAT.h"
#include "time_manager.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

// attention: after called constructor of NAT_manager, "c_NAT_template" has been initialized
class NAT_admin : public NAT_manager {
protected:
    // paths:
    // const string NAT_detail_file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\NAT_personal_detail_info)";
    // const string status_of_folder_file_location = NAT_detail_file_root + R"(\status_of_folder.dat)";
    // string current_NAT_detail_file_folder_location;

    // functions => third_layer:
    /* return_num_of_nat */
    int return_num_of_nat_by_name(const string& input_name);
    int return_num_of_nat_by_sno(const string& input_sno);
    /* return_finished_num_of_nat */
    int return_finished_num_of_nat_by_name(const string& input_name);
    int return_finished_num_of_nat_by_sno(const string& input_sno);
    /* if_institute/profession/class_is_valid */
    bool check_if_institute_is_valid(const string& institute_code);
    bool check_if_profession_is_valid(
        const string& institute_code,
        const string& profession_code);
    bool check_if_political_class_is_valid(
        const string& institute_code,
        const string& profession_code,
        const string& political_class_code);
    bool group_existence_checking_manager(
        const string& institute_code = "empty",
        const string& profession_code = "empty",
        const string& political_class_code = "empty");
    /* ָ�� ������ */
    string set_group_code();
    /* name + sno => ���� �ļ�����path */
    inline string generate_detail_file_path(const string& sno, const string& name) const;

    // functions => middle_layer:
    void set_c_nat_template_by_name(const string& input_name);
    void set_c_nat_template_by_sno(const string& input_sno);
    void arrange_nat_for_input_users(const vector<map<string, time_manager>>& input_users);
    void arrange_nat_for_input_groups(const vector<map<string, time_manager>>& input_groups);
    /* arranged_person_occasion_validation_checker */
    bool if_person_has_collective_nat_check_by_name(const string& input_real_name, const time_manager& input_time);
    bool if_person_has_collective_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    bool if_person_has_nat_check_by_sno(const string& input_sno, const time_manager& input_time);
    // => ���������������Ӧ �ع�ǰ�� �ļ�������
    bool search_in_detail_folder_if_person_has_collective_nat_check(
        const string& file_path,
        const int& file_num,
        const time_manager& input_time) const;
    // => ���������������Ӧ �ع���� �ļ�������
    bool search_in_detail_file_if_person_has_collective_nat_check(
        const string& name,
        const string& sno,
        const time_manager& time);
    /* ָ��ѧ�����޴����еĺ����� */
    static void if_user_has_unfinished_nat_check_by_name(); // ���
    void if_user_has_unfinished_nat_check_by_sno(); // ���
    void show_sp_user_unfinished_nat_check_details(
        const string& sno,
        const string& name,
        const bool& if_generate_file = false) const; // ���
    /* ����/ָ�� �������޴����еĺ����� */
    void if_sp_group_has_nat_check(); // ���Ĳ��� ���
    void if_any_group_has_nat_check(); // ���Ĳ��� ���
    /* ��ǰ���޴����еļ�������� */
    static bool if_have_unfinished_group_nat_check(
        const string& institute = "empty",
        const string& profession = "empty",
        const string& political_class = "empty");

    // functions => first_layer
    void new_nat_arranger(); // ���
    void personal_nat_arranger(); // ���
    void collective_nat_arranger(); // ���
    void show_if_user_has_unfinished_nat_check(); // ���
    void show_if_we_have_unfinished_group_nat_check(); // ���Ĳ������
    static void manual_confirm_finish_nat_of_user(); // ��������
    static void manual_confirm_finish_nat_of_group(); // ��������
    void show_nat_check_suggested_user(const bool& if_generate_file); // ���
    void generate_file_of_suggested_nat_check_user(); // ���
    void generate_file_of_unfinished_nat_check_user();

    // personal_file_folder_generator
    void generate_input_personal_detail_folder(const string& input);

public:
    void shell_of_NAT_admin(); // ���

    NAT_admin()
        : NAT_manager() {}

    ~NAT_admin();
};
