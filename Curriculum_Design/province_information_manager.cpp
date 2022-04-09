#include "province_information_manager.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

province_information_manager::province_information_manager()
{
    for (int& i : status_of_province) {
        i = 0; // ���ȳ�ʼ��
    }
    try_to_load_province_information_file(); // ���ļ���ʼ��
}

void province_information_manager::change_province_status()
{
    string temp_province;
    int temp_status;
    int returned_code;
    while (true) {
        cout << "��������Ҫ�ı� <����״̬> �� <ʡ����������>��";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "����� <ʡ����������> ��Ч������������" << endl;
        }
    }
    while (true) {
        cout << temp_province << " ��ǰ��״̬�ǣ�" << status_list[status_of_province[returned_code]] << endl;
        cout << "������ <���º��״̬����> (0=�ͷ��գ�1=�з��գ�2=�߷���)��";
        cin >> temp_status;
        if (temp_status < 0 || temp_status > 2) {
            system("cls");
            cout << "����� <״̬����> ��Ч������������" << endl;
        } else {
            status_of_province[returned_code] = temp_status;
            cout << "�ѽ� " << temp_province << " ����Ϊ " << status_list[temp_status] << " ״̬" << endl;
            break;
        }
    }
    write_province_information_file_trunc();
}

void province_information_manager::show_input_province_status()
{
    string temp_province;
    int returned_code;
    while (true) {
        cout << "��������Ҫ�鿴 <����״̬> �� <ʡ����������>��";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "����� <ʡ����������> ��Ч������������" << endl;
        }
    }
    cout << endl;
    cout << temp_province << " ��״̬�ǣ�" << status_list[status_of_province[returned_code]] << endl;
}

void province_information_manager::show_all_province_status()
{
    bool if_0 = false, if_1 = false, if_2 = false;
    cout << "���潫���� <״̬��Ϣ> ������� <ʡ������> �������Ϣ��" << endl
         << endl;
    cout << "=========================================" << endl;
    //�߷��յ�����
    cout << endl
         << "  �߷��յ�����" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 2) {
                if_2 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_2) {
        cout << "    �޸߷��յ�����" << endl;
    }
    //�з��յ�����
    cout << endl
         << "  �з��յ�����" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 1) {
                if_1 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_1) {
        cout << "    ���з��յ�����" << endl;
    }
    //�ͷ��յ�����
    cout << endl
         << "  �ͷ��յ�����" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 0) {
                if_0 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_0) {
        cout << "    �޵ͷ��յ�����" << endl;
    }
    cout << endl
         << "=========================================" << endl;
    cout << endl
         << "�����ϣ�" << endl;
}

void province_information_manager::try_to_load_province_information_file()
{
    fstream file;
    file.open(province_file, ios::binary | ios::in);
    if (!file.is_open()) {
        //�����޷��ж��ǡ�û���ļ������ǡ����ļ����Ǵ�ʧ�ܡ�����ʱ��������
    } else {
        for (int i = 0; i < 34; ++i) {
            file.read((char*)(status_of_province + i), sizeof(int));
        }
    }
    file.close();
}

void province_information_manager::write_province_information_file_trunc()
{
    fstream file;
    file.open(province_file, ios::binary | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "��province_information.datʧ�ܣ����򼴽��˳���" << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.write((char*)(status_of_province + i), sizeof(int)); // һ��ֻд��һ���ڴ浥Ԫ����ֹ��������
        }
    }
    file.close();
}

auto province_information_manager::if_input_province_valid(const string& input_province)
    -> int
{
    int result = -1;
    for (int i = 0; i < 34; ++i) {
        if (province_list[i] == input_province) {
            result = i;
        }
    }
    return result;
}

void province_information_manager::show_high_and_medium_risk_regions()
{
    bool if_1 = false, if_2 = false;
    cout << "=========================================" << endl;
    //�߷��յ�����
    cout << "  �߷��յ�����" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 2) {
                if_2 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_2) {
        cout << "    �޸߷��յ�����" << endl;
    }
    //�з��յ�����
    cout << endl
         << "  �з��յ�����" << endl;
    for (int i = 0; i < 34; ++i) {
        cout << "    ";
        for (int j = 0; j < 5; ++j) {
            cout << "    ";
            if (status_of_province[i] == 1) {
                if_1 = true;
                cout.setf(ios::left); // formatter
                cout.width(4); // formatter
                cout << province_list[i];
            }
        }
        cout << endl;
    }
    if (!if_1) {
        cout << "    ���з��յ�����" << endl;
    }
    cout << "=========================================" << endl;
}

auto province_information_manager::if_have_high_and_medium_risk_regions() -> bool
{
    bool result = false;
    for (int i : status_of_province) {
        if (i == 1
            || i == 2) {
            result = true;
        }
    }
    return result;
}