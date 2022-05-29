#define _CRT_SECURE_NO_WARNINGS
#include "NAT_user.h"
#include <Windows.h>
#include <algorithm>
#include <corecrt_io.h>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void NAT_user::fill_list_of_unfinished_nat_checks_former_than_today()
{
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "Ԥ���� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "�� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (detail_file.read(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list))) {
        if (!(checker->time_should_do_this_NAT > today_) && checker->if_have_done_this_NAT == false) {
            cache_of_unfinished_nat_check current(
                checker->time_should_do_this_NAT,
                checker->type_of_this_NAT,
                checker->code_of_group_check_if_have);
            list_of_unfinished_nat_checks_former_than_today.push_back(current);
        }
    }
    delete checker;
    detail_file.close();
    // TODO: �� list_of_unfinished_nat_checks_former_than_today ȥ�� => û�б�Ҫ�����Ǽ��ϱ��գ�
    auto& ref = list_of_unfinished_nat_checks_former_than_today;
    // sort(ref.begin(), ref.end());
    ref.erase(unique(ref.begin(), ref.end()), ref.end());
}

void NAT_user::fill_list_of_all_unfinished_nat_checks()
{
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "Ԥ���� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "�� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (detail_file.read(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list))) {
        if (checker->if_have_done_this_NAT == false) {
            cache_of_unfinished_nat_check current(
                checker->time_should_do_this_NAT,
                checker->type_of_this_NAT,
                checker->code_of_group_check_if_have);
            list_of_all_unfinished_nat_checks.push_back(current);
        }
    }
    delete checker;
    detail_file.close();
    // TODO: �� list_of_unfinished_nat_checks_former_than_today ȥ�� => û�б�Ҫ
    auto& ref = list_of_all_unfinished_nat_checks;
    // sort(ref.begin(), ref.end());
    ref.erase(unique(ref.begin(), ref.end()), ref.end());
}

bool NAT_user::return_if_have_unfinished_task_no_later_than_today() const
{
    return if_have_unfinished_task_no_later_than_today_;
}

string NAT_user::generate_detail_file_path(const string& sno, const string& name) const
{
    const string folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
    string file_path = folder_path + sno + R"(_)" + name + ".dat";
    return file_path;
}

string NAT_user::generate_temp_detail_file_path(const string& sno, const string& name) const
{
    const string folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
    string file_path = folder_path + sno + R"(_)" + name + R"(_temp)" + ".dat";
    return file_path;
}

