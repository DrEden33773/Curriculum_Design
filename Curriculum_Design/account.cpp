#include "account.h"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random> // ���������
#include <string>
#include <utility>
#include <windows.h>
#include <winerror.h>

using namespace std;

/*  ������������Ĺ��캯���е��û���Ĺ��캯����
    load_used_time_from_file�ں���ʼ������Ĺ���  */
account_manager::account_manager()
{ // �ȳ�ʼ��
    load_used_time_from_file(); // �ٶ��ļ�
}

//������
auto account_manager::if_password_legal(string temp_password) -> bool
{
    bool result = false;
    bool if_length = false;
    bool if_number = false;
    bool if_letter = false;
    int len = temp_password.length(); // ��ȡ����
    if (len >= 8)
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

void account_manager::write_account_to_list(
    string temp_account,
    string temp_password,
    bool if_admin,
    char* temp_sp_code)
{
    auto* c = new account_info;
    c->account = std::move(temp_account);
    c->password = std::move(temp_password);
    c->if_admin = if_admin;
    strcpy_s(c->sp_code, temp_sp_code);
    c->next = nullptr;
    c->prev = nullptr;
    if (!head) {
        head = c;
        tail = c;
    } else {
        tail->next = c;
        c->prev = tail;
        tail = c;
    }
}

void account_manager::write_account_to_cache(
    string temp_account,
    string temp_password,
    bool if_admin,
    char* temp_sp_code)
{
    // ���ع�
    cache2 = new account_info;
    cache2->account = std::move(temp_account);
    cache2->password = std::move(temp_password);
    cache2->if_admin = if_admin;
    strcpy_s(cache2->sp_code, temp_sp_code);
    cache2->next = nullptr;
    cache2->prev = nullptr;
    // ��Ҫ����ռ�
}

void account_manager::write_list_to_file_trunc()
{
    fstream file;
    file.open(file_location, ios::binary | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "��account_info.datʧ�ܣ������˳�����" << endl;
        Sleep(150);
        exit(-1);
    } else {
        account_info* c;
        for (c = head; c; c = c->next) {
            file.write((char*)(c), sizeof(account_info));
        }
        file.close();
        //��ʱcָ�գ�û��Ҫdelete
    }
}

// write_list_to_file_app
void account_manager::write_list_to_file_app()
{
    fstream file;
    file.open(file_location, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "д���ļ������У��� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    } else {
        file.write((char*)(cache2), sizeof(account_info));
    }
    delete cache2;
    file.close();
}

// change_account_password_in_file
void account_manager::change_account_password_in_file(const string& changed_account)
{
    int POS;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "�޸�����ǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    auto* temp = new account_info;
    while (file.read((char*)(temp), sizeof(account_info))) {
        if (changed_account == temp->account) {
            POS = file.tellg(); // g => ��ָ��
            break;
        }
    }
    delete temp;
    file.close();
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "�޸�����ǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    file.seekp(POS, ios::beg);
    file.write((char*)(cache2), sizeof(account_info));
    file.close();
}

void account_manager::load_file_to_list()
{
    auto* c = new account_info;
    fstream file;
    file.open(file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "��account_info.datʧ�ܣ������˳�����" << endl;
        Sleep(150);
        exit(-1);
    } else {
        while (file.read((char*)(cache), sizeof(account_info))) {
            write_account_to_list(
                c->account,
                c->password,
                c->if_admin,
                c->sp_code);
        }
        // delete cache; //���Ͼͱ���
        file.close();
    }
}

auto account_manager::check_account(
    const string& input_account,
    const string& input_password) -> int
{
    // ȫ�µ��߼� -- ֱ�Ӵ��ļ�����
    bool if_account_exists = false;
    bool if_password_correct = false;
    int result = -2;
    cache2 = new account_info;
    fstream file(account_info_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�����˺���Ϣʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read((char*)(cache), sizeof(account_info))) {
        if (cache2->account == input_account) {
            if_account_exists = true;
            if (cache2->password == input_password) {
                if_password_correct = true;
                if (cache2->if_admin)
                    result = 1;
                else
                    result = 0;
            }
        }
    }
    if (!if_account_exists)
        result = -2;
    else if (!if_password_correct)
        result = -1;
    delete cache2;
    file.close();
    return result;
}

account_manager::account_info* account_manager::if_account_exists(const string& temp_account)
{
    account_info* c;
    for (c = head; c; c = c->next) {
        if (c->account == temp_account) {
            break;
        }
    }
    return c;
}

auto account_manager::generate_sp_code() -> char*
{
    char* temp = new char[11];
    uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e(time(nullptr)); // ����=��ǰʱ�䣬ȷ�����Ӳ�������ȷ����������Ĳ���
    for (int i = 0; i < 11; i++) {
        temp[i] = ('0' + u(e));
    }
    temp[10] = '\0';
    return temp;
}

void account_manager::change_account_in_list(
    account_manager::account_info* changed_account,
    string changed_password,
    char* changed_sp_code)
{
    changed_account->password = std::move(changed_password);
    strcpy_s(changed_account->sp_code, changed_sp_code);
}

void account_manager::change_account_in_cache(
    account_manager::account_info* changed_account,
    string changed_password,
    char* changed_sp_code)
{
    changed_account->password = std::move(changed_password);
    strcpy_s(changed_account->sp_code, changed_sp_code);
}

auto account_manager::if_sp_code_is_correct(
    const string& temp_account,
    char* temp_sp_code) -> account_manager::account_info*
{
    cache2 = new account_info;
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "�����˺���Ϣʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (account_into_file.read((char*)(cache), sizeof(account_info))) {
        if (cache2->account == temp_account && strcmp(cache2->sp_code, temp_sp_code) == 0) {
            result = cache2;
            break;
        }
    }
    account_into_file.close();
    return result;
}

