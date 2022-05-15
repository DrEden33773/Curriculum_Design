// ReSharper disable CppClangTidyConcurrencyMtUnsafe
#include "province_information_manager.h"

#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

province_information_manager::province_information_manager()
{
    try_to_load_province_information_file(); // ���ļ���ʼ��
}

void province_information_manager::change_province_status()
{
    string temp_province;
    int temp_status;
    int returned_code;
    while (true) {
        cout << "��������Ҫ�ı� <����״̬> �� <ʡ����������>��";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "����� <ʡ����������> ��Ч������������" << endl;
        }
    }
    while (true) {
        cout << temp_province << " ��ǰ��״̬�ǣ�" << status_list[status_of_province[returned_code]] << endl;
        cout << "������ <���º��״̬����> (0=�ͷ��գ�1=�з��գ�2=�߷���)��";
        cin >> temp_status;
        if (temp_status < 0 || temp_status > 2) {
            system("cls");
            cout << "����� <״̬����> ��Ч������������" << endl;
        } else {
            status_of_province[returned_code] = temp_status;
            cout << "�ѽ� " << temp_province << " ����Ϊ " << status_list[temp_status] << " ״̬" << endl;
            break;
        }
    }
    write_province_information_file_trunc();
}

void province_information_manager::show_input_province_status() const
{
    string temp_province;
    int returned_code;
    while (true) {
        cout << "��������Ҫ�鿴 <����״̬> �� <ʡ����������>��";
        cin >> temp_province;
        returned_code = if_input_province_valid(temp_province);
        if (returned_code != -1) {
            break;
        } else {
            system("cls");
            cout << "����� <ʡ����������> ��Ч������������" << endl;
        }
    }
    cout << endl;
    cout << temp_province << " ��״̬�ǣ�" << status_list[status_of_province[returned_code]] << endl;
}

