#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <future>

using namespace std;

class A {
public:
    int my_thread(const int& mypar) {
        cout << mypar << endl;
        return mypar;
    }
};

int my_thread() {
    std::cout << "my_thread() start , thread_id = " << std::this_thread::get_id() << std::endl;
//    std::chrono::milliseconds dura(5000); // 5000ms = 5s
//    std::this_thread::sleep_for(dura);
    std::cout << "my_thread() end , thread_id = " << std::this_thread::get_id() << std::endl;
    return 5;
}

int packaged_thread(const int &mypar) {
    cout << mypar << endl;
    cout << "packaged_thread() start" << "threadid = " << std::this_thread::get_id() << endl;
//    std::chrono::milliseconds dura(5000);
//    std::this_thread::sleep_for(dura);
    cout << "packaged_thread() end" << "threadid = " << std::this_thread::get_id() << endl;
    return 5;
}

void promise_thread(std::promise<int> &tmp, int clac) {
    cout << "promise_thread() start, thread_id = " << std::this_thread::get_id() << endl;
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    cout << "promise_thread() end, thread_id = " << std::this_thread::get_id() << endl;
    int result = clac;
    tmp.set_value(result);
}


int main() {
//    // 普通函数
//    cout << "main thread, thread_id = " << std::this_thread::get_id() << endl;
//    //std::launch::async，在调用async函数的时候就开始创建新线程。
//    std::future<int> result_1 = std::async(std::launch::async, my_thread);
//    std::cout << "continue..." << std::endl;
//    // get()等待线程执行结束并返回结果
//    std::cout << result_1.get() << std::endl;
//
//    // 类成员函数
//    //std::lunch::deferred：
//    //（defer推迟，延期）表示线程入口函数的调用会被延迟，一直到std::future的wait()或者get()函数被调用时（由主线程调用）才会执行；如果wait()或者get()没有被调用，则不会执行。
//    A a;
//    int tmp = 12;
//    std::future<int> result_2 = std::async(std::launch::deferred, &A::my_thread, &a, tmp);
//    std::cout << result_2.get() << std::endl;
//
//    // std::packaged_task：打包任务，把任务包装起来。
//    std::packaged_task<int(int)> my_pt(packaged_thread);
//    // std::ref 引用来改变原来的函数
//    std::thread t1(std::ref(packaged_thread), 1);
//    t1.join();
//    std::future<int> result = my_pt.get_future();
//    cout << result.get() << endl;

    // std::promise 类模板
    // 在某个线程中给它赋值，在其他线程中，把这个值取出来
    std::promise<int> my_promise;
    std::thread promise_t1(promise_thread, std::ref(my_promise), 180);
    promise_t1.join();
    std::future<int> fu1 = my_promise.get_future(); //
    auto promise_result = fu1.get();
    cout << "promise_result = " << promise_result << endl;
    return 0;
}

