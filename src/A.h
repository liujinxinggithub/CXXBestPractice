//
// Created by ljx on 2022/2/7.
//

#ifndef CONCURRENCE_PRACTICES_A_H
#define CONCURRENCE_PRACTICES_A_H


class A {
public:
    mutable int m_i; //m_i即使是在const中也可以被修改
    explicit A(int i) : m_i(i) {};

};


#endif //CONCURRENCE_PRACTICES_A_H
