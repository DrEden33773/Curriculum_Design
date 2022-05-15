#define _CRT_SECURE_NO_WARNINGS
#include "account.h"
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random> // ���������
#include <string>

#include "time_manager.h"

using namespace std;

account_manager::account_manager(const string& any)
{
    // var_initialization
    cache = nullptr;
    cache_base = nullptr;
    login = nullptr;
    // �Ѿ��ع�
    // make sure account_list exists
    fstream file;
    file.open(account_info_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� account_info.dat ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    // check if file is empty
    if_acct_info_file_have_admin = false;
    file.open(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� account_info.dat ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cache_base = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (cache_base->if_admin) {
            if_acct_info_file_have_admin = true;
            break;
        }
    }
    file.close();
}

account_manager::account_manager()
{
    if_acct_info_file_have_admin = true;
    // Reason => the constructor without any parameter will be called in derived class,
    // and you won't have the chance to use the derived class without successfully used the base class,
    // which means, you must have created an "admin" account in the account_info.dat
    cache = nullptr;
    cache_base = nullptr;
    login = nullptr;
}

//������
bool account_manager::if_password_legal(const string& temp_password)
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    const int len = temp_password.length(); // ��ȡ����
    if (len >= 8 && len <= 24) // ���볤�� => С��24
        if_length = true;
    for (int x = 0; x < len; ++x) {
        if (temp_password[x] >= '0' && temp_password[x] <= '9')
            if_number = true;
        if (temp_password[x] >= 'a' && temp_password[x] <= 'z')
            if_letter = true;
        if (temp_password[x] >= 'A' && temp_password[x] <= 'Z')
            if_letter = true;
    }
    if (if_number && if_length && if_letter)
        result = true;
    return result; // return
}

bool account_manager::if_account_legal(const string& temp_account)
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    const int len = temp_account.length(); // ��ȡ����
    if (len >= 8 && len <= 16) // �˺������� => ������16
        if_length = true;
    for (int x = 0; x < len; ++x) {
        if (temp_account[x] >= '0' && temp_account[x] <= '9')
            if_number = true;
        if (temp_account[x] >= 'a' && temp_account[x] <= 'z')
            if_letter = true;
        if (temp_account[x] >= 'A' && temp_account[x] <= 'Z')
            if_letter = true;
    }
    if (if_number && if_length && if_letter)
        result = true;
    return result; // return
}

void account_manager::write_account_to_cache(
    const string& temp_account,
    const string& temp_password,
    bool if_admin,
    const char* temp_sp_code)
{
    // ���ع�
    cache_base = new account_info;
    strcpy(cache_base->account_str, temp_account.c_str());
    strcpy(cache_base->password_str, temp_password.c_str());
    cache_base->if_admin = if_admin;
    strcpy(cache_base->sp_code, temp_sp_code);
    // ��Ҫ����ռ�
}

// write_cache_to_file_app
void account_manager::write_cache_to_file_app() const
{
    fstream file;
    file.open(file_location, ios::binary | ios::app); // �� ios::app ��û��Ҫ�� ios::out
    if (!file.is_open()) {
        cout << "д���ļ������У��� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    } else {
        file.write(reinterpret_cast<char*>(cache_base), sizeof(account_info));
    }
    // delete cache_base;
    file.close();
}

// change_account_password_in_file
void account_manager::change_account_password_in_file(const account_info* changed_account) const
{
    int POS;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "�޸�����ǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(changed_account->account_str, cache_base->account_str)) {
            POS = file.tellg(); // g => ��ָ��
            break;
        }
    }
    file.close();
    strcpy(cache_base->password_str, changed_account->password_str);
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "�޸�����ǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    file.seekp(POS, ios::beg);
    file.write(reinterpret_cast<char*>(cache_base), sizeof(account_info));
    file.close();
}

int account_manager::check_account(
    const string& input_account,
    const string& input_password) const
{
    // ȫ�µ��߼� -- ֱ�Ӵ��ļ�����
    bool if_account_exists = false;
    bool if_password_correct = false;
    int result = -2;
    fstream file(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�����˺���Ϣʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(cache_base->account_str, input_account.c_str())) {
            if_account_exists = true;
            if (!strcmp(cache_base->password_str, input_password.c_str())) {
                if_password_correct = true;
                if (cache_base->if_admin)
                    result = 1;
                else
                    result = 0;
                break;
            }
        }
    }
    // delete cache_base;
    if (!if_account_exists)
        result = -2;
    else if (!if_password_correct)
        result = -1;
    file.close();
    return result;
}

