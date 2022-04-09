#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

daily_health_check::daily_health_check()
{
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
        file.write((char*)(&current_time), sizeof(time_manager));
    } else {
        // �ȶ�β�����ж��Ƿ�д��
        file.seekg(-sizeof(time_manager), ios::end);
        file.seekp(-sizeof(time_manager), ios::end);
        file.read((char*)(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // ���µ�ʱ����ǵ�ǰ���ڣ�nothing to do
        } else {
            file.seekp(0, ios::end); // дָ��ָβ
            file.write((char*)(&current_time), sizeof(time_manager)); // ����д��
        }
    }
    file.close(); // ��ʱ�ر�
}

inline void daily_health_check::make_sure_file_exists()
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

auto daily_health_check::check_if_file_is_empty() -> bool
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
    checker = new health_check_info;
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(health_check_info))) {
        if_empty = false;
        break;
    }
    file.close();
    delete checker;
    if_daily_check_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::make_sure_dictionary_exists() // �õ�time_dictionary_file_location
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

auto daily_health_check::check_if_dictionary_is_empty() -> bool
{
    make_sure_file_exists(); // ȷ���ļ������Ĳ���
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
    while (file.read((char*)(time_dict_checker), sizeof(dict_checker))) {
        if_empty = false;
        break;
    }
    file.close();
    delete time_dict_checker;
    if_time_dictionary_file_is_empty = if_empty;
    return if_empty;
}
