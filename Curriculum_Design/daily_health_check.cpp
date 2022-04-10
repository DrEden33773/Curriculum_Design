#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

daily_health_check::daily_health_check() /// 接下来需要考虑要不要处理此函数
{
    var_initializer();
    check_if_file_is_empty(); // 直接忽略返回值就行
    check_if_dictionary_is_empty(); // 直接忽略返回值就行
    // 下面，准备更新 => 时间索引文件
    fstream file;
    file.open(time_dictionary_file_location, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "更新时间索引时，打开 time_dictionary.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (if_time_dictionary_file_is_empty) {
        // 直接写入
        file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager));
    } else {
        constexpr int trans = sizeof(time_manager); // constexpr => 编译期优化
        // 比对尾部，判断是否写入
        file.seekg(-trans, ios::end);
        file.seekp(-trans, ios::end);
        file.read(reinterpret_cast<char*>(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // 最新的时间就是当前日期，nothing to do
        } else {
            file.seekp(0, ios::end); // 写指针指尾
            file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager)); // 单次写入
        }
    }
    file.close(); // 及时关闭
}

daily_health_check::daily_health_check(const string& any)
{
    var_initializer();
    check_if_file_is_empty(); // 直接忽略返回值就行
    check_if_dictionary_is_empty(); // 直接忽略返回值就行
    // 下面，准备更新 => 时间索引文件
    fstream file;
    file.open(time_dictionary_file_location, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "更新时间索引时，打开 time_dictionary.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (if_time_dictionary_file_is_empty) {
        // 直接写入
        file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager));
    } else {
        constexpr int trans = sizeof(time_manager);
        // 比对尾部，判断是否写入
        file.seekg(-trans, ios::end);
        file.seekp(-trans, ios::end);
        file.read(reinterpret_cast<char*>(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // 最新的时间就是当前日期，nothing to do
        } else {
            file.seekp(0, ios::end); // 写指针指尾
            file.write(reinterpret_cast<char*>(&current_time), sizeof(time_manager)); // 单次写入
        }
    }
    file.close(); // 及时关闭
}

daily_health_check::~daily_health_check()
{
    // bug => crtisvalidheappointer(block) [fixed]
    delete cached_health_check_info_tr;
    delete cached_health_check_info;
    delete current_health_check_info;
    delete checker; // => bug!!! [fixed]
}

