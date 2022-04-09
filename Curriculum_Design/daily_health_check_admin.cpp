#include "daily_health_check_admin.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <synchapi.h>
#include <utility>

void daily_health_check_admin::try_to_load_check_status_file()
{
    // 现在可以确保 => 健康打卡文件一定存在
    // 本函数 [暂时冗余]
}

void daily_health_check_admin::change_all_status_in_file()
{
    cout << "正在修改 <健康打卡状态> ... " << endl;
    Sleep(250);
    // 打开文件
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in); // 双指针迫不得已
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        // 修改
        cached_health_check_info = new health_check_info;
        while (file_daily_check_list.read((char*)cached_health_check_info, sizeof(health_check_info))) {
            cached_health_check_info->if_check_is_necessary = status_of_if_need_to_check;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info));
        }
        delete cached_health_check_info;
        file_daily_check_list.close();
    }
    // end
    cout << "文件中的 状态 修改完毕！即将返回 [功能列表] ... " << endl;
}

void daily_health_check_admin::update_health_check_file()
{
    // 核心功能，自动更新 “健康打卡文件” 的成员列表 => 覆盖全部用户
    cout << "正在更新健康打卡文件 ... " << endl;
    Sleep(1000);
    // 开始更新文件
    cu_cache = new current_user_info;
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
    // 分情况讨论，看看 健康打卡文件 是不是空的
    if (check_if_file_is_empty()) { // 空的
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))) {
            cached_health_check_info = new health_check_info;
            // 只有下面这三个变量，需要进行 结构体外的初始化
            cached_health_check_info->account_id = cu_cache->c_account;
            cached_health_check_info->student_id = cu_cache->student_number;
            cached_health_check_info->student_name = cu_cache->real_name;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // 写指针会自动后跳
            delete cached_health_check_info;
        }
    } else { // 不是空的
        cached_health_check_info = new health_check_info;
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))
            && file_daily_check_list.read((char*)cached_health_check_info, sizeof(health_check_info))) {
            // something to do! 如果有更改过 个人信息 的话，一定要更新个人信息 [注意，这里的健康打卡个人信息列表已经被更改了]
            // 上面的意思是，当管理员修改个人信息的时候，不需要在 [账户管理模块] 中单独修改这个 [健康打卡个人信息列表]
            // 但是如果，管理员删除了一个用户时，需要在 [账户管理模块] 中单独维护这个 [健康打卡个人信息列表] (删除相应信息)
            if (cu_cache->student_number != cached_health_check_info->student_id || cu_cache->real_name != cached_health_check_info->student_name) {
                cached_health_check_info->account_id = cu_cache->c_account;
                cached_health_check_info->student_id = cu_cache->student_number;
                cached_health_check_info->student_name = cu_cache->real_name;
                // 然后回写
                int temp_POS = file_daily_check_list.tellg(); // 获取读指针
                file_daily_check_list.seekp(temp_POS, ios::beg); // 写指针同步到读指针
                file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // 单次写入
            }
        }
        delete cached_health_check_info;
        // now, reach the end of "file_daily_check_list", prepare to write!
        int POS = file_daily_check_list.tellg(); /// tell the read ptr
        file_daily_check_list.seekp(POS, ios::beg); /// update the write ptr
        while (file_user_info.read((char*)cu_cache, sizeof(current_user_info))) {
            cached_health_check_info = new health_check_info; // 必须反复new，因为new出来的才是正确的初始化了的
            cached_health_check_info->account_id = cu_cache->c_account;
            cached_health_check_info->student_id = cu_cache->student_number;
            cached_health_check_info->student_name = cu_cache->real_name;
            file_daily_check_list.write((char*)cached_health_check_info, sizeof(health_check_info)); // 写指针会自动后跳
            delete cached_health_check_info;
        }
    }
    // 更新文件结束，关闭文件，回收指针
    file_daily_check_list.close();
    file_user_info.close();
    delete cached_health_check_info;
    delete cu_cache;
}

void daily_health_check_admin::auto_delete()
{
    // 自动删除 => 1.时间索引中的过期索引 2.过期的未打卡用户文件
}

