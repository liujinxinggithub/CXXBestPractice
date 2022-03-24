//
// Created by ljx on 2022/2/15.
//

#ifndef CONCURRENCE_PRACTICES_HUNGER_H
#define CONCURRENCE_PRACTICES_HUNGER_H

using namespace std;

/*********************************************************
 *
 * 单例模式：饿汉式
 * 类产生的时候就创建好实例化对象，这是一种空间换时间的方式！
 *
 *
 *
 */
class CSingletonHunger {
public:
    // 获取实例化对象
    static CSingletonHunger* GetInstance() {
        return my_instance_;
    }
    // 手动释放实例化的对象
    static void ReleaseInstance() {
        delete my_instance_;
    }
private:
    // 默认构造函数
    CSingletonHunger() {
        cout << "饿汉式单例对象创建" << endl;
    }

    // 默认析构函数
    ~CSingletonHunger() {
        cout << "饿汉式单例对象销毁" << endl;
    }

    // 实例化对象
    static CSingletonHunger* my_instance_;
};

CSingletonHunger* CSingletonHunger::my_instance_ = new CSingletonHunger;


#endif //CONCURRENCE_PRACTICES_HUNGER_H
