#include "user_AccountInfoReceiver.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> // Sleep() ʹ��
using namespace std;

user_info_receiver::user_info_receiver()
{
    string trans_account = return_account_name();
    user_import_from_login_interface(trans_account);
    try_to_load_user_file(trans_account);
    ask_to_set_name_and_sno();
}

inline void user_info_receiver::user_import_from_login_interface(const string& input_account)
{
    cu_info = new current_user_info; // ����������ռ�
    cu_info->c_account = input_account;
    cu_info->if_first_use = true; // ��ʼ�� �Ƿ��һ��ʹ��
    // ��Ҫ�ͷ�cu_info�Ŀռ䣬������
}

void user_info_receiver::try_to_load_user_file(const string& correct_account)
{
    cu_cache = new current_user_info; // ����������ռ�
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        // �򿪲������ǰ���£��򲻿����Ǿ���û��
        // nothing happened
    } else {
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == correct_account) {
                cu_info->real_name = cu_cache->real_name;
                cu_info->student_number = cu_cache->student_number;
                cu_info->if_first_use = false;
                break;
            }
        }
    }
    delete cu_cache; // ������� cu_cache
    // ���ǲ�Ҫ��� ���洢���� cu_info
}

void user_info_receiver::ask_to_set_name_and_sno()
{
    if (cu_info->if_first_use) {
        while (true) {
            cout << "��һ��ʹ�� "
                 << cu_info->c_account
                 << " ����˺ţ��Ե�Ƭ�̣��밴����ʾ������ʵ����ȷ����Ϣ��"
                 << endl;
            cout << "��ע�⣬���������Ϣ��������Ȩ���ĸ�����Ϣ(���й���Ա�д�Ȩ��)" << endl;
            Sleep(1000);
            system("cls");
            //������
            string temp_name, temp_name_check;
            string temp_sno, temp_sno_check;
            int temp_dorm_no, temp_dorm_no_check;
            bool if_back_to_first_step_when_name_conflict;
            bool if_back_to_first_step_when_sno_conflict;
            bool if_back_to_first_step_when_dorm_no_conflict;
            //��������
            while (true) {
                cout << "������������ʵ������";
                cin >> temp_name;
                while (true) {
                    char temp_flag;
                    cout << "���ٴ������� (�ո�����) ����ʵ������";
                    cin >> temp_name_check;
                    if (temp_name_check == temp_name) {
                        if_back_to_first_step_when_name_conflict = false;
                        break;
                    } else {
                        cout << "���������������ͬ" << endl
                             << "����A/a -> �ٴ�����������������"
                             << "������������ -> ����ָ������ >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            system("cls");
                            cout << "�Ե�Ƭ�̣�׼�� [�ٴ�����������������]" << endl;
                            Sleep(1000);
                        } else {
                            system("cls");
                            cout << "�Ե�Ƭ�̣�׼�� [����ָ������]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_name_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_name_conflict) {
                    break;
                }
            }
            cout << "�ѳɹ����� [��ʵ����]���Ե�Ƭ�������� [��ʵѧ��]" << endl;
            Sleep(1000);
            system("cls");
            //����ѧ��
            while (true) {
                cout << "������������ʵѧ�ţ�";
                cin >> temp_dorm_no;
                while (true) {
                    char temp_flag;
                    cout << "���ٴ������� (�ո�����) ����ʵѧ�ţ�";
                    cin >> temp_dorm_no_check;
                    if (temp_dorm_no_check == temp_dorm_no) {
                        if_back_to_first_step_when_sno_conflict = false;
                        break;
                    } else {
                        cout << "���������ѧ�Ų�ͬ" << endl
                             << "����A/a -> �ٴ�������������ѧ��"
                             << "������������ -> ����ָ��ѧ�� >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            system("cls");
                            cout << "�Ե�Ƭ�̣�׼�� [�ٴ�������������ѧ��]" << endl;
                            Sleep(1000);
                        } else {
                            system("cls");
                            cout << "�Ե�Ƭ�̣�׼�� [����ָ��ѧ��]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_sno_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_sno_conflict) {
                    break;
                }
            }
            //���������
            cout << "��������ǰ�Ƿ�סУ��(Y->סУ�������ַ�->��סУ) >>> ";
            char flag;
            cin >> flag;
            if (flag == 'Y' || flag == 'y') {
                while (true) {
                    cout << "��������Ŀǰ����������ţ�";
                    cin >> temp_sno;
                    while (true) {
                        char temp_flag;
                        cout << "���ٴ������� (�ո�����) ������ţ�";
                        cin >> temp_sno_check;
                        if (temp_sno_check == temp_sno) {
                            if_back_to_first_step_when_dorm_no_conflict = false;
                            break;
                        } else {
                            cout << "�������������Ų�ͬ" << endl
                                 << "����A/a -> �ٴ������������������ ; "
                                 << "������������ -> ����ָ������� >>> ";
                            cin >> temp_flag;
                            if (temp_flag == 'A' || temp_flag == 'a') {
                                system("cls");
                                cout << "�Ե�Ƭ�̣�׼�� [�ٴ������������������]" << endl;
                                Sleep(1000);
                            } else {
                                system("cls");
                                cout << "�Ե�Ƭ�̣�׼�� [����ָ�������]" << endl;
                                Sleep(1000);
                                if_back_to_first_step_when_dorm_no_conflict = true;
                                break;
                            }
                        }
                    }
                    if (!if_back_to_first_step_when_dorm_no_conflict) {
                        break;
                    }
                }
            } else {
                temp_dorm_no = -1; // ��סУ������ţ�¼�� -1
                cout << "������Ŀǰ��סУ��ϵͳ���Զ����� <���������> ���ڣ���֮��סУ������ϵ����Ա���ƴ���Ϣ��" << endl;
            }

            cout << "�� ==���һ��== ȷ��������ĸ�����Ϣ��" << endl
                 << endl;
            cout << "==============================================" << endl;
            cout.setf(ios::left); // �����
            cout << "   ������ " << setw(8) << temp_name << endl;
            cout << "   ѧ�ţ� " << setw(8) << temp_sno << endl;
            cout << "   ����ţ� " << setw(8) << temp_dorm_no << endl;
            cout << "==============================================" << endl
                 << endl;
            cout << "�Ƿ���ȷ����ȷ=>������Y/y || ����ȷ=>��������������ǿ��ַ�(�Ժ��Զ���������������������ѧ��) >>> ";
            char flag_of_flush;
            cin >> flag_of_flush;
            if (flag_of_flush == 'Y' || flag_of_flush == 'y') {
                // д��ṹ��
                cu_info->real_name = temp_name;
                cu_info->student_number = temp_sno;
                cu_info->dorm_number = temp_dorm_no;
                // next
                system("cls");
                break;
            } else {
                cout << "���Ժ�ϵͳ���Զ���������������������ѧ��" << endl;
                Sleep(1000);
                system("cls");
            }
        }
        // �����û�״̬ -> �Ƿ��һ��ʹ��
        cu_info->if_first_use = false;
        // д���û��ļ�
        write_to_user_file();
        // end of function
        cout << "�ѳɹ����� [������Ϣ]���Ե�Ƭ�̽����� <�û�����>" << endl;
        Sleep(1000);
        system("cls");
    }
}

void user_info_receiver::write_to_user_file()
{
    fstream file;
    file.open(file_location, ios::app | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "д���ļ�ʱ���� user_list.dat ʧ�ܣ������Զ��˳�����" << endl;
        Sleep(250);
        exit(-1);
    }
    file.write((char*)(cu_info), sizeof(current_user_info)); // �ļ�β�� д��
    file.close();
}

//�ӿں���
auto user_info_receiver::return_c_account() -> string
{
    return cu_info->c_account;
}

auto user_info_receiver::return_real_name() -> string
{
    return cu_info->real_name;
}

auto user_info_receiver::return_student_number() -> string
{
    return cu_info->student_number;
}
