#include <iostream>
#include <memory>

using namespace std;

class BB;
class AA {
public:
    shared_ptr<BB> b_ptr; // weak_ptr<BB> b_ptr;
    ~AA() {
        cout << "~AA()" << endl;
    }
    AA() {
        cout << "AA()" << endl;
    }
};

class BB {
public:
    weak_ptr<AA> a_ptr; // weak_ptr<AA> a_ptr;
    ~BB() {
        cout << "~BB()" << endl;
    }
    BB() {
        cout << "BB()" << endl;
    }
};

int main() {
    /*
 * share_ptr循环引用，引出weak_ptr的作用。
 * 循环引用：两个对象相互使用shared_ptr成员变量指向对方造成循环引用，导致引用计数失效。
 * 即A内部有指向B，B内部有指向A; 这样对于AA，必定是在BB析构后才析构; 对于BB，必定是AA析
 * 构后才析构B;
 * 这就是循环引用的问题，违反常规，导致内存泄露。
 */
    shared_ptr<AA> aa = make_shared<AA>();
    shared_ptr<BB> bb = make_shared<BB>();
    aa->b_ptr = bb;
    bb->a_ptr = aa;
    cout << aa.use_count() << endl;
    cout << bb.use_count() << endl;

    return 0;
}
