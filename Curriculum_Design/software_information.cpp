#include "software_information.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

auto info::if_sftwr_info_is_empty() -> bool
{
    make_sure_sftwr_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 software_information.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* checker = new info(0);
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(info))) {
        if_empty = false;
        break;
    }
    delete checker;
    return if_empty;
}

inline void info::make_sure_sftwr_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 software_information.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

info::info()
{ // 不要在这里执行 load_used_time_from_file, 会无限递归
    used_time = 0;
}
info::info(int)
{
    // 防止无限递归，创造的构造函数，这里面不会存放任何语句
}
info::~info()
{
    // 一定不要在析构函数中，试图进行变量指向空间的释放
    // 上面的操作会调用析构函数
    // 但是析构函数不能有参，无法像构造函数那样，构成重载
}
void info::write_used_time_into_file()
{
    auto* cached_info = new info(0); // 没必要初始化，可以带参数，也可以不带参数
    cached_info->used_time = used_time;
    fstream file;
    file.open(file_location, ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "打开 software_information.dat 失败，即将自动退出" << endl;
        Sleep(100);
        exit(-1);
    } else {
        file.write((char*)(cached_info), sizeof(info));
        delete cached_info;
        file.close();
    }
}
void info::update_used_time()
{
    used_time += 1;
}
long long info::get_used_time() const
{
    return used_time;
}
void info::load_used_time_from_file()
{
    auto* cached_info = new info(0); // 缓存，用于比对信息
    fstream file;
    bool if_file_is_empty = if_sftwr_info_is_empty();
    if (if_file_is_empty) { // 文件是空的
        // 保留 默认参数
    } else {
        file.open(file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            delete cached_info;
            // 现在一定存在这个文件，打不开就是失败
            cout << "无法打开 software_information.dat！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read((char*)(cached_info), sizeof(info)); // 整体读入
        used_time = cached_info->used_time; // 更新
        file.close(); // 及时关闭
        delete cached_info; // 解除缓存
    }
}