void daily_health_check_admin::change_auto_delete_range()
{
    cout << "当前的 <{未打卡名单} 自动删除期限> 为 => [" << auto_delete_range << "天] ... " << endl;
    cout << "<自动删除期限 N> 指的是：将删除 N 天前(含)的所有 {未打卡名单} ... " << endl;
    cout << "请注意！如果想要停用该功能，请输入任意负数；但如果不想停用该功能，请输入 [大于零的正数] ！" << endl;
    while (true) {
        Sleep(250);
        cout << "现在请输入修改后的 <自动删除期限> : ";
        int input;
        cin >> input;
        if (!input) {
            cout << "输入无效！请重新输入！" << endl;
            cout << endl;
        } else {
            auto_delete_range = input;
            break;
        }
    }
    change_auto_delete_range_file();
    if (auto_delete_range > 0) {
        cout << "已将 <{未打卡名单} 自动删除期限> 调整为 [" << auto_delete_range << "天] ，即将返回 [健康打卡管理菜单] ... " << endl;
    } else {
        cout << "已取消 <自动删除 {未打卡名单}> 功能！即将返回 [健康打卡管理菜单] ... " << endl;
    }
    Sleep(300);
    system("cls");
}

void daily_health_check_admin::try_to_load_auto_delete_range_file()
{
    if (if_auto_delete_range_file_empty) {
        // 自动删除期限文件 为空
        // 维持默认 => 7天
    } else {
        // 自动删除期限文件 有数据 => 读取
        // 现在文件必定存在
        fstream file;
        file.open(auto_delete_range_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "读取自动删除期限过程中，打开 auto_delete_range.dat 失败！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read((char*)(&auto_delete_range), sizeof(int));
        // 读取结束
        file.close();
    }
}

void daily_health_check_admin::make_sure_auto_delete_range_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(auto_delete_range_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 auto_delete_range.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

auto daily_health_check_admin::if_auto_delete_range_file_is_empty() -> bool
{
    make_sure_auto_delete_range_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(auto_delete_range_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 auto_delete_range.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* auto_delete_range_checker = new int;
    bool if_empty = true;
    while (file.read((char*)(auto_delete_range_checker), sizeof(int))) {
        if_empty = false;
        break;
    }
    file.close();
    delete auto_delete_range_checker;
    if_auto_delete_range_file_empty = if_empty;
    return if_empty;
}

daily_health_check_admin::daily_health_check_admin()
{
    // 初始化
    if_have_unchecked_all = false;
    if_have_unchecked_only_necessary = false;
    status_of_if_need_to_check = false;
    auto_delete_range = 7; // 自动删除期限默认为7天
    today_unchecked_file_location += current_time.time_str();
    today_unchecked_file_location += ".txt";
    temp_today_unchecked_file_location += current_time.time_str();
    temp_today_unchecked_file_location += ".txt";
    // 自动读取 自动删除期限
    try_to_load_auto_delete_range_file();
    cout << "已加载 自动删除期限！" << endl;
    // 自动更新 健康打卡 文件
    update_health_check_file();
    // 给出提示
    cout << "已更新健康打卡文件！即将进入 [健康打卡管理界面] ... " << endl;
    Sleep(250);
}

inline void daily_health_check_admin::change_auto_delete_range_file()
{
    fstream file;
    file.open(auto_delete_range_file_location, ios::out | ios::binary);
    // ios::app => 打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 auto_delete_range.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.write((char*)(&auto_delete_range), sizeof(int));
    file.close();
}

void daily_health_check_admin::switch_status_of_check()
{
    show_status_of_check();
    cout << "是否切换状态？(输入Y/y以切换，输入其他任意非空字符则不切换) >> ";
    char flag;
    cin >> flag;
    if (flag == 'y' || flag == 'Y') {
        if (status_of_if_need_to_check) {
            status_of_if_need_to_check = false;
            cout << "状态已切换为 => <不需要> 进行每日健康打卡！";
        } else {
            status_of_if_need_to_check = true;
            cout << "状态已切换为 => <需要> 进行每日健康打卡！";
        }
    } else {
        cout << "未切换状态！";
    }
    cout << endl;

    cout << "即将返回 [功能菜单] ... " << endl;
}

inline void daily_health_check_admin::show_status_of_check()
{
    cout << "当前状态为 => ";
    if (status_of_if_need_to_check) {
        cout << "<需要> 进行每日健康打卡" << endl;
    } else {
        cout << "<不需要> 进行每日健康打卡" << endl;
    }
}

void daily_health_check_admin::show_unchecked_user()
{
    cout << "输入1 => 展示“所有未打卡”的用户 || 输入其他任意非空字符 => 只展示“被强制而未打卡”的用户 >> ";
    char flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::binary | ios::in);
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // pre-print the list
    cout << "开始输出名单：" << endl;
    cout << "=================================================" << endl;
    cout << setw(4) << "姓名" << setw(10) << "学号" << endl;
    // print by case
    bool judger;
    cached_health_check_info = new health_check_info;
    if (flag == '1') {
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked) {
                cout << setw(4);
                cout << cached_health_check_info->student_name;
                cout << setw(10);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    } else {
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                cout << setw(4);
                cout << cached_health_check_info->student_name;
                cout << setw(10);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    }
    cout << "=================================================" << endl;
    file_daily_check_list.close();
    delete cached_health_check_info;
    cout << "名单输出完毕！即将回到 [健康打卡管理菜单] ... " << endl;
    Sleep(250);
}

void daily_health_check_admin::generate_unchecked_user_list()
{
    // 这次必须是 “文件格式保存了” => 因为要有“可读性”，且这个文件恰好没有“隐私性”
    cout << "输入1 => 生成“所有未打卡”用户的名单 || 输入其他任意非空字符 => 只生成“被强制而未打卡”用户的名单 >> ";
    char flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::in | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream file_unchecked_list(today_unchecked_file_location, ios::out);
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 unchecked_list_XXXX-XX-XX.txt 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // start generate the new file
    cached_health_check_info = new health_check_info;
    if (flag == '1') {
        file_unchecked_list << current_time.time_str() << " 所有未打卡的 用户名单：" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << setw(4) << "姓名" << setw(10) << "学号" << endl;
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked) {
                file_unchecked_list << setw(4);
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(10);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    } else {
        file_unchecked_list << current_time.time_str() << " 被强制，但未打卡的 用户名单：" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << setw(4) << "姓名" << setw(10) << "学号" << endl;
        while (file_daily_check_list.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                file_unchecked_list << setw(4);
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(10);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    }
    file_unchecked_list.close();
    file_daily_check_list.close();
    delete cached_health_check_info;
    cout << "已生成 相应的 未打卡用户名单！即将返回 [健康打卡管理界面] ... " << endl;
    Sleep(250);
}

void daily_health_check_admin::shell()
{
    // 管理界面
    cout << "欢迎进入 [健康打卡管理界面]！下面即将展示 [功能菜单] ... " << endl;
    Sleep(250);
    while (true) {
        cout << endl;
        cout << "============================================" << endl;
        cout << setw(4) << "1. 查看当前状态";
        cout << setw(4) << "2. 切换状态";
        cout << setw(4) << "3. 查看未打卡用户";
        cout << setw(4) << "4. 生成未打卡用户列表";
        cout << setw(4) << "5. 更新健康打卡文件";
        cout << setw(4) << "6. 修改 <自动删除未打卡用户列表> 的期限 (默认为7天(含)前)";
        cout << setw(4) << "7. 再次显示 [功能菜单]";
        cout << setw(4) << "8. 退出管理界面";
        cout << "============================================" << endl;
        cout << "请输入您的选择 >> ";
        int flag;
        cin >> flag;
        if (flag == 1) {
            show_status_of_check();
        } else if (flag == 2) {
            switch_status_of_check();
        } else if (flag == 3) {
            show_unchecked_user();
        } else if (flag == 4) {
            generate_unchecked_user_list();
        } else if (flag == 5) {
            cout << "现在开始<手动更新>健康打卡文件 ... " << endl;
            update_health_check_file();
            Sleep(250);
            cout << "已完成 <健康打卡文件 的 手动更新>！即将回到 [功能菜单] ... " << endl;
        } else if (flag == 6) {
            change_auto_delete_range();
        } else if (flag == 7) {
            cout << "即将再次展示 [功能菜单] ... " << endl;
            Sleep(250);
            continue;
        } else if (flag == 8) {
            cout << "收到！即将返回 [管理员菜单] ... " << endl;
            Sleep(350);
            system("cls");
            break;
        } else {
            cout << "功能未开发！即将重新返回 [功能菜单] ... " << endl;
            Sleep(250);
        }
    }
}
