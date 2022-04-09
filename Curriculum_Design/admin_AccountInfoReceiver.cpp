#include "admin_AccountInfoReceiver.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> // Sleep() ʹ��
using namespace std;

auto admin_info_receiver::if_profession_type_valid(int input) -> bool
{
    if (input >= 1 && input <= 20) {
        return true;
    } else {
        return false;
    }
}

inline void admin_info_receiver::make_sure_admin_list_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(admin_list_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� admin_list.dat ʧ�ܣ������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // ��ʱ�ر�
}

auto admin_info_receiver::if_admin_list_file_empty() -> bool
{
    make_sure_admin_list_file_exists(); // ȷ���ļ������Ĳ���
    fstream file;
    file.open(admin_list_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // ����һ����������ļ����򲻿�����ʧ��
        cout << "�޷��� admin_list.dat�������Զ��˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    checker = new current_admin_info;
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(current_admin_info))) {
        if_empty = false;
        break;
    }
    delete checker;
    if_admin_list_file_is_empty = if_empty;
    return if_empty;
}

admin_info_receiver::admin_info_receiver()
{
    string trans_account = return_account_name();
    admin_import_from_login_interface(trans_account);
    try_to_load_admin_file(trans_account);
}

admin_info_receiver::admin_info_receiver(
    const string& input_account,
    const string& input_password)
{
    // Empty
}

void admin_info_receiver::admin_import_from_login_interface(const string& input_account)
{
    ca_info = new current_admin_info;
    ca_info->c_account = input_account;
    ca_info->if_first_use = true; // Ĭ�ϲ���
}

void admin_info_receiver::try_to_load_admin_file(const string& correct_account)
{
    ca_cache = new current_admin_info; // ���棬���ڱȶ���Ϣ
    fstream file;
    bool if_file_is_empty = if_admin_list_file_empty();
    if (if_file_is_empty) { // �ļ��ǿյ�
        // ����Ĭ�ϲ���
    } else {
        file.open(admin_list_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            delete ca_cache;
            // ����һ����������ļ����򲻿�����ʧ��
            cout << "�޷��� admin_list.dat�������Զ��˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (file.read((char*)(ca_cache), sizeof(current_admin_info))) {
            if (ca_cache->c_account == ca_info->c_account) {
                // move value
                ca_info = std::move(ca_cache); // ���������
                break;
            }
        }
        file.close(); // ��ʱ�ر�
        delete ca_cache; // �������
    }
}

void admin_info_receiver::write_to_admin_file()
{
    ca_cache = new current_admin_info;
    fstream file(admin_list_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "��Ϣд��׶Σ��� admin_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!if_admin_list_file_is_empty) { // �ļ��ﲻ�ǿյ� => ��Ҫ�ҵ���ȷ��λ��
        int POS;
        while (file.read((char*)(ca_cache), sizeof(current_admin_info))) {
            if (ca_cache->c_account == ca_info->c_account) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        file.open(admin_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "��Ϣд��׶Σ��� admin_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)(ca_cache), sizeof(current_admin_info));
        file.close();
    } else { // �ļ��ǿյ� => ֱ�Ӳ�����λ���ˣ�д��ͷ�Ͼ���ȫOK
        file.close();
        file.open(admin_list_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "��Ϣд��׶Σ��� admin_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.write((char*)(ca_cache), sizeof(current_admin_info));
        file.close();
    }
}

void admin_info_receiver::ask_to_set_profession_type()
{
    if (ca_info->if_first_use) {
        cout << "���˺��ǵ�һ��ʹ�� ... ��ϵͳ��ʱ������ [ָ���ֹ�ѧԺ] ���� ... " << endl;
        cout << "���е� <����Ա�˺�> �����й��� <�����û�> ��Ȩ�� ... " << endl;
        cout << "����ϵͳ�Ѿ�����������ʹ��״̬���Ե�Ƭ�̺󣬽��� <����Ա����> ... " << endl;
        // ��ʱ������ => �ֹ�ѧԺ����
        // while (false) {
        //     cout << "��һ��ʹ�� "
        //          << ca_info->c_account
        //          << " ����˺ţ��Ե�Ƭ�̣��밴����ʾ������ʵ����ȷ����Ϣ��"
        //          << endl;
        //     Sleep(600);
        //     system("cls");
        //     // ������
        //     int temp_profession_code, temp_profession_code_check;
        //     bool if_back_to_first_step_when_code_conflict;
        //     // ����Ա��Ҫ������
        //     // ����ֹ�רҵ����
        //     while (true) {
        //         cout << "������ֹ�ѧԺ�Ĵ��ţ�";
        //         cin >> temp_profession_code;
        //         while (true) {
        //             char temp_flag;
        //             cout << "���ٴ������� (�ո������) �ֹ�ѧԺ�Ĵ��ţ�";
        //             cin >> temp_profession_code_check;
        //             if (temp_profession_code_check == temp_profession_code) {
        //                 if_back_to_first_step_when_code_conflict = false;
        //                 break;
        //             } else {
        //                 cout << "��������Ĵ��Ų�ͬ" << endl
        //                      << "����A/a -> �ٴ������������Ĵ���"
        //                      << "������������ -> ����ָ������ >>> ";
        //                 cin >> temp_flag;
        //                 if (temp_flag == 'A' || temp_flag == 'a') {
        //                     system("cls");
        //                     cout << "�Ե�Ƭ�̣�׼�� [�ٴ������������Ĵ���]" << endl;
        //                     Sleep(1000);
        //                 } else {
        //                     system("cls");
        //                     cout << "�Ե�Ƭ�̣�׼�� [����ָ������]" << endl;
        //                     Sleep(1000);
        //                     if_back_to_first_step_when_code_conflict = true;
        //                     break;
        //                 }
        //             }
        //             if (!if_back_to_first_step_when_code_conflict) {
        //                 break;
        //             }
        //         }
        //         cout << "�� ==���һ��== ȷ��������ı�Ҫ��Ϣ��" << endl
        //              << endl;
        //         cout << "==============================================" << endl;
        //         // cout.setf(ios::left); // ����� => ���������ﲻ��Ҫ
        //         cout << "   �ֹ�ѧԺ���ţ�  " << setw(5) << temp_profession_code << endl;
        //         cout << "==============================================" << endl
        //              << endl;
        //         cout << "�Ƿ���ȷ����ȷ������Y/y������ȷ��������������ǿ��ַ�(�Ժ��Զ��������������� �ֹ�ѧԺ����) >>> ";
        //         char flag_of_flush;
        //         cin >> flag_of_flush;
        //         if (flag_of_flush == 'Y' && flag_of_flush == 'y') {
        //             system("cls");
        //             break;
        //         } else {
        //             cout << "���Ժ�ϵͳ���Զ��������������� �ֹ�ѧԺ����" << endl;
        //             Sleep(1000);
        //             system("cls");
        //         }
        //     }
        // }

        //���¹���Ա״̬ -> �Ƿ��һ��ʹ��
        ca_info->if_first_use = false;

        //д���ļ�
        write_to_admin_file();

        // end of function
        // cout << "�ѳɹ����� [��Ҫ��Ϣ]���Ե�Ƭ�̽����� <����Ա����>" << endl;
        Sleep(1000);
        system("cls");
    }
}

//�ӿں���
auto admin_info_receiver::return_c_account() -> string
{
    return ca_info->c_account;
}