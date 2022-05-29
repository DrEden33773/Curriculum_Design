#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

void daily_health_check::update_health_check_file()
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
    auto num_of_user_info = end_pos_user_list / sizeof(current_user_info_tr);
    file_daily_check_list.seekg(0, ios::end);
    const auto end_pos_daily_check_list = file_daily_check_list.tellg();
    auto num_of_daily_check = end_pos_daily_check_list / sizeof(health_check_info_trans);
    // bug => ԭ��û������<��дָ�����ûؿ�ͷ>�������ļ��д����⣡[fixed]
    file_user_info.seekg(0, ios::beg);
    file_user_info.seekp(0, ios::beg);
    file_daily_check_list.seekg(0, ios::beg);
    file_daily_check_list.seekp(0, ios::beg);
    // �ȿ���user_list_file�ǲ��ǿյ�
    if (!num_of_user_info) {
        file_daily_check_list.clear();
    } else {
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
