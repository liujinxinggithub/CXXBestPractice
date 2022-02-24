#include <iostream>
#include <future>

using namespace std;

int my_thread() {
    cout << "my_thread() start" << "thread_id = " << std::this_thread::get_id() << endl;
//    std::chrono::milliseconds dura(5000);
//    std::this_thread::sleep_for(dura);
    cout << "my_thread() end" << "thread_id = " << std::this_thread::get_id() << endl;
    return 5;
}


int main() {
    cout << "main thread | thread_id = " << std::this_thread::get_id() << endl;
//    std::future<int> fu1 = std::async(my_thread); //创建线程
//    std::future<int> fu1 = std::async(std::launch::async, my_thread); //创建线程
    std::future<int> fu1 = std::async(std::launch::deferred, my_thread); //不创建线程

    cout << "开始调用get()" << endl;



    cout << fu1.get() << endl;
    return 0;
}