void NAT_user::set_detail_file_path()
{
    const string folder_path = NAT_detail_file_root + R"(\)" + sno_ + R"(_)" + name_ + R"(_detail_info)";
    // make sure the folder of folder_path exists
    if (_access(folder_path.c_str(), 0) == -1) {
        if (_mkdir(folder_path.c_str()) == 0) {
            // success
        } else {
            cout << "����" << folder_path << " Ŀ¼ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    const string file_path = folder_path + R"(\)" + sno_ + R"(_)" + name_ + ".dat";
    current_detail_file_name_ = file_path;
}

void NAT_user::set_temp_detail_file_path()
{
    const string folder_path = NAT_detail_file_root + R"(\)" + sno_ + R"(_)" + name_ + R"(_detail_info)";
    // make sure the folder of folder_path exists
    if (_access(folder_path.c_str(), 0) == -1) {
        if (_mkdir(folder_path.c_str()) == 0) {
            // success
        } else {
            cout << "����" << folder_path << " Ŀ¼ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
    const string file_path = folder_path + R"(\)" + sno_ + R"(_)" + name_ + R"(_temp)" + ".dat";
    temp_current_detail_file_name_ = file_path;
}

void NAT_user::check_if_have_unfinished_task_no_later_than_today()
{
    // TODO: CHECK & FILL THE VAR "if_have_unfinished_task_no_later_than_today_"
    bool result = false;
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "Ԥ���� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "�� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (detail_file.read(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list))) {
        if (checker->if_have_done_this_NAT == false && !(checker->time_should_do_this_NAT > today_)) {
            result = true;
            break;
        }
    }
    if_have_unfinished_task_no_later_than_today_ = result;
    delete checker;
    detail_file.close();
}

void NAT_user::urge_to_finish_unfinished()
{
    // ǿ�� => Ҫ���� ȷ����� ֮ǰδ��ɵ�
    confirm_unfinished_tasks_former_than_today(true);
}

void NAT_user::auto_remove_in_list_of_unfinished_nat_checks_former_than_today(const vector<time_manager>& remove_index_list)
{
    auto& ref = list_of_unfinished_nat_checks_former_than_today;
    // TODO: use remove_index to remove specific element from list_of_unfinished_nat_checks_former_than_today
    for (auto& remove_index : remove_index_list) {
        cache_of_unfinished_nat_check removed(remove_index);
        const auto iterator = remove(ref.begin(), ref.end(), removed);
        ref.erase(iterator, ref.end());
    }
    // end
}

void NAT_user::auto_remove_in_list_of_all_unfinished_nat_checks(const vector<time_manager>& remove_index_list)
{
    // TODO: use remove_index to remove specific element from list_of_all_unfinished_nat_checks
    // ��ʱ����
}

void NAT_user::confirm_unfinished_tasks_in_detail_file(const vector<time_manager>& confirm_index_list) const
{
    time_manager today;
    // TODO: use confirm_index to confirm in detail_file
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "Ԥ���� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    for (auto& confirm_index : confirm_index_list) {
        detail_file.open(current_detail_file_name_, ios::in | ios::binary);
        if (!detail_file.is_open()) {
            cout << "�� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        fstream temp_detail_file(temp_current_detail_file_name_, ios::out | ios::binary);
        if (!temp_detail_file.is_open()) {
            cout << "д�� personal_NAT_list ʧ�ܣ� �����˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (detail_file.read(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list))) {
            if (checker->if_have_done_this_NAT == false && checker->time_should_do_this_NAT == confirm_index) {
                checker->if_have_done_this_NAT = true; // ����Ϊ�����
                checker->time_of_finishing_this_NAT = today;
            }
            if (!checker->if_have_done_this_NAT) {
                // ֻ���� personal_list.dat �У����� δ��ɵĺ��� �� �������
                temp_detail_file.write(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list)); // ��д
            }
        }
        detail_file.close();
        temp_detail_file.close();
        remove(current_detail_file_name_.c_str());
        // bug => _OldFileName & _NewFileName ���� -> fixed
        rename(temp_current_detail_file_name_.c_str(), current_detail_file_name_.c_str());
    }
    delete checker;
}

void NAT_user::show_unfinished_tasks_former_than_today() const
{
    //
    if (!list_of_unfinished_nat_checks_former_than_today.empty()) {
        cout << R"(�������п��ܳ��ֵ� <�������> ���ȿ���Ϊ2/3/5���ֱ��Ӧ ��ѧԺ���š�����ѧԺ����+רҵ���š�����ѧԺ����+רҵ����+�༶���š� �����������֪Ϥ��)" << endl;
        Sleep(500);
        cout << "���漴����ӡ ��"
             << " ���� ���� " << today_ << " δ��ɵ� <������> �� ��ϸ��Ϣ��" << endl;
        Sleep(250);
        cout << endl;
        cout << sno_ << "_" << name_ << " ���� " << today_ << " δ��ɵ� <������> �� ��ϸ��Ϣ >> " << endl;
        cout << "======================================================================================" << endl;
        cout << "\t"
             << "���" << setw(20) << "Ԥ�����������" << setw(26) << "����������(����/����)" << setw(24) << "�������(������ʾNA)" << endl;
        int num = 1;
        for (auto& current : list_of_unfinished_nat_checks_former_than_today) {
            cout << "\t"
                 << num << ".";
            cout << setw(16) << current.time_should_do_this_NAT;
            cout << setw(22) << (current.type_of_this_NAT == 1 ? "����" : "����");
            cout << setw(20) << (current.group_code_if_have.empty() ? "NA" : current.group_code_if_have.c_str());
            cout << endl;
            ++num;
        }
        cout << "======================================================================================" << endl;
    } else {
        cout << "��ϲ����������� ���� <Ӧ�ڽ���ǰ��ɵ� ������> ��" << endl;
        Sleep(250);
    }
}

void NAT_user::confirm_unfinished_tasks_former_than_today(const bool& if_multi_confirm)
{
    vector<time_manager> remove_and_confirm_index_list {};
    vector<int> list_of_index_num {};
    bool if_multi_confirm_func = if_multi_confirm;
    if (list_of_unfinished_nat_checks_former_than_today.empty()) {
        cout << "û�� <Ӧ�ڽ���ǰ(��)��� ��δ��ɵ� ������>�������ص����ܲ˵� ..." << endl;
        Sleep(250);
        return;
    }
    if (!if_multi_confirm_func) {
        while (true) {
            cout << "����ѡ��ȷ��ģʽ => ����M/m������ȷ��(ȫ��ȷ��) || ����S/s��ֻȷ��һ�� >> ";
            string mode_flag;
            cin >> mode_flag;
            if (mode_flag == "M" || mode_flag == "m") {
                if_multi_confirm_func = true;
            } else if (mode_flag == "S" || mode_flag == "s") {
                if_multi_confirm_func = false;
            } else {
                cout << "������Ч����������ָ�������룡" << endl;
                Sleep(150);
                continue;
            }
            break;
        }
    }
    cout << "���ȣ������г� <Ӧ�ڽ���ǰ(��)��� ��δ��ɵ� ������> �б� >> " << endl
         << endl;
    show_unfinished_tasks_former_than_today();
    cout << endl;
    if (!if_multi_confirm_func) {
        int index_num;
        while (true) {
            cout << "���ڣ���������Ҫȷ�ϵ� ������ �� �ոյ��б��е� ���" << endl;
            cin >> index_num;
            if (index_num < 1 || index_num > list_of_unfinished_nat_checks_former_than_today.size()) {
                cout << "�����������Ч�������������������� ��� ... " << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        // operate
        const time_manager removed_time = list_of_unfinished_nat_checks_former_than_today[index_num - 1].time_should_do_this_NAT;
        remove_and_confirm_index_list.push_back(removed_time);
        update_num_of_finished_nat_of_input_sno(sno_); // NAT_list_file �е� ����ɺ����� ����
        confirm_unfinished_tasks_in_detail_file(remove_and_confirm_index_list);
    } else {
        bool all_confirm = false;
        bool partial_confirm_as_finished = false;
        constexpr bool partial_confirm_as_unfinished = false;
        while (true) {
            cout << "����ݸոյ��б�ѡ����ʵ� <��������ģʽ> :" << endl;
            cout << "\t"
                 << "A/a => ȫ��ȷ��Ϊ{�����}" << endl;
            cout << "\t"
                 << "B/b => ��һ�����ֶ�ȷ��Ϊ{�����}������ȫ���Զ�ȷ��Ϊ{δ���}" << endl;
            cout << "\t"
                 << "C/c => ��һ�����ֶ�ȷ��Ϊ{δ���}������ȫ���Զ�ȷ��Ϊ{�����} <�ݲ�֧��>" << endl;
            cout << "��������������ѡ�� >> ";
            string mode_flag;
            cin >> mode_flag;
            if (mode_flag == "A" || mode_flag == "a") {
                all_confirm = true;
            } else if (mode_flag == "B" || mode_flag == "b") {
                partial_confirm_as_finished = true;
            } else if (mode_flag == "C" || mode_flag == "c") {
                cout << "��Ǹ������ʱ��Ե�ʣ��� <����ģʽ> �ݲ�֧�֣���������������ѡ��" << endl;
                Sleep(250);
                continue;
            } else {
                cout << "������Ч������ָ�����������룡" << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        if (all_confirm) {
            // TODO: ȫ��ȷ��Ϊ{�����}
        }
        if (partial_confirm_as_finished) {
            // TODO: ��һ�����ֶ�ȷ��Ϊ{�����}������ȫ���Զ�ȷ��Ϊ{δ���}
            cout << "��������Ҫȷ��Ϊ{�����}�����(��Ч���뽫�ᱻ�Զ�����)[�ÿո�ָ������ɺ����������⸺������]: " << endl;
            for (;;) {
                int input;
                cin >> input;
                if (input < 0) {
                    break;
                } else if (input <= list_of_unfinished_nat_checks_former_than_today.size()) {
                    list_of_index_num.push_back(input);
                } else {
                    continue;
                }
            }
            cout << "������ɣ�" << endl;
        }
        if (partial_confirm_as_unfinished) {
            // TODO: ��һ�����ֶ�ȷ��Ϊ{δ���}������ȫ���Զ�ȷ��Ϊ{�����}
            // ��ʱ���������ģʽ
        }
        // TODO: branch_of_operation
        if (list_of_index_num.empty()) {
            // ����ߵ��� ��ȫ��ȷ��Ϊ����ɡ�
            for (const auto& element : list_of_unfinished_nat_checks_former_than_today) {
                time_manager removed_time = element.time_should_do_this_NAT;
                remove_and_confirm_index_list.push_back(removed_time);
            }
        } else {
            // ����ߵ��� ������ȷ��Ϊ����ɡ�
            for (const auto& index_num : list_of_index_num) {
                time_manager removed_time = list_of_unfinished_nat_checks_former_than_today[index_num - 1].time_should_do_this_NAT;
                remove_and_confirm_index_list.push_back(removed_time);
            }
        }
        // ��ʱ��ȥ��
        vector<cache_of_unfinished_nat_check>& ref = list_of_unfinished_nat_checks_former_than_today;
        // sort(ref.begin(), ref.end());
        ref.erase(unique(ref.begin(), ref.end()), ref.end());
        // update num_of_finished_nat_of_input_sno
        multi_update_num_of_finished_nat_of_input_sno(sno_, ref.size());
        // confirm in detail file
        confirm_unfinished_tasks_in_detail_file(remove_and_confirm_index_list);
    }
    auto_remove_in_list_of_unfinished_nat_checks_former_than_today(remove_and_confirm_index_list);
}

void NAT_user::confirm_all_unfinished_tasks(const bool& if_multi_confirm)
{
    // ����
}

bool NAT_user::return_if_have_unfinished_nat_no_later_than_today() const
{
    return if_have_unfinished_task_no_later_than_today_;
}

NAT_user::NAT_user(
    const string& student_name,
    const string& student_number,
    const string& dorm_number,
    const bool& if_use_as_plug_only,
    const bool& if_passed_by_high_risk_regions,
    const bool& if_passed_by_medium_risk_regions)
    : NAT_manager(student_name, student_number, dorm_number,
        if_passed_by_high_risk_regions, if_passed_by_medium_risk_regions)
{
    this->name_ = student_name;
    this->sno_ = student_number;
    this->dorm_num_ = dorm_number;
    this->if_passed_by_high_risk_regions_ = if_passed_by_high_risk_regions;
    this->if_passed_by_medium_risk_regions_ = if_passed_by_medium_risk_regions;
    // current_detail_file_name_ = generate_detail_file_path(sno_, name_); => ���ܿ����Դ�
    set_detail_file_path();
    set_temp_detail_file_path();
    check_if_have_unfinished_task_no_later_than_today();
    if (if_use_as_plug_only) {
        // ֻ������ ���ӿڡ� ����ô��ʱ ���캯����Ӧ�ý�����
        return;
    }
    fill_list_of_unfinished_nat_checks_former_than_today(); // pre_fill
    fill_list_of_all_unfinished_nat_checks(); // pre_fill
    if (if_have_unfinished_task_no_later_than_today_) {
        cout << "���ڼ�⵽���� <Ӧ�ڽ���ǰ(��)��� ��δ��ɵ� ������>���ʽ��Զ������� �����˹�ȷ�����Ƿ���ɣ�" << endl;
        confirm_unfinished_tasks_former_than_today(true);
    }
}

void NAT_user::shell_of_user_NAT_check()
{
    system("cls");
    cout << endl;
    cout << "��ӭʹ�� [��������Ϣ] ����ƽ̨ (�û���) ��������ʾ���ܲ˵���" << endl;
    while (true) {
        cout << endl;
        cout << "[��������Ϣ] ����ƽ̨ (�û���) >>> ���ܲ˵���" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1.�鿴 <Ӧ�ڽ���ǰ(��)��� ��δ��ɵ� ������> �б�" << endl;
        cout << "\t"
             << "2.�˹�ȷ�� <Ӧ�ڽ���ǰ(��)��� ��δ��ɵ� ������> �Ƿ���� (������)" << endl;
        cout << "\t"
             << "3.�˹�ȷ�� <δ��ɵ� ������> �Ƿ���� (������) [Ϊ��ֹ�������ͣ�øù���]" << endl;
        cout << "\t"
             << "4.�ٴ���ʾ ���ܲ˵�" << endl;
        cout << "\t"
             << "5.���� [�û��˹��ܲ˵�]" << endl;
        cout << "=====================================================" << endl;
        cout << "�������Ӧ��ѡ�";
        string choice;
        cin >> choice;
        if (choice == "5") {
            cout << "�յ��������˳��ù���ƽ̨����������һ���˵� ... " << endl;
            Sleep(250);
            break;
        } else if (choice == "4") {
            cout << "�յ������� �ٴ���ʾ ���ܲ˵� ... " << endl;
            Sleep(250);
        } else if (choice == "3") {
            confirm_all_unfinished_tasks();
            cout << "Ϊ��ֹ���������ͣ�øù��ܣ����� �ٴ���ʾ ���ܲ˵� ... " << endl;
            Sleep(250);
        } else if (choice == "2") {
            confirm_unfinished_tasks_former_than_today(false);
        } else if (choice == "1") {
            show_unfinished_tasks_former_than_today();
        } else {
            cout << "��Ǹ����δ������Ӧ�Ĺ��ܣ����� �ٴ���ʾ ���ܲ˵� ... " << endl;
            Sleep(250);
        }
    }
}
