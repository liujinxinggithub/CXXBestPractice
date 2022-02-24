#include <iostream>
#include <future>
#include <atomic>

using namespace std;

std::atomic_int g_count(0);

int my_thread() {
    cout << "my_thread() start" << "thread_id = " << std::this_thread::get_id() << endl;
//    std::chrono::milliseconds dura(5000);
//    std::this_thread::sleep_for(dura);
    cout << "my_thread() end" << "thread_id = " << std::this_thread::get_id() << endl;
    return 5;
}

void mythread1() {
    for (int i = 0; i < 1000000; i++) {
        g_count++;
    }
}

int main() {
    cout << "main thread | thread_id = " << std::this_thread::get_id() << endl;
    // std::async是一个函数模板，用来启动一个异步任务，启动起来一个异步任务之后，它返回一个std::future对象，
    std::future<int> result = std::async(std::launch::deferred, my_thread);
    cout << "continue........" << endl;

    // cout << result.get() << endl; //等待my_thread执行完毕，拿到结果

    // 等待1s
    std::future_status status = result.wait_for(std::chrono::milliseconds(100));
    if (status == std::future_status::timeout) {
        cout << "线程超时了，还没有执行完" << endl;
    } else if (status == std::future_status::ready) {
        cout << "执行完成，返回" << endl;
        cout << result.get() << endl;
    } else if (status == std::future_status::deferred) {
        //如果设置 std::future<int> result = std::async(std::launch::deferred, my_thread);，则本条件成立
        cout << "线程延迟执行" << endl;
        cout << result.get() << endl;
    }

    // std::shared_future：也是个类模板
    // std::future的 get() 成员函数是转移数据
    // std::shared_future 的 get()成员函数是复制数据
//    std::packaged_task<int()> mypt(my_thread);
//    std::thread t1(std::ref(mypt));
//    std::future<int> packaged_result = mypt.get_future();

    bool ifcanget = result.valid(); // 判断future中的值是不是一个有效值
    std::shared_future<int> result_s(result.share()); //执行完毕后result_s里有值，而result里空了
    //std::shared_future<int> result_s(std::move(result));
    //通过get_future返回值直接构造一个shared_future对象
    //std::shared_future<int> result_s(mypt.get_future());
    // t1.join();

    std::thread my_t1(mythread1);
    std::thread my_t2(mythread1);
    my_t1.join();
    my_t2.join();
    cout << "正常情况下结果应该是2000 000次，实际是" << g_count << endl;

    return 0;
}

