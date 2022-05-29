#pragma once

#include "daily_health_check.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using namespace std;

// ����Ҫ�Ľ� => �޷����� ��ǰ �����û� ǿ�ƴ�״̬

// ��Ҫά�����ļ� => daily_health_check_file_location [����Ǳ�����]
class daily_health_check_admin : public daily_health_check {
    // ���ﲻ��Ҫ�̳С�admin_info_receiver����ֻ��Ҫ�̳С�daily_health_check��
    // ��Ϊ ����Ա�� ���� ����Ҫ ��֪�� ���� �� ������Ϣ

private:
    bool status_of_if_need_to_check; // �Ƿ���Ҫǿ�ƴ� => Ĭ��false
    bool if_have_unchecked_all; // �Ƿ���û�д򿨵� [�����Ƿ�ǿ��] => Ĭ��false
    bool if_have_unchecked_only_necessary; // �Ƿ���û�д򿨵� [ֻ���Ǳ�ǿ�Ƶ�] => Ĭ��false
    bool if_auto_delete_range_file_empty; // �Զ�ɾ���������ļ��Ƿ�Ϊ��
    int auto_delete_range; // �Զ�ɾ�� auto_delete_range ��ǰ(��) �� ʱ���������� �� δ������
    const string auto_delete_range_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\auto_delete_range.dat)";

    class user_in_danger_template {
    public:
        string sno;
        string name;
        string danger_code;
        user_in_danger_template() = default;
        user_in_danger_template(
            string sno,
            string name,
            string danger_code)
            : sno(std::move(sno))
            , name(std::move(name))
            , danger_code(std::move(danger_code))
        {
        }
    };

protected:
    void try_to_load_check_status_file(); // ���Դ� ��״̬ �ļ� // ��ʱ���༴��
    void change_all_status_in_daily_check_file(); // д��״̬
    void auto_delete(); // �Զ�ɾ�� ʱ�������еĹ������� �� ���ڵ�δ���б�
    void change_auto_delete_range(); // ���� �Զ�ɾ�� ����
    void try_to_load_auto_delete_range_file(); // ���ļ��ж�ȡ �Զ�ɾ�� ����
    inline void change_auto_delete_range_file(); // ���ļ��и��� �Զ�ɾ�� ����
    auto if_auto_delete_range_file_is_empty() -> bool; // �Զ�ɾ������ �ļ� �Ƿ�Ϊ��
    void make_sure_auto_delete_range_file_exists() const; // ��Ч�� �Զ�ɾ������ �ļ�
    void switch_status_of_check(); // => �л� �Ƿ�ǿ�ƴ�
    inline void show_status_of_check() const; // => չʾ ��ǰ�Ƿ�ǿ�ƴ�
    void show_unchecked_user(); // => չʾ δ�򿨵��û� [����չʾ���У�Ҳ����ֻչʾǿ�ƶ�δ�򿨵�]
    void generate_unchecked_user_list(); // => ���� δ���û����� [�����������У�Ҳ����ֻ����ǿ�ƶ�δ�򿨵�]
    void show_user_in_danger_today(); // �鿴���� �򿨺� ����Σ�ս���״̬�� �û�
    static void generate_file_of_user_in_danger_today(const vector<user_in_danger_template>& input); // ���� ���� �򿨺� ����Σ�ս���״̬�� �û����� (�ļ�)
    void show_check_status_of_input_user(); // �鿴 �����û��� �����

public:
    daily_health_check_admin(); // => �Զ����¡������򿨡���Ա�б�
    ~daily_health_check_admin();
    void shell_of_nat_admin(); // => ����
};