void daily_health_check::update_health_check_file()
{
    time_manager today;
    // 核心功能，自动更新 “健康打卡文件” 的成员列表 => 覆盖全部用户
    cout << "正在更新健康打卡文件 ... " << endl;
    Sleep(350);
    // 开始更新文件
    cu_cache = new current_user_info;
    cu_cache_tr = new current_user_info_tr;
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    user_list_file_empty_check(); // 必须要有！
    fstream file_user_info(user_list_file_location, ios::in | ios::binary);
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in); // 双指针迫不得已
    if (!file_user_info.is_open()) {
        cout << "更新过程中，打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!file_daily_check_list.is_open()) {
        cout << "更新过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // 现在需要搞清楚，user_list.dat 和 daily_check_list.dat 中 用户个数 是否一样
    file_user_info.seekg(0, ios::end);
    const auto end_pos_user_list = file_user_info.tellg();
    auto num_of_user_info = end_pos_user_list / sizeof(current_user_info_tr);
    file_daily_check_list.seekg(0, ios::end);
    const auto end_pos_daily_check_list = file_daily_check_list.tellg();
    auto num_of_daily_check = end_pos_daily_check_list / sizeof(health_check_info_trans);
    // bug => 原先没有设置<读写指针重置回开头>，导致文件有大问题！[fixed]
    file_user_info.seekg(0, ios::beg);
    file_user_info.seekp(0, ios::beg);
    file_daily_check_list.seekg(0, ios::beg);
    file_daily_check_list.seekp(0, ios::beg);
    // 先看，user_list_file是不是空的
    if (!num_of_user_info) {
        file_daily_check_list.clear();
    } else {
        // 分情况讨论，看看 健康打卡文件 是不是空的
        if (check_if_file_is_empty()) {
            // 空的
            while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
                *cu_cache = *cu_cache_tr;
                cached_health_check_info->account_id = cu_cache->c_account;
                cached_health_check_info->student_id = cu_cache->student_number;
                cached_health_check_info->student_name = cu_cache->real_name;
                *cached_health_check_info_tr = *cached_health_check_info;
                file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // 写指针会自动后跳
            }
        } else {
            // 不是空的
            if (num_of_user_info == num_of_daily_check) {
                // 人数相等，只可能改名
                fstream temp_file_daily_check_list(temp_daily_health_check_file_location, ios::out | ios::binary);
                if (!temp_file_daily_check_list.is_open()) {
                    cout << "更新过程中，生成 temp_daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
                    Sleep(250);
                    exit(-1);
                }
                while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))
                    && file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
                    *cu_cache = *cu_cache_tr;
                    *cached_health_check_info = *cached_health_check_info_tr;
                    if (!(cu_cache->student_number == cached_health_check_info->student_id) || !(cu_cache->real_name == cached_health_check_info->student_name)) {
                        // cached_health_check_info->account_id = cu_cache->c_account;
                        cached_health_check_info->student_id = cu_cache->student_number;
                        cached_health_check_info->student_name = cu_cache->real_name;
                    }
                    if (!(cached_health_check_info->record_time == today)) {
                        // 日期发生更新
                        cached_health_check_info->record_time = today;
                        cached_health_check_info->if_checked = false;
                    }
                    // 写入 翻译器类
                    *cached_health_check_info_tr = *cached_health_check_info;
                    *cu_cache_tr = *cu_cache;
                    // 然后回写
                    temp_file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // 单次写入
                }
                file_daily_check_list.close();
                temp_file_daily_check_list.close();
                remove(daily_health_check_file_location.c_str());
                rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
            } else {
                // 人数不相等，有用户删除
                // 直接写入 temp 然后再改名改回来
                // TODO: 待修改 => 不合理的但是改起来很麻烦的 => 一旦用户数量发生了变动，就会清除原来用户的所有status => fixed
                // TODO: 用上vector暂存，然后判断
                // pre_job => fill the vector
                vector<health_check_info> original_health_check_info {};
                while (file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
                    *cached_health_check_info = *cached_health_check_info_tr;
                    original_health_check_info.push_back(*cached_health_check_info);
                }
                // first: get original record time
                file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
                *cached_health_check_info = *cached_health_check_info_tr;
                const time_manager original_record_time = cached_health_check_info->record_time;
                bool if_updated_date = !(original_record_time == today);
                // second: write temp
                file_daily_check_list.close();
                fstream temp_file_daily_check_list(temp_daily_health_check_file_location, ios::out | ios::binary);
                if (!temp_file_daily_check_list.is_open()) {
                    cout << "更新过程中，生成 temp_daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
                    Sleep(250);
                    exit(-1);
                }
                while (file_user_info.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
                    *cu_cache = *cu_cache_tr;
                    cached_health_check_info->account_id = cu_cache->c_account;
                    cached_health_check_info->student_id = cu_cache->student_number;
                    cached_health_check_info->student_name = cu_cache->real_name;
                    auto iter = find(
                        original_health_check_info.begin(),
                        original_health_check_info.end(),
                        *cached_health_check_info);
                    bool if_have_record_in_original = iter != original_health_check_info.end(); // 不用担心，end迭代器指空，相当于nullptr
                    if (if_have_record_in_original) {
                        cached_health_check_info->record_time = iter->record_time;
                        cached_health_check_info->if_checked = iter->if_checked;
                        if (if_updated_date) {
                            cached_health_check_info->record_time = today;
                            cached_health_check_info->if_checked = false;
                        }
                    } else {
                        cached_health_check_info->record_time = today;
                        cached_health_check_info->if_checked = false;
                    }
                    *cached_health_check_info_tr = *cached_health_check_info;
                    temp_file_daily_check_list.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans)); // 写指针会自动后跳
                }
                temp_file_daily_check_list.close();
                // third: rename
                remove(daily_health_check_file_location.c_str());
                rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
            }
        }
    }
    // 更新文件结束，关闭文件，回收指针
    file_daily_check_list.close();
    file_user_info.close();
    delete cu_cache;
    delete cu_cache_tr;
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
}

inline void daily_health_check::make_sure_file_exists() const
{
    fstream file;
    /// now, tries to new the file
    file.open(daily_health_check_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 daily_health_check_list.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

bool daily_health_check::check_if_file_is_empty()
{
    make_sure_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 daily_health_check_list.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // checker = new health_check_info;
    checker_trans = new health_check_info_trans;
    bool if_empty = true;
    while (file.read(reinterpret_cast<char*>(checker_trans), sizeof(health_check_info_trans))) {
        if_empty = false;
        break;
    }
    file.close();
    delete checker_trans;
    checker_trans = nullptr;
    // delete checker;
    // checker = nullptr; // => 防止野指针
    if_daily_check_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::make_sure_dictionary_exists() const
// 用到time_dictionary_file_location
{
    fstream file;
    /// now, tries to new the file
    file.open(time_dictionary_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 time_dictionary.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

bool daily_health_check::check_if_dictionary_is_empty()
{
    make_sure_dictionary_exists(); // 确保 时间索引文件 正常的产生
    fstream file;
    file.open(time_dictionary_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 time_dictionary.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    time_dict_checker = new dict_checker;
    bool if_empty = true;
    while (file.read(reinterpret_cast<char*>(time_dict_checker), sizeof(dict_checker))) {
        if_empty = false;
        break;
    }
    file.close();
    delete time_dict_checker;
    time_dict_checker = nullptr;
    if_time_dictionary_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::var_initializer()
{
    today_unchecked_file_location = name_base;
    temp_today_unchecked_file_location = temp_name_base;
    time_dict_checker = nullptr;
    current_health_check_info = nullptr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    checker = nullptr;
}
