#define _CRT_SECURE_NO_WARNINGS
#include "account.h"
#include "admin_AccountInfoReceiver.h"
#include "admin_interface.h"
#include "software_information.h"
#include "user_AccountInfoReceiver.h"
#include "user_interface.h"
#include <iostream>
#include <string>

using namespace std;

auto main() -> int
{
    // ��¼
    account_manager login_kernel;
    int returned_value;
    string returned_account;
    string returned_password;
    returned_value = login_kernel.shell_of_account_login();
    returned_account = login_kernel.return_account_name();
    returned_password = login_kernel.return_account_password();
    // ��¼�ɹ��󣬽��й���
    if (returned_value == 0) {
        admin_info_receiver admin_transmitter;
        // don't need transmit parameters
    } else {
        user_info_receiver user_transmitter;
        // don't need transmit parameters
    }
    // ���벻ͬ�Ľ���
    if (returned_value == 0) {
        // TODO
    } else {
        // TODO
    }
    // ���мܹ������� [�û�/����Ա ����] ���޷�ע���ص�¼���棬ֻ�ܽ�������ȫ�˳�
}
