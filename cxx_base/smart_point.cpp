#include <iostream>
#include <list>
#include <memory>

using namespace std;

int main() {
//    shared_ptr<string> p1;
//    shared_ptr<list<int>> p2;
//    if(p1  && p1->empty()) {
//        *p1 = "hi";
//    }
//    shared_ptr<int> p3 = make_shared<int>(42);
//    shared_ptr<string> p4 = make_shared<string>(10,'9');
//    shared_ptr<int> p5 = make_shared<int>();
//    auto p = make_shared<int>(42);
//    cout << "与p共享的智能指针数量" << p.use_count() << endl; //1
//    cout << "p=" << *p << endl; // 42
//    cout << "p的地址" << p << endl; // p
//    auto q(p);
//    cout << "与q共享的智能指针数量" << q.use_count() << endl; //2
//    cout << "q=" << *q << endl; // 42
//    cout << "q的地址" << q << endl; // =p
//
//    auto r = make_shared<int>(100);//r指向的int只有一个引用者
//    cout << "与r共享的智能指针数量" << r.use_count() << endl; //1
//    cout << "r=" << *r << endl; // 100
//    cout << "r的地址" << r << endl; //r, !=p
//    r=q;//给r赋值，令它指向另一个地址
//    cout << "与r共享的智能指针数量" << r.use_count() << endl; //3
//    cout << "r=" << *r << endl; // 42
//    cout << "r的地址" << r << endl; // p
    //递增q指向的对象的引用计数
    //递减r原来指向的对象的引用计数
    //r原来指向的对象已没有引用者，会自动释放

    // shared_ptr<int> p11 = new int(1024);//错误：必须使用直接初始化形式
    shared_ptr<int> p22(new int(1024));//正确：使用了直接初始化形式

    // p = new int(1024);//错误：不能将一个指针赋予shared_ptr
//    auto p = make_shared<int>(42);
//    cout << p.use_count() << endl;
//    p.reset();//p是唯一指向的对象，reset会释放此对象
//    cout << p.use_count() << endl;
//    p.reset(new int(4));//传递了可选的参数内置指针，会让p指向new int(4)
//    cout << p.use_count() << endl;
//    auto x = new int(10);
//    p.reset(x, std::default_delete<int>());//传递了可选的参数内置指针，会让p指向new int(4)
//    cout << p.use_count() << endl;

    auto p = make_shared<int>(42);
    cout << p.use_count() << endl;

    weak_ptr<int> w(p);
    cout << p.use_count() << endl;

    return 0;
}
