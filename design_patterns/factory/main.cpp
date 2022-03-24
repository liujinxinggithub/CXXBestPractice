#include <iostream>
#include "easylogging++.h"
#include "easy_factory.h"

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

    return 0;
}