bool account_manager::if_account_exists_new(const string& input) const
{
    bool result = false;
    fstream file;
    file.open(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "��ȡ��Ϣʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (!strcmp(cache_base->account_str, input.c_str())) {
            result = true;
            break;
        }
    }
    file.close();
    return result;
}

char* account_manager::generate_sp_code()
{
    const auto temp = new char[11]; // �ڶ��ϴ����ַ����飬ָ��Ϊtemp
    const uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e(time(nullptr)); // ����=��ǰʱ�䣬ȷ�����Ӳ�������ȷ����������Ĳ���
    for (int i = 0; i < 11; i++) {
        temp[i] = '0' + u(e);
    }
    temp[10] = '\0';
    return temp;
}

void account_manager::change_account_in_cache(
    account_manager::account_info* changed_account,
    const string& changed_password,
    const char* changed_sp_code)
{
    strcpy(changed_account->password_str, changed_password.c_str());
    strcpy(changed_account->sp_code, changed_sp_code);
}

account_manager::account_info* account_manager::if_sp_code_is_correct(
    const string& temp_account,
    const char* temp_sp_code) const
{
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "�����˺���Ϣʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!account_into_file.eof()) {
        account_into_file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (strcmp(cache_base->account_str, temp_account.c_str()) == 0
            && strcmp(cache_base->sp_code, temp_sp_code) == 0) {
            result = cache_base;
            break;
        }
    }
    account_into_file.close();
    return result;
}

account_manager::account_info* account_manager::if_sp_code_exists(const char* temp_sp_code) const
{
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "�����˺���Ϣǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // cache_base = new account_info;
    while (!account_into_file.eof()) {
        account_into_file.read(reinterpret_cast<char*>(cache_base), sizeof(account_info));
        if (strcmp(cache_base->sp_code, temp_sp_code) == 0) {
            bool if_found = true;
            result = cache_base;
            break;
        }
    }
    account_into_file.close();
    return result;
}

// interface-����
int account_manager::shell_of_account_login()
{
    time_manager today;
    delete cache_base;
    cache_base = nullptr;
    cache_base = new account_info;
    int judger = -1;
    if (!if_acct_info_file_have_admin) {
        //��δʹ�ù����
        first_create_admin_account();
    }
    cout << endl;
    cout << "������ >> " << today << endl;
    cout << endl;
    cout << "��ӭʹ�� [�������һ�廯����ϵͳ]�����������¼ҳ��" << endl
        << endl;
    for (;;) {
        cout << "������ʾ��¼ѡ�" << endl;
        cout << "====================================================" << endl;
        cout << "\t";
        cout << "1.ʹ��--�˺�����--��¼" << endl;
        cout << "\t";
        cout << "2.ʹ��--�˺�ƾ����--��¼" << endl;
        cout << "\t";
        cout << "3.�½��˺�" << endl;
        cout << "\t";
        cout << "4.��������/�޸�����" << endl;
        cout << "\t";
        cout << "5.�ٴ���ʾ�����б�" << endl;
        cout << "\t";
        cout << "6.ȡ����¼���˳�����" << endl;
        cout << "====================================================" << endl;
        cout << "�������Ӧ���(����5�ٴ���ʾ�����б�): ";
        string temp;
        cin >> temp;
        cout << endl
            << endl;
        if (temp == "6") {
            // ����Ҳ��Ҫ���� �˺Ÿ��� ��Ӧ�� �ļ�
            cout << "ȡ����¼�����򼴽��Զ��˳�" << endl;
            Sleep(300);
            exit(1);
        }
        if (temp == "1") {
            judger = sign_in_by_account();
            if (judger == -2) {
                cout << "�����ڸ��˻��������ٴ���ʾ��¼ѡ��" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //����
            } else if (judger == -1) {
                cout << "�˻����ڣ�����������󣡼����ٴ���ʾ��¼ѡ��" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //����
            } else {
                system("cls"); //����
                break;
            }
        } else if (temp == "2") {
            judger = sign_in_by_sp_code();
            if (judger == -2) {
                cout << "�����������ƾ����ƥ����˻��������ٴ���ʾ��¼ѡ��" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //����
            } else if (judger == -1) {
                // sp_code��¼�������ڷ���-1�����
                cout << "�˻����ڣ�����������󣡼����ٴ���ʾ��¼ѡ��" << endl
                    << endl;
                Sleep(150);
                // system("cls"); //����
            } else {
                system("cls"); //����
                break;
            }
        } else if (temp == "3") {
            create_account();
        } else if (temp == "4") {
            change_password();
        } else if (temp == "5") {
            system("cls");
            continue;
        } else {
            cout << "û����" << temp << "��Ӧ�Ĺ��ܣ������ٴ���ʾ��¼ѡ��" << endl
                << endl;
            Sleep(150);
            // system("cls"); //����
        }
    }
    return judger;
}

