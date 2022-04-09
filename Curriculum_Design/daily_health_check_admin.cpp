#include "daily_health_check_admin.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <synchapi.h>
#include <utility>

void daily_health_check_admin::try_to_load_check_status_file()
{
    // ���ڿ���ȷ�� => �������ļ�һ������
    // ������ [��ʱ����]
}

void daily_health_check_admin::change_all_status_in_file()
{
    cout << "�����޸� <������״̬> ... " << endl;
    Sleep(250);
    // ���ļ�
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in); // ˫ָ���Ȳ�����
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        // �޸�
        cached_health_check_info = new health_check_info;
        while (file_daily_check_list.read((char*)cached_health_check_info, sizeof(health_check_info))) {
            cached_health_check_info->if_check_is_necessary = status_of_if_need_to_check;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info));
        }
        delete cached_health_check_info;
        file_daily_check_list.close();
    }
    // end
    cout << "�ļ��е� ״̬ �޸���ϣ��������� [�����б�] ... " << endl;
}

void daily_health_check_admin::update_health_check_file()
{
    // ���Ĺ��ܣ��Զ����� ���������ļ��� �ĳ�Ա�б� => ����ȫ���û�
    cout << "���ڸ��½������ļ� ... " << endl;
    Sleep(1000);
    // ��ʼ�����ļ�
    cu_cache = new current_user_info;
    fstream file_user_info(user_list_file_location, ios::in | ios::binary);
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in); // ˫ָ���Ȳ�����
    if (!file_user_info.is_open()) {
        cout << "���¹����У��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!file_daily_check_list.is_open()) {
        cout << "���¹����У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // ��������ۣ����� �������ļ� �ǲ��ǿյ�
    if (check_if_file_is_empty()) { // �յ�
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))) {
            cached_health_check_info = new health_check_info;
            // ֻ��������������������Ҫ���� �ṹ����ĳ�ʼ��
            cached_health_check_info->account_id = cu_cache->c_account;
            cached_health_check_info->student_id = cu_cache->student_number;
            cached_health_check_info->student_name = cu_cache->real_name;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // дָ����Զ�����
            delete cached_health_check_info;
        }
    } else { // ���ǿյ�
        cached_health_check_info = new health_check_info;
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))
            && file_daily_check_list.read((char*)cached_health_check_info, sizeof(health_check_info))) {
            // something to do! ����и��Ĺ� ������Ϣ �Ļ���һ��Ҫ���¸�����Ϣ [ע�⣬����Ľ����򿨸�����Ϣ�б��Ѿ���������]
            // �������˼�ǣ�������Ա�޸ĸ�����Ϣ��ʱ�򣬲���Ҫ�� [�˻�����ģ��] �е����޸���� [�����򿨸�����Ϣ�б�]
            // �������������Աɾ����һ���û�ʱ����Ҫ�� [�˻�����ģ��] �е���ά����� [�����򿨸�����Ϣ�б�] (ɾ����Ӧ��Ϣ)
            if (cu_cache->student_number != cached_health_check_info->student_id || cu_cache->real_name != cached_health_check_info->student_name) {
                cached_health_check_info->account_id = cu_cache->c_account;
                cached_health_check_info->student_id = cu_cache->student_number;
                cached_health_check_info->student_name = cu_cache->real_name;
                // Ȼ���д
                int temp_POS = file_daily_check_list.tellg(); // ��ȡ��ָ��
                file_daily_check_list.seekp(temp_POS, ios::beg); // дָ��ͬ������ָ��
                file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // ����д��
            }
        }
        delete cached_health_check_info;
        // now, reach the end of "file_daily_check_list", prepare to write!
        int POS = file_daily_check_list.tellg(); /// tell the read ptr
        file_daily_check_list.seekp(POS, ios::beg); /// update the write ptr
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))) {
            cached_health_check_info = new health_check_info; // ���뷴��new����Ϊnew�����Ĳ�����ȷ�ĳ�ʼ���˵�
            cached_health_check_info->account_id = cu_cache->c_account;
            cached_health_check_info->student_id = cu_cache->student_number;
            cached_health_check_info->student_name = cu_cache->real_name;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // дָ����Զ�����
            delete cached_health_check_info;
        }
    }
    // �����ļ��������ر��ļ�������ָ��
    file_daily_check_list.close();
    file_user_info.close();
    delete cached_health_check_info;
    delete cu_cache;
}

void daily_health_check_admin::auto_delete()
{
    // �Զ�ɾ�� => 1.ʱ�������еĹ������� 2.���ڵ�δ���û��ļ�
}

