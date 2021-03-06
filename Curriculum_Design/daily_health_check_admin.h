#pragma once

#include "daily_health_check.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using namespace std;

// 还需要改进 => 无法保存 当前 所有用户 强制打卡状态

// 需要维护的文件 => daily_health_check_file_location [这个是变量名]
class daily_health_check_admin : public daily_health_check {
    // 这里不需要继承“admin_info_receiver”，只需要继承“daily_health_check”
    // 因为 管理员的 操作 不需要 获知其 姓名 等 个人信息

private:
    bool status_of_if_need_to_check; // 是否需要强制打卡 => 默认false
    bool if_have_unchecked_all; // 是否有没有打卡的 [不论是否强制] => 默认false
    bool if_have_unchecked_only_necessary; // 是否有没有打卡的 [只考虑被强制的] => 默认false
    bool if_auto_delete_range_file_empty; // 自动删除的设置文件是否为空
    int auto_delete_range; // 自动删除 auto_delete_range 天前(含) 的 时间索引数据 和 未打卡名单
    const string auto_delete_range_file_location = R"(C:\Users\edwar\Desktop\cpp_final_task\auto_delete_range.dat)";

    class user_in_danger_template {
    public:
        string sno;
        string name;
        string danger_code;
        user_in_danger_template() = default;
        user_in_danger_template(
            string sno,
            string name,
            string danger_code)
            : sno(std::move(sno))
            , name(std::move(name))
            , danger_code(std::move(danger_code))
        {
        }
    };

protected:
    void try_to_load_check_status_file(); // 尝试打开 打卡状态 文件 // 暂时冗余即可
    void change_all_status_in_daily_check_file(); // 写入状态
    void auto_delete(); // 自动删除 时间索引中的过期索引 和 过期的未打卡列表
    void change_auto_delete_range(); // 更改 自动删除 期限
    void try_to_load_auto_delete_range_file(); // 从文件中读取 自动删除 期限
    inline void change_auto_delete_range_file(); // 在文件中更改 自动删除 期限
    auto if_auto_delete_range_file_is_empty() -> bool; // 自动删除期限 文件 是否为空
    void make_sure_auto_delete_range_file_exists() const; // 有效化 自动删除期限 文件
    void switch_status_of_check(); // => 切换 是否强制打卡
    inline void show_status_of_check() const; // => 展示 当前是否强制打卡
    void show_unchecked_user(); // => 展示 未打卡的用户 [可以展示所有，也可以只展示强制而未打卡的]
    void generate_unchecked_user_list(); // => 生成 未打卡用户名单 [可以生成所有，也可以只生成强制而未打卡的]
    void show_user_in_danger_today(); // 查看当天 打卡后 处于危险健康状态的 用户
    static void generate_file_of_user_in_danger_today(const vector<user_in_danger_template>& input); // 生成 当天 打卡后 处于危险健康状态的 用户名单 (文件)
    void show_check_status_of_input_user(); // 查看 输入用户的 打卡情况

public:
    daily_health_check_admin(); // => 自动更新“健康打卡”成员列表
    ~daily_health_check_admin();
    void shell_of_nat_admin(); // => 界面
};