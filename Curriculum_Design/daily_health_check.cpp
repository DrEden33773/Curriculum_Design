#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

daily_health_check::daily_health_check() /// ��������Ҫ����Ҫ��Ҫ����˺���
{
    var_initializer();
    check_if_file_is_empty(); // ֱ�Ӻ��Է���ֵ����
    check_if_dictionary_is_empty(); // ֱ�Ӻ��Է���ֵ����
    // ���棬׼������ => ʱ�������ļ�
    fstream file;
    file.open(time_dictionary_file_location, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "����ʱ������ʱ���� time_dictionary.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (if_time_dictionary_file_is_empty) {
        // ֱ��д��
        file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager));
    } else {
        constexpr int trans = sizeof(time_manager); // constexpr => �������Ż�
        // �ȶ�β�����ж��Ƿ�д��
        file.seekg(-trans, ios::end);
        file.seekp(-trans, ios::end);
        file.read(reinterpret_cast<char*>(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // ���µ�ʱ����ǵ�ǰ���ڣ�nothing to do
        } else {
            file.seekp(0, ios::end); // дָ��ָβ
            file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager)); // ����д��
        }
    }
    file.close(); // ��ʱ�ر�
}

daily_health_check::daily_health_check(const string& any)
{
    var_initializer();
    check_if_file_is_empty(); // ֱ�Ӻ��Է���ֵ����
    check_if_dictionary_is_empty(); // ֱ�Ӻ��Է���ֵ����
    // ���棬׼������ => ʱ�������ļ�
    fstream file;
    file.open(time_dictionary_file_location, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "����ʱ������ʱ���� time_dictionary.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (if_time_dictionary_file_is_empty) {
        // ֱ��д��
        file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager));
    } else {
        constexpr int trans = sizeof(time_manager);
        // �ȶ�β�����ж��Ƿ�д��
        file.seekg(-trans, ios::end);
        file.seekp(-trans, ios::end);
        file.read(reinterpret_cast<char*>(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // ���µ�ʱ����ǵ�ǰ���ڣ�nothing to do
        } else {
            file.seekp(0, ios::end); // дָ��ָβ
            file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager)); // ����д��
        }
    }
    file.close(); // ��ʱ�ر�
}

daily_health_check::~daily_health_check()
{
    // bug => crtisvalidheappointer(block) [fixed]
    delete cached_health_check_info_tr;
    delete cached_health_check_info;
    delete current_health_check_info;
    delete checker; // => bug!!! [fixed]
}

inline void daily_health_check::make_sure_file_exists() const
{
    fstream file;
    /// now, tries to new the file
    file.open(daily_health_check_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� daily_health_check_list.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // ��ʱ�ر�
}

bool daily_health_check::check_if_file_is_empty()
{
    make_sure_file_exists(); // ȷ���ļ������Ĳ���
    fstream file;
    file.open(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� daily_health_check_list.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // checker = new health_check_info;
    checker_trans = new health_check_info_trans;
    bool if_empty = true;
    while (file.read(reinterpret_cast<char*>(checker_trans), sizeof(health_check_info_trans))) {
        if_empty = false;
        break;
    }
    file.close();
    delete checker_trans;
    checker_trans = nullptr;
    // delete checker;
    // checker = nullptr; // => ��ֹҰָ��
    if_daily_check_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::make_sure_dictionary_exists() const
// �õ�time_dictionary_file_location
{
    fstream file;
    /// now, tries to new the file
    file.open(time_dictionary_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� time_dictionary.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // ��ʱ�ر�
}

bool daily_health_check::check_if_dictionary_is_empty()
{
    make_sure_dictionary_exists(); // ȷ�� ʱ�������ļ� �����Ĳ���
    fstream file;
    file.open(time_dictionary_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� time_dictionary.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    time_dict_checker = new dict_checker;
    bool if_empty = true;
    while (file.read(reinterpret_cast<char*>(time_dict_checker), sizeof(dict_checker))) {
        if_empty = false;
        break;
    }
    file.close();
    delete time_dict_checker;
    time_dict_checker = nullptr;
    if_time_dictionary_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::var_initializer()
{
    today_unchecked_file_location = name_base;
    temp_today_unchecked_file_location = temp_name_base;
    time_dict_checker = nullptr;
    current_health_check_info = nullptr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    checker = nullptr;
}
