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
    // 把收到的消息入到一個队列的线程
    void inMsgRecvQueue() {
        for (int i = 0; i < 100000; ++i) {
            {
                cout << "inMsgRecvQueue()执行，插入一个元素: " << i << endl;
                std::lock_guard<std::mutex> my_guard(my_mutex);//my_guard构造函数执行了lock()
                msgRecvQueue.push_back(i);
            }// 提前结束my_guard的生命周期，解锁掉
            // .....
            // 这里有其他处理代码时，上面提前结束才有意思
        }
    }

    bool outMsgLULProc(int &command) {
        std::lock_guard<std::mutex> my_guard(my_mutex);//my_guard构造函数执行了lock()
        if (!msgRecvQueue.empty()) {
            // 消息不为空
            command = msgRecvQueue.front(); // 返回第一个元素，但不检查元素是否存在
            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
            return true;
        }
        return false;
        // 局部对象my_guard析构的时候，执行了unlock()
    }

    // 把数据从消息队列中取出的线程
    void outMsgRecvQueue() {
        int command = 0;
        for (int i = 0; i < 100000; ++i) {
            bool result = outMsgLULProc(command);
            if (result) {
                cout << "outMsgRecvQueue执行。取出一个元素：" << command << endl;
                // 其他处理代码
            } else {
                // 消息队列为空
                cout << "outMsgRecvQueue()执行，但目前队列为空 " << i << endl;
            }
        }
        cout << "end" << endl;
    }

private:
    std::list<int> msgRecvQueue; // 容器（消息队列）,专门用于代表玩家发送的命令
    std::mutex my_mutex;
};


int main() {
    A myobja;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja); // 第二个参数是引用才能保证线程里用的是用一个对象
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
    myInMsgObj.join();
    myOutMsgObj.join();
    // （1）互斥量
    // 互斥量是一个对象，理解成一把锁，多个线程尝试lock()这把锁，只有一个线程锁定成功
    // 使用时要小心，保护数据不多也不少，少了达不到保护效果。多了，影响效率；
    // （2）用法
    // （2.1）lock() unlock()
    // 步骤：先lock()--->操作共享数据--->unlock()
    // 使用原则：要成对使用，有lock()必然要有unlock()
    // （2.2）std::lock_guard: 类模板，忘记unlock(),它替你lock();直接取代Lock()和unlock(),不能在继续使用lock和unlock了
    return 0;
}