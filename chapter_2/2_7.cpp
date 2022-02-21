//
// Created by ljx on 2022/2/9.
//

#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <fstream>

using namespace std;


std::mutex resource_mutex;

std::once_flag g_flag; //这个系统定义的标记

// 单例类
class MyCAS //单例类
{
    static void CreateInstance() { // 莫仍私有
        std::chrono::milliseconds duration(2000); // 20s
        std::this_thread::sleep_for(duration);
        m_instance_ = new MyCAS;
        static CGarbageCollect cl;

        cout << "CreateInstance 执行了" << endl;
    }

private:
    MyCAS() = default;

private:
    static MyCAS *m_instance_; //静态成员变量

public:
    static MyCAS *GetInstance() {
        // std::unique_lock<std::mutex> my_mutex(resource_mutex); //自动加锁，但是效率很低, 不用！！！
//        if (m_instance_ == nullptr) { // 双重锁定
//            std::unique_lock<std::mutex> my_mutex(resource_mutex); //自动加锁，只有第一次调用时才进来
//            if (m_instance_ == nullptr) {
//                m_instance_ = new MyCAS;
//                static CGarbageCollect cl;
//            }
//        }
        std::call_once(g_flag, CreateInstance);// 两个线程同时执行到这里，其中一个线程要等另外一个线程执行完毕
        cout << "call_once 执行完毕了" << endl;
        return m_instance_;
    }

    class CGarbageCollect // 类中套类，用来释放对象
    {
    public:
        ~CGarbageCollect() {
            if (MyCAS::m_instance_) {
                delete MyCAS::m_instance_;
                MyCAS::m_instance_ = nullptr;
            }
        }
    };

    void func() {
        std::cout << "单例类" << std::endl;
    }
};

// 静态变量初始化
MyCAS *MyCAS::m_instance_ = nullptr;

// 线程入口函数
void mythread() {
    cout << "我的线程开始执行了" << endl;
    MyCAS *p_a = MyCAS::GetInstance();
    cout << "我的线程执行完毕了" << endl;

};

int main() {
    // 一：设计模式大概谈
    // “设计模式”：代码的一些写法，程序灵活，维护起来方便。

    // 二：单例模式（使用频率高）
    // 单例：整个项目中，有某个类只能创建一个！
//    MyCAS *p_a = MyCAS::GetInstance(); // 创建一个对象，返回该类对象的指针
//    MyCAS *p_b = MyCAS::GetInstance();
//    p_a->func(); //该装载的数据装载
//    MyCAS::GetInstance()->func();

    // 三：单例设计模式共享数据问题分析、解决
    // 问题：需要在我们自己创建的线程（不是main线程）中创建这个单例类对象，这种线程可能不止一个
    std::thread my_thread1(mythread);
    std::thread my_thread2(mythread);
    my_thread1.join();
    my_thread2.join();

    // 四：std::call_once(); c++11,该函数第二个参数是函数名a();
    // 功能：保证a()只能被调用一次
    // 具备互斥量的能力，效率上更高效，消耗资源更少：
    // 需要和标记std::once_flag结合使用
    // 调用后改变std::once_flag的状态“已调用”

    return 0;
}