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
    std::mutex my_mutex1;
    std::mutex my_mutex2;
};


int main() {
    A myobja;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja); // 第二个参数是引用才能保证线程里用的是用一个对象
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
    myInMsgObj.join();
    myOutMsgObj.join();



    return 0;
}