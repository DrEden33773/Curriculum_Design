#pragma once

#include "daily_health_check.h"
#include "province_information_manager.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// ��Ҫά�����ļ� => daily_health_check_file_location [����Ǳ�����]
class daily_health_check_user : public daily_health_check { // inherited from user_info_receiver
protected:
    void try_to_load_from_file(const string&); // ���� ������ �ļ� [����]
    void try_to_load_from_file_new(const string& input_sno); // ���� ������ �ļ� [����]
    void write_to_file(const string&); // д�� ������ �ļ� [����]
    void write_to_file_new(); // д�� ������ �ļ� [����]
    void show_province_info_direct(); // ��ʾ �и߷����� ��Ϣ
    auto if_have_medium_and_high_risk_region_direct() -> bool; // �Ƿ�����и߷�����

public:
    daily_health_check_user();
    void do_the_check(); // ���� ��
    inline void pre_push_lable()
    {
        cout << "����ǿ��Ҫ����н����򿨣�������δ�򿨣�ϵͳ�����Զ���ת����ҳ�� >>> " << endl
             << endl;
        Sleep(350);
    }
    void show_check_status(); // չʾ ��״̬ [ֻ���Ѿ���ɴ򿨺�չʾ]
};
