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
        cout << "预加载 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "打开 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
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
    // TODO: 给 list_of_unfinished_nat_checks_former_than_today 去重 => 没有必要，但是加上保险！
    auto& ref = list_of_unfinished_nat_checks_former_than_today;
    // sort(ref.begin(), ref.end());
    ref.erase(unique(ref.begin(), ref.end()), ref.end());
}

void NAT_user::fill_list_of_all_unfinished_nat_checks()
{
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "预加载 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "打开 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
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
    // TODO: 给 list_of_unfinished_nat_checks_former_than_today 去重 => 没有必要
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
            cout << "创建" << folder_path << " 目录失败！即将退出程序 ... " << endl;
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
            cout << "创建" << folder_path << " 目录失败！即将退出程序 ... " << endl;
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
        cout << "预加载 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    detail_file.open(current_detail_file_name_, ios::in | ios::binary);
    if (!detail_file.is_open()) {
        cout << "打开 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
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
    // 强制 => 要求你 确认完成 之前未完成的
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
    // 暂时冗余
}

void NAT_user::confirm_unfinished_tasks_in_detail_file(const vector<time_manager>& confirm_index_list) const
{
    time_manager today;
    // TODO: use confirm_index to confirm in detail_file
    auto* checker = new personal_NAT_list;
    fstream detail_file(current_detail_file_name_, ios::app | ios::binary);
    if (!detail_file.is_open()) {
        cout << "预加载 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    detail_file.close();
    for (auto& confirm_index : confirm_index_list) {
        detail_file.open(current_detail_file_name_, ios::in | ios::binary);
        if (!detail_file.is_open()) {
            cout << "打开 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        fstream temp_detail_file(temp_current_detail_file_name_, ios::out | ios::binary);
        if (!temp_detail_file.is_open()) {
            cout << "写入 personal_NAT_list 失败！ 即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (detail_file.read(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list))) {
            if (checker->if_have_done_this_NAT == false && checker->time_should_do_this_NAT == confirm_index) {
                checker->if_have_done_this_NAT = true; // 设置为已完成
                checker->time_of_finishing_this_NAT = today;
            }
            if (!checker->if_have_done_this_NAT) {
                // 只会在 personal_list.dat 中，保存 未完成的核酸 的 相关数据
                temp_detail_file.write(reinterpret_cast<char*>(checker), sizeof(personal_NAT_list)); // 重写
            }
        }
        detail_file.close();
        temp_detail_file.close();
        remove(current_detail_file_name_.c_str());
        // bug => _OldFileName & _NewFileName 反了 -> fixed
        rename(temp_current_detail_file_name_.c_str(), current_detail_file_name_.c_str());
    }
    delete checker;
}

void NAT_user::show_unfinished_tasks_former_than_today() const
{
    //
    if (!list_of_unfinished_nat_checks_former_than_today.empty()) {
        cout << R"(接下来有可能出现的 <团体代号> 长度可能为2/3/5，分别对应 “学院代号”、“学院代号+专业代号”、“学院代号+专业代号+班级代号” 三种情况，请知悉！)" << endl;
        Sleep(500);
        cout << "下面即将打印 您"
             << " 所有 截至 " << today_ << " 未完成的 <核酸检测> 的 详细信息！" << endl;
        Sleep(250);
        cout << endl;
        cout << sno_ << "_" << name_ << " 截至 " << today_ << " 未完成的 <核酸检测> 的 详细信息 >> " << endl;
        cout << "======================================================================================" << endl;
        cout << "\t"
             << "序号" << setw(20) << "预定的完成日期" << setw(26) << "核酸检测类型(团体/个人)" << setw(24) << "团体代号(无则显示NA)" << endl;
        int num = 1;
        for (auto& current : list_of_unfinished_nat_checks_former_than_today) {
            cout << "\t"
                 << num << ".";
            cout << setw(16) << current.time_should_do_this_NAT;
            cout << setw(22) << (current.type_of_this_NAT == 1 ? "个人" : "团体");
            cout << setw(20) << (current.group_code_if_have.empty() ? "NA" : current.group_code_if_have.c_str());
            cout << endl;
            ++num;
        }
        cout << "======================================================================================" << endl;
    } else {
        cout << "恭喜您，已完成了 所有 <应于今天前完成的 核酸检测> ！" << endl;
        Sleep(250);
    }
}

void NAT_user::confirm_unfinished_tasks_former_than_today(const bool& if_multi_confirm)
{
    vector<time_manager> remove_and_confirm_index_list {};
    vector<int> list_of_index_num {};
    bool if_multi_confirm_func = if_multi_confirm;
    if (list_of_unfinished_nat_checks_former_than_today.empty()) {
        cout << "没有 <应在今天前(含)完成 而未完成的 核酸检测>！即将回到功能菜单 ..." << endl;
        Sleep(250);
        return;
    }
    if (!if_multi_confirm_func) {
        while (true) {
            cout << "请先选择确认模式 => 输入M/m：批量确认(全部确认) || 输入S/s：只确认一次 >> ";
            string mode_flag;
            cin >> mode_flag;
            if (mode_flag == "M" || mode_flag == "m") {
                if_multi_confirm_func = true;
            } else if (mode_flag == "S" || mode_flag == "s") {
                if_multi_confirm_func = false;
            } else {
                cout << "输入无效，即将重新指引您输入！" << endl;
                Sleep(150);
                continue;
            }
            break;
        }
    }
    cout << "首先，不妨列出 <应在今天前(含)完成 而未完成的 核酸检测> 列表 >> " << endl
         << endl;
    show_unfinished_tasks_former_than_today();
    cout << endl;
    if (!if_multi_confirm_func) {
        int index_num;
        while (true) {
            cout << "现在，请输入您要确认的 核酸检测 在 刚刚的列表中的 序号" << endl;
            cin >> index_num;
            if (index_num < 1 || index_num > list_of_unfinished_nat_checks_former_than_today.size()) {
                cout << "输入的数字无效，即将引导您重新输入 序号 ... " << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        // operate
        const time_manager removed_time = list_of_unfinished_nat_checks_former_than_today[index_num - 1].time_should_do_this_NAT;
        remove_and_confirm_index_list.push_back(removed_time);
        update_num_of_finished_nat_of_input_sno(sno_); // NAT_list_file 中的 已完成核酸数 更新
        confirm_unfinished_tasks_in_detail_file(remove_and_confirm_index_list);
    } else {
        bool all_confirm = false;
        bool partial_confirm_as_finished = false;
        constexpr bool partial_confirm_as_unfinished = false;
        while (true) {
            cout << "请根据刚刚的列表，选择合适的 <批量操作模式> :" << endl;
            cout << "\t"
                 << "A/a => 全部确认为{已完成}" << endl;
            cout << "\t"
                 << "B/b => 将一部分手动确定为{已完成}，其他全部自动确定为{未完成}" << endl;
            cout << "\t"
                 << "C/c => 将一部分手动确定为{未完成}，其他全部自动确定为{已完成} <暂不支持>" << endl;
            cout << "现在请输入您的选择 >> ";
            string mode_flag;
            cin >> mode_flag;
            if (mode_flag == "A" || mode_flag == "a") {
                all_confirm = true;
            } else if (mode_flag == "B" || mode_flag == "b") {
                partial_confirm_as_finished = true;
            } else if (mode_flag == "C" || mode_flag == "c") {
                cout << "抱歉，出于时间缘故，本 <操作模式> 暂不支持！即将引导您重新选择！" << endl;
                Sleep(250);
                continue;
            } else {
                cout << "输入无效，即将指引您重新输入！" << endl;
                Sleep(250);
                continue;
            }
            break;
        }
        if (all_confirm) {
            // TODO: 全部确认为{已完成}
        }
        if (partial_confirm_as_finished) {
            // TODO: 将一部分手动确定为{已完成}，其他全部自动确定为{未完成}
            cout << "请输入想要确定为{已完成}的序号(无效输入将会被自动忽略)[用空格分割，输入完成后，再输入任意负数即可]: " << endl;
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
            cout << "输入完成！" << endl;
        }
        if (partial_confirm_as_unfinished) {
            // TODO: 将一部分手动确定为{未完成}，其他全部自动确定为{已完成}
            // 暂时不开放这个模式
        }
        // TODO: branch_of_operation
        if (list_of_index_num.empty()) {
            // 这个走的是 “全部确定为已完成”
            for (const auto& element : list_of_unfinished_nat_checks_former_than_today) {
                time_manager removed_time = element.time_should_do_this_NAT;
                remove_and_confirm_index_list.push_back(removed_time);
            }
        } else {
            // 这个走的是 “部分确定为已完成”
            for (const auto& index_num : list_of_index_num) {
                time_manager removed_time = list_of_unfinished_nat_checks_former_than_today[index_num - 1].time_should_do_this_NAT;
                remove_and_confirm_index_list.push_back(removed_time);
            }
        }
        // 给时间去重
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
    // 禁用
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
    // current_detail_file_name_ = generate_detail_file_path(sno_, name_); => 性能开销略大
    set_detail_file_path();
    set_temp_detail_file_path();
    check_if_have_unfinished_task_no_later_than_today();
    if (if_use_as_plug_only) {
        // 只是用作 “接口” ，那么此时 构造函数就应该结束了
        return;
    }
    fill_list_of_unfinished_nat_checks_former_than_today(); // pre_fill
    fill_list_of_all_unfinished_nat_checks(); // pre_fill
    if (if_have_unfinished_task_no_later_than_today_) {
        cout << "由于检测到您有 <应在今天前(含)完成 而未完成的 核酸检测>，故将自动引导您 批量人工确认其是否完成！" << endl;
        confirm_unfinished_tasks_former_than_today(true);
    }
}

void NAT_user::shell_of_user_NAT_check()
{
    system("cls");
    cout << endl;
    cout << "欢迎使用 [核酸检测信息] 管理平台 (用户端) ！下面显示功能菜单：" << endl;
    while (true) {
        cout << endl;
        cout << "[核酸检测信息] 管理平台 (用户端) >>> 功能菜单：" << endl;
        cout << "=====================================================" << endl;
        cout << "\t"
             << "1.查看 <应在今天前(含)完成 而未完成的 核酸检测> 列表" << endl;
        cout << "\t"
             << "2.人工确认 <应在今天前(含)完成 而未完成的 核酸检测> 是否完成 (可批量)" << endl;
        cout << "\t"
             << "3.人工确认 <未完成的 核酸检测> 是否完成 (可批量) [为防止误操作，停用该功能]" << endl;
        cout << "\t"
             << "4.再次显示 功能菜单" << endl;
        cout << "\t"
             << "5.返回 [用户端功能菜单]" << endl;
        cout << "=====================================================" << endl;
        cout << "请输入对应的选项：";
        string choice;
        cin >> choice;
        if (choice == "5") {
            cout << "收到！即将退出该管理平台，并返回上一级菜单 ... " << endl;
            Sleep(250);
            break;
        } else if (choice == "4") {
            cout << "收到！即将 再次显示 功能菜单 ... " << endl;
            Sleep(250);
        } else if (choice == "3") {
            confirm_all_unfinished_tasks();
            cout << "为防止误操作，已停用该功能！即将 再次显示 功能菜单 ... " << endl;
            Sleep(250);
        } else if (choice == "2") {
            confirm_unfinished_tasks_former_than_today(false);
        } else if (choice == "1") {
            show_unfinished_tasks_former_than_today();
        } else {
            cout << "抱歉，尚未开发对应的功能！即将 再次显示 功能菜单 ... " << endl;
            Sleep(250);
        }
    }
}
