#include <iostream>
#include <cstring>

class MyString {
private:
    char* data; // 指向字符串的动态内存

public:
    // 构造函数（从 const char* 初始化）
    MyString(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 赋值运算符重载（重点！）
    MyString& operator=(const MyString& other) {
        if (this != &other) { // 防止自我赋值
            delete[] data; // 释放旧的内存
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;	// 返回自身
    }

    // 支持直接用 C 字符串赋值
    MyString& operator=(const char* str) {
        delete[] data;
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // 输出内容
    void print() const {
        std::cout << data << std::endl;
    }
};

int main() {
    MyString s = "Hello World";
    s.print();

    s = "hello";
    s.print();

    MyString t;
    t = s;
    t.print();

    return 0;
}
