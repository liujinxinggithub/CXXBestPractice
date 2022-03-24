#include <iostream>
#include "easylogging++.h"
#include "easy_factory.h"
#include "factory.h"

INITIALIZE_EASYLOGGINGPP

void loadLogConf() {
    // 加载easylog配置
    el::Configurations conf("../config/log.conf");
    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);
}

int main() {
    loadLogConf();
    LOG(INFO) << "简单工厂模式";
    try {
        auto oper = OperationFactory::CreateOperate('-');
        oper->SetFirstNumber(1);
        oper->SetSecondNumber(2);
        double result = oper->GetResult();
        LOG(INFO) << result;
    }
    catch (const char *err) {
        LOG(ERROR) << err;
        exit(EXIT_FAILURE);
    }

    LOG(INFO) << "工厂模式";
    IFactory* addFactory = new AddFactory;
    auto add_operator = addFactory->CreateOperator();
    add_operator->SetNumA(1);
    add_operator->SetNumB(2);
    add_operator->GetResult();
    return 0;
}