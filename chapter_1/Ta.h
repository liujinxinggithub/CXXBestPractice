//
// Created by ljx on 2022/2/7.
//

#ifndef CONCURRENCE_PRACTICES_TA_H
#define CONCURRENCE_PRACTICES_TA_H

#include <iostream>
using namespace std;

class Ta {
public:
    void operator() () {
        cout << "类对象 线程开始运行" << endl;
        // ...
        cout << "圆括号重载函数" << endl;
        // ...
        cout << "类对象 线程运行完毕" << endl;
    }

    void operator() (int i) {
        cout << "类对象 线程开始运行" << endl;
        // ...
        cout << "圆括号重载函数" << endl;
        cout << "输入的是" << i << endl;
        // ...
        cout << "类对象 线程运行完毕" << endl;
    }
};


#endif //CONCURRENCE_PRACTICES_TA_H
