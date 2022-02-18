#include <iostream>
#include <dirent.h> //linux下使用头文件 <unistd.h>
#include <zconf.h>
#include <memory>
#include "lazy.h"
#include "hunger.h"

using namespace std;

int main() {
    std::unique_ptr<int> p5(new int);
    *p5 = 10;
    // p 接收 p5 释放的堆内存
    int * p = p5.release();
    cout << *p << endl;
    //判断 p5 是否为空指针
    if (p5) {
        cout << "p5 is not nullptr" << endl;
    }
    else {
        cout << "p5 is nullptr" << endl;
    }
    std::unique_ptr<int> p6;
    //p6 获取 p 的所有权
    p6.reset(p);
    cout << *p6 << endl;;
    return 0;

}



