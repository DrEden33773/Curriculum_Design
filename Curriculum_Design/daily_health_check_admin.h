#pragma once

#include "admin_AccountInfoReceiver.h"
#include "daily_health_check.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

protected:
    void try_to_load_check_status_file(); // ���Դ��ļ�
    void change_all_status_in_file(); // д��״̬
    void update_health_check_file(); // ���� ������ ��Ա�б�
    void auto_delete(); // �Զ�ɾ�� ʱ�������еĹ������� �� ���ڵ�δ���б�
    void change_auto_delete_range(); // ���� �Զ�ɾ�� ����
    void try_to_load_auto_delete_range_file(); // ���ļ��ж�ȡ �Զ�ɾ�� ����
    inline void change_auto_delete_range_file(); // ���ļ��и��� �Զ�ɾ�� ����
    auto if_auto_delete_range_file_is_empty() -> bool; // �Զ�ɾ������ �ļ� �Ƿ�Ϊ��
    void make_sure_auto_delete_range_file_exists(); // ��Ч�� �Զ�ɾ������ �ļ�
    void switch_status_of_check(); // => �л� �Ƿ�ǿ�ƴ�
    inline void show_status_of_check(); // => չʾ ��ǰ�Ƿ�ǿ�ƴ�
    void show_unchecked_user(); // => չʾ δ�򿨵��û� [����չʾ���У�Ҳ����ֻչʾǿ�ƶ�δ�򿨵�]
    void generate_unchecked_user_list(); // => ���� δ���û����� [�����������У�Ҳ����ֻ����ǿ�ƶ�δ�򿨵�]

public:
    daily_health_check_admin(); // => �Զ����¡������򿨡���Ա�б�
    void shell(); // => ����
};