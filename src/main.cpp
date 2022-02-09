#include <iostream>
#include <thread>
#include "Ta.h"
#include "Data_.h"
#include "A.h"

using namespace std;

void myPrint() {
    cout << "我的线程开始运行" << endl;
    //-------------
    cout << "子线程id：" << std::this_thread::get_id() << endl;

    //-------------
    cout << "我的线程运行完毕" << endl;
}

void myPrint1(const int i, const std::string &pmybuf) {
    cout << i << endl;
    cout << "子线程id：" << std::this_thread::get_id() << endl;

    cout << pmybuf << endl;
}

void PrintA(const A& a) {
    a.m_i = 99;
    cout << "子线程PrintA的参数地址是" << &a << "thread = " << std::this_thread::get_id() << endl;
}

int main() {
    //(1)创建了线程，线程执行起点（入口）是myPrint；(2)执行线程
    thread myThread(myPrint);

    //(2)阻塞主线程并等待myPrint执行完，当myPrint执行完毕，join()就执行完毕，主线程继续往下执行
    //join意为汇合，子线程和主线程回合
    myThread.join();

    //设置断点可看到主线程等待子线程的过程
    //F11逐语句，就是每次执行一行语句，如果碰到函数调用，它就会进入到函数里面
    //F10逐过程，碰到函数时，不进入函数，把函数调用当成一条语句执行

    //(3)传统多线程程序中，主线程要等待子线程执行完毕，然后自己才能向下执行
    //detach:分离，主线程不再与子线程汇合，不再等待子线程
    //detach后，子线程和主线程失去关联，驻留在后台，由C++运行时库接管
    //myThread.detach();

    //(4)joinable()判断是否可以成功使用join()或者detach()
    //如果返回true，证明可以调用join()或者detach()
    //如果返回false，证明调用过join()或者detach()，join()和detach()都不能再调用了
    if (myThread.joinable()) {
        cout << "可以调用可以调用join()或者detach()" << endl;
    } else {
        cout << "不能调用可以调用join()或者detach()" << endl;
    }

    // 1)创建一个类，并编写圆括号重载函数，初始化一个该类的对象，把该对象作为线程入口地址
    Ta ta;
    std::thread class_object_thread(ta);// 会执行Ta的拷贝构造函数，复制一份对象到线程中
    class_object_thread.join();
    std::thread class_object_thread2(ta, 100);
    class_object_thread2.join();
    // 2)lambda 表达式
    auto lambda = []() {
        cout << "lambda 表达式线程开始执行了" << endl;
        //-------------
        cout << "子线程id：" << std::this_thread::get_id() << endl;

        //-------------
        cout << "lambda 表达式线程开始执行了" << endl;
    };
    std::thread lambda_thread(lambda);
    lambda_thread.join();

    // 3)类中的某个函数作为线程的入口地址
    Data_ data(3);
    std::thread one_obj(&Data_::GetMsg); // 静态函数
    std::thread two_obj(&Data_::SaveMsg, &data, "哈哈哈哈"); // 普通函数
    one_obj.join();
    two_obj.join();

    int mvar = 1;
    int &mvary = mvar;
    char mybuf[] = "this is a test";
    //如果detach了，这样仍然是不安全的
    //因为存在主线程运行完了，mybuf被回收了，系统采用mybuf隐式类型转换成string
    //推荐先创建一个临时对象thread myThread(myPrint, mvar, string(mybuf));就绝对安全了。。。。
    thread myThread1(myPrint1, mvar, string(mybuf));
    myThread1.join();
    cout << "主线程id：" << std::this_thread::get_id() << endl;

    // 传递类对象
    A a(10);
    std::thread a_thread(PrintA, a);
    a_thread.join();
    return 0;
}
