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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
    // 指定集体类型
    string flag;
    while (true) {
        cout << "请先指定 <团体> 的类型" << endl;
        cout << "\t"
             << "1. 所有用户(全校)" << endl;
        cout << "\t"
             << "2. 特定院系的 所用用户" << endl;
        cout << "\t"
             << "3. 特定院系下的 特定专业的 所用用户" << endl;
        cout << "\t"
             << "4. 特定院系下的 特定专业内的 特定行政班的 所用用户" << endl;
        cout << "现在请输入对应的数字完成 类型指定 >> ";
        cin >> flag;
        if (!(flag == "1" || flag == "2" || flag == "3" || flag == "4")) {
            cout << "输入无效，即将重新指定！" << endl;
            continue;
        }
        break;
    }
    // flag has been set
    string code_of_institute; // 院校 的 代号
    string code_of_profession; // 专业 的 代号
    string code_of_political_class; // 专业 的 代号
    if (flag == "1") {
        // 全用户
    } else {
        while (true) {
            cout << "请输入指定的 院校 代号 >> ";
            cin >> code_of_institute;
            if (!group_existence_checking_manager(code_of_institute)) {
                cout << "数据库中不存在 这样的 院校代号，即将引导您重新输入 ... " << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        if (!(flag == "2")) {
            while (true) {
                cout << "请输入指定的 专业 代号 >> ";
                cin >> code_of_profession;
                if (!group_existence_checking_manager(code_of_institute, code_of_profession)) {
                    cout << "数据库中不存在 这样的 院校代号&专业代号 组合，即将引导您重新输入 专业代号 ... " << endl;
                    Sleep(250);
                    continue;
                }
                break;
            }
            if (!(flag == "3")) {
                while (true) {
                    cout << "请输入指定的 行政班 代号 >> ";
                    cin >> code_of_political_class;
                    if (!group_existence_checking_manager(code_of_institute, code_of_profession, code_of_political_class)) {
                        cout << "数据库中不存在 这样的 院校代号&专业代号&行政班代号 组合，即将引导您重新输入 行政班代号 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
            cout << "预加载 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.close();
        file.open(refactored_file_name, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "打开 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
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
                cout << current_sno << " 在 " << current_time_to_do_NAT << " 还有未完成的 核酸检测，自动放弃这个时间的安排！" << endl;
            }
        }
        file.close();
        file.open(refactored_file_name, ios::in | ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "写入 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        if (if_store) {
            // append it to the tail (of the file)
            file.seekp(0, ios::end);
            file.write(reinterpret_cast<char*>(storage_temp), sizeof(personal_NAT_list));
            // 更新 当前学号 对应 用户的 总预定 NAT 次数
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
                // 院校
                institute_code = current_group.substr(0, 2);
                if (group_code_len == 3 || group_code_len == 5) {
                    // 院校 + 专业
                    profession_code = current_group.substr(2, 1);
                    if (group_code_len == 5) {
                        // 院校 + 专业 + 班级
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
            cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
                cout << "预加载 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
                Sleep(250);
                exit(-1);
            }
            file.close();
            file.open(file_path, ios::in | ios::binary);
            if (!file.is_open()) {
                cout << "打开 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
                Sleep(250);
                exit(-1);
            }
            // 判断安排的时间有没有撞车
            auto* temp_personal_nat_info = new personal_NAT_list;
            auto* temp_time_collapse_judger = new personal_NAT_list;
            bool if_time_collision_occured = false;
            while (file.read(reinterpret_cast<char*>(temp_time_collapse_judger), sizeof(personal_NAT_list))) {
                if (temp_time_collapse_judger->time_should_do_this_NAT == current_time_to_do_NAT && temp_time_collapse_judger->type_of_this_NAT == 0 && temp_time_collapse_judger->if_have_done_this_NAT == false) {
                    // 这里不用判别 组织类型 => 因为只要有一个组织完成了，结果就可以直接在24h内反复使用
                    // 所以 => 同一个学生，一天内最多只安排一个组织
                    if_time_collision_occured = true;
                    break;
                }
            }
            file.close();
            delete temp_time_collapse_judger;
            file.open(file_path, ios::in | ios::out | ios::binary);
            if (!file.is_open()) {
                cout << "打开 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
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
    // 安排新的核酸检测
    int type = 0;
    cout << "请注意！为了在保证科学、准确的前提下，确保不浪费广大师生的时间，每个用户一天最多被安排一次核酸检测！" << endl;
    Sleep(800);
    while (true) {
        cout << "请输入特定数字，以指定将要安排的核酸检测类型 (1：个人检测，2：集体检测) >> ";
        string flag;
        cin >> flag;
        if (flag == "1") {
            type = 1;
        } else if (flag == "2") {
            type = 2;
        } else {
            cout << "输入无效！即将重新引导输入 ... " << endl;
            continue;
        }
        break;
    }
    if (type == 1) {
        // 个人检测
        personal_nat_arranger();
    } else if (type == 2) {
        // 集体检测 => 非常复杂！！！！！
        collective_nat_arranger();
    }
}

void NAT_admin::personal_nat_arranger()
{
    // 个人检测
    /// ATTENTION:
    /// 应该把 学号 作为 输入，因为 可能重名，但是不可能重学号
    // TODO: 添加 （个人是否已经有集体核酸安排） 判断模块 => done
    // TODO: 如果给个人 安排的 时间 已经被 安排过，自动忽略，同时加以提示，但是不会终止程序运行
    vector<map<string, time_manager>> list_of_name_and_time;
    cout << R"(您想要为 几个人 安排 核酸检测？请指定 >> )";
    int num;
    cin >> num;
    for (int i = 1; i <= num; ++i) {
        string stop_flag;
        cout << "是否提前终止输入？输入Y/y以终止，输入其他非空内容则继续 >> ";
        cin >> stop_flag;
        if (stop_flag == "y" || stop_flag == "Y") {
            cout << "收到，提前终止输入" << endl;
            break;
        }
        const int remained_num = num - i + 1;
        cout << "即将输入第" << i << "条数据 (还剩" << remained_num << "条数据待输入) ... " << endl;
        string temp_sno;
        string returned_name;
        int temp_year, temp_month, temp_day;
        time_manager glb_temp_time;
        while (true) {
            // name_input
            cout << "请输入 被安排核酸检测的 学号 (系统将自动匹配唯一姓名) >> ";
            cin >> temp_sno;
            if (!check_user_existence_by_sno(temp_sno)) {
                cout << "数据库中 没有学号为 " << temp_sno << " 的学生，请重新输入！" << endl;
                Sleep(200);
                continue;
            }
            returned_name = return_real_name_by_sno(temp_sno);
            break;
        }
        while (true) {
            // time_input
            cout << "请输入 为 " << temp_sno << "_" << returned_name << " 安排的 核酸检测进行时间" << endl;
            cout << "(输入格式为：年、月、日，用空格分隔，输入完成后回车换行) >> ";
            cin >> temp_year >> temp_month >> temp_day;
            time_manager temp_time(temp_year, temp_month, temp_day);
            if (!temp_time.if_date_valid(&temp_time)) {
                cout << "日期无效，请重新输入！" << endl;
                Sleep(200);
                continue;
            }
            glb_temp_time = temp_time;
            break;
        }
        // judger
        if (if_person_has_collective_nat_check_by_sno(temp_sno, glb_temp_time)) {
            cout << "检测到 " << temp_sno << "_" << returned_name << " 当天有 预定的 集体核算检测活动，自动报废此条记录！" << endl;
            cout << "即将重新回到 录入提示 界面 ..." << endl;
            Sleep(250);
            --i; // 废弃本次录入，直接进入下一步
            continue;
        }
        // data confirm
        cout << "请确认 您刚刚输入的信息 ：" << endl;
        cout << "\t"
             << "姓名：" << returned_name << endl;
        cout << "\t"
             << "学号：" << temp_sno << endl;
        cout << "\t"
             << "安排的日期：" << glb_temp_time << endl;
        cout << "输入 Y/y 确认录入，否则请输入其他非空内容 >> ";
        string flag;
        cin >> flag;
        if (!(flag == "Y" || flag == "y")) {
            cout << "废弃本次录入，即将重新回到 录入提示 界面 ... " << endl;
            Sleep(250);
            --i; // 废弃本次录入，直接进入下一步
            continue;
        }
        map<string, time_manager> one_name_and_time;
        one_name_and_time[temp_sno] = glb_temp_time;
        list_of_name_and_time.push_back(one_name_and_time);
        cout << "已成功录入第 " << i << " 条数据！" << endl;
    }
    // store the vector
    arrange_nat_for_input_users(list_of_name_and_time);
    cout << "已成功为 输入的用户(们) 安排了 相应的 核酸检测(并自动回避了时间冲突)！即将回到 上一级菜单 ... " << endl;
    Sleep(250);
    // end
}

void NAT_admin::collective_nat_arranger()
{
    // 集体检测
    vector<map<string, time_manager>> list_of_groups_and_time;
    cout << R"(为了减少不必要的录入错误，一次只能为一个团体安排核酸检测！ )" << endl;
    Sleep(250);
    constexpr int num = 1;
    // cin >> num;
    for (int i = 1; i <= num; ++i) {
        string stop_flag;
        cout << "是否提前终止输入？输入Y/y以终止，输入其他非空内容则继续 >> ";
        cin >> stop_flag;
        if (stop_flag == "y" || stop_flag == "Y") {
            cout << "收到，提前终止输入" << endl;
            break;
        }
        const int remained_num = num - i + 1;
        cout << "即将输入第" << i << "条数据 (还剩" << remained_num << "条数据待输入) ... " << endl;
        // 集体类型
        string final_group_code = set_group_code();
        // end of entering group, start enter time
        time_manager scheduled_time;
        int temp_year, temp_month, temp_day;
        cout << "接下来将会为 团体 安排 进行核酸检测的 时间，";
        cout << "但是请注意，系统暂不支持检测选定时间、指定团体中 是否存在此时间有未参加的核酸检测的 个人！功能简陋，还请谅解！" << endl;
        while (true) {
            cout << "现在请输入 " << final_group_code << " 这一团体 应该进行 核酸检测的时间(年月日，分别用空格隔开，随后回车即可) >> ";
            cin >> temp_year >> temp_month >> temp_day;
            const auto* temp_time = new time_manager(temp_year, temp_month, temp_day);
            if (!time_manager::if_date_valid(temp_time)) {
                // if_date_valid is a static function, so you could simply enter it in the upper way
                cout << "输入的日期不合法！即将引导您重新输入日期 ... " << endl;
                delete temp_time;
                Sleep(250);
                continue;
            }
            scheduled_time = *temp_time;
            break;
        }
        // data confirm
        cout << "请确认 您刚刚输入的信息 ：" << endl;
        cout << "\t"
             << "团体代号：" << final_group_code << endl;
        cout << "\t"
             << "安排的日期：" << scheduled_time << endl;
        cout << "输入 Y/y 确认录入，否则请输入其他非空内容 >> ";
        string flag;
        cin >> flag;
        if (!(flag == "Y" || flag == "y")) {
            cout << "废弃本次录入，即将重新回到 录入提示 界面 ... " << endl;
            Sleep(250);
            --i; // 废弃本次录入，直接进入下一步
            continue;
        }
        map<string, time_manager> one_group_and_time;
        one_group_and_time[final_group_code] = scheduled_time;
        list_of_groups_and_time.push_back(one_group_and_time);
        cout << "已成功录入第 " << i << " 条数据！" << endl;
    }
    arrange_nat_for_input_groups(list_of_groups_and_time);
    cout << "已成功为 指定的团体(们) 安排了 相应的 核酸检测 (并自动回避了时间冲突)！即将回到 上一级菜单 ... " << endl;
    Sleep(250);
}

void NAT_admin::show_if_user_has_unfinished_nat_check()
{
    // 检测凭据应该是学号
    string temp_sno;
    string temp_mode;
    string index_type = "sno";
    cout << "提供两种搜索模式 => 1. 姓名精确搜索 (暂不开放) , 2. 学号精确搜索; 默认使用学号精确搜索" << endl;
    cout << "需要注意的是，重名可能存在，但是不可能存在相同的学号" << endl;
    cout << "现在请问您是否需要更改 搜索模式呢？如有需要则请输入Y/y，否则直接输入任意非空内容后回车 >> ";
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
    // TODO: 对所有的集体进行查询
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
            cout << "预加载 personal_NAT_info 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        detail_file.close();
        detail_file.open(refactored_filename, ios::in | ios::binary);
        if (!detail_file.is_open()) {
            cout << "打开 personal_NAT_info 失败！即将退出程序 ... " << endl;
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
    cout << "目前 " << (if_any_group_has_unfinished_nat_check ? "有" : "无") << " 未完成的 集体核酸检测" << endl;
    if (if_any_group_has_unfinished_nat_check) {
        // TODO: 提示 是否需要 列出 所有未进行的 集体核酸检测
        // 比较复杂，暂时不做
    }
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_admin::if_sp_group_has_nat_check()
{
    string final_group_code = set_group_code(); // 这个直接用就可以. 必定存在
    unsigned long long len = final_group_code.length();
    // 拆分得到有效信息 => [冗余模块]
    {
        // 冗余模块
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    {
        // 冗余
        bool judger = false;
        bool if_institute = true;
        bool if_profession = true;
        bool if_political_class = true;
    }
    bool if_sp_group_has_nat_check = false;
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        // 直接判断是否 是 当前的 组别，是的话，打开文件进行检查
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
                cout << "预加载 personal_NAT_info 失败！即将退出程序 ... " << endl;
                Sleep(250);
                exit(-1);
            }
            detail_file.close();
            detail_file.open(refactored_filename, ios::in | ios::binary);
            if (!detail_file.is_open()) {
                cout << "打开 personal_NAT_info 失败！即将退出程序 ... " << endl;
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
    cout << "本组 " << (if_sp_group_has_nat_check ? "有" : "无") << " 未完成的 集体核酸检测！" << endl;
    if (if_sp_group_has_nat_check) {
        // TODO: 提示 是否需要 详细的列出这一组 未进行的 集体核酸检测 的 时间
        // 比较复杂，暂时不做
    }
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_admin::show_if_we_have_unfinished_group_nat_check()
{
    cout << "是否需要查询 特定的团体 (输入Y/y=>是，输入其他非空内容=>否) >> ";
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
    cout << "出于时间问题，本功能暂时不予开发，敬请谅解！" << endl;
}

void NAT_admin::manual_confirm_finish_nat_of_group()
{
    cout << "出于时间问题，本功能暂时不予开发，敬请谅解！" << endl;
}

void NAT_admin::show_nat_check_suggested_user(const bool& if_generate_file)
{
    // 存储
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
    vector<judger> part_1 {}; // 第一部分 => 强直接建议 => 他们自己就是 经过 高风险区
    vector<judger> part_2 {}; // 第二部分 => 弱直接建议 => 他们自己就是 经过 中风险区
    vector<judger> part_3 {}; // 第三部分 => 强间接建议 => 与 第一类 同宿舍，但不是第一类
    vector<judger> part_4 {}; // 第四部分 => 弱间接建议 => 与 第二类 同宿舍，但不是第二类
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
            // 这里如果 同时经过 中高风险区 => 按照只经过 高风险区 处理
        } else {
            bool if_this_person_is_in_part_3 = false;
            for (auto& person : part_1) {
                if (dorm_num == person.dorm_num) {
                    // 第三类
                    judger current(sno, name, dorm_num);
                    part_3.push_back(current);
                    if_this_person_is_in_part_3 = true;
                }
            }
            if (!if_this_person_is_in_part_3) {
                for (auto& person : part_2) {
                    if (dorm_num == person.dorm_num) {
                        // 第四类
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
        cout << "请先阅读声明：" << endl;
        cout << R"(一共有4种级别的建议，分别如下：)" << endl;
        cout << R"(第1级 => 近期途径高风险区)" << endl;
        cout << R"(第2级 => 近期途径中风险区，但未途径高风险区)" << endl;
        cout << R"(第3级 => 未途径 中高风险区，但与近期途径 高风险区 的学生同宿舍)" << endl;
        cout << R"(第4级 => 未途径 中高风险区，但与近期途径 中风险区 的学生同宿舍)" << endl;
        cout << endl;
        Sleep(2000);
        cout << "现在开始打印 建议名单 ：" << endl;
        cout << endl;
        cout << "第 1 级 建议名单" << endl;
        cout << "=====================================================================" << endl;
        if (part_1.empty()) {
            cout << "\t"
                 << "无 （第1级建议名单 暂时为空）" << endl;
        } else {
            cout << "\t"
                 << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            cout << endl;
            for (auto& part : part_1) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "第 2 级 建议名单" << endl;
        cout << "=====================================================================" << endl;
        if (part_2.empty()) {
            cout << "\t"
                 << "无 （第2级建议名单 暂时为空）" << endl;
        } else {
            cout << "\t"
                 << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            cout << endl;
            for (auto& part : part_2) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "第 3 级 建议名单" << endl;
        cout << "=====================================================================" << endl;
        if (part_3.empty()) {
            cout << "\t"
                 << "无 （第3级建议名单 暂时为空）" << endl;
        } else {
            cout << "\t"
                 << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            cout << endl;
            for (auto& part : part_3) {
                cout << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        cout << "=====================================================================" << endl;
        cout << endl;
        cout << "第 4 级 建议名单" << endl;
        cout << "=====================================================================" << endl;
        if (part_4.empty()) {
            cout << "\t"
                 << "无 （第4级建议名单 暂时为空）" << endl;
        } else {
            cout << "\t"
                 << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
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
            cout << "打开 users_suggested_to_do_NAT.txt 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        // contents:
        generated_file << "请先阅读声明：" << endl;
        generated_file << R"(一共有4种级别的建议，分别如下：)" << endl;
        generated_file << R"(第1级 => 近期途径高风险区)" << endl;
        generated_file << R"(第2级 => 近期途径中风险区，但未途径高风险区)" << endl;
        generated_file << R"(第3级 => 未途径 中高风险区，但与近期途径 高风险区 的学生同宿舍)" << endl;
        generated_file << R"(第4级 => 未途径 中高风险区，但与近期途径 中风险区 的学生同宿舍)" << endl;
        generated_file << endl;
        //
        generated_file << endl;
        generated_file << "第1级 建议名单" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_1.empty()) {
            generated_file << "\t"
                           << "无 （第1级建议名单 暂时为空）" << endl;
        } else {
            generated_file << "\t"
                           << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            generated_file << endl;
            for (auto& part : part_1) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "第2级 建议名单" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_2.empty()) {
            generated_file << "\t"
                           << "无 （第2级建议名单 暂时为空）" << endl;
        } else {
            generated_file << "\t"
                           << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            generated_file << endl;
            for (auto& part : part_2) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "第3级 建议名单" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_3.empty()) {
            generated_file << "\t"
                           << "无 （第3级建议名单 暂时为空）" << endl;
        } else {
            generated_file << "\t"
                           << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
            generated_file << endl;
            for (auto& part : part_3) {
                generated_file << "\t" << part.name << setw(18) << part.sno << setw(18) << part.dorm_num << endl;
            }
        }
        generated_file << "=====================================================================" << endl;
        generated_file << endl;
        generated_file << "第4级 建议名单" << endl;
        generated_file << "=====================================================================" << endl;
        if (part_4.empty()) {
            generated_file << "\t"
                           << "无 （第4级建议名单 暂时为空）" << endl;
        } else {
            generated_file << "\t"
                           << "姓名" << setw(18) << "学号" << setw(18) << "宿舍号" << endl;
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
    // 这里，只会生成 截至 当天 还有未完成的核酸检测 的 用户的 名单
    time_manager today;
    const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
    const string file_path = file_root + "list_of_users_with_unfinished_nat_check.txt";
    cout << "请注意，只生成"
         << R"(“未完成所有应该在今天前完成的核酸检测”)"
         << "的用户名单！" << endl;
    cout << "例如 >> "
         << "今天的日期是 " << today << ", 若用户只有 " << ++today << " 之后应完成而未完成的核酸检测，则不会再这个名单上！" << endl;
    --today; // 必须有
    Sleep(750);
    cout << "现在开始读取数据并生成文件 ... " << endl;
    Sleep(250);
    fstream index(NAT_file_location, ios::in | ios::binary);
    if (!index.is_open()) {
        cout << "打开 NAT_list 失败！即将退出程序 ... " << endl;
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
            cout << "打开 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
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
        cout << "没有"
             << "未完成 " << today << " 前(含) 所有 <应完成的核酸检测> 的 {用户}，跳过生成名单 " << endl;
        Sleep(250);
        return;
    }
    fstream file(file_path, ios::out);
    if (!file.is_open()) {
        cout << "创建 list_of_users_with_unfinished_nat_check.txt 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // output
    file << "未完成 " << today << " 前(含) 所有 <应完成的核酸检测> 的 {用户名单} >> " << endl;
    file << endl;
    file << "================================================================" << endl;
    file << "\t"
         << "学号" << setw(18) << "姓名" << endl;
    for (auto& customized_pair : customized_list) {
        file << "\t" << customized_pair.sno.c_str() << setw(18) << customized_pair.name.c_str() << endl;
    }
    file << "================================================================" << endl;
    file.close();
    cout << "文件 list_of_users_with_unfinished_nat_check.txt 已在 " << file_root << " 中生成！" << endl;
    Sleep(250);
}

void NAT_admin::generate_input_personal_detail_folder(const string& input)
{
    if (_access(input.c_str(), 0) == -1) {
        if (_mkdir(input.c_str()) == 0) {
            // cout << "创建 NAT_detail_file_root 文件夹成功" << endl;
        } else {
            cout << "创建 personal_detail_file_root 文件夹失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
    }
}

// 下面这个函数被弃用了 => 原先的文件结构不合理
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
            cout << "打开 personal_NAT_info 中的 相关文件 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read(reinterpret_cast<char*>(cache_detail_info), sizeof(personal_NAT_list));
        if (cache_detail_info->if_have_done_this_NAT == false && cache_detail_info->type_of_this_NAT == 0 && cache_detail_info->time_should_do_this_NAT == input_time) {
            // 注意判断条件 => 一定是 未完成的 集体核酸, 并且日期和输入日期一致 [产生冲突]
            result = true;
            break;
        }
    }
    delete cache_detail_info;
    return result;
}

// 启用下面这个函数 => 针对重构后的 文件结构
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
        cout << "预加载 " << sno << R"(_)" << name << ".dat"
             << " 文件失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(refactored_filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 " << sno << R"(_)" << name << ".dat"
             << " 文件失败！即将退出程序 ... " << endl;
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
            // 注意判断条件 => 一定是 未完成的 集体核酸, 并且日期和输入日期一致 [产生冲突]
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
    cout << "出于时间问题，本功能暂时不予开发，敬请谅解！" << endl;
}

void NAT_admin::if_user_has_unfinished_nat_check_by_sno()
{
    string temp_sno;
    string temp_name;
    while (true) {
        cout << R"(现在请输入欲查询的 学号 >> )";
        cin >> temp_sno;
        if (!check_user_existence_by_sno(temp_sno)) {
            cout << "数据库中不存在您刚刚输入的学号，即将引导您重新输入 ... " << endl;
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
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
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
    cout << temp_sno << "_" << temp_name << (if_have_unfinished_nat_check ? " 有" : " 无") << " 未完成的 核酸检测！" << endl;
    if (if_have_unfinished_nat_check) {
        cout << "是否还需要显示其 未完成的核酸检测 的 应完成时间和具体类型？输入Y/y则显示，输入其他非空内容以跳过 >> ";
        string temp;
        cin >> temp;
        if (temp == "y" || temp == "Y") {
            show_sp_user_unfinished_nat_check_details(temp_sno, temp_name, false);
            cout << "显示完毕！是否还需要 将刚才显示的列表 生成为 文件？输入Y/y则生成，输入其他非空内容以跳过 >> ";
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
    // 这里只显示 截至今天 没有完成的
    time_manager today;
    string detail_file_path = generate_detail_file_path(sno, name);
    fstream detail_file(detail_file_path, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "预加载 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(detail_file_path, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "打开 personal_NAT_info_file 失败！即将退出程序 ... " << endl;
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
        cout << R"(接下来有可能出现的 <团体代号> 长度可能为2/3/5，分别对应 “学院代号”、“学院代号+专业代号”、“学院代号+专业代号+班级代号” 三种情况，请知悉！)" << endl;
        Sleep(500);
        cout << "下面即将打印 " << sno << "_" << name << " 所有 截至 " << today << " 未完成的 <核酸检测> 的 详细信息！" << endl;
        Sleep(250);
        cout << endl;
        cout << sno << "_" << name << " 截至 " << today << " 未完成的 <核酸检测> 的 详细信息 >> " << endl;
        cout << "===========================================================================" << endl;
        cout << "\t"
             << "预定的完成日期" << setw(26) << "核酸检测类型(团体/个人)" << setw(24) << "团体代号(无则显示NA)" << endl;
        for (auto& current : list_of_unfinished_nat_checks) {
            cout << "\t" << current.time_should_do_this_NAT;
            cout << setw(26) << (current.type_of_this_NAT == 1 ? "个人" : "团体");
            cout << setw(24) << current.group_code_if_have.c_str();
            cout << endl;
        }
        cout << "===========================================================================" << endl;
    } else {
        // TODO: GENERATE FILE
        const string file_root = R"(C:\Users\edwar\Desktop\cpp_final_task\)";
        const string file_path = file_root + sno + R"(_)" + name + R"(_截至_)" + today.time_str() + R"(_所有未完成的核酸检测之细节.txt)";
        const string file_name_without_root = sno + R"(_)" + name + R"(_截至_)" + today.time_str() + R"(_所有未完成的核酸检测之细节.txt)";
        fstream file(file_path, ios::out);
        if (!file.is_open()) {
            cout << "创建文件失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file << R"(接下来有可能出现的 <团体代号> 长度可能为2/3/5，分别对应 “学院代号”、“学院代号+专业代号”、“学院代号+专业代号+班级代号” 三种情况，请知悉！)" << endl;
        file << endl;
        file << sno << "_" << name << " 截至 " << today << " 未完成的 <核酸检测> 的 详细信息 >> " << endl;
        file << "===========================================================================" << endl;
        file << "\t"
             << "预定的完成日期" << setw(26) << "核酸检测类型(团体/个人)" << setw(24) << "团体代号(无则显示NA)" << endl;
        for (auto& current : list_of_unfinished_nat_checks) {
            file << "\t" << current.time_should_do_this_NAT;
            file << setw(26) << (current.type_of_this_NAT == 1 ? "个人" : "团体");
            file << setw(24) << current.group_code_if_have.c_str();
            file << endl;
        }
        file << "===========================================================================" << endl;
        file.close();
        cout << "已经成功的在 " << file_root << " 目录下生成了文件 >> " << file_name_without_root << endl;
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
    // TODO: 进入文件夹，遍历式搜索 => 这需要知道文件夹中总共有多少个文件 => 不要依赖 文件打不开 来判断
    if (return_finished_num_of_nat_by_name(input_real_name) == return_num_of_nat_by_name(input_real_name)) {
        // 所有的 NAT 都完成了，result 自然是 false
        return false;
    }
    result = search_in_detail_file_if_person_has_collective_nat_check(input_real_name, returned_sno, input_time);
    return result;
}

bool NAT_admin::if_person_has_collective_nat_check_by_sno(const string& input_sno, const time_manager& input_time)
{
    bool result = false;
    const string returned_name = return_real_name_by_sno(input_sno);
    // TODO: 进入文件夹，遍历式搜索 => 这需要知道文件夹中总共有多少个文件 => 不要依赖 文件打不开 来判断
    if (return_finished_num_of_nat_by_sno(input_sno) == return_num_of_nat_by_sno(input_sno)) {
        // 所有的 NAT 都完成了，result 自然是 false
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
        cout << "预加载 " << input_sno << R"(_)" << returned_name << ".dat"
             << " 文件失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(detail_file_path, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 " << input_sno << R"(_)" << returned_name << ".dat"
             << " 文件失败！即将退出程序 ... " << endl;
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
            // 注意判断条件 => 一定是 未完成的 集体核酸, 并且日期和输入日期一致 [产生冲突]
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
    cout << "欢迎使用 [核酸检测信息] 管理平台 (管理员端) ！下面显示功能菜单：" << endl;
    while (true) {
        cout << endl;
        cout << "[核酸检测信息] 管理平台 (管理员端) 功能菜单" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1.查看 有无 未完成的集体核酸检测(可查询指定集体)" << endl; // DONE
        cout << "\t"
             << "2.查看 指定学生有无 未完成的核酸检测" << endl; // DONE
        cout << "\t"
             << "3.发布 新的核酸检测" << endl; // DONE
        cout << "\t"
             << "4.进入 [志愿者招募模块] (未开发)" << endl; // Abandoned-Project
        cout << "\t"
             << "5.查看 建议进行核酸检测的学生名单" << endl; // DONE
        cout << "\t"
             << "6.人工确认 未完成的集体核酸检测 完成状态 (未开发)" << endl;
        cout << "\t"
             << "7.人工确认 指定学生未完成的核酸检测 完成状态 (未开发)" << endl;
        cout << "\t"
             << "8.生成 建议进行核酸检测的学生名单" << endl; // done
        cout << "\t"
             << "9.生成 有未进行核酸检测的学生名单" << endl; //
        cout << "\t"
             << "10.再次显示 功能菜单" << endl; // DONE
        cout << "\t"
             << "11.退出该 管理平台" << endl; // DONE
        cout << "=====================================================" << endl;
        cout << "请输入对应的选项：";
        string choice;
        cin >> choice;
        if (choice == "1") {
            show_if_we_have_unfinished_group_nat_check();
        } else if (choice == "2") {
            show_if_user_has_unfinished_nat_check();
        } else if (choice == "3") {
            new_nat_arranger();
        } else if (choice == "4") {
            cout << "抱歉，当前功能正在开发中 ... 后续将会完善 ... 即将重新显示功能菜单 ... " << endl;
            Sleep(250);
        } else if (choice == "5") {
            show_nat_check_suggested_user(false); // 不生成文件
        } else if (choice == "6") {
            manual_confirm_finish_nat_of_group();
        } else if (choice == "7") {
            manual_confirm_finish_nat_of_user();
        } else if (choice == "8") {
            generate_file_of_suggested_nat_check_user();
        } else if (choice == "9") {
            generate_file_of_unfinished_nat_check_user();
        } else if (choice == "10") {
            cout << "收到！即将重新显示功能菜单 ... " << endl;
            Sleep(250);
        } else if (choice == "11") {
            cout << "收到！即将返回 上一级菜单 ... " << endl;
            Sleep(250);
            break;
        } else {
            cout << "抱歉，尚未开发此功能！即将重新显示功能菜单 ... " << endl;
            Sleep(250);
        }
    }
}

NAT_admin::~NAT_admin()
{
    // do not need to delete the list
}