auto account_manager::if_sp_code_exits(char* temp_sp_code) -> account_manager::account_info*
{
    bool if_found = false;
    cache2 = new account_info;
    account_info* result = nullptr;
    fstream account_into_file(account_info_file_location, ios::in | ios::binary);
    if (!account_into_file.is_open()) {
        cout << "�����˺���Ϣǰ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (account_into_file.read((char*)(cache2), sizeof(account_info))) {
        if (strcmp(cache2->sp_code, temp_sp_code) == 0) {
            if_found = true;
            result = cache2;
            break;
        }
    }
    account_into_file.close();
    return result;
}

// interface-����
auto account_manager::shell_of_account_login() -> int // ��Ҫ�ڵ��Բ㣬�������룬�������ڹ��캯���н���
{
    int judger = -1;
    int temp_used_time = get_used_time();
    if (temp_used_time == 0) { //��δʹ�ù����
        first_create_account();
    }
    if (temp_used_time != 0) {
        // load_file_to_list(); //���ǵ�һ��ʹ�ã��Ű�"�˺���Ϣ"���뻺��
        // �ع�֮�󣬲�����ȫ�����ˣ�DFD [Direct from disk]
    }
    cout << "��ӭʹ�� [�������һ�廯����ϵͳ]�����������¼ҳ��" << endl
         << endl;
    for (;;) {
        cout << "������ʾ��¼ѡ�" << endl;
        cout << "====================================================" << endl;
        cout << "     1.ʹ��--�˺�����--��¼" << endl;
        cout << "     2.ʹ��--ƾ���ļ�--��¼" << endl;
        cout << "     3.�½��˺�" << endl;
        cout << "     4.��������/�޸�����" << endl;
        cout << "     5.�ٴ���ʾ�����б�" << endl;
        cout << "     6.ȡ����¼���˳�����" << endl;
        cout << "====================================================" << endl;
        cout << "�������Ӧ���(����5�ٴ���ʾ�����б�): ";
        int temp;
        cin >> temp;
        cout << endl
             << endl;
        if (temp == 6) { // ����Ҳ��Ҫ���� �˺Ÿ��� ��Ӧ�� �ļ�
            cout << "ȡ����¼�����򼴽��Զ��˳�" << endl;
            Sleep(300);
            exit(1);
        } else if (temp == 1) {
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
                break;
            }
        } else if (temp == 2) {
            judger = sign_in_by_sp_code();
            if (judger == -2) {
                cout << "�����������ƾ����ƥ����˻��������ٴ���ʾ��¼ѡ��" << endl
                     << endl;
                Sleep(150);
                // system("cls"); //����
            } else if (judger == -1) { // sp_code��¼�������ڷ���-1�����
                cout << "�˻����ڣ�����������󣡼����ٴ���ʾ��¼ѡ��" << endl
                     << endl;
                Sleep(150);
                // system("cls"); //����
            } else {
                break;
            }
        } else if (temp == 3) {
            create_account();
        } else if (temp == 4) {
            change_password();
        } else if (temp == 5) {
            system("cls");
            continue;
        } else {
            cout << "û����" << temp << "��Ӧ�Ĺ��ܣ������ٴ���ʾ��¼ѡ��" << endl
                 << endl;
            Sleep(150);
            // system("cls"); //����
        }
    }
    delete_list();
    return judger;
}

