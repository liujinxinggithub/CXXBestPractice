//
// Created by ljx on 2022/2/9.
//

#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <fstream>

using namespace std;

class A {
public:
    // 把收到的消息（玩家命令）入到一个队列的线程

private:
    std::list<int> msgRecvQueue;
};

//vector<int> g_v = {1, 2, 3}; //共享数据，只读
//
//void myprint(int inum) {
//    cout << "id=" << std::this_thread::get_id << "g_v" << g_v[0] << g_v[1]<< g_v[2] << endl;
//}

class LogFile {
    std::mutex _mu;
    ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }
    ~LogFile() {
        f.close();
    }
    void shared_print(const string& msg) {
        std::unique_lock<std::mutex> guard(_mu);
        cout << "函数中的线程号：" << std::this_thread::get_id() << endl;
    }

};

int main() {
//    //一：创建和等待多个线程
//    vector<thread> mythreads;
//    // 创建10个线程，入口统一使用myprint
//    // a)10线程还行顺序时乱的，和操作系统对内部线程的运行调度机制有关
//    // b)使用迭代器创建多个线程的写法需要记忆（对管理大量线程很方便）
//    mythreads.reserve(10);
//    for (int i = 0; i < 10; ++i) {
//        mythreads.emplace_back(myprint, i);
//    }
//
//    for (auto &mythread : mythreads) {
//        mythread.join();
//    }
//    cout << "我爱中国" << endl;

    // 使用成员函数作为线程函数的方法来写线程
    cout << "主线程号：" << std::hex << std::this_thread::get_id() << endl;
    LogFile a;
    a.shared_print("hhh");

    return 0;
}