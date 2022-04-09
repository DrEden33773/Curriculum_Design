#include "user_AccountInfoReceiver.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> // Sleep() 使用
using namespace std;

user_info_receiver::user_info_receiver()
{
    string trans_account = return_account_name();
    user_import_from_login_interface(trans_account);
    try_to_load_user_file(trans_account);
    ask_to_set_name_and_sno();
}

inline void user_info_receiver::user_import_from_login_interface(const string& input_account)
{
    cu_info = new current_user_info; // 别忘了申请空间
    cu_info->c_account = input_account;
    cu_info->if_first_use = true; // 初始化 是否第一次使用
    // 不要释放cu_info的空间，后面用
}

void user_info_receiver::try_to_load_user_file(const string& correct_account)
{
    cu_cache = new current_user_info; // 别忘了申请空间
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        // 打开不出错的前提下，打不开，那就是没有
        // nothing happened
    } else {
        while (file.read((char*)(cu_cache), sizeof(current_user_info))) {
            if (cu_cache->c_account == correct_account) {
                cu_info->real_name = cu_cache->real_name;
                cu_info->student_number = cu_cache->student_number;
                cu_info->if_first_use = false;
                break;
            }
        }
    }
    delete cu_cache; // 解除缓存 cu_cache
    // 但是不要解除 主存储变量 cu_info
}

