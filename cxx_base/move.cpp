#include <iostream>
#include <memory>
#include <cassert>
#include "easylogging++.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

// assert(),运行断言，不可以提前到编译器发现错误，在发行版中，assert都会被关掉
// 会对表达式expression进行检测：
// 如果expression的结果为 0（条件不成立），那么断言失败，表明程序出错，assert() 会向标准输出设备（一般是显示器）打印一条错误信息，并调用 abort() 函数终止程序的执行。
// 如果expression的结果为非 0（条件成立），那么断言成功，表明程序正确，assert() 不进行任何操作。

// static_assert,编译断言，可以在编译期间发现更多的错误。
// 性能方面：由于static_assert编译期间断言，不生成目标代码，因此不会造成任何运行期性能损失

// 该static_assert用来确保编译仅在64位的平台上进行，不支持32位的平台
// 该语句可以放在文件的开头处，这样可以尽早检查，以节省失败情况下的编译时间。
static_assert(sizeof(void *) == 8, "32-bit code generation is not supported.");

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
//private:
    int *data_{};
    int size_{};
};

std::unique_ptr<A> foo() {
    auto ret = std::make_unique<A>(100);
    //...
    return ret;  // -> return ret;
}

int main() {


    A a(10);
    A b = a;
    A c = std::move(a); // 调用移动构造函数

    unique_ptr<int> p = std::make_unique<int>(1);
    unique_ptr<int> q = std::move(p);
    LOG(INFO) << sizeof(void *);
    assert(p == nullptr);  // OK: reset to default
    p = std::make_unique<int>(2);
    assert(*p == 2);       // OK: reset to int*(2

    std::unique_ptr<A> ret = foo();
    LOG(INFO) << ret->size_;

    return 0;
}

