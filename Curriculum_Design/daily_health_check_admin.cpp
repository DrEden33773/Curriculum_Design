#include "daily_health_check_admin.h"

#include <conio.h>

#include "time_manager.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <synchapi.h>
#include <vector>

void daily_health_check_admin::try_to_load_check_status_file()
{
    fstream file_daily_check_list(daily_health_check_file_location, ios::app | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "Ԥ���� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file_daily_check_list.close();
    file_daily_check_list.open(daily_health_check_file_location, ios::binary | ios::in);
    if (!file_daily_check_list.is_open()) {
        cout << "�� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cached_health_check_info_tr = new health_check_info_trans;
    file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
    status_of_if_need_to_check = cached_health_check_info_tr->if_check_is_necessary;
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
}

void daily_health_check_admin::change_all_status_in_daily_check_file()
{
    cout << "���ڣ����ļ��е� <������״̬> ���и��� ... " << endl;
    Sleep(250);
    // ���ļ�
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in);
    // ʹ�� out & in ���ļ� => ȷ�� ��дָ����ι�ָ��λ�� ͬʱ ȷ�� ���ļ���ʱ��ɾ��ԭ������
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // �޸�
    cached_health_check_info_tr = new health_check_info_trans;
    // bug => ��� ��д ������ [������˵��Ӧ�������ֶ�д������]
    // bug => �޸�����ֻ���ǿ�һ����ʱ�ļ�Ȼ������д��, Ȼ����ļ���
    fstream temp(temp_daily_health_check_file_location, ios::out | ios::binary);
    if (!temp.is_open()) {
        cout << "д���ļ������У����� temp_daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file_daily_check_list.read(
        reinterpret_cast<char*>(cached_health_check_info_tr),
        sizeof(health_check_info_trans))) {
        cached_health_check_info_tr->if_check_is_necessary = status_of_if_need_to_check;
        temp.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
    }
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
    file_daily_check_list.close();
    temp.close();
    remove(daily_health_check_file_location.c_str());
    rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
    // end
    cout << "�ļ��е� <�Ƿ�ǿ�ƽ�����״̬> �޸���ϣ��������� [�����б�] ... " << endl;
}

