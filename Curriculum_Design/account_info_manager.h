// (��) ɾ �� �� => ѧ����Ϣ

#pragma once

#include "user_AccountInfoReceiver.h" // �༶�̳�

class account_info_manager : public user_info_receiver {
protected:
    const string user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    const string account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\account_info.dat)";
    const string temp_user_list_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_user_list.dat)";
    const string temp_account_info_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_account_info.dat)";
    // ������ -- done
    auto if_input_user_exists(const string&, const int& mode, const bool& if_print) -> bool; // ���� �����û�[��ȷƥ��] �Ƿ���� (����ָ���Ƿ��ӡ���ڵ��û�)
    auto if_input_user_exists_sub(const string&, const int& mode, const bool& if_print) -> bool; // �����������������ǣ���[ģ��ƥ��]
    inline void print_detail_info();
    inline void print_partial_matched_info();
    inline void open_all_files(fstream& account_info_file, fstream& user_list_file);
    /* [mode => 1.ѧ�ž�ȷ���� 2.������ȷ���� 3.�û�����ȷ����] */
    // չʾ��Ϣ -- done
    void precisely_show_specific_user_info(); // ��ȷ���� �û� [�������û�����Ҳ������ѧ�ţ�������������]
    void show_all_user_info(); // չʾ���� �û� ��Ϣ
    void search_then_show_specific_user(); // ģ������ �û� [�������û�����Ҳ������ѧ�ţ�������������]
    static inline void not_found(); // �������û�
    // �޸���Ϣ -- done
    void change_specific_user_information(); // ���� �ض��û� �� ��Ϣ [ѡ�������ĸ��е�һ��]
    void change_specific_user_password(const string&); // ���� �ض��û� �� ����
    void change_specific_user_realname(const string&); // ���� �ض��û� �� ����
    void change_specific_user_student_number(const string&); // ���� �ض��û� �� ѧ��
    void change_specific_user_student_dorm_number(const string&); // ���� �ض��û� �� �����
    // �����û� [����]
    static void add_a_user(); // ����һ���û� [����]
    // ɾ���û� -- done
    void delete_input_user_in_account_info(const string&);
    void delete_input_user_in_user_list(const string&);
    void delete_a_user(); // ɾ��һ���û�

public:
    account_info_manager();
    void shell_of_account_info_manager(); // ��������
};
