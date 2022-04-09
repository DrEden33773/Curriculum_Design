#include "account_info_manager.h"
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

account_info_manager::account_info_manager()
{
    // load_file_to_list(); // => �Ѿ�����˶� ��¼ģ����ع������ڲ���Ҫ������������ֱ�Ӵ��ļ��ж�ȡ
}

// ������
/* [mode => 1.ѧ�ž�ȷ���� 2.������ȷ���� 3.�û�����ȷ����] */
auto account_info_manager::if_input_user_exists(
    const string& input, const int& mode, const bool& if_print) -> bool
{
    bool result = false;
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    if (mode == 3) {
        cache = new account_info;
        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account == input) {
                result = true;
                if (if_print) {
                    while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                        if (cu_cache->c_account == cache->account) {
                            break;
                        }
                    }
                    print_detail_info();
                }
                break;
            }
        }
    } else {
        cu_cache = new current_user_info;
        if (mode == 2) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->real_name == input) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_detail_info();
                    }
                    break;
                }
            }
        } else if (mode == 1) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->student_number == input) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_detail_info();
                    }
                    break;
                }
            }
        }
    }
    account_info_file.close();
    user_list_file.close();
    return result;
}

auto account_info_manager::if_input_user_exists_sub( // ģ������
    const string& input, const int& mode, const bool& if_print) -> bool
{
    bool result = false;
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    if (mode == 3) {
        cache = new account_info;
        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account.find(input)) {
                result = true;
                if (if_print) {
                    while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                        if (cu_cache->c_account == cache->account) {
                            break;
                        }
                    }
                    print_partial_matched_info();
                }
            }
        }
    } else {
        cu_cache = new current_user_info;
        if (mode == 2) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->real_name.find(input)) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_partial_matched_info();
                    }
                }
            }
        } else if (mode == 1) {
            while (user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
                if (cu_cache->student_number.find(input)) {
                    result = true;
                    if (if_print) {
                        while (account_info_file.read((char*)(cache), sizeof(account_info))) {
                            if (cu_cache->c_account == cache->account) {
                                break;
                            }
                        }
                        print_partial_matched_info();
                    }
                }
            }
        }
    }
    account_info_file.close();
    user_list_file.close();
    return result;
}

inline void account_info_manager::print_detail_info()
{
    cout << "=============================================================================================" << endl;
    cout << "����" << setw(7 + 3) << "�û���" << setw(14) << "����" << setw(10) << "ѧ��" << setw(9 + 4) << "�����" << setw(3 + 4) << endl;
    cout << endl;
    cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << cache->password << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
    cout << "=============================================================================================" << endl;
}

inline void account_info_manager::print_partial_matched_info()
{
    cout << "������" << cu_cache->real_name << setw(7 + 3)
         << "�û�����" << cache->account << setw(14)
         << "���룺" << cache->password << setw(10)
         << "ѧ�ţ�" << cu_cache->student_number << setw(9 + 4)
         << "����ţ�" << cu_cache->dorm_number << setw(3 + 4) << endl;
}

