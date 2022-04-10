#include "NAT.h"
#include "daily_health_check.h"
#include "user_AccountInfoReceiver.h" // 这个绝对用得上
#include <Windows.h>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void NAT_manager::generate_main_folder_for_nat_detail_info() const
{
    if (_access(NAT_detail_file_root.c_str(), 0) == -1) {
        if (_mkdir(NAT_detail_file_root.c_str()) == 0) {
            // cout << "创建 NAT_detail_file_root 文件夹成功" << endl;
        } else {
            cout << "创建 NAT_detail_file_root 文件夹失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
    } else {
        // cout << "NAT_detail_file_root 文件夹已存在" << endl;
    }
}

void NAT_manager::generate_all_personal_nat_detail_info_folder()
{
    // TODO: Update all_personal_nat_detail_info_folder
    // using "user_list.dat" to generate all personal nat detail info folder
    string temp_folder_file_path = NAT_detail_file_root + R"(\)";
    user_list_file_empty_check();
    fstream file(user_list_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cu_cache = new current_user_info;
    cu_cache_tr = new current_user_info_tr;
    while (file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
        *cu_cache = *cu_cache_tr;
        temp_folder_file_path += cu_cache->student_number;
        temp_folder_file_path += R"(_)";
        temp_folder_file_path += cu_cache->real_name;
        if (_access(temp_folder_file_path.c_str(), 0) == -1) {
            if (_mkdir(temp_folder_file_path.c_str()) == 0) {
            } else {
                cout << "创建 personal_NAT_detail_info 文件夹失败！即将退出程序 ... " << endl;
                Sleep(250);
                exit(-1);
            }
        } else {
        }
    }
    delete cu_cache;
    delete cu_cache_tr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
}

void NAT_manager::load_status_of_folder()
{
    fstream file;
    // make_sure_file_exists
    file.open(status_of_folder_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预加载阶段，打开 status_of_folder.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    // open_again
    file.open(status_of_folder_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 status_of_folder.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.read(reinterpret_cast<char*>(&if_generate_all_personal_nat_detail_info_folder), sizeof(bool));
    // 这种情况下，就算是空的，也不会影响结果的正确性
    file.close();
}

void NAT_manager::write_status_of_folder()
{
    fstream file;
    // make_sure_file_exists
    file.open(status_of_folder_file_location, ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 status_of_folder.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.write(reinterpret_cast<char*>(&if_generate_all_personal_nat_detail_info_folder), sizeof(bool));
    file.close();
}

void NAT_manager::write_status_of_all_personal_folder(const bool& input_status)
{
    if_generate_all_personal_nat_detail_info_folder = input_status;
}

void NAT_manager::update_NAT_list_file()
{
    // TODO: 2022/05/05 => add get region => []
    // TODO: Update NAT_list.dat
    fstream user_list_file;
    fstream NAT_list_file;
    NAT_list_file.open(NAT_file_location, ios::app | ios::binary);
    if (!NAT_list_file.is_open()) {
        cout << "预加载 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    NAT_list_file.close();
    NAT_list_file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    user_list_file.open(user_list_file_location, ios::in | ios::binary);
    if (!NAT_list_file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!user_list_file.is_open()) {
        cout << "打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    NAT_list_file.seekg(0, ios::end);
    auto endPOS = NAT_list_file.tellg();
    NAT_list_file.seekg(0, ios::beg);
    auto begPOS = NAT_list_file.tellg();
    user_list_file.seekg(0, ios::end);
    auto endPOS_user_list = user_list_file.tellg();
    user_list_file.seekg(0, ios::beg);
    auto begPOS_user_list = user_list_file.tellg();
    if_NAT_list_file_empty = endPOS == 0;
    bool if_user_list_file_is_empty = endPOS_user_list == 0;
    if (if_user_list_file_is_empty) {
        // user_list_file_is_empty!
        return;
    }
    if (if_NAT_list_file_empty) {
        // TODO: Fully Import from user_list.dat
        cu_cache = new current_user_info;
        cu_cache_tr = new current_user_info_tr;
        cache_NAT_template = new NAT_template;
        cache_NAT_template_tr = new NAT_template_translator;
        while (user_list_file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
            *cu_cache = *cu_cache_tr;
            cache_NAT_template->student_name = cu_cache->real_name;
            cache_NAT_template->student_number = cu_cache->student_number;
            cache_NAT_template->dorm_number = cu_cache->dorm_number;
            cache_NAT_template->auto_filled_vars_initializer();
            /// TODO => fetch region_information
            fetch_region_information();
            /// TODO END
            *cache_NAT_template_tr = *cache_NAT_template;
            NAT_list_file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
        }
        delete cu_cache;
        delete cu_cache_tr;
        delete cache_NAT_template;
        delete cache_NAT_template_tr;
        cu_cache = nullptr;
        cu_cache_tr = nullptr;
        cache_NAT_template = nullptr;
        cache_NAT_template_tr = nullptr;
        NAT_list_file.close();
        user_list_file.close();
    } else {
        // TODO: Carefully Import from user_list.dat
        cu_cache = new current_user_info;
        cu_cache_tr = new current_user_info_tr;
        cache_NAT_template = new NAT_template;
        cache_NAT_template_tr = new NAT_template_translator;
        NAT_list_file.seekg(0, ios::beg);
        // get num of element in NAT_list_file
        auto start_pos_of_nat_list_file = NAT_list_file.tellg();
        NAT_list_file.seekg(0, ios::end);
        auto end_pos_of_nat_list_file = NAT_list_file.tellg();
        NAT_list_file.seekg(0, ios::beg);
        int num_of_element_in_NAT_list_file = (end_pos_of_nat_list_file - start_pos_of_nat_list_file) / sizeof(NAT_template_translator);
        // get num of element in user_list_file
        user_list_file.seekg(0, ios::beg);
        auto start_pos_of_user_list_file = user_list_file.tellg();
        user_list_file.seekg(0, ios::end);
        auto end_pos_of_user_list_file = user_list_file.tellg();
        user_list_file.seekg(0, ios::beg);
        int num_of_element_in_user_list_file = (end_pos_of_user_list_file - start_pos_of_user_list_file) / sizeof(current_user_info_tr);
        // check if num of element in two files changed
        bool if_element_changed = !(num_of_element_in_user_list_file == num_of_element_in_NAT_list_file);
        // Complex Core =>
        while (user_list_file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
            *cu_cache = *cu_cache_tr;
            auto read_ptr_POS_of_NAT_list_file = NAT_list_file.tellg();
            NAT_list_file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
            *cache_NAT_template = *cache_NAT_template_tr;
            /// TODO => fetch region_information
            fetch_region_information();
            /// TODO END
            bool ifNameChanged = !(cache_NAT_template->student_name == cu_cache->real_name);
            bool ifSnoChanged = !(cache_NAT_template->student_number == cu_cache->student_number);
            bool ifDormChanged = !(cache_NAT_template->dorm_number == cu_cache->dorm_number);
            if (ifNameChanged && if_element_changed) {
                // 当前 姓名、学号 已经在库中 被删除
                // 先转移到 temp_NAT_list_file (只要不是被删除的读指针对应的位置，全部转移覆写)
                // 再删除 + 重命名
                fstream temp_NAT_list_file;
                temp_NAT_list_file.open(temp_NAT_file_location, ios::out | ios::binary);
                if (!temp_NAT_list_file.is_open()) {
                    cout << "预创建 temp_NAT_list.dat 失败！即将退出程序 ... " << endl;
                    Sleep(250);
                    exit(-1);
                }
                NAT_list_file.seekg(0, ios::beg);
                auto temp_read_ptr_POS_of_NAT_list_file = NAT_list_file.tellg();
                while (NAT_list_file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
                    if (temp_read_ptr_POS_of_NAT_list_file != read_ptr_POS_of_NAT_list_file) {
                        temp_NAT_list_file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
                    }
                    temp_read_ptr_POS_of_NAT_list_file = NAT_list_file.tellg(); // 更新 读指针 位置
                }
                temp_NAT_list_file.close();
                NAT_list_file.close(); // 删除文件之前必须关闭
                remove(NAT_file_location.c_str());
                rename(temp_NAT_file_location.c_str(), NAT_file_location.c_str());
            } else {
                NAT_list_file.seekp(read_ptr_POS_of_NAT_list_file, ios::beg);
                if (ifDormChanged) {
                    cache_NAT_template->dorm_number = cu_cache->dorm_number;
                }
                if (ifNameChanged) {
                    cache_NAT_template->student_name = cu_cache->real_name;
                }
                if (ifSnoChanged) {
                    cache_NAT_template->student_number = cu_cache->student_number;
                }
                if (ifDormChanged || ifNameChanged || ifSnoChanged) {
                    *cache_NAT_template_tr = *cache_NAT_template;
                    NAT_list_file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
                }
            }
        }
        delete cu_cache;
        delete cu_cache_tr;
        delete cache_NAT_template;
        delete cache_NAT_template_tr;
        cu_cache = nullptr;
        cu_cache_tr = nullptr;
        cache_NAT_template = nullptr;
        cache_NAT_template_tr = nullptr;
        NAT_list_file.close();
        user_list_file.close();
    }
}

void NAT_manager::fetch_region_information() const
{
    const string daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\daily_health_check_list.dat)";
    const string temp_daily_health_check_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\temp_daily_health_check_list.dat)";
    fstream daily_check(daily_health_check_file_location, ios::app | ios::binary);
    if (!daily_check.is_open()) {
        cout << "预加载 daily_health_check.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    daily_check.close();
    daily_check.open(daily_health_check_file_location, ios::in | ios::binary);
    if (!daily_check.is_open()) {
        cout << "预加载 daily_health_check.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* t_cached_health_check = new daily_health_check::health_check_info;
    auto* t_cached_health_check_tr = new daily_health_check::health_check_info_trans;
    while (daily_check.read(reinterpret_cast<char*>(t_cached_health_check_tr),
        sizeof(daily_health_check::health_check_info_trans))) {
        *t_cached_health_check = *t_cached_health_check_tr;
        if (t_cached_health_check->student_id == cache_NAT_template->student_number) {
            // 学号是 完全可以 一一对应的
            // 这样的话，就可以获得 => 中高风险区的信息了
            cache_NAT_template->if_passed_by_high_risk_regions = t_cached_health_check->if_passed_by_high_risk_regions;
            cache_NAT_template->if_passed_by_medium_risk_regions = t_cached_health_check->if_passed_by_medium_risk_regions;
            break;
        }
    }
    delete t_cached_health_check;
    delete t_cached_health_check_tr;
    t_cached_health_check = nullptr;
    t_cached_health_check_tr = nullptr;
    daily_check.close();
}

void NAT_manager::update_num_of_nat_of_input_name(const string& input_real_name)
{
    // update directly in file
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto readPtr = file.tellg();
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_name == input_real_name) {
            ++cache_NAT_template->total_num_of_NAT;
            ++cache_NAT_template_tr->total_num_of_NAT;
            file.close();
            break;
        }
        readPtr = file.tellg();
    }
    file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekp(readPtr, ios::beg);
    file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_manager::update_num_of_nat_of_input_sno(const string& input_sno)
{
    // bug => forget to close the file after find the POS => fixed
    // update directly in file
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto readPtr = file.tellg();
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            ++cache_NAT_template->total_num_of_NAT;
            ++cache_NAT_template_tr->total_num_of_NAT;
            file.close();
            break;
        }
        readPtr = file.tellg();
    }
    file.close();
    file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekp(readPtr, ios::beg);
    file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_manager::update_num_of_finished_nat_of_input_sno(const string& input_sno)
{
    // bug => forget to close the file after find the POS => fixed
    // update directly in file
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto readPtr = file.tellg();
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            ++cache_NAT_template->total_num_of_finished_NAT;
            ++cache_NAT_template_tr->total_num_of_finished_NAT;
            file.close();
            break;
        }
        readPtr = file.tellg();
    }
    file.close();
    file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekp(readPtr, ios::beg);
    file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_manager::update_num_of_finished_nat_of_input_name(const string& input_real_name)
{
    // update directly in file
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto readPtr = file.tellg();
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_name == input_real_name) {
            ++cache_NAT_template->total_num_of_finished_NAT;
            ++cache_NAT_template_tr->total_num_of_finished_NAT;
            file.close();
            break;
        }
        readPtr = file.tellg();
    }
    file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekp(readPtr, ios::beg);
    file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

void NAT_manager::multi_update_num_of_finished_nat_of_input_sno(const string& input_sno, const int& times)
{
    // update directly in file
    cache_NAT_template = new NAT_template;
    cache_NAT_template_tr = new NAT_template_translator;
    fstream file(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto readPtr = file.tellg();
    while (file.read(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator))) {
        *cache_NAT_template = *cache_NAT_template_tr;
        if (cache_NAT_template->student_number == input_sno) {
            for (int i = 1; i <= times; ++i) {
                ++cache_NAT_template->total_num_of_finished_NAT;
                ++cache_NAT_template_tr->total_num_of_finished_NAT;
            }
            file.close();
            break;
        }
        readPtr = file.tellg();
    }
    file.close();
    file.open(NAT_file_location, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "打开 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekp(readPtr, ios::beg);
    file.write(reinterpret_cast<char*>(cache_NAT_template_tr), sizeof(NAT_template_translator));
    file.close();
    delete cache_NAT_template;
    delete cache_NAT_template_tr;
    cache_NAT_template = nullptr;
    cache_NAT_template_tr = nullptr;
}

bool NAT_manager::check_user_existence_by_real_name(const string& input_real_name)
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
        if (cache_NAT_template->student_name == input_real_name) {
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

bool NAT_manager::check_user_existence_by_sno(const string& input_student_number)
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
        if (cache_NAT_template->student_number == input_student_number) {
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

string NAT_manager::return_real_name_by_sno(const string& input_student_number)
{
    string result;
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
        if (cache_NAT_template->student_number == input_student_number) {
            result = cache_NAT_template->student_name;
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

string NAT_manager::return_sno_by_real_name(const string& input_real_name)
{
    string result;
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
        if (cache_NAT_template->student_name == input_real_name) {
            result = cache_NAT_template->student_number;
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

void NAT_manager::pre_generate_nat_file_location() const
{
    fstream file(NAT_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预加载 NAT_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
}

NAT_manager::NAT_manager()
    : user_info_receiver()
{
    if_generate_all_personal_nat_detail_info_folder = false;
    if_NAT_list_file_empty = true;
    pre_generate_nat_file_location();
    generate_main_folder_for_nat_detail_info();
    // load_status_of_folder();
    // if (!if_generate_all_personal_nat_detail_info_folder) {
    //     generate_all_personal_nat_detail_info_folder();
    // }
    update_NAT_list_file();
    c_NAT_template = new NAT_template;
}

NAT_manager::NAT_manager(
    const string& student_name,
    const string& student_number,
    const string& dorm_number,
    const bool& if_passed_by_high_risk_regions,
    const bool& if_passed_by_medium_risk_regions)
    : user_info_receiver()
{
    if_generate_all_personal_nat_detail_info_folder = false;
    if_NAT_list_file_empty = true;
    pre_generate_nat_file_location();
    generate_main_folder_for_nat_detail_info();
    // load_status_of_folder();
    // if (!if_generate_all_personal_nat_detail_info_folder) {
    //     generate_all_personal_nat_detail_info_folder();
    // }
    update_NAT_list_file(); // => bug!
    c_NAT_template = new NAT_template;
    c_NAT_template->student_name = student_name;
    c_NAT_template->student_number = student_number;
    c_NAT_template->dorm_number = dorm_number;
    c_NAT_template->if_passed_by_high_risk_regions = if_passed_by_high_risk_regions;
    c_NAT_template->if_passed_by_medium_risk_regions = if_passed_by_medium_risk_regions;
}