void daily_health_check_admin::update_health_check_file()
{
    time_manager today;
    // ���Ĺ��ܣ��Զ����� ���������ļ��� �ĳ�Ա�б� => ����ȫ���û�
    cout << "���ڸ��½������ļ� ... " << endl;
    Sleep(350);
    // ��ʼ�����ļ�
    cu_cache = new current_user_info;
    cu_cache_tr = new current_user_info_tr;
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    user_list_file_empty_check(); // ����Ҫ�У�
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
    // ������Ҫ�������user_list.dat �� daily_check_list.dat �� �û����� �Ƿ�һ��
    file_user_info.seekg(0, ios::end);
    const auto end_pos_user_list = file_user_info.tellg();
    int num_of_user_info = end_pos_user_list / sizeof(current_user_info_tr);
    file_daily_check_list.seekg(0, ios::end);
    const auto end_pos_daily_check_list = file_daily_check_list.tellg();
    int num_of_daily_check = end_pos_daily_check_list / sizeof(health_check_info_trans);
    // bug => ԭ��û������<��дָ�����ûؿ�ͷ>�������ļ��д����⣡[fixed]
    file_user_info.seekg(0, ios::beg);
    file_user_info.seekp(0, ios::beg);
    file_daily_check_list.seekg(0, ios::beg);
    file_daily_check_list.seekp(0, ios::beg);
    // ��������ۣ����� �������ļ� �ǲ��ǿյ�
    if (check_if_file_is_empty()) {
        // �յ�
        while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
            *cu_cache = *cu_cache_tr;
            cached_health_check_info->account_id = cu_cache->c_account;
            cached_health_check_info->student_id = cu_cache->student_number;
            cached_health_check_info->student_name = cu_cache->real_name;
            *cached_health_check_info_tr = *cached_health_check_info;
            file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // дָ����Զ�����
        }
    } else {
        // ���ǿյ�
        if (num_of_user_info == num_of_daily_check) {
            // ������ȣ�ֻ���ܸ���
            fstream temp_file_daily_check_list(temp_daily_health_check_file_location, ios::out | ios::binary);
            if (!temp_file_daily_check_list.is_open()) {
                cout << "���¹����У����� temp_daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))
                && file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
                *cu_cache = *cu_cache_tr;
                *cached_health_check_info = *cached_health_check_info_tr;
                if (!(cu_cache->student_number == cached_health_check_info->student_id) || !(cu_cache->real_name == cached_health_check_info->student_name)) {
                    // cached_health_check_info->account_id = cu_cache->c_account;
                    cached_health_check_info->student_id = cu_cache->student_number;
                    cached_health_check_info->student_name = cu_cache->real_name;
                }
                if (!(cached_health_check_info->record_time == today)) {
                    // ���ڷ�������
                    cached_health_check_info->record_time = today;
                    cached_health_check_info->if_checked = false;
                }
                // д�� ��������
                *cached_health_check_info_tr = *cached_health_check_info;
                *cu_cache_tr = *cu_cache;
                // Ȼ���д
                temp_file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // ����д��
            }
            file_daily_check_list.close();
            temp_file_daily_check_list.close();
            remove(daily_health_check_file_location.c_str());
            rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
        } else {
            // ��������ȣ����û�ɾ��
            // ֱ��д�� temp Ȼ���ٸ����Ļ���
            // TODO: ���޸� => ������ĵ��Ǹ��������鷳�� => һ���û����������˱䶯���ͻ����ԭ���û�������status => fixed
            // TODO: ����vector�ݴ棬Ȼ���ж�
            // pre_job => fill the vector
            vector<health_check_info> original_health_check_info {};
            while (file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
                *cached_health_check_info = *cached_health_check_info_tr;
                original_health_check_info.push_back(*cached_health_check_info);
            }
            // first: get original record time
            file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
            *cached_health_check_info = *cached_health_check_info_tr;
            const time_manager original_record_time = cached_health_check_info->record_time;
            bool if_updated_date = !(original_record_time == today);
            // second: write temp
            file_daily_check_list.close();
            fstream temp_file_daily_check_list(temp_daily_health_check_file_location, ios::out | ios::binary);
            if (!temp_file_daily_check_list.is_open()) {
                cout << "���¹����У����� temp_daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
                *cu_cache = *cu_cache_tr;
                cached_health_check_info->account_id = cu_cache->c_account;
                cached_health_check_info->student_id = cu_cache->student_number;
                cached_health_check_info->student_name = cu_cache->real_name;
                auto iter = find(
                    original_health_check_info.begin(),
                    original_health_check_info.end(),
                    *cached_health_check_info);
                bool if_have_record_in_original = iter != original_health_check_info.end(); // ���õ��ģ�end������ָ�գ��൱��nullptr
                if (if_have_record_in_original) {
                    cached_health_check_info->record_time = iter->record_time;
                    cached_health_check_info->if_checked = iter->if_checked;
                    if (if_updated_date) {
                        cached_health_check_info->record_time = today;
                        cached_health_check_info->if_checked = false;
                    }
                } else {
                    cached_health_check_info->record_time = today;
                    cached_health_check_info->if_checked = false;
                }
                *cached_health_check_info_tr = *cached_health_check_info;
                temp_file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // дָ����Զ�����
            }
            temp_file_daily_check_list.close();
            // third: rename
            remove(daily_health_check_file_location.c_str());
            rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
        }
    }
    // �����ļ��������ر��ļ�������ָ��
    file_daily_check_list.close();
    file_user_info.close();
    delete cu_cache;
    delete cu_cache_tr;
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
}

void daily_health_check_admin::auto_delete()
{
    // ���� remove �� rename �������������������ļ��Ĳ�����������Ҫ���ļ�
    // �Զ�ɾ�� => 1.ʱ�������еĹ������� 2.���ڵ�δ���û��ļ�
    if (auto_delete_range > 0) {
        // �õ��µ�ʱ������ & ɾ������δ���ļ�
        fstream old_time_dict_file(time_dictionary_file_location, ios::in | ios::binary);
        fstream new_time_dict_file(temp_time_dictionary_file_location, ios::out | ios::binary);
        if (!old_time_dict_file.is_open()) {
            cout << "�Զ�ɾ�������У��޷���ԭ�е� time_dictionary.dat �������Զ��˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        if (!new_time_dict_file.is_open()) {
            cout << "�Զ�ɾ�������У��޷������µ� time_dictionary.dat �������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (old_time_dict_file.read(reinterpret_cast<char*>(&cached_time), sizeof(time_manager))) {
            if (current_time - cached_time < auto_delete_range) {
                new_time_dict_file.write(reinterpret_cast<char*>(&cached_time), sizeof(time_manager));
            } else {
                // ��������
                string cached_unchecked_file_location = name_base;
                cached_unchecked_file_location += cached_time.time_str();
                cached_unchecked_file_location += ".txt";
                remove(cached_unchecked_file_location.c_str());
            }
        }
        old_time_dict_file.close();
        new_time_dict_file.close();
        // ɾ���ɵ�ʱ������
        remove(time_dictionary_file_location.c_str());
        // �������µ�ʱ������
        rename(temp_time_dictionary_file_location.c_str(), time_dictionary_file_location.c_str());
        // done!
        cout << "��ɾ�� <���ڵ�δ���û��ļ�> ... " << endl;
    } else {
        cout << "�ѽ��� <�Զ�ɾ�����ڵ�δ���û��ļ�> ���ܣ������˲��� ... " << endl;
    }
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
        cout << "�ѽ� <{δ������} �Զ�ɾ������> ����Ϊ [" << auto_delete_range << "��] ������������� [�����򿨹���˵�] ... " << endl;
    } else {
        cout << "��ȡ�� <�Զ�ɾ�� {δ������}> ���ܣ������������ [�����򿨹���˵�] ... " << endl;
    }
    _getch();
    Sleep(250);
    system("cls");
}

