#include "daily_health_check_user.h"

#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "province_information_manager.h"

using namespace std;

daily_health_check_user::daily_health_check_user()
{
    // empty
}

daily_health_check_user::daily_health_check_user(
    const string& real_name,
    const string& c_account,
    const string& student_number) // ���û����洫��������
    : daily_health_check("flag")
{
    system("cls");
    // ���ڱ�д => �°� => �ļ��ṹ����~�޴�ĸı�
    /*write into current_info*/
    current_health_check_info = new health_check_info; // new���ǵ�delete
    current_health_check_info->student_name = real_name;
    current_health_check_info->account_id = c_account;
    current_health_check_info->student_id = student_number;
    current_health_check_info->if_check_is_necessary = true; // Ĭ�� �����ϱ�
    current_health_check_info->if_checked = false; // Ĭ�� û�д�
    plug_of_if_should_alert = false;
    /*load from file*/
    try_to_load_from_file_new(current_health_check_info->student_id);
    if (current_health_check_info->if_checked) {
        cout << "������ɽ����򿨣��Ƿ���Ҫ�鿴��ǰ�Ľ�����״̬��(����Y/y��鿴�������ַ��򲻲鿴�����Զ��ص���һ���˵�) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            show_check_status();
        } else {
            cout << "�յ����������� [�û�����] ... " << endl;
            Sleep(250);
        }
    } else if (current_health_check_info->if_check_is_necessary) {
        pre_push_label(); // û��ÿ�մ򿨣���ʾ��Ȼ��ǿ�ƴ�
        do_the_check();
    } else {
        cout << "����δ��ǿ��Ҫ����� <������>���������Ƿ�Ҫ��Ը�򿨣�(����Y/y��򿨣������ַ��򲻴򿨣����Զ��ص���һ���˵�) >>> ";
        string flag;
        cin >> flag;
        if (flag == "y" || flag == "Y") {
            do_the_check();
        } else {
            cout << "�յ����������� [�û�����] ... " << endl;
            Sleep(250);
        }
    }
}

daily_health_check_user::daily_health_check_user(
    const string& real_name,
    const string& c_account,
    const string& student_number,
    const string& any) // �ӿ���
{
    current_health_check_info = new health_check_info; // new���ǵ�delete
    current_health_check_info->student_name = real_name;
    current_health_check_info->account_id = c_account;
    current_health_check_info->student_id = student_number;
    current_health_check_info->if_check_is_necessary = true; // Ĭ�� �����ϱ�
    current_health_check_info->if_checked = false; // Ĭ�� û�д�
    plug_of_if_should_alert = false;
    try_to_load_from_file_new(current_health_check_info->student_id);
    if (!current_health_check_info->if_checked && current_health_check_info->if_check_is_necessary) {
        plug_of_if_should_alert = true;
    }
}

daily_health_check_user::~daily_health_check_user()
{
    /*
     * Nothing to do!
     * 'Cause this destructor will call the one of base class,
     * which will free all ptr_var-allocated space in the heap
     */
}

// ������������ѱ�����
void daily_health_check_user::try_to_load_from_file(const string& possible_file_name)
{
    fstream file;
    file.open(possible_file_name, ios::in | ios::binary);
    if (!file.is_open()) {
        // û�г��������£�����û������ļ���׼��ִ��
        if (current_health_check_info->if_check_is_necessary) {
            pre_push_label();
            do_the_check();
        } else {
            file.read(reinterpret_cast<char*>(current_health_check_info), sizeof(health_check_info));
        }
    }
    file.close(); // ��ʱ�ر�
}

// ������������ѱ�����

void daily_health_check_user::try_to_load_from_file_new(const string& input_sno)
{
    cached_health_check_info_tr = new health_check_info_trans;
    cached_health_check_info = new health_check_info;
    fstream file;
    const bool if_file_is_empty = check_if_file_is_empty();
    if (if_file_is_empty) {
        // �ļ��ǿյ�
        // ���� current_health_check_info �е�Ĭ�ϲ���
    } else {
        file.open(daily_health_check_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            // ����һ����������ļ����򲻿�����ʧ��
            cout << "�޷��� daily_health_check_list.dat�������Զ��˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (file.read(reinterpret_cast<char*>(cached_health_check_info_tr),
            sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (cached_health_check_info->account_id == current_health_check_info->account_id) {
                // move value
                *current_health_check_info = *cached_health_check_info; // �Ѿ�������������
                break;
            }
        }
        file.close(); // ��ʱ�ر�
        delete cached_health_check_info_tr; // �������
        delete cached_health_check_info; // �������
        cached_health_check_info_tr = nullptr;
        cached_health_check_info = nullptr;
    }
}

