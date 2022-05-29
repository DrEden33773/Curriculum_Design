// �ع����

#define _CRT_SECURE_NO_WARNINGS
#include "user_AccountInfoReceiver.h"
#include <Windows.h> // Sleep() ʹ��
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

user_info_receiver::user_info_receiver(const string& input_account)
{
    if_user_list_empty = true;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    const string& trans_account = input_account;
    user_import_from_login_interface(trans_account);
    user_list_file_empty_check();
    if (!if_user_list_empty) {
        try_to_load_user_file(trans_account);
    }
    ask_to_set_user_info();
}

user_info_receiver::user_info_receiver() // �޲ι��캯��
{
    if_user_list_empty = true;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    user_list_file_empty_check();
}

inline void user_info_receiver::user_import_from_login_interface(const string& input_account)
{
    cu_info = new current_user_info; // ����������ռ�
    cu_info->c_account = input_account;
    cu_info->if_first_use = true; // ��ʼ�� �Ƿ��һ��ʹ��
    // ��Ҫ�ͷ�cu_info�Ŀռ䣬������
}

bool user_info_receiver::if_sno_already_exists(const string& input_sno)
{
    const string user_list_file_location_ = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    bool result = false;
    cu_cache = new current_user_info;
    cu_cache_tr = new current_user_info_tr;
    fstream file(user_list_file_location_, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� user_list_file.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(user_list_file_location_, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� user_list_file.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
        *cu_cache = *cu_cache_tr;
        if (cu_cache->student_number == input_sno) {
            result = true;
            break;
        }
    }
    file.close();
    delete cu_cache;
    delete cu_cache_tr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    return result;
}

void user_info_receiver::initialize_user_list_file() const
{
    fstream file;
    file.open(file_location, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ԥ����ʱ���� user_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
}

void user_info_receiver::user_list_file_empty_check()
{
    // �ж� user_list.dat �Ƿ�Ϊ��
    // �����·��������ض�ȡһ���ļ���ֱ���ж��ļ��Ƿ�Ϊ��
    initialize_user_list_file();
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "Ԥ����ʱ���� user_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        if_user_list_empty = true;
    } else {
        if_user_list_empty = false;
    }
    file.close();
}

void user_info_receiver::try_to_load_user_file(const string& correct_account)
{
    cu_cache_tr = new current_user_info_tr;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "�� user_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        while (file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
            if (strcmp(cu_cache_tr->c_account, correct_account.c_str()) == 0) {
                cu_cache = new current_user_info(cu_cache_tr); // copy constructor
                cu_info->real_name = cu_cache->real_name;
                cu_info->student_number = cu_cache->student_number;
                cu_info->dorm_number = cu_cache->dorm_number;
                cu_info->if_first_use = false;
                break;
            }
        }
    }
    delete cu_cache; // ������� cu_cache
    delete cu_cache_tr; // ������� cu_cache_tr
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    // ���ǲ�Ҫ��� ���洢���� cu_info
}

