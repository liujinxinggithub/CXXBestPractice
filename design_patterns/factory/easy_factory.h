//
// Created by ljx on 2022/3/2.
//

#ifndef CONCURRENCE_PRACTICES_EASY_FACTORY_H
#define CONCURRENCE_PRACTICES_EASY_FACTORY_H

#include <string>
#include <cmath>
#include <memory>

using namespace std;

class Operation {
public:
    // 设置输入的计算数据
    void SetFirstNumber(const double &first_number) {first_number_ = first_number;}
    void SetSecondNumber(const double &second_number) {second_number_ = second_number;}

    // 获取计算数据
    double GetFirstNumber() const {return first_number_;}
    double GetSecondNumber() const {return second_number_;}

    // 纯虚函数
    virtual double GetResult() = 0;

private:
    double first_number_{}, second_number_{};
};

class Add : public Operation {
public:
    double GetResult() override {return GetFirstNumber() + GetSecondNumber();}
};

class Subtraction : public Operation {
public:
    double GetResult() override {return GetFirstNumber() - GetSecondNumber();}
};

class Multiplication : public Operation {
public:
    double GetResult() override {return GetFirstNumber() * GetSecondNumber();}
};

class Division : public Operation {
public:
    double GetResult() override {
        if (GetSecondNumber() == 0) {throw "The divisor cannot be 0";}
        return GetFirstNumber() / GetSecondNumber();
    }
};

class OperationFactory {
public:
    static Operation *CreateOperate(const char &operate);
private:
    static Operation *oper;
};

Operation *OperationFactory::oper = nullptr;

Operation *OperationFactory::CreateOperate(const char &operate) {
    switch (operate) {
        case '+' : {
            oper = new Add;
            break;
        }
        case '-' : {
            oper = new Subtraction;
            break;
        }
        case '*' : {
            oper = new Multiplication;
            break;
        }
        case '/' : {
            oper = new Division;
            break;
        }
        default: {
            throw "输入有误！";
        }
    }
    return oper;
}


#endif //CONCURRENCE_PRACTICES_EASY_FACTORY_H
