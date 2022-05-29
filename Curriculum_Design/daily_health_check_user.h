#pragma once

#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// ��Ҫά�����ļ� => daily_health_check_file_location [����Ǳ�����]
class daily_health_check_user : public daily_health_check {
    // inherited from user_info_receiver
protected:
    void try_to_load_from_file(const string&); // ���� ������ �ļ� [����]
    void try_to_load_from_file_new(const string& input_sno); // ���� ������ �ļ� [����]
    void write_to_file(const string&) const; // д�� ������ �ļ� [����]
    void write_to_file_new(); // д�� ������ �ļ� [����]
    static void show_province_info_direct(); // ��ʾ �и߷����� ��Ϣ
    static bool if_have_medium_and_high_risk_region_direct(); // �Ƿ�����и߷�����

public:
    bool plug_of_if_should_alert;
    daily_health_check_user(); // �չ��캯��
    daily_health_check_user(const string&, const string&, const string&); // �湹�캯��
    daily_health_check_user(const string&, const string&, const string&, const string&); // �ӿڹ��캯��
    ~daily_health_check_user();
    void do_the_check(); // ���� ��
    static void pre_push_label()
    {
        cout << "����ǿ��Ҫ����н����򿨣�������δ�򿨣�ϵͳ�����Զ���ת����ҳ�� >>> " << endl
            << endl;
        Sleep(350);
    }

    static string trans_bool(const bool& in)
    {
        return in ? "��" : "��";
    }

    void show_check_status() const; // չʾ ��״̬ [ֻ���Ѿ���ɴ򿨺�չʾ]
};
