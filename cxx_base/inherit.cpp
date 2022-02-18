//
// Created by ljx on 2022/2/15.
//

#include <iostream>

using namespace std;

class CBase {
private:
    int nPrivate;   //私有成员
public:
    int nPublic;    //公有成员
protected:    // 保护成员
    int nProtected;
};

class CDerived : public CBase {
    void AccessBase() {
        nPublic = 1;      // OK
        // nPrivate = 1;    // 错，不能访问基类私有成员
        nProtected = 1;  // OK，访问从基类继承的protected成员
        CBase f{};
        // f.nProtected = 1; //错，不能访问别的对象的保护成员，只能访问自己的（this）
    }
};

int main() {

    cout << "cxx base!" << endl;

    return 0;
}