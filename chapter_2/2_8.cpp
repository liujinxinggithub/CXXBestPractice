#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace std;

class A {
public:
    // 把收到的消息入到一個队列的线程
    void inMsgRecvQueue() {
        for (int i = 0; i < 100000; ++i) {
            {
                cout << "inMsgRecvQueue()执行，插入一个元素: " << i << endl;
                std::unique_lock<std::mutex> my_guard1(my_mutex1);
                msgRecvQueue.push_back(i);
                my_cond.notify_one(); // 尝试把wait线程唤醒，执行完这行，outMsgRecvQueue中的wait被唤醒
            }
            return;
        }
    }

//    bool outMsgLULProc(int &command)
//    {
//        std::unique_lock<std::mutex> my_guard(my_mutex1);//my_guard构造函数执行了lock()，每次都加锁效率低
//        if (!msgRecvQueue.empty()) {
//            // 消息不为空
//            command = msgRecvQueue.front(); // 返回第一个元素，但不检查元素是否存在
//            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
//            return true;
//        }
//
//        return false;
//    }

    // 把数据从消息队列中取出的线程
    void outMsgRecvQueue() {
        int command = 0;
        while (true) {
            std::unique_lock<std::mutex> my_thread(my_mutex1);
            my_cond.wait(my_thread, [this] {
                if (!msgRecvQueue.empty())
                    return true;
                return false;
            });

            // 只要流程能走到这里，那么互斥量一定被锁定的
            command = msgRecvQueue.front(); //返回第一个元素
            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
            my_thread.unlock(); //unique_lock随时可以解锁
            cout << "outMsgRecvQueue()执行，取出第一个元素" << command << endl;
        } //end while
    }

private:
    std::list<int> msgRecvQueue; // 容器（消息队列）,专门用于代表玩家发送的命令
    std::mutex my_mutex1;
    std::condition_variable my_cond; //生成条件类的对象
};

int main() {
    //一：条件变量std::condition_variable、wait()、notify_one()
    //线程A：等待一个条件满足
    //线程B：专门往消息队列中扔消息（数据）
    // 双重锁定
//    if (!msgRecvQueue.empty()) {
//        std::unique_lock<std::mutex> my_guard(my_mutex1);//my_guard构造函数执行了lock()，每次都加锁效率低
//        if (!msgRecvQueue.empty()) {
//            // 消息不为空
//            command = msgRecvQueue.front(); // 返回第一个元素，但不检查元素是否存在
//            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
//            return true;
//        }
//    }
    // 当消息队列不为空时，通知我们去取数据
    // std::condition_variable是一个类，等待一个条件达成，配合互斥量,用的时候要生成类的对象
    // wait()等待一个东西
    // wait第二个参数lambda返回true，那么wait()直接返回
    // wait第二个参数lambda返回false，wait将解锁互斥量，并堵塞本行。直到某个线程调用了notify_one()成员为止
    // my_cond.wait(my_thread)
    // 如果没有第二个参数，那么wait将解锁互斥量，并堵塞本行。
    // 当其他线程用notify_one()将本wait唤醒后，wait恢复干活，
    // a) wait()不断尝试获取互斥锁，获取不到就卡在这里等着获取。如果拿到锁了，那么就继续执行
    // b) wait()获取到了锁，也就是加锁了；
    // (b.1)如果第二个参数为false,那么就解锁互斥量，并堵塞本行，又开始休眠
    // (b.2)如果第二个参数为true,wait返回，继续流程（此时互斥量被锁定lock）
    // (b.3)如果没有第二个参数为true,wait返回，继续流程（此时互斥量被锁定lock）

    A myobja;
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja); // 第二个参数是引用才能保证线程里用的是用一个对象
    myOutMsgObj.join();
    myInMsgObj.join();


    return 0;
}