void daily_health_check_admin::change_auto_delete_range()
{
    cout << "��ǰ�� <{δ������} �Զ�ɾ������> Ϊ => [" << auto_delete_range << "��] ... " << endl;
    cout << "<�Զ�ɾ������ N> ָ���ǣ���ɾ�� N ��ǰ(��)������ {δ������} ... " << endl;
    cout << "��ע�⣡�����Ҫͣ�øù��ܣ����������⸺�������������ͣ�øù��ܣ������� [�����������] ��" << endl;
    while (true) {
        Sleep(250);
        cout << "�����������޸ĺ�� <�Զ�ɾ������> : ";
        int input;
        cin >> input;
        if (!input) {
            cout << "������Ч�����������룡" << endl;
            cout << endl;
        } else {
            auto_delete_range = input;
            break;
        }
    }
    change_auto_delete_range_file();
    if (auto_delete_range > 0) {
        cout << "�ѽ� <{δ������} �Զ�ɾ������> ����Ϊ [" << auto_delete_range << "��] ���������� [�����򿨹���˵�] ... " << endl;
    } else {
        cout << "��ȡ�� <�Զ�ɾ�� {δ������}> ���ܣ��������� [�����򿨹���˵�] ... " << endl;
    }
    Sleep(300);
    system("cls");
}