void daily_health_check_user::do_the_check()
{
    // �����õ����ļ��� [����]
    // const string file_name = file_root + current_health_check_info->student_id + "_daily_check.dat";
    // �Ƿ�ѯ�� �Ƿ�У
    bool if_ask_if_accommodated;
    // �Ƿ�У
    while (true) {
        cout << endl;
        cout << "�������Ƿ��Ѿ���У ��(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_returned_school = true;
            if_ask_if_accommodated = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_returned_school = false;
            if_ask_if_accommodated = false;
            break;
        } else {
            cout << "������ַ���Ч��������Y/y/N/n�����ٴ���ʾ֮ǰ��ѡ�" << endl;
        }
    }
    // �Ƿ�סУ
    if (!if_ask_if_accommodated) {
        current_health_check_info->if_is_accommodated = false;
    } else {
        while (true) {
            cout << endl;
            cout << "�������Ƿ�סУ ��(Y/N) >>> ";
            char temp;
            cin >> temp;
            if (temp == 'y' || temp == 'Y') {
                current_health_check_info->if_is_accommodated = true;
                break;
            } else if (temp == 'n' || temp == 'N') {
                current_health_check_info->if_is_accommodated = false;
                break;
            } else {
                cout << "������ַ���Ч��������Y/y/N/n�����ٴ���ʾ֮ǰ��ѡ�" << endl;
            }
        }
    }
    // �����Ƿ�����
    while (true) {
        cout << endl;
        cout << "������������Ƿ񳬹� 37 ���϶� ��(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_temperature_higher_than_37 = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_temperature_higher_than_37 = false;
            break;
        } else {
            cout << "������ַ���Ч��������Y/y/N/n�����ٴ���ʾ֮ǰ��ѡ�" << endl;
        }
    }
    // 14���� �Ƿ������� �з���/�߷��յ��� ͣ������һ��
    if (if_have_medium_and_high_risk_region_direct()) {
        while (true) {
            cout << endl;
            cout << "14���ڣ��Ƿ������� <�з���/�߷��յ���> ͣ������һ�� " << endl
                 << "(0=>�ޣ�1=>���з�������ͣ������һ�죬2=>�ڸ߷�������ͣ������һ�죬3=>��ʾ�С��߷��������б�) >>> ";
            int temp;
            cin >> temp;
            if (temp == 0) {
                current_health_check_info->if_passed_by_high_risk_regions = false;
                current_health_check_info->if_passed_by_medium_risk_regions = false;
            } else if (temp == 1) {
                current_health_check_info->if_passed_by_medium_risk_regions = true;
                current_health_check_info->if_passed_by_high_risk_regions = false;
            } else if (temp == 2) {
                current_health_check_info->if_passed_by_high_risk_regions = true;
                current_health_check_info->if_passed_by_medium_risk_regions = false;
            } else if (temp == 3) {
                // TODO: function_show_high_and_medium_risk_regions
                show_province_info_direct();
                continue; // �����У����������ȥ��
            } else {
                cout << "������ַ���Ч��������0/1/2/3�����ٴ���ʾ֮ǰ��ѡ�" << endl;
                continue;
            }
            break;
        }
    } else {
        current_health_check_info->if_passed_by_medium_risk_regions = false;
        current_health_check_info->if_passed_by_high_risk_regions = false;
        cout << endl
             << "Ŀǰ��34��ʡ�����򣬾�Ϊ�ͷ�������ϵͳ������ <�Ƿ����и߷�����ͣ��> ��һѡ�" << endl;
    }
    // �Ƿ��г����þ�ʷ
    while (true) {
        cout << endl;
        cout << "�����Ƿ��г����þ�ʷ ��(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_temperature_higher_than_37 = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_temperature_higher_than_37 = false;
            break;
        } else {
            cout << "������ַ���Ч��������Y/y/N/n�����ٴ���ʾ֮ǰ��ѡ�" << endl;
        }
    }
    // ���´򿨵�������
    current_health_check_info->if_checked = true;
    // д�� ���ļ�
    write_to_file_new(); // ���� �º���
    // end
    cout << endl;
    cout << "������� <ÿ�ս�����> ����л������ϣ�" << endl;
}

