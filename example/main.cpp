#include <iostream>

// 定义模板类 B
template <typename T>
class B {
public:
    void foo() {
        std::cout << "Calling foo() from class B" << std::endl;
    }
};

// 定义模板类 D，继承自 B
template <typename T>
class D : public B<T> {
public:
    void bar() {
        this->foo();  // 调用父类 B 中的 foo 函数
    }
};

int main() {
    D<int> dObj;
    dObj.bar();

    return 0;
}