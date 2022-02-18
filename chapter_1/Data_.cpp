//
// Created by ljx on 2022/2/7.
//

#include "Data_.h"

void Data_::GetMsg() {
    cout << "我的线程开始运行" << endl;
    //-------------
    std::cout << "GetMsg 函数" << std::endl;

    //-------------
    cout << "我的线程运行完毕" << endl;
}

void Data_::SaveMsg(const std::string &msg) {
    cout << "我的线程开始运行" << endl;
    //-------------
    std::cout << "SaveMsg 函数" << std::endl;
    std::cout << msg << std::endl;

    //-------------
    cout << "我的线程运行完毕" << endl;

}

