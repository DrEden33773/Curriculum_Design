// ReSharper disable All
#include "NAT_admin.h"

#include <Windows.h>
#include <corecrt_io.h>
#include <cstdlib>
#include <cstring>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
using namespace std;

int NAT_admin::return_num_of_nat_by_name(const string& input_name)
{
    int result = 0;
    // assume that input_name exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_name == input_name) {
            break;
        }
    }
    result = cache_NAT_template_tr->total_num_of_NAT;
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

int NAT_admin::return_num_of_nat_by_sno(const string& input_sno)
{
    int result = 0;
    // assume that input_sno exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            break;
        }
    }
    result = cache_NAT_template_tr->total_num_of_NAT;
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

int NAT_admin::return_finished_num_of_nat_by_name(const string& input_name)
{
    int result = 0;
    // assume that input_name exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_name == input_name) {
            break;
        }
    }
    result = cache_NAT_template_tr->total_num_of_finished_NAT;
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

int NAT_admin::return_finished_num_of_nat_by_sno(const string& input_sno)
{
    int result = 0;
    // assume that input_sno exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            break;
        }
    }
    result = cache_NAT_template_tr->total_num_of_finished_NAT;
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

bool NAT_admin::check_if_institute_is_valid(const string& institute_code)
{
    bool result = false;
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->department_num == institute_code) {
            result = true;
            break;
        }
    }
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

bool NAT_admin::check_if_profession_is_valid(const string& institute_code, const string& profession_code)
{
    bool result = false;
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->department_num == institute_code && cache_NAT_template->profession_num == profession_code) {
            result = true;
            break;
        }
    }
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

bool NAT_admin::check_if_political_class_is_valid(const string& institute_code, const string& profession_code, const string& political_class_code)
{
    bool result = false;
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->department_num == institute_code && cache_NAT_template->profession_num == profession_code && cache_NAT_template->class_num == political_class_code) {
            result = true;
            break;
        }
    }
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    return result;
}

bool NAT_admin::group_existence_checking_manager(
    const string& institute_code,
    const string& profession_code,
    const string& political_class_code)
{
    if (!(institute_code == "empty")) {
        if (check_if_institute_is_valid(institute_code)) {
            if (!(profession_code == "empty")) {
                if (check_if_profession_is_valid(institute_code, profession_code)) {
                    if (!(political_class_code == "empty")) {
                        if (check_if_political_class_is_valid(institute_code, profession_code, political_class_code)) {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return true;
                    }
                } else {
                    return false;
                }
            } else {
                return true;
            }
        } else {
            return false;
        }
    } else {
        return true;
    }
}

string NAT_admin::set_group_code()
{
    // ָ����������
    string flag;
    while (true) {
        cout << "����ָ�� <����> ������" << endl;
        cout << "\t"
             << "1. �����û�(ȫУ)" << endl;
        cout << "\t"
             << "2. �ض�Ժϵ�� �����û�" << endl;
        cout << "\t"
             << "3. �ض�Ժϵ�µ� �ض�רҵ�� �����û�" << endl;
        cout << "\t"
             << "4. �ض�Ժϵ�µ� �ض�רҵ�ڵ� �ض�������� �����û�" << endl;
        cout << "�����������Ӧ��������� ����ָ�� >> ";
        cin >> flag;
        if (!(flag == "1" || flag == "2" || flag == "3" || flag == "4")) {
            cout << "������Ч����������ָ����" << endl;
            continue;
        }
        break;
    }
    // flag has been set
    string code_of_institute; // ԺУ �� ����
    string code_of_profession; // רҵ �� ����
    string code_of_political_class; // רҵ �� ����
    if (flag == "1") {
        // ȫ�û�
    } else {
        while (true) {
            cout << "������ָ���� ԺУ ���� >> ";
            cin >> code_of_institute;
            if (!group_existence_checking_manager(code_of_institute)) {
                cout << "���ݿ��в����� ������ ԺУ���ţ������������������� ... " << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        if (!(flag == "2")) {
            while (true) {
                cout << "������ָ���� רҵ ���� >> ";
                cin >> code_of_profession;
                if (!group_existence_checking_manager(code_of_institute, code_of_profession)) {
                    cout << "���ݿ��в����� ������ ԺУ����&רҵ���� ��ϣ������������������� רҵ���� ... " << endl;
                    Sleep(250);
                    continue;
                }
                break;
            }
            if (!(flag == "3")) {
                while (true) {
                    cout << "������ָ���� ������ ���� >> ";
                    cin >> code_of_political_class;
                    if (!group_existence_checking_manager(code_of_institute, code_of_profession, code_of_political_class)) {
                        cout << "���ݿ��в����� ������ ԺУ����&רҵ����&��������� ��ϣ������������������� ��������� ... " << endl;
                        Sleep(250);
                        continue;
                    }
                    break;
                }
            }
        }
    }
    string final_group_code = code_of_institute + code_of_profession + code_of_political_class;
    if (flag == "1") {
        final_group_code = "all";
    }
    return final_group_code;
}

inline string NAT_admin::generate_detail_file_path(const string& sno, const string& name) const
{
    const string folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
    string file_path = folder_path + sno + R"(_)" + name + ".dat";
    return file_path;
}

void NAT_admin::set_c_nat_template_by_name(const string& input_name)
{
    // attention: after called constructor of NAT_manager, "c_NAT_template" has been initialized
    // assume that input_name exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_name == input_name) {
            *c_NAT_template = *cache_NAT_template;
            break;
        }
    }
}

void NAT_admin::set_c_nat_template_by_sno(const string& input_sno)
{
    // attention: after called constructor of NAT_manager, "c_NAT_template" has been initialized
    // assume that input_sno exists
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            *c_NAT_template = *cache_NAT_template;
            break;
        }
    }
}

