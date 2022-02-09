//
// Created by ljx on 2022/2/7.
//

#ifndef CONCURRENCE_PRACTICES_DATA__H
#define CONCURRENCE_PRACTICES_DATA__H

#include <iostream>

using namespace std;

class Data_ {
public:
    explicit Data_(int i) : number(i) {};
    static void GetMsg();

    void SaveMsg(const std::string& msg);

private:
    int number;
};


#endif //CONCURRENCE_PRACTICES_DATA__H
