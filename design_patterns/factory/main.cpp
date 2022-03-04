#include <iostream>
#include "easylogging++.h"
#include "easy_factory.h"

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
    catch (const char *err) {
        LOG(ERROR) << err;
        exit(EXIT_FAILURE);
    }
    char *buffer = (char *) malloc(sizeof(char) * 10);
    cout << "buffer 指向" << &buffer << endl;
    char *my_buffer = buffer;
    cout << "my_buffer 指向" << &my_buffer << endl;

    free(buffer);

    cout << "buffer 指向" << &buffer << endl;
    cout << "my_buffer 指向" << &my_buffer << endl;
    if (my_buffer == nullptr) {
        LOG(ERROR) << "my_buffer == nullptr";
    }
    return 0;
}