void user_info_receiver::ask_to_set_name_and_sno()
{
    if (cu_info->if_first_use) {
        while (true) {
            cout << "第一次使用 "
                 << cu_info->c_account
                 << " 这个账号，稍等片刻，请按照提示填入真实且正确的信息："
                 << endl;
            cout << "请注意，输入个人信息后，您将无权更改个人信息(仅有管理员有此权限)" << endl;
            Sleep(1000);
            system("cls");
            //变量池
            string temp_name, temp_name_check;
            string temp_sno, temp_sno_check;
            int temp_dorm_no, temp_dorm_no_check;
            bool if_back_to_first_step_when_name_conflict;
            bool if_back_to_first_step_when_sno_conflict;
            bool if_back_to_first_step_when_dorm_no_conflict;
            //输入姓名
            while (true) {
                cout << "请输入您的真实姓名：";
                cin >> temp_name;
                while (true) {
                    char temp_flag;
                    cout << "请再次输入您 (刚刚输入) 的真实姓名：";
                    cin >> temp_name_check;
                    if (temp_name_check == temp_name) {
                        if_back_to_first_step_when_name_conflict = false;
                        break;
                    } else {
                        cout << "两次输入的姓名不同" << endl
                             << "输入A/a -> 再次输入最初输入的姓名"
                             << "输入其他内容 -> 重新指定姓名 >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            system("cls");
                            cout << "稍等片刻，准备 [再次输入最初输入的姓名]" << endl;
                            Sleep(1000);
                        } else {
                            system("cls");
                            cout << "稍等片刻，准备 [重新指定姓名]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_name_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_name_conflict) {
                    break;
                }
            }
            cout << "已成功输入 [真实姓名]，稍等片刻请输入 [真实学号]" << endl;
            Sleep(1000);
            system("cls");
            //输入学号
            while (true) {
                cout << "请输入您的真实学号：";
                cin >> temp_dorm_no;
                while (true) {
                    char temp_flag;
                    cout << "请再次输入您 (刚刚输入) 的真实学号：";
                    cin >> temp_dorm_no_check;
                    if (temp_dorm_no_check == temp_dorm_no) {
                        if_back_to_first_step_when_sno_conflict = false;
                        break;
                    } else {
                        cout << "两次输入的学号不同" << endl
                             << "输入A/a -> 再次输入最初输入的学号"
                             << "输入其他内容 -> 重新指定学号 >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            system("cls");
                            cout << "稍等片刻，准备 [再次输入最初输入的学号]" << endl;
                            Sleep(1000);
                        } else {
                            system("cls");
                            cout << "稍等片刻，准备 [重新指定学号]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_sno_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_sno_conflict) {
                    break;
                }
            }
            //输入宿舍号
            cout << "请问您当前是否住校？(Y->住校，其他字符->不住校) >>> ";
            char flag;
            cin >> flag;
            if (flag == 'Y' || flag == 'y') {
                while (true) {
                    cout << "请输入您目前所处的宿舍号：";
                    cin >> temp_sno;
                    while (true) {
                        char temp_flag;
                        cout << "请再次输入您 (刚刚输入) 的宿舍号：";
                        cin >> temp_sno_check;
                        if (temp_sno_check == temp_sno) {
                            if_back_to_first_step_when_dorm_no_conflict = false;
                            break;
                        } else {
                            cout << "两次输入的宿舍号不同" << endl
                                 << "输入A/a -> 再次输入最初输入的宿舍号 ; "
                                 << "输入其他内容 -> 重新指定宿舍号 >>> ";
                            cin >> temp_flag;
                            if (temp_flag == 'A' || temp_flag == 'a') {
                                system("cls");
                                cout << "稍等片刻，准备 [再次输入最初输入的宿舍号]" << endl;
                                Sleep(1000);
                            } else {
                                system("cls");
                                cout << "稍等片刻，准备 [重新指定宿舍号]" << endl;
                                Sleep(1000);
                                if_back_to_first_step_when_dorm_no_conflict = true;
                                break;
                            }
                        }
                    }
                    if (!if_back_to_first_step_when_dorm_no_conflict) {
                        break;
                    }
                }
            } else {
                temp_dorm_no = -1; // 不住校，宿舍号，录入 -1
                cout << "由于您目前不住校，系统将自动跳过 <输入宿舍号> 环节，若之后住校，请联系管理员完善此信息！" << endl;
            }

            cout << "请 ==最后一次== 确认您输入的个人信息：" << endl
                 << endl;
            cout << "==============================================" << endl;
            cout.setf(ios::left); // 左对齐
            cout << "   姓名： " << setw(8) << temp_name << endl;
            cout << "   学号： " << setw(8) << temp_sno << endl;
            cout << "   宿舍号： " << setw(8) << temp_dorm_no << endl;
            cout << "==============================================" << endl
                 << endl;
            cout << "是否正确？正确=>请输入Y/y || 不正确=>请输入其他任意非空字符(稍后将自动重新引导您输入姓名、学号) >>> ";
            char flag_of_flush;
            cin >> flag_of_flush;
            if (flag_of_flush == 'Y' || flag_of_flush == 'y') {
                // 写入结构体
                cu_info->real_name = temp_name;
                cu_info->student_number = temp_sno;
                cu_info->dorm_number = temp_dorm_no;
                // next
                system("cls");
                break;
            } else {
                cout << "请稍后，系统将自动重新引导您输入姓名、学号" << endl;
                Sleep(1000);
                system("cls");
            }
        }
        // 更新用户状态 -> 是否第一次使用
        cu_info->if_first_use = false;
        // 写入用户文件
        write_to_user_file();
        // end of function
        cout << "已成功输入 [个人信息]，稍等片刻将进入 <用户界面>" << endl;
        Sleep(1000);
        system("cls");
    }
}

void user_info_receiver::write_to_user_file()
{
    fstream file;
    file.open(file_location, ios::app | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "写入文件时，打开 user_list.dat 失败！即将自动退出程序" << endl;
        Sleep(250);
        exit(-1);
    }
    file.write((char*)(cu_info), sizeof(current_user_info)); // 文件尾部 写入
    file.close();
}

//接口函数
auto user_info_receiver::return_c_account() -> string
{
    return cu_info->c_account;
}

auto user_info_receiver::return_real_name() -> string
{
    return cu_info->real_name;
}

auto user_info_receiver::return_student_number() -> string
{
    return cu_info->student_number;
}
