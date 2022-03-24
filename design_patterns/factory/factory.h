//
// Created by ljx on 2022/3/24.
//

#ifndef CONCURRENCE_PRACTICES_FACTORY_H
#define CONCURRENCE_PRACTICES_FACTORY_H

#include <cstdio>

class Operator // 抽象类-计算器类
{
public:
    virtual void GetResult() = 0;
    void SetNumA(const double &numA) { a = numA; }
    void SetNumB(const double &numB) { b = numB; }

protected:
    double a{}, b{};
};

class OperatorAdd : public Operator { // 加法器类，继承计算器类
public:
    void GetResult() override { printf("a+b=%lf\n", a + b); }
};

class OperatorSub : public Operator { // 减法器类，继承计算器类
public:
    void GetResult() override { printf("a-b=%lf\n", a - b); }
};

class IFactory { // 工厂类
public:
    virtual Operator *CreateOperator() = 0;
};

class AddFactory : public IFactory {
private:
    Operator *CreateOperator() override {return new OperatorAdd();}
};

class SubFactory : public IFactory {
private:
    Operator *CreateOperator() override {return new OperatorSub();}
};

#endif //CONCURRENCE_PRACTICES_FACTORY_H
