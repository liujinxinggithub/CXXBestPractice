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
    void SetFirstNumber(const double &first_number) {
        first_number_ = first_number;
    }

    void SetSecondNumber(const double &second_number) {
        second_number_ = second_number;
    }

    // 获取计算数据
    double GetFirstNumber() const {
        return first_number_;
    }

    double GetSecondNumber() const {
        return second_number_;
    }

    // 纯虚函数
    virtual double GetResult() = 0;

private:
    double first_number_{};
    double second_number_{};
};

class Add : public Operation {
public:
    double GetResult() override {
        double result = 0;
        result = GetFirstNumber() + GetSecondNumber();
        return result;
    }
};

class Subtraction : public Operation {
public:
    double GetResult() override {
        double result = 0;
        result = GetFirstNumber() - GetSecondNumber();
        return result;
    }
};

class Multiplication : public Operation {
public:
    double GetResult() override {
        double result = 0;
        result = GetFirstNumber() * GetSecondNumber();
        return result;
    }
};

class Division : public Operation {
public:
    double GetResult() override {
        if (GetSecondNumber() == 0) {
            throw "The divisor cannot be 0";
        }
        double result = 0;
        result = GetFirstNumber() / GetSecondNumber();
        return result;
    }
};

class OperationFactory {
public:
    static Operation *CreateOperate(const char &operate);
};

#endif //CONCURRENCE_PRACTICES_EASY_FACTORY_H
