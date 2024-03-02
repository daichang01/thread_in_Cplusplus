/*
topic: use of join(), detach(), and joinable() in thread in c++ (c++ 11)

join notes
0.once a thread is started we wait for this thread to finish by calling join() function on thread object.
1.double join will result into program termination.
2.if needed we should check thread is joinable before joining.(using joinable() function)

detach notes
0. this is used to detach newly created thread from parent thread.
1.always check before detaching a thread that it is joinable othrewise we may end up double detaching and double detach()
will result into program termination.
2.if we have detached thread and mian function is returning then the detached thread execetion suspended.

notes:
either join() or detach() should be called on thread object,otherwise during thread object's destructor it will terminate the 
program. because inside destructor it checks if thread is still joinable? if yes then it terminates the program.
如果要创建线程，必须编写join()或detach()
*/

#include <iostream>
#include <thread>
#include <chrono>

void run(int num) {
    while (num --> 0) {
        std::cout << num << "runthread:" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    std::thread t1(run, 10);
    std::cout << "main():" << std::endl;
    // t1.join();
    //一个好的习惯是join()前先判断joinable()
    // if (t1.joinable())
    //     t1.join();

    if (t1.joinable())
        t1.detach();
    for (int i = 0; i< 10000; i++) {
        if (i % 100 == 0) {
            std::cout<< i << std::endl;
        }
    }
    std::cout << "main() after" << std::endl;
    return 0;
}