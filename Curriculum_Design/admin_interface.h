#pragma once

#include <string>
using namespace std;

class admin_interface {
protected:
    string c_account;
    // ǰ�� province_info_manager ģ�� (ʡ�����������������Ϣ����ģ��)
    static inline void goto_province_info_manager(); 
    // ��ʾ ��ǰ�û���Ϣ
    inline void show_current_user_info() const;
    // ǰ�� ������Ϣ���� ģ��
    static inline void goto_nat_admin();
    // ǰ�� ÿ�ս����򿨹��� ģ��
    static inline void goto_daily_health_check_admin();
    // ǰ�� ��ͨ�û���Ϣ���� ģ��
    static inline void goto_account_info_manager();

public:
    admin_interface() = default; // empty constructor
    admin_interface(const string&); // useful constructor
    void shell_of_admin_interface() const;
    string return_c_account(); // returns the account name
};