void daily_health_check_admin::try_to_load_auto_delete_range_file()
{
    if (if_auto_delete_range_file_empty) {
        // �Զ�ɾ�������ļ� Ϊ��
        // ά��Ĭ�� => 7��
    } else {
        // �Զ�ɾ�������ļ� ������ => ��ȡ
        // �����ļ��ض�����
        fstream file;
        file.open(auto_delete_range_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "��ȡ�Զ�ɾ�����޹����У��� auto_delete_range.dat ʧ�ܣ������Զ��˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read((char*)(&auto_delete_range), sizeof(int));
        // ��ȡ����
        file.close();
    }
}

void daily_health_check_admin::make_sure_auto_delete_range_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(auto_delete_range_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� auto_delete_range.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // ��ʱ�ر�
}

auto daily_health_check_admin::if_auto_delete_range_file_is_empty() -> bool
{
    make_sure_auto_delete_range_file_exists(); // ȷ���ļ������Ĳ���
    fstream file;
    file.open(auto_delete_range_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� auto_delete_range.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* auto_delete_range_checker = new int;
    bool if_empty = true;
    while (file.read((char*)(auto_delete_range_checker), sizeof(int))) {
        if_empty = false;
        break;
    }
    file.close();
    delete auto_delete_range_checker;
    if_auto_delete_range_file_empty = if_empty;
    return if_empty;
}

daily_health_check_admin::daily_health_check_admin()
{
    // ��ʼ��
    if_have_unchecked_all = false;
    if_have_unchecked_only_necessary = false;
    status_of_if_need_to_check = false;
    auto_delete_range = 7; // �Զ�ɾ������Ĭ��Ϊ7��
    today_unchecked_file_location += current_time.time_str();
    today_unchecked_file_location += ".txt";
    temp_today_unchecked_file_location += current_time.time_str();
    temp_today_unchecked_file_location += ".txt";
    // �Զ���ȡ �Զ�ɾ������
    try_to_load_auto_delete_range_file();
    cout << "�Ѽ��� �Զ�ɾ�����ޣ�" << endl;
    // �Զ����� ������ �ļ�
    update_health_check_file();
    // ������ʾ
    cout << "�Ѹ��½������ļ����������� [�����򿨹������] ... " << endl;
    Sleep(250);
}

inline void daily_health_check_admin::change_auto_delete_range_file()
{
    fstream file;
    file.open(auto_delete_range_file_location, ios::out | ios::binary);
    // ios::app => ���ļ�����������β��������ݡ�����ļ������ڣ����½����ļ�
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� auto_delete_range.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.write((char*)(&auto_delete_range), sizeof(int));
    file.close();
}

void daily_health_check_admin::switch_status_of_check()
{
    show_status_of_check();
    cout << "�Ƿ��л�״̬��(����Y/y���л���������������ǿ��ַ����л�) >> ";
    char flag;
    cin >> flag;
    if (flag == 'y' || flag == 'Y') {
        if (status_of_if_need_to_check) {
            status_of_if_need_to_check = false;
            cout << "״̬���л�Ϊ => <����Ҫ> ����ÿ�ս����򿨣�";
        } else {
            status_of_if_need_to_check = true;
            cout << "״̬���л�Ϊ => <��Ҫ> ����ÿ�ս����򿨣�";
        }
    } else {
        cout << "δ�л�״̬��";
    }
    cout << endl;

    cout << "�������� [���ܲ˵�] ... " << endl;
}

inline void daily_health_check_admin::show_status_of_check()
{
    cout << "��ǰ״̬Ϊ => ";
    if (status_of_if_need_to_check) {
        cout << "<��Ҫ> ����ÿ�ս�����" << endl;
    } else {
        cout << "<����Ҫ> ����ÿ�ս�����" << endl;
    }
}

void daily_health_check_admin::show_unchecked_user()
{
    cout << "����1 => չʾ������δ�򿨡����û� || ������������ǿ��ַ� => ֻչʾ����ǿ�ƶ�δ�򿨡����û� >> ";
    char flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::binary | ios::in);
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // pre-print the list
    cout << "��ʼ���������" << endl;
    cout << "=================================================" << endl;
    cout << setw(4) << "����" << setw(10) << "ѧ��" << endl;
    // print by case
    bool judger;
    cached_health_check_info = new health_check_info;
    if (flag == '1') {
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked) {
                cout << setw(4);
                cout << cached_health_check_info->student_name;
                cout << setw(10);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    } else {
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                cout << setw(4);
                cout << cached_health_check_info->student_name;
                cout << setw(10);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    }
    cout << "=================================================" << endl;
    file_daily_check_list.close();
    delete cached_health_check_info;
    cout << "���������ϣ������ص� [�����򿨹���˵�] ... " << endl;
    Sleep(250);
}

void daily_health_check_admin::generate_unchecked_user_list()
{
    // ��α����� ���ļ���ʽ�����ˡ� => ��ΪҪ�С��ɶ��ԡ���������ļ�ǡ��û�С���˽�ԡ�
    cout << "����1 => ���ɡ�����δ�򿨡��û������� || ������������ǿ��ַ� => ֻ���ɡ���ǿ�ƶ�δ�򿨡��û������� >> ";
    char flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::in | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream file_unchecked_list(today_unchecked_file_location, ios::out);
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� unchecked_list_XXXX-XX-XX.txt ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // start generate the new file
    cached_health_check_info = new health_check_info;
    if (flag == '1') {
        file_unchecked_list << current_time.time_str() << " ����δ�򿨵� �û�������" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << setw(4) << "����" << setw(10) << "ѧ��" << endl;
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked) {
                file_unchecked_list << setw(4);
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(10);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    } else {
        file_unchecked_list << current_time.time_str() << " ��ǿ�ƣ���δ�򿨵� �û�������" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << setw(4) << "����" << setw(10) << "ѧ��" << endl;
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                file_unchecked_list << setw(4);
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(10);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    }
    file_unchecked_list.close();
    file_daily_check_list.close();
    delete cached_health_check_info;
    cout << "������ ��Ӧ�� δ���û��������������� [�����򿨹������] ... " << endl;
    Sleep(250);
}

void daily_health_check_admin::shell()
{
    // �������
    cout << "��ӭ���� [�����򿨹������]�����漴��չʾ [���ܲ˵�] ... " << endl;
    Sleep(250);
    while (true) {
        cout << endl;
        cout << "============================================" << endl;
        cout << setw(4) << "1. �鿴��ǰ״̬";
        cout << setw(4) << "2. �л�״̬";
        cout << setw(4) << "3. �鿴δ���û�";
        cout << setw(4) << "4. ����δ���û��б�";
        cout << setw(4) << "5. ���½������ļ�";
        cout << setw(4) << "6. �޸� <�Զ�ɾ��δ���û��б�> ������ (Ĭ��Ϊ7��(��)ǰ)";
        cout << setw(4) << "7. �ٴ���ʾ [���ܲ˵�]";
        cout << setw(4) << "8. �˳��������";
        cout << "============================================" << endl;
        cout << "����������ѡ�� >> ";
        int flag;
        cin >> flag;
        if (flag == 1) {
            show_status_of_check();
        } else if (flag == 2) {
            switch_status_of_check();
        } else if (flag == 3) {
            show_unchecked_user();
        } else if (flag == 4) {
            generate_unchecked_user_list();
        } else if (flag == 5) {
            cout << "���ڿ�ʼ<�ֶ�����>�������ļ� ... " << endl;
            update_health_check_file();
            Sleep(250);
            cout << "����� <�������ļ� �� �ֶ�����>�������ص� [���ܲ˵�] ... " << endl;
        } else if (flag == 6) {
            change_auto_delete_range();
        } else if (flag == 7) {
            cout << "�����ٴ�չʾ [���ܲ˵�] ... " << endl;
            Sleep(250);
            continue;
        } else if (flag == 8) {
            cout << "�յ����������� [����Ա�˵�] ... " << endl;
            Sleep(350);
            system("cls");
            break;
        } else {
            cout << "����δ�������������·��� [���ܲ˵�] ... " << endl;
            Sleep(250);
        }
    }
}