void province_information_manager::show_all_province_status() const
{
    cout.setf(ios::left); // formatter
    vector<string> high_risks;
    vector<string> mid_risks;
    vector<string> low_risks;
    for (int i = 0; i < 34; ++i) {
        if (status_of_province[i] == 2) {
            high_risks.push_back(province_list[i]);
        } else if (status_of_province[i] == 1) {
            mid_risks.push_back(province_list[i]);
        } else {
            low_risks.push_back(province_list[i]);
        }
    }
    const bool if_0 = !low_risks.empty();
    const bool if_1 = !mid_risks.empty();
    const bool if_2 = !high_risks.empty();
    cout << "���潫���� <״̬��Ϣ> ������� <ʡ������> �������Ϣ��" << endl
         << endl;
    cout << "==================================================================" << endl;
    //�߷��յ�����
    cout << endl
         << "  �߷��յ�����" << endl;
    if (!if_2) {
        cout << endl;
        cout << "\t" << setw(10) << "�޸߷��յ�����" << endl;
    } else {
        int num_of_high_risks = 0;
        for (const auto& high_risk : high_risks) {
            if (num_of_high_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << high_risk;
            ++num_of_high_risks;
        }
        cout << endl;
    }
    //�з��յ�����
    cout << endl
         << "  �з��յ�����" << endl;
    if (!if_1) {
        cout << endl;
        cout << "\t" << setw(10) << "���з��յ�����" << endl;
    } else {
        int num_of_mid_risks = 0;
        for (const auto& mid_risk : mid_risks) {
            if (num_of_mid_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << mid_risk;
            ++num_of_mid_risks;
        }
        cout << endl;
    }
    //�ͷ��յ�����
    cout << endl
         << "  �ͷ��յ�����" << endl;
    if (!if_0) {
        cout << endl;
        cout << "\t" << setw(10) << "�޵ͷ��յ�����" << endl;
    } else {
        int num_of_low_risks = 0;
        for (const auto& low_risk : low_risks) {
            if (num_of_low_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << low_risk;
            ++num_of_low_risks;
        }
        cout << endl;
    }
    cout << endl
         << "==================================================================" << endl;
    cout << endl
         << "�����ϣ�" << endl;
    cout << "����������� ... ";
    _getch();
    cout << endl;
    cout.unsetf(ios::left); // de_formatter
}

void province_information_manager::try_to_load_province_information_file()
{
    fstream file;
    file.open(province_file, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ԥ���ؽ׶Σ����� province_information.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(province_file, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "�� province_information.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.read(reinterpret_cast<char*>(status_of_province + i), sizeof(int));
        }
    }
    file.close();
}

void province_information_manager::write_province_information_file_trunc()
{
    fstream file;
    file.open(province_file, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "�� province_information.dat ʧ�ܣ����򼴽��˳���" << endl;
        Sleep(250);
        exit(-1);
    } else {
        for (int i = 0; i < 34; ++i) {
            file.write(reinterpret_cast<char*>(status_of_province + i), sizeof(int)); // һ��ֻд��һ���ڴ浥Ԫ����ֹ��������
        }
    }
    file.close();
}

int province_information_manager::if_input_province_valid(const string& input_province) const
{
    int result = -1;
    for (int i = 0; i < 34; ++i) {
        if (province_list[i] == input_province) {
            result = i;
        }
    }
    return result;
}

void province_information_manager::show_high_and_medium_risk_regions() const
{
    cout.setf(ios::left); // formatter
    vector<string> high_risks;
    vector<string> mid_risks;
    for (int i = 0; i < 34; ++i) {
        if (status_of_province[i] == 2) {
            high_risks.push_back(province_list[i]);
        } else if (status_of_province[i] == 1) {
            mid_risks.push_back(province_list[i]);
        }
    }
    const bool if_1 = !mid_risks.empty();
    const bool if_2 = !high_risks.empty();
    cout << endl;
    cout << "==================================================================" << endl;
    //�߷��յ�����
    cout << endl
         << "  �߷��յ�����" << endl;
    if (!if_2) {
        cout << endl;
        cout << "\t" << setw(10) << "�޸߷��յ�����" << endl;
    } else {
        int num_of_high_risks = 0;
        for (const auto& high_risk : high_risks) {
            if (num_of_high_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << high_risk;
            ++num_of_high_risks;
        }
        cout << endl;
    }
    //�з��յ�����
    cout << endl
         << "  �з��յ�����" << endl;
    if (!if_1) {
        cout << endl;
        cout << "\t" << setw(10) << "���з��յ�����" << endl;
    } else {
        int num_of_mid_risks = 0;
        for (const auto& mid_risk : mid_risks) {
            if (num_of_mid_risks % 5 == 0) {
                cout << endl;
            }
            cout << setw(10) << mid_risk;
            ++num_of_mid_risks;
        }
        cout << endl;
    }
    cout << endl
         << "==================================================================" << endl;
    cout << endl;
    cout.unsetf(ios::left); // de_formatter
}

bool province_information_manager::if_have_high_and_medium_risk_regions()
{
    bool result = false;
    for (const int i : status_of_province) {
        if (i == 1 || i == 2) {
            result = true;
        }
    }
    return result;
}

void province_information_manager::shell_admin()
{
    system("cls");
    cout << endl;
    cout << "��ӭ���� [ʡ�����������������Ϣ] ����ƽ̨, ������ʾ���ܲ˵� ... " << endl;
    bool if_continue = true;
    while (true) {
        cout << endl;
        cout << "[ʡ�����������������Ϣ] ����ƽ̨ <���ܲ˵�>" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1. ��ʾ����ʡ������� ����״̬" << endl;
        cout << "\t"
             << "2. ��ʾָ��ʡ������� ����״̬" << endl;
        cout << "\t"
             << "3. �����ض�ʡ������� ����״̬" << endl;
        cout << "\t"
             << "4. �ٴ���ʾ ���ܲ˵�" << endl;
        cout << "\t"
             << "5. ���� [����Ա����]" << endl;
        cout << "=====================================================" << endl;
        cout << "�������Ӧ������ >> ";
        char flag;
        cin >> flag;
        system("cls");
        switch (flag) {
        case '1':
            show_all_province_status();
            break;
        case '2':
            show_input_province_status();
            break;
        case '3':
            change_province_status();
            break;
        case '4':
            cout << "�յ�������������ʾ [���ܲ˵�] ... " << endl;
            Sleep(250);
            break;
        case '5':
            cout << "�յ��������˳���ƽ̨������ [����Ա����] ..." << endl;
            Sleep(250);
            if_continue = false;
            break;
        default:
            cout << "����δ����������������ʾ ���ܲ˵� ... " << endl;
            Sleep(250);
            break;
        }
        if (!if_continue)
            break;
    }
}

void province_information_manager::shell_user() { }
