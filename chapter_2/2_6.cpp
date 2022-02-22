#include <iostream>
#include <thread>
#include <list>
#include <mutex>

using namespace std;

class A
{
public:
    std::unique_lock<std::mutex> rtn_unique_lock()
    {
        std::unique_lock<std::mutex> tmp_guard(my_mutex1);
        return tmp_guard;// 返回局部对象，会导致系统生成临时的unique_lock对象，额外调用unique_lock的移动构造函数
    }

    // 把收到的消息入到一個队列的线程
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 100000; ++i) {
            {
                cout << "inMsgRecvQueue()执行，插入一个元素: " << i << endl;
//                std::lock_guard<std::mutex> my_guard(my_mutex1);//my_guard构造函数执行了lock()
//                my_mutex1.lock(); // 要先lock，后续才能用unique_lock的std::adopt_lock参数
//                std::unique_lock<std::mutex> my_guard(my_mutex1, std::adopt_lock);//my_guard构造函数执行了lock()
//                std::unique_lock<std::mutex> my_guard(my_mutex1, std::try_to_lock);//my_guard构造函数执行了lock()
//                if (my_guard.owns_lock())
//                {
//                    // 拿到了锁，操作共享数据
//                    msgRecvQueue.push_back(i);
//                    cout << "终于拿到锁了！！！！！！！！" << endl;
//
//                }
//                else {
//                    // 没有拿到锁
//                    cout << "没有拿到锁！干点别的事情" << endl;
//
//                }
//                std::unique_lock<std::mutex> my_guard(my_mutex1, std::defer_lock);// 没有加锁
//                my_guard.lock(); //调用的时unique_lock的成员函数。自己不用unlock,很智能！
//                msgRecvQueue.push_back(i);
//                my_guard.unlock();
//                // 这里处理非共享数据，临时把锁放开，去处理非共享数据
//                std::cout << "这里处理非共享数据" << std::endl;
//                my_guard.lock(); //调用的时unique_lock的成员函数。自己不用unlock,很智能！
//                std::unique_lock<std::mutex> my_guard(my_mutex1);// 加锁
//                std::mutex *ptx = my_guard.release(); //现在你有责任自己解锁这个my_mutex1，ptx指向my_mutex1
//                std::unique_lock<std::mutex> my_guard1(std::move(my_guard));// my_guard指向了空，my_guard1绑定了my_mutex1
                std::unique_lock<std::mutex> my_guard1 = rtn_unique_lock();
                msgRecvQueue.push_back(i);
//                ptx->unlock(); // 自己负责my_mutex1的解锁
//                if(my_guard.try_lock()) {
//                    //返回true,表示拿到锁了
//                    msgRecvQueue.push_back(i);
//                }
//                else {
//                    std::cout << "没有拿到锁！！！！！！！" << std::endl;
//
//                }
            }// 提前结束my_guard的生命周期，解锁掉
            // .....
            // 这里有其他处理代码时，上面提前结束才有意思
        }
    }

    bool outMsgLULProc(int &command)
    {
        // std::lock_guard<std::mutex> my_guard(my_mutex);//my_guard构造函数执行了lock()
        std::unique_lock<std::mutex> my_guard(my_mutex1);//my_guard构造函数执行了lock()

        std::chrono::milliseconds dura(2); // 20 * 1000 ms
        std::this_thread::sleep_for(dura);

        if (!msgRecvQueue.empty()) {
            // 消息不为空
            command = msgRecvQueue.front(); // 返回第一个元素，但不检查元素是否存在
            msgRecvQueue.pop_front(); // 移除第一个元素，但不返回
            return true;
        }

        return false;
    }

    // 把数据从消息队列中取出的线程
    [[noreturn]] [[noreturn]] void outMsgRecvQueue()
    {
        int command = 0;
        for (int i = 0; i < 100000; ++i) {
            bool result = outMsgLULProc(command);
            if (result) {
                cout << "outMsgRecvQueue执行。取出一个元素：" << command << endl;
                // 其他处理代码
            }
            else {
                // 消息队列为空
                cout << "outMsgRecvQueue()执行，但目前队列为空 " << i << endl;
            }
        }
        cout << "end" << endl;
    }

private:
    std::list<int> msgRecvQueue; // 容器（消息队列）,专门用于代表玩家发送的命令
    std::mutex my_mutex1;
};

int main()
{
    A myobja;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja); // 第二个参数是引用才能保证线程里用的是用一个对象
    std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
    myInMsgObj.join();
    myOutMsgObj.join();

    // 一：unique_lock取代lock_guard
    // unique_lock是一个类模板，在工作中，一般用lock_guard（推荐使用）；
    // unique_lock比lock_guard灵活很多；效率上差一点，内存占用多一点

    // 二：unique_lock的第二个参数
    // std::lock_guard可以带第二个参数
    // std::lock_guard<std::mutex> my_guard1(my_mutex1, std::adopt_lock);

    //（2.1）std::adopt_lock：表示互斥量已经被lock了（你必须提前lock互斥量，否则报异常）
    // std::adopt_lock标记的效果就是“假设调用方线程已经拥有了互斥的所有权（已经lock成功）”；
    // 通知lock_guard不需要在构造函数中lock这个互斥量了；
    // unique_lock也可以带std::adopt_lock标记，含义相同。就是不希望在unique_lock的构造函数中继续lock

    //（2.2）std::try_to_lock
    // 我们会尝试用mutex的lock()去锁定这个mutex,但是如果没有成功，我也会立即返回，并不会阻塞在那里；
    // 用这个try_to_lock的前提是你不可以先去lock

    //（2.3）std::defer_lock
    // 前提：不可以自己先lock，否则会报异常
    // std::defer_lock：是初始化了一个没有加锁的mutex

    // 三：unique_lock的成员函数
    //（3.1）lock()，之后离开作用域后，不需要手动unlock
    //（3.2）unlock(),可能有一些别的非共享代码要处理。先解锁，处理非共享代码，然后再次lock，去处理共享数据
    //（3.3）try_lock()。尝试给互斥量枷锁，成功返回true，失败false
    //（3.4）release()。返回它管理的mutex对象指针，并释放所有权；也就是说，这个unique_lock和mutex不在有关系；
    // 严格区分unlock()和release()的关系，不要混淆。
    // 如果mutex处理加锁状态。你要有责任接管过来，并负责解锁

    // 四：unique_lock所有权的传递 (绑定mutex)
    // std::unique_lock<std::mutex> my_guard(my_mutex1);
    // my_guard将自己对my_mutex1的所有权转移给其他unique_lock对象；但是不可以复制！
    // 不可以复制！std::unique_lock<std::mutex> my_guard1(my_guard); error！
    // a) std::move
    // b) return std::unique_lock<std::mutex> tmp_guard(my_mutex1);
    return 0;
}