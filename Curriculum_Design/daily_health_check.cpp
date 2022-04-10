#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
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
