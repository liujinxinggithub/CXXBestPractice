//
// Created by ljx on 2022/2/15.
//

#ifndef CONCURRENCE_PRACTICES_HUNGER_H
#define CONCURRENCE_PRACTICES_HUNGER_H

class CSingletonHunger {
public:
    static CSingletonHunger& GetInstance();

protected://基类的保护成员可以在派生类的成员函数中被访问。
    CSingletonHunger();
    ~CSingletonHunger();

private:
    // 静态成员对象变量，在程序运行一开始就分配了内存，就要调用构造函数（饿怕了！）
    static CSingletonHunger instance_;

private:
    bool m_flag_;

public:
    // bool GetCSingletonHunger();
    bool SetCSingletonHunger(const bool& b_hunger);
};

CSingletonHunger &CSingletonHunger::GetInstance() {
    std::cout << "CSingletonHunger::GetInstance()" << std::endl;
    return instance_;
}

CSingletonHunger::CSingletonHunger() : m_flag_(false) {
    std::cout << "enter CSingletonHunger::CSingletonHunger()" << std::endl;
}

CSingletonHunger::~CSingletonHunger() {
    std::cout << "enter CSingletonHunger::~CSingletonHunger()" << std::endl;
}

bool CSingletonHunger::SetCSingletonHunger(const bool &b_hunger) {
    m_flag_ = b_hunger;
    return false;
}

CSingletonHunger CSingletonHunger::instance_;


#endif //CONCURRENCE_PRACTICES_HUNGER_H