void NAT_admin::arrange_nat_for_input_users(const vector<map<string, time_manager>>& input_users)
{
    // REFACTORED =>
    // assume that input_users all exist
    for (auto& input_user_map : input_users) {
        string current_sno;
        time_manager current_time_to_do_NAT;
        for (auto& input_user_pair : input_user_map) {
            current_sno = input_user_pair.first;
            current_time_to_do_NAT = input_user_pair.second;
        }
        // now store current_sno
        string returned_name = return_real_name_by_sno(current_sno);
        string current_detail_info_folder_path = NAT_detail_file_root + R"(\)" + current_sno + R"(_)" + returned_name + R"(_detail_info\)";
        string to_generate_folder = NAT_detail_file_root + R"(\)" + current_sno + R"(_)" + returned_name + R"(_detail_info)";
        generate_input_personal_detail_folder(to_generate_folder);
        int current_nat_num = return_num_of_nat_by_sno(current_sno);
        string current_info_file_name = current_detail_info_folder_path + std::to_string(current_nat_num) + ".dat";
        string refactored_file_name = current_detail_info_folder_path + current_sno + "_" + returned_name + ".dat";
        fstream file(refactored_file_name, ios::app | ios::binary);
        if (!file.is_open()) {
            cout << "Ԥ���� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.close();
        file.open(refactored_file_name, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        auto* storage_temp = new personal_NAT_list;
        storage_temp->time_should_do_this_NAT = current_time_to_do_NAT;
        storage_temp->type_of_this_NAT = 1;
        storage_temp->if_have_done_this_NAT = false;
        storage_temp->no_ = current_nat_num;
        auto* judger_temp = new personal_NAT_list;
        bool if_store = true;
        while (file.read(reinterpret_cast<char*>(judger_temp), sizeof(personal_NAT_list))) {
            if (judger_temp->time_should_do_this_NAT == current_time_to_do_NAT && judger_temp->if_have_done_this_NAT == false) {
                if_store = false;
                cout << "\t";
                cout << current_sno << " �� " << current_time_to_do_NAT << " ����δ��ɵ� �����⣬�Զ��������ʱ��İ��ţ�" << endl;
            }
        }
        file.close();
        file.open(refactored_file_name, ios::in | ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "д�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        if (if_store) {
            // append it to the tail (of the file)
            file.seekp(0, ios::end);
            file.write(reinterpret_cast<char*>(storage_temp), sizeof(personal_NAT_list));
            // ���� ��ǰѧ�� ��Ӧ �û��� ��Ԥ�� NAT ����
            update_num_of_nat_of_input_sno(current_sno);
        }
        delete storage_temp;
        delete judger_temp;
        file.close();
    }
}

void NAT_admin::arrange_nat_for_input_groups(const vector<map<string, time_manager>>& input_groups)
{
    // bug => forget to update total_num_of_nat for each user in the group => fixed
    // assume that input_political_classes all exist
    for (auto& input_group_map : input_groups) {
        string current_group;
        time_manager current_time_to_do_NAT;
        for (auto& input_user_pair : input_group_map) {
            current_group = input_user_pair.first;
            current_time_to_do_NAT = input_user_pair.second;
        }
        string institute_code, profession_code, political_class_code;
        unsigned long long group_code_len = current_group.length();
        if (!(current_group == "all")) {
            if (group_code_len == 2 || group_code_len == 3 || group_code_len == 5) {
                // ԺУ
                institute_code = current_group.substr(0, 2);
                if (group_code_len == 3 || group_code_len == 5) {
                    // ԺУ + רҵ
                    profession_code = current_group.substr(2, 1);
                    if (group_code_len == 5) {
                        // ԺУ + רҵ + �༶
                        political_class_code = current_group.substr(3, 2);
                    }
                }
            }
        }
        // TODO: to store => QUITE COMPLEX !!!!!
        cache_NAT_template = new NAT_template;
        cache_NAT_template_tr = new NAT_template_translator;
        fstream index_file(NAT_file_location, ios::in | ios::binary | ios::out);
        if (!index_file.is_open()) {
            cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        vector<string> list_of_sno_of_user_in_group {};
        while (index_file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
            *cache_NAT_template = *cache_NAT_template_tr;
            if (current_group != "all") {
                if (group_code_len == 2) {
                    // EG => 16
                    if (cache_NAT_template->department_num != institute_code) {
                        continue;
                    }
                }
                if (group_code_len == 3) {
                    // EG => 161
                    if (cache_NAT_template->department_num != institute_code || cache_NAT_template->profession_num != profession_code) {
                        continue;
                    }
                }
                if (group_code_len == 5) {
                    // EG => 16103
                    if (cache_NAT_template->department_num != institute_code || cache_NAT_template->profession_num != profession_code || cache_NAT_template->class_num != political_class_code) {
                        continue;
                    }
                }
            }
            const string name = cache_NAT_template->student_name;
            const string sno = cache_NAT_template->student_number;
            const string folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
            const string to_generate_folder = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info)";
            generate_input_personal_detail_folder(to_generate_folder);
            const string file_path = folder_path + sno + R"(_)" + name + ".dat";
            const string temp_file_path = folder_path + sno + R"(_)" + name + "_temp.dat";
            fstream file(file_path, ios::app | ios::binary);
            if (!file.is_open()) {
                cout << "Ԥ���� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            file.close();
            file.open(file_path, ios::in | ios::binary);
            if (!file.is_open()) {
                cout << "�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            // �жϰ��ŵ�ʱ����û��ײ��
            auto* temp_personal_nat_info = new personal_NAT_list;
            auto* temp_time_collapse_judger = new personal_NAT_list;
            bool if_time_collision_occured = false;
            while (file.read(reinterpret_cast<char*>(temp_time_collapse_judger), sizeof(personal_NAT_list))) {
                if (temp_time_collapse_judger->time_should_do_this_NAT == current_time_to_do_NAT && temp_time_collapse_judger->type_of_this_NAT == 0 && temp_time_collapse_judger->if_have_done_this_NAT == false) {
                    // ���ﲻ���б� ��֯���� => ��ΪֻҪ��һ����֯����ˣ�����Ϳ���ֱ����24h�ڷ���ʹ��
                    // ���� => ͬһ��ѧ����һ�������ֻ����һ����֯
                    if_time_collision_occured = true;
                    break;
                }
            }
            file.close();
            delete temp_time_collapse_judger;
            file.open(file_path, ios::in | ios::out | ios::binary);
            if (!file.is_open()) {
                cout << "�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            if (!if_time_collision_occured) {
                temp_personal_nat_info->time_should_do_this_NAT = current_time_to_do_NAT;
                temp_personal_nat_info->type_of_this_NAT = 0;
                temp_personal_nat_info->if_have_done_this_NAT = false;
                strcpy(temp_personal_nat_info->code_of_group_check_if_have, current_group.c_str());
                file.seekp(0, ios::end);
                file.write(reinterpret_cast<char*>(temp_personal_nat_info), sizeof(personal_NAT_list));
            }
            delete temp_personal_nat_info;
            file.close();
            // add => update total_num_of_nat for each user in the group
            // update_num_of_nat_of_input_sno(sno); -> bug: open index file again => fixed
            list_of_sno_of_user_in_group.push_back(sno);
        }
        index_file.close();
        for (const auto& sno : list_of_sno_of_user_in_group) {
            update_num_of_nat_of_input_sno(sno);
        }
        delete cache_NAT_template;
        delete cache_NAT_template_tr;
        cache_NAT_template_tr = nullptr;
        cache_NAT_template = nullptr;
    }
}

void NAT_admin::new_nat_arranger()
{
    // �����µĺ�����
    int type = 0;
    cout << "��ע�⣡Ϊ���ڱ�֤��ѧ��׼ȷ��ǰ���£�ȷ�����˷ѹ��ʦ����ʱ�䣬ÿ���û�һ����౻����һ�κ����⣡" << endl;
    Sleep(800);
    while (true) {
        cout << "�������ض����֣���ָ����Ҫ���ŵĺ��������� (1�����˼�⣬2��������) >> ";
        string flag;
        cin >> flag;
        if (flag == "1") {
            type = 1;
        } else if (flag == "2") {
            type = 2;
        } else {
            cout << "������Ч������������������ ... " << endl;
            continue;
        }
        break;
    }
    if (type == 1) {
        // ���˼��
        personal_nat_arranger();
    } else if (type == 2) {
        // ������ => �ǳ����ӣ���������
        collective_nat_arranger();
    }
}

void NAT_admin::personal_nat_arranger()
{
    // ���˼��
    /// ATTENTION:
    /// Ӧ�ð� ѧ�� ��Ϊ ���룬��Ϊ �������������ǲ�������ѧ��
    // TODO: ��� �������Ƿ��Ѿ��м�����ᰲ�ţ� �ж�ģ�� => done
    // TODO: ��������� ���ŵ� ʱ�� �Ѿ��� ���Ź����Զ����ԣ�ͬʱ������ʾ�����ǲ�����ֹ��������
    vector<map<string, time_manager>> list_of_name_and_time;
    cout << R"(����ҪΪ ������ ���� �����⣿��ָ�� >> )";
    int num;
    cin >> num;
    for (int i = 1; i <= num; ++i) {
        string stop_flag;
        cout << "�Ƿ���ǰ��ֹ���룿����Y/y����ֹ�����������ǿ���������� >> ";
        cin >> stop_flag;
        if (stop_flag == "y" || stop_flag == "Y") {
            cout << "�յ�����ǰ��ֹ����" << endl;
            break;
        }
        const int remained_num = num - i + 1;
        cout << "���������" << i << "������ (��ʣ" << remained_num << "�����ݴ�����) ... " << endl;
        string temp_sno;
        string returned_name;
        int temp_year, temp_month, temp_day;
        time_manager glb_temp_time;
        while (true) {
            // name_input
            cout << "������ �����ź������ ѧ�� (ϵͳ���Զ�ƥ��Ψһ����) >> ";
            cin >> temp_sno;
            if (!check_user_existence_by_sno(temp_sno)) {
                cout << "���ݿ��� û��ѧ��Ϊ " << temp_sno << " ��ѧ�������������룡" << endl;
                Sleep(200);
                continue;
            }
            returned_name = return_real_name_by_sno(temp_sno);
            break;
        }
        while (true) {
            // time_input
            cout << "������ Ϊ " << temp_sno << "_" << returned_name << " ���ŵ� ���������ʱ��" << endl;
            cout << "(�����ʽΪ���ꡢ�¡��գ��ÿո�ָ���������ɺ�س�����) >> ";
            cin >> temp_year >> temp_month >> temp_day;
            time_manager temp_time(temp_year, temp_month, temp_day);
            if (!temp_time.if_date_valid(&temp_time)) {
                cout << "������Ч�����������룡" << endl;
                Sleep(200);
                continue;
            }
            glb_temp_time = temp_time;
            break;
        }
        // judger
        if (if_person_has_collective_nat_check_by_sno(temp_sno, glb_temp_time)) {
            cout << "��⵽ " << temp_sno << "_" << returned_name << " ������ Ԥ���� ������������Զ����ϴ�����¼��" << endl;
            cout << "�������»ص� ¼����ʾ ���� ..." << endl;
            Sleep(250);
            --i; // ��������¼�룬ֱ�ӽ�����һ��
            continue;
        }
        // data confirm
        cout << "��ȷ�� ���ո��������Ϣ ��" << endl;
        cout << "\t"
             << "������" << returned_name << endl;
        cout << "\t"
             << "ѧ�ţ�" << temp_sno << endl;
        cout << "\t"
             << "���ŵ����ڣ�" << glb_temp_time << endl;
        cout << "���� Y/y ȷ��¼�룬���������������ǿ����� >> ";
        string flag;
        cin >> flag;
        if (!(flag == "Y" || flag == "y")) {
            cout << "��������¼�룬�������»ص� ¼����ʾ ���� ... " << endl;
            Sleep(250);
            --i; // ��������¼�룬ֱ�ӽ�����һ��
            continue;
        }
        map<string, time_manager> one_name_and_time;
        one_name_and_time[temp_sno] = glb_temp_time;
        list_of_name_and_time.push_back(one_name_and_time);
        cout << "�ѳɹ�¼��� " << i << " �����ݣ�" << endl;
    }
    // store the vector
    arrange_nat_for_input_users(list_of_name_and_time);
    cout << "�ѳɹ�Ϊ ������û�(��) ������ ��Ӧ�� ������(���Զ��ر���ʱ���ͻ)�������ص� ��һ���˵� ... " << endl;
    Sleep(250);
    // end
}

void NAT_admin::collective_nat_arranger()
{
    // ������
    vector<map<string, time_manager>> list_of_groups_and_time;
    cout << R"(Ϊ�˼��ٲ���Ҫ��¼�����һ��ֻ��Ϊһ�����尲�ź����⣡ )" << endl;
    Sleep(250);
    constexpr int num = 1;
    // cin >> num;
    for (int i = 1; i <= num; ++i) {
        string stop_flag;
        cout << "�Ƿ���ǰ��ֹ���룿����Y/y����ֹ�����������ǿ���������� >> ";
        cin >> stop_flag;
        if (stop_flag == "y" || stop_flag == "Y") {
            cout << "�յ�����ǰ��ֹ����" << endl;
            break;
        }
        const int remained_num = num - i + 1;
        cout << "���������" << i << "������ (��ʣ" << remained_num << "�����ݴ�����) ... " << endl;
        // ��������
        string final_group_code = set_group_code();
        // end of entering group, start enter time
        time_manager scheduled_time;
        int temp_year, temp_month, temp_day;
        cout << "����������Ϊ ���� ���� ���к������ ʱ�䣬";
        cout << "������ע�⣬ϵͳ�ݲ�֧�ּ��ѡ��ʱ�䡢ָ�������� �Ƿ���ڴ�ʱ����δ�μӵĺ������ ���ˣ����ܼ�ª�������½⣡" << endl;
        while (true) {
            cout << "���������� " << final_group_code << " ��һ���� Ӧ�ý��� �������ʱ��(�����գ��ֱ��ÿո���������س�����) >> ";
            cin >> temp_year >> temp_month >> temp_day;
            const auto* temp_time = new time_manager(temp_year, temp_month, temp_day);
            if (!time_manager::if_date_valid(temp_time)) {
                // if_date_valid is a static function, so you could simply enter it in the upper way
                cout << "��������ڲ��Ϸ������������������������� ... " << endl;
                delete temp_time;
                Sleep(250);
                continue;
            }
            scheduled_time = *temp_time;
            break;
        }
        // data confirm
        cout << "��ȷ�� ���ո��������Ϣ ��" << endl;
        cout << "\t"
             << "������ţ�" << final_group_code << endl;
        cout << "\t"
             << "���ŵ����ڣ�" << scheduled_time << endl;
        cout << "���� Y/y ȷ��¼�룬���������������ǿ����� >> ";
        string flag;
        cin >> flag;
        if (!(flag == "Y" || flag == "y")) {
            cout << "��������¼�룬�������»ص� ¼����ʾ ���� ... " << endl;
            Sleep(250);
            --i; // ��������¼�룬ֱ�ӽ�����һ��
            continue;
        }
        map<string, time_manager> one_group_and_time;
        one_group_and_time[final_group_code] = scheduled_time;
        list_of_groups_and_time.push_back(one_group_and_time);
        cout << "�ѳɹ�¼��� " << i << " �����ݣ�" << endl;
    }
    arrange_nat_for_input_groups(list_of_groups_and_time);
    cout << "�ѳɹ�Ϊ ָ��������(��) ������ ��Ӧ�� ������ (���Զ��ر���ʱ���ͻ)�������ص� ��һ���˵� ... " << endl;
    Sleep(250);
}

void NAT_admin::show_if_user_has_unfinished_nat_check()
{
    // ���ƾ��Ӧ����ѧ��
    string temp_sno;
    string temp_mode;
    string index_type = "sno";
    cout << "�ṩ��������ģʽ => 1. ������ȷ���� (�ݲ�����) , 2. ѧ�ž�ȷ����; Ĭ��ʹ��ѧ�ž�ȷ����" << endl;
    cout << "��Ҫע����ǣ��������ܴ��ڣ����ǲ����ܴ�����ͬ��ѧ��" << endl;
    cout << "�����������Ƿ���Ҫ���� ����ģʽ�أ�������Ҫ��������Y/y������ֱ����������ǿ����ݺ�س� >> ";
    string flag_of_index_mode;
    cin >> flag_of_index_mode;
    if (flag_of_index_mode == "Y" || flag_of_index_mode == "y") {
        index_type = "name";
    }
    if (index_type == "name") {
        if_user_has_unfinished_nat_check_by_name();
    }
    if (index_type == "sno") {
        if_user_has_unfinished_nat_check_by_sno();
    }
}

void NAT_admin::if_any_group_has_nat_check()
{
    // TODO: �����еļ�����в�ѯ
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    bool if_any_group_has_unfinished_nat_check = false;
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        string sno = cache_NAT_template->student_number;
        string name = cache_NAT_template->student_name;
        string current_detail_info_folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
        string to_generate = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info)";
        generate_input_personal_detail_folder(to_generate);
        string refactored_filename = current_detail_info_folder_path + sno + R"(_)" + name + ".dat";
        fstream detail_file(refactored_filename, ios::app | ios::binary);
        if (!detail_file.is_open()) {
            cout << "Ԥ���� personal_NAT_info ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        detail_file.close();
        detail_file.open(refactored_filename, ios::in | ios::binary);
        if (!detail_file.is_open()) {
            cout << "�� personal_NAT_info ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        auto* temp_detail = new personal_NAT_list;
        while (detail_file.read(reinterpret_cast<char*>(temp_detail), sizeof(personal_NAT_list))) {
            if (temp_detail->if_have_done_this_NAT == false && temp_detail->type_of_this_NAT == 0) {
                if_any_group_has_unfinished_nat_check = true;
                // delete temp_detail;
                break;
            }
        }
        if (if_any_group_has_unfinished_nat_check) {
            delete temp_detail;
            break;
        }
        delete temp_detail;
    }
    cout << "Ŀǰ " << (if_any_group_has_unfinished_nat_check ? "��" : "��") << " δ��ɵ� ���������" << endl;
    if (if_any_group_has_unfinished_nat_check) {
        // TODO: ��ʾ �Ƿ���Ҫ �г� ����δ���е� ���������
        // �Ƚϸ��ӣ���ʱ����
    }
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_admin::if_sp_group_has_nat_check()
{
    string final_group_code = set_group_code(); // ���ֱ���þͿ���. �ض�����
    unsigned long long len = final_group_code.length();
    // ��ֵõ���Ч��Ϣ => [����ģ��]
    {
        // ����ģ��
        string institute = "empty";
        string profession = "empty";
        string political_class = "empty";
        if (len == 2 || len == 3 || len == 5) {
            institute = final_group_code.substr(0, 2);
        }
        if (len == 3 || len == 5) {
            profession = final_group_code.substr(2, 1);
        }
        if (len == 5) {
            political_class = final_group_code.substr(3, 2);
        }
    }
    // start to show =>
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    {
        // ����
        bool judger = false;
        bool if_institute = true;
        bool if_profession = true;
        bool if_political_class = true;
    }
    bool if_sp_group_has_nat_check = false;
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        // ֱ���ж��Ƿ� �� ��ǰ�� ����ǵĻ������ļ����м��
        string final_compare_code;
        bool if_open_detail_file = false;
        if (final_group_code != "all") {
            if (len == 2 || len == 3 || len == 5) {
                final_compare_code += cache_NAT_template->department_num;
            }
            if (len == 3 || len == 5) {
                final_compare_code += cache_NAT_template->profession_num;
            }
            if (len == 5) {
                final_compare_code += cache_NAT_template->class_num;
            }
            if (final_compare_code == final_group_code) {
                if_open_detail_file = true;
            }
        } else {
            if_open_detail_file = true;
        }
        if (if_open_detail_file) {
            string sno = cache_NAT_template->student_number;
            string name = cache_NAT_template->student_name;
            string current_detail_info_folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
            string to_generate = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info)";
            generate_input_personal_detail_folder(to_generate);
            string refactored_filename = current_detail_info_folder_path + sno + R"(_)" + name + ".dat";
            fstream detail_file(refactored_filename, ios::app | ios::binary);
            if (!detail_file.is_open()) {
                cout << "Ԥ���� personal_NAT_info ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            detail_file.close();
            detail_file.open(refactored_filename, ios::in | ios::binary);
            if (!detail_file.is_open()) {
                cout << "�� personal_NAT_info ʧ�ܣ������˳����� ... " << endl;
                Sleep(250);
                exit(-1);
            }
            auto* temp_detail = new personal_NAT_list;
            while (detail_file.read(reinterpret_cast<char*>(temp_detail), sizeof(personal_NAT_list))) {
                if (temp_detail->if_have_done_this_NAT == false && temp_detail->type_of_this_NAT == 0 && strcmp(temp_detail->code_of_group_check_if_have, final_group_code.c_str()) == 0) {
                    if_sp_group_has_nat_check = true;
                    // delete temp_detail;
                    break;
                }
            }
            if (if_sp_group_has_nat_check) {
                delete temp_detail;
                break;
            }
        }
    }
    cout << "���� " << (if_sp_group_has_nat_check ? "��" : "��") << " δ��ɵ� ��������⣡" << endl;
    if (if_sp_group_has_nat_check) {
        // TODO: ��ʾ �Ƿ���Ҫ ��ϸ���г���һ�� δ���е� ��������� �� ʱ��
        // �Ƚϸ��ӣ���ʱ����
    }
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_admin::show_if_we_have_unfinished_group_nat_check()
{
    cout << "�Ƿ���Ҫ��ѯ �ض������� (����Y/y=>�ǣ����������ǿ�����=>��) >> ";
    string if_sp_group_flag;
    cin >> if_sp_group_flag;
    if (if_sp_group_flag == "Y" || if_sp_group_flag == "y") {
        if_sp_group_has_nat_check();
    } else {
        if_any_group_has_nat_check();
    }
}

void NAT_admin::manual_confirm_finish_nat_of_user()
{
    cout << "����ʱ�����⣬��������ʱ���迪���������½⣡" << endl;
}

void NAT_admin::manual_confirm_finish_nat_of_group()
{
    cout << "����ʱ�����⣬��������ʱ���迪���������½⣡" << endl;
}

void NAT_admin::show_nat_check_suggested_user(const bool& if_generate_file)
{
    // �洢
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    class judger {
    public:
        string sno;
        string name;
        string dorm_num;
        judger(
            string sno,
            string name,
            string dorm_num)
            : sno(std::move(sno))
            , name(std::move(name))
            , dorm_num(std::move(dorm_num))
        {
        }
        judger() = default;
    };
    vector<judger> part_1 {}; // ��һ���� => ǿֱ�ӽ��� => �����Լ����� ���� �߷�����
    vector<judger> part_2 {}; // �ڶ����� => ��ֱ�ӽ��� => �����Լ����� ���� �з�����
    vector<judger> part_3 {}; // �������� => ǿ��ӽ��� => �� ��һ�� ͬ���ᣬ�����ǵ�һ��
    vector<judger> part_4 {}; // ���Ĳ��� => ����ӽ��� => �� �ڶ��� ͬ���ᣬ�����ǵڶ���
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        string sno = cache_NAT_template->student_number;
        string name = cache_NAT_template->student_name;
        string dorm_num = cache_NAT_template->dorm_number;
        if (cache_NAT_template->if_passed_by_high_risk_regions || cache_NAT_template->if_passed_by_medium_risk_regions) {
            if (cache_NAT_template->if_passed_by_high_risk_regions) {
                judger current(sno, name, dorm_num);
                part_1.push_back(current);
            } else if (cache_NAT_template->if_passed_by_medium_risk_regions) {
                judger current(sno, name, dorm_num);
                part_2.push_back(current);
            }
            // ������� ͬʱ���� �и߷����� => ����ֻ���� �߷����� ����
        } else {
            bool if_this_person_is_in_part_3 = false;
            for (auto& person : part_1) {
                if (dorm_num == person.dorm_num) {
                    // ������
                    judger current(sno, name, dorm_num);
                    part_3.push_back(current);
                    if_this_person_is_in_part_3 = true;
                }
            }
            if (!if_this_person_is_in_part_3) {
                for (auto& person : part_2) {
                    if (dorm_num == person.dorm_num) {
                        // ������
                        judger current(sno, name, dorm_num);
                        part_4.push_back(current);
                    }
                }
            }
        }
    }
    // next
    if (!if_generate_file) {
        // TODO: print
        cout << "�����Ķ�������" << endl;
        cout << R"(һ����4�ּ���Ľ��飬�ֱ����£�)" << endl;
        cout << R"(��1�� => ����;���߷�����)" << endl;
        cout << R"(��2�� => ����;���з���������δ;���߷�����)" << endl;
        cout << R"(��3�� => δ;�� �и߷��������������;�� �߷����� ��ѧ��ͬ����)" << endl;
        cout << R"(��4�� => δ;�� �и߷��������������;�� �з����� ��ѧ��ͬ����)" << endl;
        cout << endl;
        Sleep(2000);
        cout << "���ڿ�ʼ��ӡ �������� ��" << endl;
        cout << endl;
        cout << "�� 1 �� ��������" << endl;
        cout << "=====================================================================" << endl;
        if (part_1.empty()) {
            cout << "\t"
                 << "�� ����1���������� ��ʱΪ�գ�" << endl;
        } else {
            cout << "\t"
                 << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            cout << endl;
            for (auto& part : part_1) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "�� 2 �� ��������" << endl;
        cout << "=====================================================================" << endl;
        if (part_2.empty()) {
            cout << "\t"
                 << "�� ����2���������� ��ʱΪ�գ�" << endl;
        } else {
            cout << "\t"
                 << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            cout << endl;
            for (auto& part : part_2) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "�� 3 �� ��������" << endl;
        cout << "=====================================================================" << endl;
        if (part_3.empty()) {
            cout << "\t"
                 << "�� ����3���������� ��ʱΪ�գ�" << endl;
        } else {
            cout << "\t"
                 << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            cout << endl;
            for (auto& part : part_3) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "�� 4 �� ��������" << endl;
        cout << "=====================================================================" << endl;
        if (part_4.empty()) {
            cout << "\t"
                 << "�� ����4���������� ��ʱΪ�գ�" << endl;
        } else {
            cout << "\t"
                 << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            cout << endl;
            for (auto& part : part_4) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
    } else {
        // TODO: generate_file
        const string file_name = R"(C:\Users\edwar\Desktop\cpp_final_task\users_suggested_to_do_NAT.txt)";
        fstream generated_file(file_name, ios::out);
        if (!generated_file.is_open()) {
            cout << "�� users_suggested_to_do_NAT.txt ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        // contents:
        generated_file << "�����Ķ�������" << endl;
        generated_file << R"(һ����4�ּ���Ľ��飬�ֱ����£�)" << endl;
        generated_file << R"(��1�� => ����;���߷�����)" << endl;
        generated_file << R"(��2�� => ����;���з���������δ;���߷�����)" << endl;
        generated_file << R"(��3�� => δ;�� �и߷��������������;�� �߷����� ��ѧ��ͬ����)" << endl;
        generated_file << R"(��4�� => δ;�� �и߷��������������;�� �з����� ��ѧ��ͬ����)" << endl;
        generated_file << endl;
        //
        generated_file << endl;
        generated_file << "��1�� ��������" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_1.empty()) {
            generated_file << "\t"
                           << "�� ����1���������� ��ʱΪ�գ�" << endl;
        } else {
            generated_file << "\t"
                           << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            generated_file << endl;
            for (auto& part : part_1) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "��2�� ��������" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_2.empty()) {
            generated_file << "\t"
                           << "�� ����2���������� ��ʱΪ�գ�" << endl;
        } else {
            generated_file << "\t"
                           << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            generated_file << endl;
            for (auto& part : part_2) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "��3�� ��������" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_3.empty()) {
            generated_file << "\t"
                           << "�� ����3���������� ��ʱΪ�գ�" << endl;
        } else {
            generated_file << "\t"
                           << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            generated_file << endl;
            for (auto& part : part_3) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "��4�� ��������" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_4.empty()) {
            generated_file << "\t"
                           << "�� ����4���������� ��ʱΪ�գ�" << endl;
        } else {
            generated_file << "\t"
                           << "����" << setw(18) << "ѧ��" << setw(18) << "�����" << endl;
            generated_file << endl;
            for (auto& part : part_4) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file.close();
    }
}

void NAT_admin::generate_file_of_suggested_nat_check_user()
{
    show_nat_check_suggested_user(true);
}

void NAT_admin::generate_file_of_unfinished_nat_check_user()
{
    // ���ֻ������ ���� ���� ����δ��ɵĺ����� �� �û��� ����
    time_manager today;
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    const string file_path = file_root + "list_of_users_with_unfinished_nat_check.txt";
    cout << "��ע�⣬ֻ����"
         << R"(��δ�������Ӧ���ڽ���ǰ��ɵĺ����⡱)"
         << "���û�������" << endl;
    cout << "���� >> "
         << "����������� " << today << ", ���û�ֻ�� " << ++today << " ֮��Ӧ��ɶ�δ��ɵĺ����⣬�򲻻�����������ϣ�" << endl;
    --today; // ������
    Sleep(750);
    cout << "���ڿ�ʼ��ȡ���ݲ������ļ� ... " << endl;
    Sleep(250);
    fstream index(NAT_file_location, ios::in | ios::binary);
    if (!index.is_open()) {
        cout << "�� NAT_list ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    class sno_name_pair {
    public:
        string sno;
        string name;
    };
    vector<sno_name_pair> customized_list {};
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    auto* temp_detail = new personal_NAT_list;
    while (index.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        const string sno = cache_NAT_template->student_number;
        const string name = cache_NAT_template->student_name;
        const string detail_file_path = generate_detail_file_path(sno, name);
        fstream detail_file(detail_file_path, ios::in | ios::binary);
        if (!detail_file.is_open()) {
            cout << "�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (detail_file.read(reinterpret_cast<char*>(temp_detail), sizeof(personal_NAT_list))) {
            if (temp_detail->if_have_done_this_NAT == false && !(temp_detail->time_should_do_this_NAT > today)) {
                sno_name_pair current;
                current.sno = sno;
                current.name = name;
                customized_list.push_back(current);
            }
        }
        detail_file.close();
    }
    delete temp_detail;
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
    index.close();
    if (customized_list.empty()) {
        cout << "û��"
             << "δ��� " << today << " ǰ(��) ���� <Ӧ��ɵĺ�����> �� {�û�}�������������� " << endl;
        Sleep(250);
        return;
    }
    fstream file(file_path, ios::out);
    if (!file.is_open()) {
        cout << "���� list_of_users_with_unfinished_nat_check.txt ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // output
    file << "δ��� " << today << " ǰ(��) ���� <Ӧ��ɵĺ�����> �� {�û�����} >> " << endl;
    file << endl;
    file << "================================================================" << endl;
    file << "\t"
         << "ѧ��" << setw(18) << "����" << endl;
    for (auto& customized_pair : customized_list) {
        file << "\t" << customized_pair.sno.c_str() << setw(18) << customized_pair.name.c_str() << endl;
    }
    file << "================================================================" << endl;
    file.close();
    cout << "�ļ� list_of_users_with_unfinished_nat_check.txt ���� " << file_root << " �����ɣ�" << endl;
    Sleep(250);
}

void NAT_admin::generate_input_personal_detail_folder(const string& input)
{
    if (_access(input.c_str(), 0) == -1) {
        if (_mkdir(input.c_str()) == 0) {
            // cout << "���� NAT_detail_file_root �ļ��гɹ�" << endl;
        } else {
            cout << "���� personal_detail_file_root �ļ���ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
}

// ������������������� => ԭ�ȵ��ļ��ṹ������
bool NAT_admin::search_in_detail_folder_if_person_has_collective_nat_check(
    const string& file_path,
    const int& file_num,
    const time_manager& input_time) const
{
    bool result = false;
    //
    auto* cache_detail_info = new personal_NAT_list;
    for (int i = 1; i <= file_num; ++i) {
        string file_name = file_path + std::to_string(i) + R"(.dat)";
        fstream file(NAT_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "�� personal_NAT_info �е� ����ļ� ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read(reinterpret_cast<char*>(cache_detail_info), sizeof(personal_NAT_list));
        if (cache_detail_info->if_have_done_this_NAT == false && cache_detail_info->type_of_this_NAT == 0 && cache_detail_info->time_should_do_this_NAT == input_time) {
            // ע���ж����� => һ���� δ��ɵ� �������, �������ں���������һ�� [������ͻ]
            result = true;
            break;
        }
    }
    delete cache_detail_info;
    return result;
}

// ��������������� => ����ع���� �ļ��ṹ
bool NAT_admin::search_in_detail_file_if_person_has_collective_nat_check(
    const string& name,
    const string& sno,
    const time_manager& time)
{
    bool result = false;
    const string current_detail_info_folder_path = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info\)";
    string to_generate = NAT_detail_file_root + R"(\)" + sno + R"(_)" + name + R"(_detail_info)";
    generate_input_personal_detail_folder(to_generate);
    const string refactored_filename = current_detail_info_folder_path + sno + R"(_)" + name + ".dat";
    fstream file(refactored_filename, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� " << sno << R"(_)" << name << ".dat"
             << " �ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(refactored_filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� " << sno << R"(_)" << name << ".dat"
             << " �ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    const auto startPOS = file.tellg();
    file.seekg(0, ios::end);
    const auto endPOS = file.tellg();
    if (startPOS == endPOS) {
        // empty refactored_file, return false
        return false;
    }
    auto* cache_detail_info = new personal_NAT_list;
    while (file.read(reinterpret_cast<char*>(cache_detail_info), sizeof(personal_NAT_list))) {
        if (cache_detail_info->if_have_done_this_NAT == false && cache_detail_info->type_of_this_NAT == 0 && cache_detail_info->time_should_do_this_NAT == time) {
            // ע���ж����� => һ���� δ��ɵ� �������, �������ں���������һ�� [������ͻ]
            result = true;
            break;
        }
    }
    file.close();
    delete cache_detail_info;
    return result;
}

void NAT_admin::if_user_has_unfinished_nat_check_by_name()
{
    cout << "����ʱ�����⣬��������ʱ���迪���������½⣡" << endl;
}

void NAT_admin::if_user_has_unfinished_nat_check_by_sno()
{
    string temp_sno;
    string temp_name;
    while (true) {
        cout << R"(��������������ѯ�� ѧ�� >> )";
        cin >> temp_sno;
        if (!check_user_existence_by_sno(temp_sno)) {
            cout << "���ݿ��в��������ո������ѧ�ţ������������������� ... " << endl;
            Sleep(250);
            continue;
        }
        break;
    }
    // get name & if_have_unfinished_nat_check
    bool if_have_unfinished_nat_check = false;
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream index_file(NAT_file_location, ios::in | ios::binary);
    if (!index_file.is_open()) {
        cout << "�� NAT_list.dat ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (index_file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == temp_sno) {
            temp_name = cache_NAT_template->student_name;
            if (cache_NAT_template->total_num_of_NAT != cache_NAT_template->total_num_of_finished_NAT) {
                if_have_unfinished_nat_check = true;
            }
            break;
        }
    }
    index_file.close();
    delete cache_NAT_template_tr;
    delete cache_NAT_template;
    cache_NAT_template_tr = nullptr;
    cache_NAT_template = nullptr;
    // out put
    cout << temp_sno << "_" << temp_name << (if_have_unfinished_nat_check ? " ��" : " ��") << " δ��ɵ� �����⣡" << endl;
    if (if_have_unfinished_nat_check) {
        cout << "�Ƿ���Ҫ��ʾ�� δ��ɵĺ����� �� Ӧ���ʱ��;������ͣ�����Y/y����ʾ�����������ǿ����������� >> ";
        string temp;
        cin >> temp;
        if (temp == "y" || temp == "Y") {
            show_sp_user_unfinished_nat_check_details(temp_sno, temp_name, false);
            cout << "��ʾ��ϣ��Ƿ���Ҫ ���ղ���ʾ���б� ����Ϊ �ļ�������Y/y�����ɣ����������ǿ����������� >> ";
            string temp2;
            cin >> temp2;
            if (temp2 == "y" || temp2 == "Y") {
                show_sp_user_unfinished_nat_check_details(temp_sno, temp_name, true);
            }
        }
    }
}

void NAT_admin::show_sp_user_unfinished_nat_check_details(
    const string& sno,
    const string& name,
    const bool& if_generate_file) const
{
    // ����ֻ��ʾ �������� û����ɵ�
    time_manager today;
    string detail_file_path = generate_detail_file_path(sno, name);
    fstream detail_file(detail_file_path, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "Ԥ���� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(detail_file_path, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "�� personal_NAT_info_file ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* temp = new personal_NAT_list;
    class cache_of_unfinished_nat_check {
    public:
        time_manager time_should_do_this_NAT;
        int type_of_this_NAT;
        string group_code_if_have = R"(NA)";
        cache_of_unfinished_nat_check() = default;
        cache_of_unfinished_nat_check(
            const time_manager& time_should_do_this_NAT,
            const int& type_of_this_NAT,
            const char* group_code_if_have)
        {
            this->time_should_do_this_NAT = time_should_do_this_NAT;
            this->type_of_this_NAT = type_of_this_NAT;
            string group_code_if_have_str = group_code_if_have;
            if (!group_code_if_have_str.empty()) {
                this->group_code_if_have = std::move(group_code_if_have_str);
            }
        }
    };
    vector<cache_of_unfinished_nat_check> list_of_unfinished_nat_checks {};
    while (detail_file.read(reinterpret_cast<char*>(temp), sizeof(personal_NAT_list))) {
        if (!(temp->time_should_do_this_NAT > today) && temp->if_have_done_this_NAT == false) {
            cache_of_unfinished_nat_check current(
                temp->time_should_do_this_NAT,
                temp->type_of_this_NAT,
                temp->code_of_group_check_if_have);
            list_of_unfinished_nat_checks.push_back(current);
        }
    }
    delete temp;
    // print or generate_file
    if (!if_generate_file) {
        // TODO: PRINT THE LIST
        cout << R"(�������п��ܳ��ֵ� <�������> ���ȿ���Ϊ2/3/5���ֱ��Ӧ ��ѧԺ���š�����ѧԺ����+רҵ���š�����ѧԺ����+רҵ����+�༶���š� �����������֪Ϥ��)" << endl;
        Sleep(500);
        cout << "���漴����ӡ " << sno << "_" << name << " ���� ���� " << today << " δ��ɵ� <������> �� ��ϸ��Ϣ��" << endl;
        Sleep(250);
        cout << endl;
        cout << sno << "_" << name << " ���� " << today << " δ��ɵ� <������> �� ��ϸ��Ϣ >> " << endl;
        cout << "===========================================================================" << endl;
        cout << "\t"
             << "Ԥ�����������" << setw(26) << "����������(����/����)" << setw(24) << "�������(������ʾNA)" << endl;
        for (auto& current : list_of_unfinished_nat_checks) {
            cout << "\t" << current.time_should_do_this_NAT;
            cout << setw(26) << (current.type_of_this_NAT == 1 ? "����" : "����");
            cout << setw(24) << current.group_code_if_have.c_str();
            cout << endl;
        }
        cout << "===========================================================================" << endl;
    } else {
        // TODO: GENERATE FILE
        const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
        const string file_path = file_root + sno + R"(_)" + name + R"(_����_)" + today.time_str() + R"(_����δ��ɵĺ�����֮ϸ��.txt)";
        const string file_name_without_root = sno + R"(_)" + name + R"(_����_)" + today.time_str() + R"(_����δ��ɵĺ�����֮ϸ��.txt)";
        fstream file(file_path, ios::out);
        if (!file.is_open()) {
            cout << "�����ļ�ʧ�ܣ������˳����� ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file << R"(�������п��ܳ��ֵ� <�������> ���ȿ���Ϊ2/3/5���ֱ��Ӧ ��ѧԺ���š�����ѧԺ����+רҵ���š�����ѧԺ����+רҵ����+�༶���š� �����������֪Ϥ��)" << endl;
        file << endl;
        file << sno << "_" << name << " ���� " << today << " δ��ɵ� <������> �� ��ϸ��Ϣ >> " << endl;
        file << "===========================================================================" << endl;
        file << "\t"
             << "Ԥ�����������" << setw(26) << "����������(����/����)" << setw(24) << "�������(������ʾNA)" << endl;
        for (auto& current : list_of_unfinished_nat_checks) {
            file << "\t" << current.time_should_do_this_NAT;
            file << setw(26) << (current.type_of_this_NAT == 1 ? "����" : "����");
            file << setw(24) << current.group_code_if_have.c_str();
            file << endl;
        }
        file << "===========================================================================" << endl;
        file.close();
        cout << "�Ѿ��ɹ����� " << file_root << " Ŀ¼���������ļ� >> " << file_name_without_root << endl;
    }
    detail_file.close();
}

bool NAT_admin::if_have_unfinished_group_nat_check(
    const string& institute,
    const string& profession,
    const string& political_class)
{
    const bool result = false;
    return result;
}

bool NAT_admin::if_person_has_collective_nat_check_by_name(const string& input_real_name, const time_manager& input_time)
{
    bool result = false;
    const string returned_sno = return_sno_by_real_name(input_real_name);
    // TODO: �����ļ��У�����ʽ���� => ����Ҫ֪���ļ������ܹ��ж��ٸ��ļ� => ��Ҫ���� �ļ��򲻿� ���ж�
    if (return_finished_num_of_nat_by_name(input_real_name) == return_num_of_nat_by_name(input_real_name)) {
        // ���е� NAT ������ˣ�result ��Ȼ�� false
        return false;
    }
    result = search_in_detail_file_if_person_has_collective_nat_check(input_real_name, returned_sno, input_time);
    return result;
}

bool NAT_admin::if_person_has_collective_nat_check_by_sno(const string& input_sno, const time_manager& input_time)
{
    bool result = false;
    const string returned_name = return_real_name_by_sno(input_sno);
    // TODO: �����ļ��У�����ʽ���� => ����Ҫ֪���ļ������ܹ��ж��ٸ��ļ� => ��Ҫ���� �ļ��򲻿� ���ж�
    if (return_finished_num_of_nat_by_sno(input_sno) == return_num_of_nat_by_sno(input_sno)) {
        // ���е� NAT ������ˣ�result ��Ȼ�� false
        return false;
    }
    result = search_in_detail_file_if_person_has_collective_nat_check(returned_name, input_sno, input_time);
    return result;
}

bool NAT_admin::if_person_has_nat_check_by_sno(const string& input_sno, const time_manager& input_time)
{
    const string returned_name = return_real_name_by_sno(input_sno);
    const string detail_file_path = generate_detail_file_path(input_sno, returned_name);
    bool result = false;
    fstream file(detail_file_path, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "Ԥ���� " << input_sno << R"(_)" << returned_name << ".dat"
             << " �ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(detail_file_path, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "�� " << input_sno << R"(_)" << returned_name << ".dat"
             << " �ļ�ʧ�ܣ������˳����� ... " << endl;
        Sleep(250);
        exit(-1);
    }
    const long long startPOS = file.tellg();
    file.seekg(0, ios::end);
    const long long endPOS = file.tellg();
    if (startPOS == endPOS) {
        // empty refactored_file, return false
        return false;
    }
    auto* cache_detail_info = new personal_NAT_list;
    while (file.read(reinterpret_cast<char*>(cache_detail_info), sizeof(personal_NAT_list))) {
        if (cache_detail_info->if_have_done_this_NAT == false && cache_detail_info->time_should_do_this_NAT == input_time) {
            // ע���ж����� => һ���� δ��ɵ� �������, �������ں���������һ�� [������ͻ]
            result = true;
            break;
        }
    }
    file.close();
    delete cache_detail_info;
    return result;
}

void NAT_admin::shell_of_NAT_admin()
{
    cout << "��ӭʹ�� [��������Ϣ] ����ƽ̨ (����Ա��) ��������ʾ���ܲ˵���" << endl;
    while (true) {
        cout << endl;
        cout << "[��������Ϣ] ����ƽ̨ (����Ա��) ���ܲ˵�" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1.�鿴 ���� δ��ɵļ��������(�ɲ�ѯָ������)" << endl; // DONE
        cout << "\t"
             << "2.�鿴 ָ��ѧ������ δ��ɵĺ�����" << endl; // DONE
        cout << "\t"
             << "3.���� �µĺ�����" << endl; // DONE
        cout << "\t"
             << "4.���� [־Ը����ļģ��] (δ����)" << endl; // Abandoned-Project
        cout << "\t"
             << "5.�鿴 ������к������ѧ������" << endl; // DONE
        cout << "\t"
             << "6.�˹�ȷ�� δ��ɵļ�������� ���״̬ (δ����)" << endl;
        cout << "\t"
             << "7.�˹�ȷ�� ָ��ѧ��δ��ɵĺ����� ���״̬ (δ����)" << endl;
        cout << "\t"
             << "8.���� ������к������ѧ������" << endl; // done
        cout << "\t"
             << "9.���� ��δ���к������ѧ������" << endl; //
        cout << "\t"
             << "10.�ٴ���ʾ ���ܲ˵�" << endl; // DONE
        cout << "\t"
             << "11.�˳��� ����ƽ̨" << endl; // DONE
        cout << "=====================================================" << endl;
        cout << "�������Ӧ��ѡ�";
        string choice;
        cin >> choice;
        if (choice == "1") {
            show_if_we_have_unfinished_group_nat_check();
        } else if (choice == "2") {
            show_if_user_has_unfinished_nat_check();
        } else if (choice == "3") {
            new_nat_arranger();
        } else if (choice == "4") {
            cout << "��Ǹ����ǰ�������ڿ����� ... ������������ ... ����������ʾ���ܲ˵� ... " << endl;
            Sleep(250);
        } else if (choice == "5") {
            show_nat_check_suggested_user(false); // �������ļ�
        } else if (choice == "6") {
            manual_confirm_finish_nat_of_group();
        } else if (choice == "7") {
            manual_confirm_finish_nat_of_user();
        } else if (choice == "8") {
            generate_file_of_suggested_nat_check_user();
        } else if (choice == "9") {
            generate_file_of_unfinished_nat_check_user();
        } else if (choice == "10") {
            cout << "�յ�������������ʾ���ܲ˵� ... " << endl;
            Sleep(250);
        } else if (choice == "11") {
            cout << "�յ����������� ��һ���˵� ... " << endl;
            Sleep(250);
            break;
        } else {
            cout << "��Ǹ����δ�����˹��ܣ�����������ʾ���ܲ˵� ... " << endl;
            Sleep(250);
        }
    }
}

NAT_admin::~NAT_admin()
{
    // do not need to delete the list
}
