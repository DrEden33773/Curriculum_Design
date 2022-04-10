#pragma once

#include <string>
using namespace std;

class admin_interface {
protected:
    string c_account;
    static inline void goto_province_info_manager();
    inline void show_current_user_info() const;
    static inline void goto_nat_admin();
    static inline void goto_daily_health_check_admin();
    static inline void goto_account_info_manager();

public:
    admin_interface() = default; // empty constructor
    admin_interface(const string&); // useful constructor
    void shell_of_admin_interface() const;
    string return_c_account(); // returns the account name
};
