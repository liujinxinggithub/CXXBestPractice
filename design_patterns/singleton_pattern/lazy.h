#ifndef CONCURRENCE_PRACTICES_LAZY_H
#define CONCURRENCE_PRACTICES_LAZY_H

class CSingletonLazy {
public:
    static CSingletonLazy *GetInstance();

private:
    // 构造函数私有
    CSingletonLazy() = default;
    // 静态成员对象指针变量，程序一开始也会分配空间，但是那个是指针的空间，不是对象的空间
    static CSingletonLazy *m_pInstance;


};

CSingletonLazy *CSingletonLazy::GetInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new CSingletonLazy();
    }
    return m_pInstance;
}

CSingletonLazy *CSingletonLazy::m_pInstance = nullptr;

#endif // CONCURRENCE_PRACTICES_LAZY_H