void daily_health_check_user::show_check_status() const
{
    // չʾ��ǰ�û��Ĵ�״̬
    cout << "����չʾ ��Ŀǰ�� ������״̬ ... " << endl;
    cout << "=======================================================" << endl;
    cout << "\t"
         << "�û����� " << current_health_check_info->account_id << endl;
    cout << "\t"
         << "������ " << current_health_check_info->student_name << endl;
    cout << "\t"
         << "ѧ�ţ� " << current_health_check_info->student_id << endl;
    cout << "\t"
         << "�Ƿ�ǿ�ƴ򿨣� " << trans_bool(current_health_check_info->if_check_is_necessary) << endl;
    cout << "\t"
         << "�Ƿ���ɴ򿨣� " << trans_bool(current_health_check_info->if_checked) << endl;
    cout << "\t"
         << "�Ƿ��Ѿ���У�� " << trans_bool(current_health_check_info->if_returned_school) << endl;
    cout << "\t"
         << "�Ƿ�סУ�� " << trans_bool(current_health_check_info->if_is_accommodated) << endl;
    cout << "\t"
         << "��14���Ƿ��� �߷��յ��� ͣ������1�죺 " << trans_bool(current_health_check_info->if_passed_by_high_risk_regions) << endl;
    cout << "\t"
         << "��14���Ƿ��� �з��յ��� ͣ������1�죺 " << trans_bool(current_health_check_info->if_passed_by_medium_risk_regions) << endl;
    cout << "\t"
         << "������������Ƿ񳬹� 37���϶ȣ� " << trans_bool(current_health_check_info->if_temperature_higher_than_37) << endl;
    cout << "\t"
         << "��14���Ƿ��� ����þ�ʷ�� " << trans_bool(current_health_check_info->if_go_abroad) << endl;
    cout << "=======================================================" << endl;
    cout << "��ʾ��ϣ�" << endl
         << endl;
    Sleep(500);
    cout << "����������󣬷��� [�û��˹��ܲ˵�] ... " << endl;
    _getch();
}

void daily_health_check_user::write_to_file(const string& filename) const
{
    fstream file;
    file.open(filename, ios::trunc | ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "��Ϣд��׶Σ��� xx_daily_check.dat ʧ�ܣ������˳�����" << endl;
        Sleep(250);
        exit(-1);
    }
    file.write(reinterpret_cast<char*>(current_health_check_info), sizeof(health_check_info));
    file.close();
}

void daily_health_check_user::write_to_file_new()
{
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    fstream file(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "��Ϣд��׶Σ��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!if_daily_check_file_is_empty) {
        // �ļ��ﲻ�ǿյ� => ��Ҫ�ҵ���ȷ��λ��
        auto POS = file.tellg();
        while (file.read(reinterpret_cast<char*>(cached_health_check_info_tr),
            sizeof(health_check_info_trans))) {
            *cached_health_check_info = cached_health_check_info_tr;
            if (cached_health_check_info->student_id == current_health_check_info->student_id) {
                break;
            }
            POS = file.tellg();
        }
        file.close();
        file.open(daily_health_check_file_location, ios::in | ios::binary | ios::out); // ���� ios::out������������ļ�
        if (!file.is_open()) {
            cout << "��Ϣд��׶Σ��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        *cached_health_check_info_tr = *current_health_check_info;
        file.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
        file.close();
    } else {
        // �ļ��ǿյ� => ֱ�Ӳ�����λ���ˣ�д��ͷ�Ͼ���ȫOK
        file.close();
        file.open(daily_health_check_file_location, ios::out | ios::binary | ios::in); // ios::in ʵ������������Ŀ������ȥ���������б�Ҫ���Ϸ�ֹ����flush���ļ�
        if (!file.is_open()) {
            cout << "��Ϣд��׶Σ��� daily_health_check_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        *cached_health_check_info_tr = *current_health_check_info;
        file.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
        file.close();
    }
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
}

void daily_health_check_user::show_province_info_direct()
{
    // ���� [չʾ����] ��public�ģ����в���Ҫ�̳л�����Ԫ������ֱ����ʱ���þͿ���
    const auto* temp = new province_information_manager;
    //
    temp->show_high_and_medium_risk_regions();
    delete temp;
}

bool daily_health_check_user::if_have_medium_and_high_risk_region_direct()
{
    auto* temp = new province_information_manager;
    const bool result = temp->if_have_high_and_medium_risk_regions();
    delete temp;
    return result;
}
