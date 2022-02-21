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
                //std::lock_guard<std::mutex> my_guard(my_mutex);//my_guard构造函数执行了lock()
                std::lock(my_mutex1, my_mutex2);
                msgRecvQueue.push_back(i);
                std::lock_guard<std::mutex> my_guard1(my_mutex1, std::adopt_lock);
                std::lock_guard<std::mutex> my_guard2(my_mutex2, std::adopt_lock);

//                my_mutex1.unlock();
//                my_mutex2.unlock();

            }// 提前结束my_guard的生命周期，解锁掉
            // .....
            // 这里有其他处理代码时，上面提前结束才有意思
        }
    }

    bool outMsgLULProc(int &command) {
        // std::lock_guard<std::mutex> my_guard(my_mutex);//my_guard构造函数执行了lock()
        std::lock(my_mutex1, my_mutex2);
        std::lock_guard<std::mutex> my_guard1(my_mutex1, std::adopt_lock);
        std::lock_guard<std::mutex> my_guard2(my_mutex2, std::adopt_lock);
        if (!msgRecvQueue.empty()) {
            // 消息不为空
            command = msgRecvQueue.front(); // 返回第一个元素，但不检查元素是否存在
            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
//            my_mutex1.unlock();
//            my_mutex2.unlock();
            return true;
        }
//        my_mutex1.unlock();
//        my_mutex2.unlock();
        return false;
        // 局部对象my_guard析构的时候，执行了unlock()
    }

    // 把数据从消息队列中取出的线程
    [[noreturn]] void outMsgRecvQueue() {
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
    std::mutex my_mutex1;
    std::mutex my_mutex2;
};


int main() {
    A myobja;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja); // 第二个参数是引用才能保证线程里用的是用一个对象
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
    myInMsgObj.join();
    myOutMsgObj.join();
//     （1）互斥量
//     互斥量是一个对象，理解成一把锁，多个线程尝试lock()这把锁，只有一个线程锁定成功
//     使用时要小心，保护数据不多也不少，少了达不到保护效果。多了，影响效率；
//     （2）用法
//     （2.1）lock() unlock()
//     步骤：先lock()--->操作共享数据--->unlock()
//     使用原则：要成对使用，有lock()必然要有unlock()
//     （2.2）std::lock_guard: 类模板，忘记unlock(),它替你lock();直接取代Lock()和unlock(),不能在继续使用lock和unlock了
//     三：死锁
//     (3.1)死锁至少有两个锁头
//     (3.2)解决方案：只要保证两个互斥量上锁顺序一致（不出现交叉），就不会导致死锁；lock_guard也一样！
//     (3.3)std::lock()函数模板,但没需要unlock
//     能力：可以一次锁定多个锁头（至少两个,一个不行）
//     如果一个没锁住，他就在那里等着，等所有都锁住，才往下走。
//     要么两个互斥量都锁定，要么都没锁定。如果只锁定了一个，另一个没锁定成功，他会立即解锁锁定了的额，然后专门去锁定没锁定的。
//     (3.4)lock_guard的std::adopt_lock
//     std::lock_guard<std::mutex> my_guard1(my_mutex1, std::adopt_lock);
//     my_guard1的构造会调用lock()函数，加入std::adopt_lock表示构造时已经调用过lock()过了，my_guard1的构造不再需要调用lock()
//     析构时照常调用unlock()


    return 0;
}