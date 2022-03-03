//
// Created by ljx on 2022/2/15.
//

#include <iostream>
#include <memory>

using namespace std;

class Animal
{
public:
    Animal() {
        cout << "Animal construct function" << endl;
    };
    ~Animal() {
        cout << "Animal destruct function" << endl;
    }
    virtual void run()
    {
        cout << "动物跑。。。" << endl;
    }
};

class Cat : public Animal
{
public:
    Cat() {
        cout << "Cat construct function" << endl;
    }
    ~Cat() {
        cout << "Cat destruct function" << endl;

    }
    virtual void run()
    {
        cout << "喵喵喵。。。" << endl;
    }
};

class Base1 {
public:
    virtual void print() {
        std::cout << "Base1 print" << std::endl;
    }
    virtual ~Base1(){
        std::cout << "Base1's destructor" << std::endl;
    }
};

class Derived1 : public Base1
{
public:
    Derived1(int n) {
        p = new char[n];
    }
    virtual void print() override {
        std::cout << "Derived1 print" << std::endl;
    }
    ~Derived1() {
        delete[]p;
        std::cout << "Derived1's destructor" << std::endl;
    }
private:
    char *p;
};


class App
{
public:
    App() = default;

    App(const App &app) = delete;

    App &operator=(const App &app) = delete;

    virtual ~App() = default;

public:
    virtual bool initInstance(int argc, char *argv[]) = 0;
    virtual void exitInstance() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
};

class LogApp : public App
{
public:
    LogApp();
    LogApp(const LogApp &app) = delete;
    LogApp &operator=(const LogApp &app) = delete;
    virtual ~LogApp();

protected:
    virtual bool initInstance(int argc, char *argv[]) override;
    virtual void exitInstance() override;
    virtual void run() override;
    virtual void exit() override;
};

LogApp::LogApp() {

}

LogApp::~LogApp() {

}

bool LogApp::initInstance(int argc, char **argv) {
    return false;
}

void LogApp::exitInstance() {

}

void LogApp::run() {

}

void LogApp::exit() {

}


int main(int argc, char *argv[]) {
    std::unique_ptr<App> app(new LogApp);

    if (app->initInstance(argc, argv))
    {
        app->run();
    }

    app->exitInstance();

    return 0;
}

//public：可以被该类中的函数、子类的函数、友元函数访问，也可以由该类的对象访问；
//protected：可以被该类中的函数、子类的函数、友元函数访问，但不可以由该类的对象访问；
//private：可以被该类中的函数、友元函数访问，但不可以由子类的函数、该类的对象、访问。
