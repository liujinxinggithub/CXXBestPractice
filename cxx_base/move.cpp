#include <iostream>
#include "easylogging++.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

class A {
public:
    explicit A(int size) : size_(size) {
        data_ = new int[size];
    }
    A(){}
    A(const A& a) {
        size_ = a.size_;
        data_ = new int[size_];
        LOG(INFO) << "copy ";
    }
    A(A&& a) {
        this->data_ = a.data_;
        a.data_ = nullptr;
        LOG(INFO) << "move ";
    }
    ~A() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }
    int *data_{};
    int size_{};
};
int main() {
    A a(10);
    A b = a;
    A c = std::move(a); // 调用移动构造函数
    return 0;
}