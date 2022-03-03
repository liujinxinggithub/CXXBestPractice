#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <mutex>
#include <memory>

using namespace std;

std::mutex capture_mutex;

struct ImageData {
    typedef std::shared_ptr<ImageData> Ptr;
    char *buffer; // 图片缓存区
    int size;     // 图片数据的大小
};

void fun1(char* b)
{
    printf("%s", b);
}

void thread_func(const int& size, ImageData& image_data) {
    std::unique_lock<std::mutex> cap_picture_lock(capture_mutex);
    char *buffer = (char *)malloc(sizeof(char) * size);
    strcpy(image_data.buffer, buffer); // 内存拷贝,error
    free(buffer);
}



int main() {
// 浅拷贝 error
//    char buf[3];
//    char *arr[3];
//
//    for (int i = 0; i < 3; ++i) {
//        scanf("%s", buf);
//        arr[i] = buf;
//    }
//
//    for (int i = 0; i < 3; ++i) {
//        printf("%s\n", arr[i]);
//    }

// 深拷贝 right
//    char buf[3];
//    char *arr[3];//指针数组
//    int i;
//    for (i = 0; i < 3; i++) {
//        scanf("%s", buf);
//        arr[i] = (char *) malloc(strlen(buf + 1) * sizeof(char));
//        strcpy(arr[i], buf);
//    }
//    for (i = 0; i < 3; i++) {
//        printf("%s\n", arr[i]);
//    }
//    for (i = 0; i < 3; i++) {
//        free(arr[i]);
//    }

/*
 * char* 和 char[]的相同点
 * */
//(1)
// 两种类型都可以对应一个字符串
//    char* a = "string1";     // a是一个指向char变量的指针
//    char b[] = "afdsafasf";  // b是一个char数组（字符数组）
//(2)
// 二者可以混用，像函数传参的时候，实参可以是char*, 形参可以是char[];反过来也可以
//    char c[]= "Hello World";
//    fun1(c);

/*
 * char* 和 char[]的不同点
 * */
//(1)
// char* 是变量，值可以改变
// char[]是常亮，值不可以改变
// 解释：a是一个char型指针变量，其值（指向）可以改变；
// b是一个char型数组的名字，也是该数组首元素的地址，是常量，其值不可以改变
//    a = b;
//    a = "string3";
//    b = a; // char[] 是只读的
//    b ="string4" ; // char[] 是只读的

//(2)
// char[] 对应的内存区域总是可写，char* 指向的区域有时可写，有时只读
//char* aa = "string1";
//char bb[] = "string2";

    return 0;
}