void account_manager::first_create_admin_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    constexpr bool if_this_is_admin = true;
    bool if_try_again = false;
    //������Ϣ
    cout << "��⵽��ǰϵͳ��û�� <����Ա�˺�> �����ȴ���һ������Ա�˺ţ�" << endl;
    while (true) {
        cout << "������ <�˻���> (����8λ������16λ����Ҫ����������Ӣ����ĸ)�� ";
        cin >> temp_account;
        if (if_account_exists_new(temp_account)) {
            // system("cls");
            cout << "�Ѵ��ڸ��˺ţ����������� <�û���> ��" << endl;
            Sleep(250);
        } else if (!if_account_legal(temp_account)) {
            cout << "�˻������Ϸ�������������" << endl;
            Sleep(150);
        } else {
            break;
        }
    }
    while (true) {
        while (true) {
            cout << "������ <����> (����8λ������24λ����Ҫ����������Ӣ����ĸ)�� ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
                break;
            } else {
                cout << "���벻�Ϸ�������������" << endl;
            }
        }
        while (true) {
            system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
            cout << "������ո����õ� <����> �� ";
            // cin >> temp_password_check; //��Ҫ��������ʾ��
            if (password_input_judger_with_fmt(temp_password)) {
                cout << "����Ա�˺Ŵ����ɹ���" << endl
                    << endl;
                // Sleep(150);
                // system("cls");
                if_try_again = false;
                break;
            } else {
                cout << "������������벻һ�£���A=>�����������룬���������ַ�=>�ٴγ�������ո����õ����룺" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                } else {
                    continue;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    //���������ƾ����
    const char* temp_so_code = generate_sp_code();
    //���뻺��
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    //��������ļ�β��
    write_cache_to_file_app();
    //չʾƾ����
    cout << "�Ѵ����˻������ɵ�ƾ����Ϊ��" << temp_so_code << endl;
    cout << "������μ�����ƾ���룬�⽫�����һص�[����Ա�˻�<����>]��Ψһƾ�ݣ�Ҳ�������һ�[��ͨ�˻�<����>]����Ҫƾ�ݣ�" << endl;
    cout << "�μ�ƾ��������������ַ����� >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

void account_manager::create_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    bool if_this_is_admin;
    bool if_try_again = false;
    //������Ϣ
    cout << "��ָ�������˻�������(����A=>����Ա�����������ַ�=>��ͨ�û�)��";
    char temp_judge;
    cin >> temp_judge; // ֻ����һ���ַ�
    if (temp_judge == 'A' || temp_judge == 'a')
        if_this_is_admin = true;
    else
        if_this_is_admin = false;
    while (true) {
        cout << "������ <�˻���> (����8λ������16λ����Ҫ����������Ӣ����ĸ)�� ";
        cin >> temp_account;
        if (if_account_exists_new(temp_account)) {
            // system("cls");
            cout << "�Ѵ��ڸ��˺ţ����������� <�û���> ��" << endl;
            Sleep(250);
        } else if (!if_account_legal(temp_account)) {
            cout << "�˻������Ϸ�������������" << endl;
            Sleep(150);
        } else {
            break;
        }
    }
    while (true) {
        while (true) {
            cout << "������ <����> (���ٰ�λ������������Ӣ����ĸ)�� ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
                break;
            } else {
                cout << "���벻�Ϸ�������������" << endl;
            }
        }
        while (true) {
            system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
            cout << "������ո����õ� <����> �� ";
            // cin >> temp_password_check; //��Ҫ��������ʾ��
            if (password_input_judger_with_fmt(temp_password)) {
                cout << "�˺Ŵ����ɹ���" << endl
                    << endl;
                // Sleep(150);
                // system("cls");
                if_try_again = false;
                break;
            } else {
                cout << "������������벻һ�£���A=>�����������룬���������ַ�=>�ٴγ�������ո����õ����룺" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                } else {
                    continue;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    // ���������ƾ����
    const char* temp_so_code = generate_sp_code();
    // д��cache
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    // cacheд���ļ�β��
    write_cache_to_file_app();
    // չʾƾ����
    cout << "�Ѵ����˻������ɵ�ƾ����Ϊ��" << temp_so_code << endl;
    cout << "������μ�����ƾ���룬�⽫�����һص�[����Ա�˻�<����>]��Ψһƾ�ݣ�Ҳ�������һ�[��ͨ�˻�<����>]����Ҫƾ�ݣ�" << endl;
    cout << "�μ�ƾ��������������ַ����� >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

int account_manager::sign_in_by_account()
{
    string temp_account;
    cout << "�������û�����";
    cin >> temp_account;
    cout << "���������룺"; // ������ʾ
    const string temp_password = password_input_with_fmt_then_return_it();
    const int temp_result = check_account(temp_account, temp_password);
    if (temp_result != -2 && temp_result != -1) {
        // give_the_plug_of_account(temp_account, temp_password);
        login = cache_base;
    }
    return temp_result;
}

int account_manager::sign_in_by_sp_code()
{
    // ������ cache_base���ǵý��ռ��
    int temp_result = 0;
    char temp_sp_code[11];
    cout << "������<ƾ����>��";
    cin >> temp_sp_code;
    const account_info* c = if_sp_code_exists(temp_sp_code);
    if (!c) {
        temp_result = -2;
    } else {
        // give_the_plug_of_account(temp_sp_code);
        login = cache_base;
    }
    if (temp_result != -2) {
        if (c->if_admin)
            temp_result = 1;
    }
    // delete cache_base;
    // delete c;
    return temp_result;
}

void account_manager::change_password() const
// ����������߼�̫��������
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    char temp_sp_code[11];
    bool if_go_next = false;
    bool if_try_again = false;
    account_info* temp_account_ptr;
    while (true) {
        while (true) {
            cout << "������Ҫ�޸������ <�û���> �� ";
            cin >> temp_account;
            if (!if_account_exists_new(temp_account)) {
                system("cls");
                cout << "�����ڸ��˺ţ����������� <�û���> ��" << endl;
                Sleep(250);
            } else {
                break;
            }
        }
        while (true) {
            cout << "������ <�˺�> �� <ƾ����> ��";
            cin.width(11);
            cin >> temp_sp_code;
            temp_account_ptr = if_sp_code_is_correct(temp_account, temp_sp_code); // �õ� cache_base
            if (temp_account_ptr) {
                if_go_next = true;
                break;
            } else {
                cout << "<ƾ����> �� <�˺�> ��ƥ�䣬����Y=>�ٴ�����<ƾ����>�����������ַ�=>��������<�û���>" << endl;
                char temp;
                cin >> temp;
                if (temp == 'y' || temp == 'Y')
                    continue;
                else {
                    system("cls");
                    Sleep(150);
                    break;
                }
            }
        }
        if (if_go_next)
            break;
    }
    system("cls");
    cout << "<ƾ����>��<�û���>�ɹ�ƥ�䣬��������<������>�����Ե�Ƭ��" << endl;
    Sleep(200);
    while (true) {
        while (true) {
            cout << "��Ϊ {" << temp_account << "} ���� <������> (���ٰ�λ������������Ӣ����ĸ)�� ";
            cin >> temp_password;
            if (if_password_legal(temp_password)) {
                system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
                break;
            } else {
                cout << "���벻�Ϸ�������������" << endl;
            }
        }
        while (true) {
            system("cls"); // �������ٴ��������룬����ʱ����Ļ��ʾ����
            cout << "������ո����õ� <������> �� ";
            // cin >> temp_password_check; //��Ҫ��������ʾ��
            if (password_input_judger_with_fmt(temp_password)) {
                system("cls");
                cout << "�����޸ĳɹ�" << endl
                    << endl;
                if_try_again = false;
                Sleep(150);
                break;
            } else {
                cout << "������������벻һ�£���A=>�����������룬���������ַ�=>�ٴγ�������ո����õ������룺" << endl;
                char temp;
                cin >> temp;
                if (temp == 'A' || temp == 'a') {
                    if_try_again = true;
                    system("cls");
                    break;
                }
            }
        }
        if (!if_try_again) {
            break;
        }
    }
    cout << " == ������ĺ󣬼��������µ�ƾ���� == " << endl;
    // �����������ƾ����
    const char* temp_so_code = generate_sp_code();
    // ��д����
    change_account_in_cache(temp_account_ptr, temp_password, temp_so_code);
    // �����ļ��ж�Ӧ������
    change_account_password_in_file(temp_account_ptr);
    // չʾƾ����
    cout << "�������ɵ�ƾ����Ϊ��" << temp_so_code << endl;
    cout << "������μ�����ƾ���룬�⽫�����һص�[����Ա�˻�<����>]��Ψһƾ�ݣ�Ҳ�������һ�[��ͨ�˻�<����>]����Ҫƾ�ݣ�" << endl;
    cout << "�μ�ƾ����������������ַ������ >>> ";
    char skipper;
    cin >> skipper;
    // delete cache_base; // ��� cache_base
    Sleep(100);
    system("cls");
}

//�ӿں���
void account_manager::give_the_plug_of_account(
    const string& input_account,
    const string& input_password)
{
    login = new account_info;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "���ݲ���ʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    account_info* c = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(c), sizeof(account_info));
        if (strcmp(c->account_str, input_account.c_str()) == 0) {
            if (strcmp(c->password_str, input_password.c_str()) == 0) {
                login = c;
                break;
            }
        }
    }
    // delete c;
    file.close();
}

void account_manager::give_the_plug_of_account(const char* input_sp_code)
{
    login = new account_info;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "���ݲ���ʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    account_info* c = new account_info;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(c), sizeof(account_info));
        if (strcmp(c->sp_code, input_sp_code) == 0) {
            login = c;
        }
    }
    // delete c;
    file.close();
}

bool account_manager::password_input_judger_with_fmt(const string& judged_str)
{
    string input;
    char chr = '\0';
    while (chr != '\r') { // δ���� �س�
        chr = _getch(); // ��ȡ������ַ�
        if (chr != '\r' && chr != '\b') { // δ���� �˸� / �س�
            input += chr; // �ַ���β�������ַ�
            cout << '*'; // ��� *
        } else if (chr == '\b') { // ������ �˸�
            if (!input.empty()) { // ��û�����
                cout << "\b \b"; // ��ոոյ�һ��*����" "���
                input.pop_back(); // �����ַ��������һ���ַ�
            }
        }
    }
    cout << endl;
    return input == judged_str;
}

string account_manager::password_input_with_fmt_then_return_it()
{
    string input;
    char chr = '\0';
    while (chr != '\r') { // δ���� �س�
        chr = _getch(); // ��ȡ������ַ�
        if (chr != '\r' && chr != '\b') { // δ���� �˸� / �س�
            input += chr; // �ַ���β�������ַ�
            cout << '*'; // ��� *
        } else if (chr == '\b') { // ������ �˸�
            if (!input.empty()) { // ��û�����
                cout << "\b \b"; // ��ոոյ�һ��*����" "���
                input.pop_back(); // �����ַ��������һ���ַ�
            }
        }
    }
    cout << endl;
    return input;
}

//�����ӿں���
string account_manager::return_account_name() const
{
    string result = login->account_str;
    return result;
}

string account_manager::return_account_password() const
{
    string result = login->password_str;
    return result;
}

account_manager::~account_manager()
{
    delete cache_base;
    cache_base = nullptr;
}
