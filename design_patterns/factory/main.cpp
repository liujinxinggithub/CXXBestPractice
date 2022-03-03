#include <iostream>
#include "easylogging++.h"
#include "factory.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

int main() {
    LOG(INFO) << "简单工厂模式";
    try {
        auto oper = OperationFactory::CreateOperate('-');
        oper->SetFirstNumber(1);
        oper->SetSecondNumber(2);
        double result = oper->GetResult();
        LOG(INFO) << result;
    }
    catch (const char* err) {
        LOG(ERROR) << err;
        exit(EXIT_FAILURE);
    }

    return 0;
}