void daily_health_check_admin::try_to_load_auto_delete_range_file()
{
    if_auto_delete_range_file_is_empty(); // => ���Է���ֵ�����ͬʱ�� ȷ����Ч�� �Զ�ɾ���ļ�
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
        file.read(reinterpret_cast<char*>(&auto_delete_range), sizeof(int));
        // ��ȡ����
        file.close();
    }
}

void daily_health_check_admin::make_sure_auto_delete_range_file_exists() const
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

bool daily_health_check_admin::if_auto_delete_range_file_is_empty()
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
    while (file.read(reinterpret_cast<char*>(auto_delete_range_checker), sizeof(int))) {
        if_empty = false;
        break;
    }
    file.close();
    delete auto_delete_range_checker;
    auto_delete_range_checker = nullptr;
    if_auto_delete_range_file_empty = if_empty;
    return if_empty;
}

daily_health_check_admin::daily_health_check_admin()
    : daily_health_check("flag")
{
    system("cls");
    // ��ʼ��
    if_have_unchecked_all = false;
    if_have_unchecked_only_necessary = false;
    status_of_if_need_to_check = false;
    auto_delete_range = 7; // �Զ�ɾ������Ĭ��Ϊ7��
    // ���ݵ������� �趨��ȷ�� δ������ �ļ���
    today_unchecked_file_location += current_time.time_str();
    today_unchecked_file_location += ".txt";
    temp_today_unchecked_file_location += current_time.time_str();
    temp_today_unchecked_file_location += ".txt";
    // �Զ���ȡ �Զ�ɾ������
    try_to_load_auto_delete_range_file();
    cout << "�Ѽ��� �Զ�ɾ�����ޣ�" << endl;
    // �Զ�ɾ�� ���ڵ� δ���û��б�
    auto_delete();
    // �Զ����� ǿ�ƽ����� ״̬
    try_to_load_check_status_file();
    cout << "�Ѽ��� �Ƿ�ǿ�ƽ����� ���״̬��" << endl;
    // �Զ����� ������ �ļ�
    update_health_check_file();
    // ������ʾ
    cout << "�Ѹ��� ���������û��� <�������б�> ���������� [�����򿨹������] ... " << endl;
    Sleep(250);
}

daily_health_check_admin::~daily_health_check_admin()
{
    /*
     * Nothing to do!
     * 'Cause this destructor will call the one of base class,
     * which will free all ptr_var-allocated space in the heap
     */
}

inline void daily_health_check_admin::change_auto_delete_range_file()
{
    fstream file;
    file.open(auto_delete_range_file_location, ios::out | ios::binary | ios::in);
    // out��in һ���� => ��ֹɾ������
    // ios::app => ���ļ�����������β��������ݡ�����ļ������ڣ����½����ļ�
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� auto_delete_range.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.write(reinterpret_cast<char*>(&auto_delete_range), sizeof(int));
    file.close();
}

void daily_health_check_admin::switch_status_of_check()
{
    show_status_of_check();
    cout << "�Ƿ��л�״̬��(����Y/y���л���������������ǿ��ַ����л�) >> ";
    string flag;
    cin >> flag;
    if (flag == "y" || flag == "Y") {
        if (status_of_if_need_to_check) {
            status_of_if_need_to_check = false;
            cout << "״̬���л�Ϊ => <����Ҫ> ����ÿ�ս����򿨣�";
        } else {
            status_of_if_need_to_check = true;
            cout << "״̬���л�Ϊ => <��Ҫ> ����ÿ�ս����򿨣�";
        }
        change_all_status_in_daily_check_file(); // ����ÿ���û��� ǿ�ƴ�״��
    } else {
        cout << "δ�л�״̬��";
    }
    cout << endl;
    cout << "�������� [���ܲ˵�] ... " << endl;
    Sleep(250);
}

inline void daily_health_check_admin::show_status_of_check() const
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
    string flag;
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
    cout << "\t"
         << "����" << setw(18) << "ѧ��" << endl;
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    if (flag == "1") {
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked) {
                cout << "\t";
                cout << cached_health_check_info->student_name;
                cout << setw(18);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    } else {
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                cout << "\t";
                cout << cached_health_check_info->student_name;
                cout << setw(18);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    }
    cout << "=================================================" << endl;
    file_daily_check_list.close();
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    cout << "���������ϣ������������ [�����򿨹������] ... " << endl;
    _getch();
    Sleep(250);
}

