//
// Created by ljx on 2022/3/2.
//

#include "easy_factory.h"

Operation *OperationFactory::CreateOperate(const char &operate) {
    Operation *oper = nullptr;
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