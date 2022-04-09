#include "software_information.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

auto info::if_sftwr_info_is_empty() -> bool
{
    make_sure_sftwr_file_exists(); // ȷ���ļ������Ĳ���
    fstream file;
    file.open(file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� software_information.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* checker = new info(0);
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(info))) {
        if_empty = false;
        break;
    }
    delete checker;
    return if_empty;
}

inline void info::make_sure_sftwr_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� software_information.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // ��ʱ�ر�
}

info::info()
{ // ��Ҫ������ִ�� load_used_time_from_file, �����޵ݹ�
    used_time = 0;
}
info::info(int)
{
    // ��ֹ���޵ݹ飬����Ĺ��캯���������治�����κ����
}
info::~info()
{
    // һ����Ҫ�����������У���ͼ���б���ָ��ռ���ͷ�
    // ����Ĳ����������������
    // �����������������вΣ��޷����캯����������������
}
void info::write_used_time_into_file()
{
    auto* cached_info = new info(0); // û��Ҫ��ʼ�������Դ�������Ҳ���Բ�������
    cached_info->used_time = used_time;
    fstream file;
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "�� software_information.dat ʧ�ܣ������Զ��˳�" << endl;
        Sleep(100);
        exit(-1);
    } else {
        file.write((char*)(cached_info), sizeof(info));
        delete cached_info;
        file.close();
    }
}
void info::update_used_time()
{
    used_time += 1;
}
long long info::get_used_time() const
{
    return used_time;
}
void info::load_used_time_from_file()
{
    auto* cached_info = new info(0); // ���棬���ڱȶ���Ϣ
    fstream file;
    bool if_file_is_empty = if_sftwr_info_is_empty();
    if (if_file_is_empty) { // �ļ��ǿյ�
        // ���� Ĭ�ϲ���
    } else {
        file.open(file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            delete cached_info;
            // ����һ����������ļ����򲻿�����ʧ��
            cout << "�޷��� software_information.dat�������Զ��˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read((char*)(cached_info), sizeof(info)); // �������
        used_time = cached_info->used_time; // ����
        file.close(); // ��ʱ�ر�
        delete cached_info; // �������
    }
}