void daily_health_check_admin::generate_unchecked_user_list()
{
    // ��α����� ���ļ���ʽ�����ˡ� => ��ΪҪ�С��ɶ��ԡ���������ļ�ǡ��û�С���˽�ԡ�
    cout << "����1 => ���ɡ�����δ�򿨡��û������� || ������������ǿ��ַ� => ֻ���ɡ���ǿ�ƶ�δ�򿨡��û������� >> ";
    string flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::in | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream file_unchecked_list(today_unchecked_file_location, ios::out); // ����� out �Ϳ��ԣ�����Ҫ�����ǰ���ݵ�
    if (!file_daily_check_list.is_open()) {
        cout << "д���ļ������У��� unchecked_list_XXXX-XX-XX.txt ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // start generate the new file
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    if (flag == "1") {
        file_unchecked_list << current_time.time_str() << " ����δ�򿨵� �û�������" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << "\t"
                            << "����" << setw(18) << "ѧ��" << endl;
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked) {
                file_unchecked_list << "\t";
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(18);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    } else {
        file_unchecked_list << current_time.time_str() << " ��ǿ�ƣ���δ�򿨵� �û�������" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << "\t"
                            << "����" << setw(18) << "ѧ��" << endl;
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                file_unchecked_list << "\t";
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(18);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    }
    file_unchecked_list.close();
    file_daily_check_list.close();
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    cout << "������ ��Ӧ�� δ���û������������������ [�����򿨹������] ... " << endl;
    _getch();
    Sleep(250);
}

void daily_health_check_admin::shell_of_NAT_admin()
{
    // �������
    cout << endl;
    cout << "��ӭ���� [������ <����Ա��>]�����漴��չʾ [���ܲ˵�] ... " << endl;
    Sleep(250);
    while (true) {
        cout << endl;
        cout << "������ <����Ա��> [���ܲ˵�] ... " << endl;
        cout << "============================================" << endl;
        cout << "\t"
             << "1. �鿴��ǰ <�Ƿ�ǿ�������û�ÿ�ս�����> ״̬" << endl;
        cout << "\t"
             << "2. �л� <�Ƿ�ǿ�������û�ÿ�ս�����> ״̬" << endl;
        cout << "\t"
             << "3. �鿴����δ���û�" << endl; // TODO: Add Today's Date => finished
        cout << "\t"
             << "4. ���ɵ���δ���û��б�" << endl; // TODO: Add Today's Date => finished
        cout << "\t"
             << "5. �ֶ����½������ļ�" << endl;
        cout << "\t"
             << "6. �޸� <�Զ�ɾ��δ���û��б�> ������ (Ĭ��Ϊ7��(��)ǰ)" << endl;
        cout << "\t"
             << "7. �鿴���� <���������û��б�> (�������ļ�)" << endl;
        cout << "\t"
             << "8. �ٴ���ʾ [���ܲ˵�]" << endl;
        cout << "\t"
             << "9. �˳��������" << endl;
        cout << "============================================" << endl;
        cout << "����������ѡ�� >> ";
        string flag;
        cin >> flag;
        cout << endl;
        if (flag == "1") {
            show_status_of_check();
        } else if (flag == "2") {
            switch_status_of_check();
        } else if (flag == "3") {
            show_unchecked_user();
        } else if (flag == "4") {
            generate_unchecked_user_list();
        } else if (flag == "5") {
            cout << "����������󣬿�ʼ<�ֶ�����>�������ļ� ... " << endl;
            // cout << "��ע�⣬���½������ļ��������û��Ľ��������״̬���ᱻ��ʼ��������������� ... ";
            _getch();
            update_health_check_file();
            Sleep(250);
            cout << "����� <�������ļ� �� �ֶ�����>�������ص� [���ܲ˵�] ... " << endl;
        } else if (flag == "6") {
            change_auto_delete_range();
        } else if (flag == "8") {
            cout << "�����ٴ�չʾ [���ܲ˵�] ... " << endl;
            Sleep(250);
        } else if (flag == "9") {
            cout << "�յ����������� [����Ա�˵�] ... " << endl;
            Sleep(350);
            system("cls");
            break;
        } else if (flag == "7") {
            // TODO: �鿴���� <�����û��б�> (�������ļ�)
            cout << "���ڼӼ������� ... " << endl;
        } else {
            cout << "����δ�������������·��� [���ܲ˵�] ... " << endl;
            Sleep(250);
        }
    }
}