inline void account_info_manager::open_all_files(fstream& account_info_file, fstream& user_list_file)
{
    account_info_file.open(account_info_file_location, ios::in | ios::binary);
    if (!account_info_file.is_open()) {
        cout << "д������У��� account_info.dat ʧ�ܣ������Զ��˳�����" << endl;
        Sleep(250);
        exit(-1);
    }
    user_list_file.open(user_list_file_location, ios::in | ios::binary);
    if (!user_list_file.is_open()) {
        cout << "д������У��� user_list.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
}

//ɾ���û�
void account_info_manager::delete_a_user()
{
    string temp_user_name;
    bool if_continue_func = true;
    while (true) {
        cout << "����������Ҫɾ�����û��� [�û���] >> ";
        cin >> temp_user_name;
        if (if_input_user_exists(temp_user_name, 3, false)) { // �û�������
            break;
        } else {
            cout << "�����ڸ��û���" << endl
                 << "����Y/y -> ���������û��������������ַ� -> ���� �û���Ϣ������� >> ";
            char flag;
            cin >> flag;
            if (flag == 'y' || flag == 'Y') {
                continue;
            } else {
                if_continue_func = false;
                break;
            }
        }
    }
    if (if_continue_func) {
        cout << "�Ƿ�ȷ��ɾ�� " << temp_user_name << " ��һ�û���(ȷ��������Y/y���������������ַ�) >> ";
        char flag;
        cin >> flag;
        if (flag == 'y' || flag == 'Y') {
            delete_input_user_in_account_info(temp_user_name);
            delete_input_user_in_user_list(temp_user_name);
        } else {
            cout << "�յ�����δɾ���κ��û��������ص��û���Ϣ�������" << endl;
            Sleep(200);
            system("cls");
        }
    }
}

void account_info_manager::delete_input_user_in_account_info(const string& input_user)
{
    // ȫ�µ��߼�
    fstream temp_account_info(temp_account_info_file_location, ios::out | ios::binary | ios::trunc);
    if (!temp_account_info.is_open()) {
        cout << "ɾ�������У�������ʱ�ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream account_info(account_info_file_location, ios::in | ios::binary);
    if (!account_info.is_open()) {
        cout << "ɾ�������У��� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cache = new struct account_info;
    while (account_info.read((char*)(cache), sizeof(account_info))) {
        if (cache->account != input_user) {
            temp_account_info.write((char*)(cache), sizeof(account_info));
        }
    }
    account_info.close();
    temp_account_info.close();
    remove(account_info_file_location.c_str()); // ɾ���ļ�
    rename(temp_account_info_file_location.c_str(), account_info_file_location.c_str()); // ���ļ������� [old-name to new-name]
    delete cache;
}

void account_info_manager::delete_input_user_in_user_list(const string& input_user)
{
    // ȫ�µ��߼�
    fstream temp_user_list(temp_user_list_file_location, ios::out | ios::binary | ios::trunc);
    if (!temp_user_list.is_open()) {
        cout << "ɾ�������У�������ʱ�ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream user_list(user_list_file_location, ios::in | ios::binary);
    if (!user_list.is_open()) {
        cout << "ɾ�������У��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cu_cache = new current_user_info;
    while (user_list.read((char*)(cu_cache), sizeof(current_user_info))) {
        if (cu_cache->c_account != input_user) {
            temp_user_list.write((char*)(cu_cache), sizeof(current_user_info));
        }
    }
    user_list.close();
    temp_user_list.close();
    remove(user_list_file_location.c_str()); // ɾ���ļ�
    rename(temp_user_list_file_location.c_str(), user_list_file_location.c_str()); // ���ļ������� [old-name to new-name]
    delete cu_cache;
}

// չʾ��Ϣ
inline void account_info_manager::not_found()
{
    cout << "��Ǹ����������û������ڣ�" << endl;
}

void account_info_manager::precisely_show_specific_user_info()
{ // ��ȷ����
    cout << "���ڣ���Ҫ���о�ȷ��ѯ ... " << endl;
    Sleep(150);
    string t_sno;
    string t_username;
    string t_realname;
    bool if_finished_search = false;
    while (true) {
        cout << "�������ض���������ָ��ģʽ [1->ѧ�ž�ȷ���� 2->������ȷ���� 3->�û�����ȷ���� 4->�˳���ȷ����] >> ";
        int mode;
        cin >> mode;
        if (mode < 1 || mode > 4) {
            cout << "������Ч�����������룡" << endl;
        } else if (mode != 4) {
            if (mode == 1) {
                cout << "������Ҫ��ȷ��ѯ�� ѧ�� >> ";
                cin >> t_sno;
                if (!if_input_user_exists(t_sno, 1, true)) {
                    not_found();
                }
            } else if (mode == 2) {
                cout << "������Ҫ��ȷ��ѯ�� ���� >> ";
                cin >> t_realname;
                if (!if_input_user_exists(t_realname, 2, true)) {
                    not_found();
                }
            } else if (mode == 3) {
                cout << "������Ҫ��ȷ��ѯ�� �û��� >> ";
                cin >> t_username;
                if (!if_input_user_exists(t_username, 3, true)) {
                    not_found();
                }
            }
            if_finished_search = true;
            break;
        } else {
            cout << "����������һ���˵� ... " << endl;
            Sleep(250);
            system("cls");
            break;
        }
    }
    if (if_finished_search) {
        cout << "����ɾ�ȷ����������������һ���˵� ... " << endl;
        Sleep(250);
        system("cls");
    }
}

void account_info_manager::show_all_user_info()
{
    fstream account_info_file;
    fstream user_list_file;
    open_all_files(account_info_file, user_list_file);
    cout << "�Ƿ���ʾ�û������룿" << endl
         << "( ����Y/y => ��ʾ || ������������ǿ��ַ� => ����ʾ ) >> ";
    char flag;
    cin >> flag;
    cout << endl
         << "������ʾ�����û��������Ϣ >> " << endl;
    cout << "=============================================================================================" << endl;
    cout << "����" << setw(7 + 3) << "�û���" << setw(14) << "����" << setw(10) << "ѧ��" << setw(9 + 4) << "�����" << setw(3 + 4) << endl;
    cout << endl;
    if (flag == 'y' || flag == 'Y') {
        while (account_info_file.read((char*)(cache), sizeof(account_info)) && user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
            cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << cache->password << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
        }
    } else {
        while (account_info_file.read((char*)(cache), sizeof(account_info)) && user_list_file.read((char*)(cu_cache), sizeof(current_user_info))) {
            cout << cu_cache->real_name << setw(7 + 3) << cache->account << setw(14) << "<���벻����ʾ>" << setw(10) << cu_cache->student_number << setw(9 + 4) << cu_cache->dorm_number << setw(3 + 4) << endl;
        }
    }
    cout << "=============================================================================================" << endl;
    cout << "��ʾ��ϣ�" << endl;
    account_info_file.close();
    user_list_file.close();
}

void account_info_manager::search_then_show_specific_user()
{ // ģ������
    cout << "���ڣ���Ҫ����ģ����ѯ ... " << endl;
    Sleep(150);
    string t_sno;
    string t_username;
    string t_realname;
    bool if_finished_search = false;
    while (true) {
        cout << "�������ض���������ָ��ģʽ [1->ѧ��ģ������ 2->����ģ������ 3->�û���ģ������ 4->�˳�ģ������] >> ";
        int mode;
        cin >> mode;
        if (mode < 1 || mode > 4) {
            cout << "������Ч�����������룡" << endl;
        } else if (mode != 4) {
            if (mode == 1) {
                cout << "������Ҫ��ȷ��ѯ�� ѧ�� >> ";
                cin >> t_sno;
                if (!if_input_user_exists_sub(t_sno, 1, true)) {
                    not_found();
                }
            } else if (mode == 2) {
                cout << "������Ҫ��ȷ��ѯ�� ���� >> ";
                cin >> t_realname;
                if (!if_input_user_exists_sub(t_realname, 2, true)) {
                    not_found();
                }
            } else if (mode == 3) {
                cout << "������Ҫ��ȷ��ѯ�� �û��� >> ";
                cin >> t_username;
                if (!if_input_user_exists_sub(t_username, 3, true)) {
                    not_found();
                }
            }
            if_finished_search = true;
            break;
        } else {
            cout << "����������һ���˵� ... " << endl;
            Sleep(250);
            system("cls");
            break;
        }
    }
    if (if_finished_search) {
        cout << "�����ģ������������������һ���˵� ... " << endl;
        Sleep(250);
        system("cls");
    }
}

// �����û� => �������ֱ�Ӳ�����
// Ŀǰ��ֻ���� ���û��� ��ɲ�������
void account_info_manager::add_a_user()
{
    cout << "�Ƿ�ȷ��������û� (ȷ��������Y/y���������������ַ�) >> ";
    char flag;
    cin >> flag;
    if (flag == 'y' || flag == 'Y') {
        // TODO
        // ��ǰ����[����]
    } else {
        cout << "����������һ���˵� ... " << endl;
        Sleep(250);
        system("cls");
    }
}

// �޸���Ϣ
void account_info_manager::change_specific_user_information()
{
    bool if_continue;
    string temp_user_name;
    while (true) {
        cout << "��������Ҫ�޸���Ϣ��[�û���] >> ";
        cin >> temp_user_name;
        if (!if_input_user_exists(temp_user_name, 3, false)) {
            cout << "������û������ڣ���������������Ϣ��������Y/y���������������ַ� >> ";
            char flag;
            cin >> flag;
            if (flag == 'y' || flag == 'Y') {
                cout << "�յ�����������<��Ϣ�޸�>���� ... " << endl;
                cout << endl;
            } else {
                if_continue = false;
                cout << "�յ�������������һ���˵� ... " << endl;
                cout << endl;
                break;
            }
        } else {
            if_continue = true;
            break;
        }
    }
    if (if_continue) {
        cout << "�ɹ��������û�����Ϣ����������ʾ[ѡ��]��" << endl;
        while (true) {
            cout << "��ǰ **���޸ĵ��û�** �� >> " << temp_user_name << endl;
            cout << "==============================================================" << endl;
            cout << setw(6) << "1. �޸� �û� �� ����" << endl;
            cout << setw(6) << "2. �޸� �û� �� ����" << endl;
            cout << setw(6) << "3. �޸� �û� �� ѧ��" << endl;
            cout << setw(6) << "4. �޸� �û� �� �����" << endl;
            cout << setw(6) << "5. �ٴ���ʾ ���˵�" << endl;
            cout << setw(6) << "6. ���� ��һ���˵�" << endl;
            cout << "==============================================================" << endl;
            cout << "�������Ӧ������ >> ";
            int case_judger;
            cin >> case_judger;
            if (case_judger == 1) {
                change_specific_user_password(temp_user_name);
            } else if (case_judger == 2) {
                change_specific_user_realname(temp_user_name);
            } else if (case_judger == 3) {
                change_specific_user_student_number(temp_user_name);
            } else if (case_judger == 4) {
                change_specific_user_student_dorm_number(temp_user_name);
            } else if (case_judger == 5) {
                cout << endl;
                cout << "�ٴ���ʾѡ��" << endl
                     << endl;
            } else if (case_judger == 6) {
                cout << "�յ����������� [����Ա����] ... " << endl;
                Sleep(250);
                cout << endl;
                break;
            } else {
                cout << endl;
                cout << "��Ӧ����δ�������ٴ���ʾ[ѡ��] ... " << endl
                     << endl;
            }
        }
    }
}

void account_info_manager::change_specific_user_password(const string& input_user)
{
    string temp_password;
    char flag;
    cout << "��ע�⣬ͨ��{����Ա}�޸�����ʱ���������޸����е� <ƾ����> ... " << endl;
    Sleep(500);
    cout << "������һ�������޸ĺ������ (�����޸�������-1) (���볤��Ӧ����8λ�����ٰ���һ��Ӣ����ĸ)" << endl;
    cout << " >> ";
    cin >> temp_password;
    if (temp_password == "-1") {
        cout << "�յ���û��ִ���κ��޸ģ��Զ�������һ���˵� ... " << endl
             << endl;
    } else if (if_password_legal(temp_password)) {
        cout << "������һ��{����ǿ��ַ�}��ϵͳ������޸�" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(account_info_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� account_info.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cache = new account_info;
        while (file.read((char*)(cache), sizeof(account_info))) {
            if (cache->account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cache->password = temp_password;
        file.open(account_info_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� account_info.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cache, sizeof(account_info));
        file.close();
        cout << "����ǰ�޸ĵ��û����� <ƾ����> �� >>" << cache->sp_code << " �������Ѹ��û��μǣ�" << endl;
        cout << "������һ��{����ǿ��ַ�}��ϵͳ����������޸� ... ";
        char tmp;
        cin >> tmp;
        delete cache;
        cout << "�ɹ��޸����룡����������һ���˵� ... " << endl
             << endl;
    } else {
        cout << "�������[������]�����Ϸ����Զ������޸ģ���������һ���˵� ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_realname(const string& input_user)
{
    string temp_real_name;
    char flag;
    cout << "������������(�����޸�������-1) >> ";
    cin >> temp_real_name;
    if (temp_real_name == "-1") {
        cout << "�յ���û��ִ���κ��޸ģ��Զ�������һ���˵� ... " << endl
             << endl;
    } else {
        cout << "������һ��{����ǿ��ַ�}��ϵͳ������޸�" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->real_name = temp_real_name;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "�ɹ��޸�����������������һ���˵� ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_student_number(const string& input_user)
{
    string temp_student_number;
    char flag;
    cout << "��������ѧ��(�����޸�������-1) >> ";
    cin >> temp_student_number;
    if (temp_student_number == "-1") {
        cout << "�յ���û��ִ���κ��޸ģ��Զ�������һ���˵� ... " << endl
             << endl;
    } else {
        cout << "������һ��{����ǿ��ַ�}��ϵͳ������޸�" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->student_number = temp_student_number;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "�ɹ��޸�ѧ�ţ�����������һ���˵� ... " << endl
             << endl;
    }
}

void account_info_manager::change_specific_user_student_dorm_number(const string& input_user)
{
    int temp_dorm_number;
    char flag;
    cout << "�������������(�����޸�������-1) >> ";
    cin >> temp_dorm_number;
    if (temp_dorm_number == -1) {
        cout << "�յ���û��ִ���κ��޸ģ��Զ�������һ���˵� ... " << endl
             << endl;
    } else {
        cout << "������һ��{����ǿ��ַ�}��ϵͳ������޸�" << endl;
        cin >> flag;
        // CORE =>
        int POS;
        fstream file(user_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        cu_cache = new current_user_info;
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == input_user) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        cu_cache->dorm_number = temp_dorm_number;
        file.open(user_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "�޸���Ϣ�׶Σ��� user_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)cu_cache, sizeof(current_user_info));
        file.close();
        delete cu_cache;
        cout << "�ɹ��޸�����ţ�����������һ���˵� ... " << endl
             << endl;
    }
}

// ��������
void account_info_manager::shell_of_account_info_manager()
{
    cout << "��ӭʹ�� <�û���Ϣ����ģ��> , ������ʾ [���ù����б�] >> " << endl;
    while (true) {
        cout << "=======================================================" << endl;
        cout << setw(6) << "1.չʾ���е� �û���Ϣ" << endl;
        cout << setw(6) << "2.ģ������ �û���Ϣ (֧���� ѧ��/����/�û��� ����)" << endl;
        cout << setw(6) << "3.��ȷ���� �û���Ϣ (֧���� ѧ��/����/�û��� ����)" << endl;
        cout << setw(6) << "4.�޸� ĳ���ض��û��� �ض���Ϣ (֧���޸� ����/ѧ��/����/�����)" << endl;
        cout << setw(6) << "5.ɾ�� ĳ���ض��û��� ������Ϣ" << endl;
        cout << setw(6) << "6.�ٴ���ʾ [���ù����б�]" << endl;
        cout << setw(6) << "7.���� [����Ա����]" << endl;
        cout << "=======================================================" << endl;
        cout << "��������Ӧ������ >> ";
        int flag;
        cin >> flag;
        cout << endl;
        if (flag == 1) {
            show_all_user_info();
        } else if (flag == 2) {
            search_then_show_specific_user();
        } else if (flag == 3) {
            precisely_show_specific_user_info();
        } else if (flag == 4) {
            change_specific_user_information();
        } else if (flag == 5) {
            delete_a_user();
        } else if (flag == 6) {
            cout << "�ٴ���ʾ [���ù��ܲ˵�] ... " << endl;
            Sleep(250);
        } else if (flag == 7) {
            cout << "�������� [����Ա����] ... " << endl;
            Sleep(250);
            break;
        } else {
            cout << "�ù�����δ�������������ٴ���ʾ [���ù��ܲ˵�] ... " << endl;
        }
    }
}