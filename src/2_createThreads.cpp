/*
topic: types of thread creation in c++ 11
there are 5 different types we can create threads in c++11 using callable objects;

note:
if we create multiple threads at the same time it doesn't guarantee which one will start first.

// 1.function pointer 函数指针
// this ts very basic form of thread creation
//2.lambda function
// we can directly inject lambda at thread creation time
//3. functor (function Object)
//特定函数将被视为可调用对象
// 4. Non_static member function




*/
#include <iostream>
#include <thread>
// 1.function pointer 函数指针
// this ts very basic form of thread creation
void function(int x) {
    while(x-- > 0) {
        std::cout <<"1:" << x << std::endl;
    }
}

/*
Lambda表达式的结构
Lambda表达式的一般形式如下：


[ capture clause ] ( parameters ) -> return_type {
    function_body
}
在你提供的例子中，lambda表达式具体分解如下：

[ capture clause ]：这个lambda没有捕获任何外部变量，因此捕获子句为空。
( parameters )：参数列表中定义了一个名为x的int类型参数。
-> return_type：这个lambda没有显式指定返回类型。当没有指定返回类型且函数体中包含直接返回语句时，返回类型可以自动推断。在这个例子中，lambda函数没有返回任何值（隐式返回void）。
{ function_body }：函数体包含一个循环，循环中递减x并在每次迭代中打印x的值，直到x减至0以下。

Lambda表达式是C++中一个强大的功能，它们允许快速定义小的、用完即丢的函数对象，非常适合作为回调、临时函数或在需要简单函数对象的任何场合使用。
*/
// auto function2 = [](int x){
//     while (x -- > 0) {
//         std::cout << "2: " << x << std::endl;
//     }
// };


class Base{
public:
//3. functor (function Object)
//特定函数将被视为可调用对象
    void operator() (int x) {
        while (x-- > 0) {
            std::cout << "3:" << x << std::endl;
        }
    }
// 4. Non_static member function
    void run(int x) {
        while(x-- > 0) {
            std::cout << "4:" << x << std::endl;
        }
    }
// 5.static member function
    static void run2(int x) {
        while(x-- > 0) {
            std::cout << "5:" << x << std::endl;
        }
    }

    
};



int main() {
    int x = 30;
    std::thread t1(function, x);
    //2.lambda function
    // we can directly inject lambda at thread creation time
    std::thread t2([](int x){
    while (x -- > 0) {
        std::cout << "2: " << x << std::endl;
        }
    }, x);
    std::thread t3((Base()), x);
    Base b;
    std::thread t4(&Base::run, &b, x);
    //调用静态成员函数，不需要任何对象，可以直接用函数地址
    std::thread t5(&Base::run2, x);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}