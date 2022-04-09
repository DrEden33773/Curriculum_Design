#pragma once

#include <iostream>
using namespace std;

class info {
private:
    bool if_sftwr_info_empty;
    auto if_sftwr_info_is_empty() -> bool;
    inline void make_sure_sftwr_file_exists();

protected:
    long long used_time; // 管理员账号数
    const string file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\software_information.dat)";

public:
    info();
    info(int);
    ~info();
    void write_used_time_into_file();
    void update_used_time(); // used_time++
    void update_used_time_but_minor(); // used_time-- // 删除管理员的时候会用到
    auto get_used_time() const -> long long;
    void load_used_time_from_file();
};
