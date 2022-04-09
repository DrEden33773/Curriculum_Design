#pragma once

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class province_information_manager {
private:
    string province_list[34] = { // λ�� �� ʡ�� �� ��Ӧ��ϵ ��Ҫ��
        "����",
        "���",
        "�Ϻ�",
        "����",
        "�ӱ�",
        "ɽ��",
        "����",
        "����",
        "������",
        "����",
        "�㽭",
        "����",
        "����",
        "����",
        "ɽ��",
        "����",
        "����",
        "����",
        "�㶫",
        "����",
        "�Ĵ�",
        "����",
        "����",
        "����",
        "����",
        "�ຣ",
        "̨��",
        "���ɹ�",
        "����",
        "����",
        "�½�",
        "����",
        "���",
        "����"
    };
    int status_of_province[34] = { 0 }; // ʡ��״̬ -- 0=�ͷ��� 1=�з��� 2=�߷���
    string status_list[3] = { "�ͷ���", "�з���", "�߷���" };
    string province_file = R"(C:\Users\edwar\Desktop\cpp_final_task\province_information.dat)";

public:
    province_information_manager();
    void try_to_load_province_information_file(); // Ԥ�����ļ�
    void write_province_information_file_trunc(); // д���ļ�
    void change_province_status(); // ����ʡ���������״̬
    void show_all_province_status(); // ��ʾ����ʡ���������״̬
    void show_input_province_status(); // ��ʾ��������ķ���״̬
    auto if_input_province_valid(const string&) -> int; // ʡ����Ч�Լ��� [��Ч����-1����Ч���� �±�]
    void show_high_and_medium_risk_regions(); // ��ʾ ���з��� ����
    auto if_have_high_and_medium_risk_regions() -> bool; // ���޸��з�����
};