void user_info_receiver::ask_to_set_user_info()
{
    if (cu_info->if_first_use) {
        while (true) {
            cout << "��һ��ʹ�� "
                 << cu_info->c_account
                 << " ����˺ţ��Ե�Ƭ�̣��밴����ʾ������ʵ����ȷ����Ϣ��"
                 << endl;
            cout << "��ע�⣬���������Ϣ��������Ȩ���ĸ�����Ϣ(���й���Ա�д�Ȩ��)" << endl;
            Sleep(1000);
            cout << endl;
            //������
            string temp_name, temp_name_check;
            string temp_sno, temp_sno_check;
            string temp_dorm_no, temp_dorm_no_check;
            bool if_back_to_first_step_when_name_conflict;
            bool if_back_to_first_step_when_sno_conflict;
            bool if_back_to_first_step_when_dorm_no_conflict;
            //��������
            while (true) {
                cout << "������������ʵ���� (ֻ����16λ���ڵ�����)��";
                cin >> temp_name;
                if (temp_name.size() > 16)
                    temp_name.erase(temp_name.begin() + 16, temp_name.end());
                while (true) {
                    char temp_flag;
                    cout << "���ٴ������� (�ո�����) ����ʵ���� (ֻ����16λ���ڵ�����)��";
                    cin >> temp_name_check;
                    if (temp_name_check.size() > 16)
                        temp_name_check.erase(temp_name_check.begin() + 16, temp_name_check.end());
                    if (temp_name_check == temp_name) {
                        if_back_to_first_step_when_name_conflict = false;
                        break;
                    } else {
                        cout << "���������������ͬ" << endl
                             << "����A/a -> �ٴ����������������� || "
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
            cout << "�ѳɹ����� [��ʵ����]���Ե�Ƭ�������� [ѧ��]" << endl;
            Sleep(1000);
            cout << endl;
            //����ѧ��
            while (true) {
                cout << "����������ѧ�� (ֻ����10λ�������ڵ�����)��";
                cin >> temp_sno;
                if (temp_sno.size() > 10)
                    temp_sno.erase(temp_sno.begin() + 10, temp_sno.end());
                // ��֤ѧ���Ƿ��Ѿ�����
                if (if_sno_already_exists(temp_sno)) {
                    cout << "ѧ���Ѿ����ڣ�����������" << endl;
                    Sleep(300);
                    continue;
                }
                while (true) {
                    char temp_flag;
                    cout << "���ٴ������� (�ո�����) ��ѧ�� (ֻ����10λ�������ڵ�����)��";
                    cin >> temp_sno_check;
                    if (temp_sno_check.size() > 10)
                        temp_sno_check.erase(temp_sno_check.begin() + 10, temp_sno_check.end());
                    if (temp_sno_check == temp_sno) {
                        if_back_to_first_step_when_sno_conflict = false;
                        break;
                    } else {
                        cout << "���������ѧ�Ų�ͬ" << endl
                             << "����A/a -> �ٴ�������������ѧ�� || "
                             << "������������ -> ����ָ��ѧ�� >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            // system("cls");
                            cout << "�Ե�Ƭ�̣�׼�� [�ٴ�������������ѧ��]" << endl;
                            Sleep(1000);
                        } else {
                            // system("cls");
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
            cout << "�ѳɹ����� [ѧ��]���Ե�Ƭ����ȷ�� [�Ƿ�ס��]����ס�޻������� [�����]" << endl;
            Sleep(1000);
            cout << endl;
            //���������
            cout << "��������ǰ�Ƿ�סУ��(Y->סУ�������ַ�->��סУ) >>> ";
            string flag;
            cin >> flag;
            if (flag == "Y" || flag == "y") {
                while (true) {
                    cout << "��������Ŀǰ����������� (ֻ����3λ�������ڵ�����)��";
                    cin >> temp_dorm_no;
                    if (temp_dorm_no.size() > 3)
                        temp_dorm_no.erase(temp_dorm_no.begin() + 3, temp_dorm_no.end());
                    while (true) {
                        char temp_flag;
                        cout << "���ٴ������� (�ո�����) ������� (ֻ����3λ�������ڵ�����)��";
                        cin >> temp_dorm_no_check;
                        if (temp_dorm_no_check.size() > 3)
                            temp_dorm_no_check.erase(temp_dorm_no_check.begin() + 3, temp_dorm_no_check.end());
                        if (temp_dorm_no_check == temp_dorm_no) {
                            if_back_to_first_step_when_dorm_no_conflict = false;
                            break;
                        } else {
                            cout << "�������������Ų�ͬ" << endl
                                 << "����A/a -> �ٴ������������������ || "
                                 << "������������ -> ����ָ������� >>> ";
                            cin >> temp_flag;
                            if (temp_flag == 'A' || temp_flag == 'a') {
                                cout << endl;
                                cout << "�Ե�Ƭ�̣�׼�� [�ٴ������������������]" << endl;
                                Sleep(1000);
                                cout << endl;
                            } else {
                                cout << endl;
                                cout << "�Ե�Ƭ�̣�׼�� [����ָ�������]" << endl;
                                Sleep(1000);
                                cout << endl;
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
            cout << endl;
            cout << "�� ==���һ��== ȷ��������ĸ�����Ϣ��" << endl
                 << endl;
            cout << "========================================================" << endl;
            cout.setf(ios::left); // �����
            cout << "\t"
                 << "������" << setw(12) << temp_name << endl;
            cout << "\t"
                 << "ѧ�ţ�" << setw(12) << temp_sno << endl;
            cout << "\t"
                 << "����ţ�" << setw(12) << temp_dorm_no << endl;
            cout << "========================================================" << endl
                 << endl;
            cout << "�Ƿ���ȷ����ȷ=>������Y/y || ����ȷ=>��������������ǿ��ַ�(�Ժ��Զ���������������������ѧ��) >>> ";
            string flag_of_flush;
            cin >> flag_of_flush;
            if (flag_of_flush == "Y" || flag_of_flush == "y") {
                // д��ṹ��
                cu_info->real_name = temp_name;
                cu_info->student_number = temp_sno;
                cu_info->dorm_number = temp_dorm_no;
                // next
                system("cls");
                break;
            } else {
                cout << "���Ժ�ϵͳ���Զ���������������������ѧ�š������" << endl;
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
    file.open(file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "д���ļ�ʱ���� user_list.dat ʧ�ܣ������Զ��˳�����" << endl;
        Sleep(250);
        exit(-1);
    }
    cu_cache_tr = new current_user_info_tr(cu_info);
    file.write(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr)); // �ļ�β�� д��
    file.close();
    delete cu_cache_tr;
    cu_cache_tr = nullptr;
}

//�ӿں���
string user_info_receiver::return_c_account() const
{
    return cu_info->c_account;
}

string user_info_receiver::return_real_name() const
{
    return cu_info->real_name;
}

string user_info_receiver::return_student_number() const
{
    return cu_info->student_number;
}

string user_info_receiver::return_dorm_number() const
{
    return cu_info->dorm_number;
}

//��������
user_info_receiver::~user_info_receiver()
{
    delete cu_info;
    delete cu_cache;
    delete cu_cache_tr;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
}