void account_manager::first_create_account()
{
    string temp_account;
    string temp_password;
    string temp_password_check;
    bool if_this_is_admin = true;
    bool if_try_again = false;
    //������Ϣ
    cout << "�״�ʹ��ϵͳ�����ȴ���һ������Ա�˺ţ�" << endl;
    while (true) {
        cout << "������ <�û���> �� ";
        cin >> temp_account;
        if (if_account_exists(temp_account)) {
            system("cls");
            cout << "�Ѵ��ڸ��˺ţ����������� <�û���> ��" << endl;
            Sleep(250);
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
            cout << "������ո����õ� <����> �� ";
            cin >> temp_password_check; //��Ҫ��������ʾ��
            if (temp_password_check == temp_password) {
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
    char* temp_so_code = generate_sp_code();
    //��������
    write_account_to_list(temp_account, temp_password, if_this_is_admin, temp_so_code);
    //��������ļ�
    write_list_to_file_trunc();
    //����������ѡ���Ƿ���¡�����Ա�˺���Ŀ��
    if (cache2->if_admin == true)
        update_used_time();
    //�µ��˺�����д���ļ�
    write_used_time_into_file();
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
        cout << "������ <�û���> �� ";
        cin >> temp_account;
        if (if_account_exists(temp_account)) {
            system("cls");
            cout << "�Ѵ��ڸ��˺ţ����������� <�û���> ��" << endl;
            Sleep(250);
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
            cout << "������ո����õ� <����> �� ";
            cin >> temp_password_check; //��Ҫ��������ʾ��
            if (temp_password_check == temp_password) {
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
    char* temp_so_code = generate_sp_code();
    // д��cache
    write_account_to_cache(temp_account, temp_password, if_this_is_admin, temp_so_code);
    // cacheд���ļ�β��
    write_list_to_file_app();
    // ������������--����Ա�˺���Ŀ
    if (cache2->if_admin == true)
        update_used_time();
    // �µ��˺�����д���ļ�
    write_used_time_into_file();
    // չʾƾ����
    cout << "�Ѵ����˻������ɵ�ƾ����Ϊ��" << temp_so_code << endl;
    cout << "������μ�����ƾ���룬�⽫�����һص�[����Ա�˻�<����>]��Ψһƾ�ݣ�Ҳ�������һ�[��ͨ�˻�<����>]����Ҫƾ�ݣ�" << endl;
    cout << "�μ�ƾ��������������ַ����� >>> ";
    char skipper;
    cin >> skipper;
    Sleep(100);
    system("cls");
}

auto account_manager::sign_in_by_account() -> int
{
    string temp_account;
    string temp_password;
    int temp_result;
    cout << "�������û�����";
    cin >> temp_account;
    cout << "���������룺";
    cin >> temp_password;
    temp_result = check_account(temp_account, temp_password);
    if (temp_result != -2 && temp_result != -1) {
        give_the_plug_of_account(temp_account, temp_password);
    }
    return temp_result;
}

auto account_manager::sign_in_by_sp_code() -> int
{
    // ������ cache2���ǵý��ռ��
    int temp_result = 0;
    char temp_sp_code[11];
    account_info* c;
    cout << "������<ƾ����>��";
    cin >> temp_sp_code;
    c = if_sp_code_exits(temp_sp_code);
    if (!c) {
        temp_result = -2;
    } else {
        give_the_plug_of_account(temp_sp_code);
    }
    if (temp_result != -2) {
        if (c->if_admin)
            temp_result = 1;
    }
    delete cache2; // �������ڿ���ɾ����
    return temp_result;
}

void account_manager::change_password()
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
            if (!if_account_exists(temp_account)) {
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
            temp_account_ptr = if_sp_code_is_correct(temp_account, temp_sp_code); // �õ� cache2
            if (temp_account_ptr) {
                if_go_next = true;
                break;
            } else {
                cout << "<ƾ����> �� <�˺�> ��ƥ�䣬����Y=>�ٴ�����<ƾ����>�����������ַ�=>��������<�û���>" << endl;
                char temp;
                cin.get(temp);
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
    cout << "<ƾ����>��<�û���>�ɹ�ƥ�䣬��������������<������>" << endl;
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
            cout << "������ո����õ� <������> �� ";
            cin >> temp_password_check; //��Ҫ��������ʾ��
            if (temp_password_check == temp_password) {
                system("cls");
                cout << "�����޸ĳɹ�" << endl
                     << endl;
                Sleep(150);
                break;
            } else {
                cout << "������������벻һ�£���A=>�����������룬���������ַ�=>�ٴγ�������ո����õ������룺" << endl;
                char temp;
                cin.get(temp);
                if (temp == 'B') {
                    continue;
                } else {
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
    char* temp_so_code = generate_sp_code();
    // ��д����
    change_account_in_list(temp_account_ptr, temp_password, temp_so_code);
    // �����ļ��ж�Ӧ������
    change_account_password_in_file(temp_account);
    // չʾƾ����
    cout << "�������ɵ�ƾ����Ϊ��" << temp_so_code << endl;
    cout << "������μ�����ƾ���룬�⽫�����һص�[����Ա�˻�<����>]��Ψһƾ�ݣ�Ҳ�������һ�[��ͨ�˻�<����>]����Ҫƾ�ݣ�" << endl;
    cout << "�μ�ƾ����������������ַ������ >>> ";
    char skipper;
    cin >> skipper;
    delete cache2; // ���cache2
    Sleep(100);
    system("cls");
}

//�ӿں���
void account_manager::give_the_plug_of_account(
    const string& input_account,
    const string& input_password)
{
    login = new account_info;
    account_info* c;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "���ݲ���ʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (file.read((char*)(c), sizeof(account_info))) {
        if (c->account == input_account) {
            if (c->password == input_password) {
                login->account = c->account;
                login->password = c->password;
                strcpy_s(login->sp_code, c->sp_code); // unsafe����Ӧ�ý�ֹ��������strcpy_s�����б�����������
                login->if_admin = c->if_admin;
                break;
            }
        }
    }
}

void account_manager::give_the_plug_of_account(char* input_sp_code)
{
    login = new account_info;
    account_info* c;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "���ݲ���ʱ���� account_info.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(150);
        exit(-1);
    }
    while (file.read((char*)(c), sizeof(account_info))) {
        if (strcmp(c->sp_code, input_sp_code) == 0) {
            login->account = c->account;
            login->password = c->password;
            strcpy_s(login->sp_code, c->sp_code); // unsafe����Ӧ�ý�ֹ��������strcpy_s�����б�����������
            login->if_admin = c->if_admin;
            break;
        }
    }
}

//�����ӿں���
auto account_manager::return_account_name() -> string
{
    return login->account;
}
auto account_manager::return_account_password() -> string
{
    return login->password;
}

//�������ռ�ռ��
void account_manager::delete_list()
{
    account_info* t = head;
    if ((!t->next) && (!t->prev)) { // �½ڵ�
        delete t;
    } else {
        for (t = tail->prev; t; t = t->prev) {
            delete t->next;
        }
        // now, t comes to head
        delete head; // the same to " delete t; "
    }
}
