/*
topic:condition variable in c++ threading

important point: CV are used for tow purpose
a. notify other threads
b. waiting for some conditions

1.condition variable allows running threads to wait on some conditions and once those conditions are met the waiting thread 
is notified using:
    a. notify_one()
    b. notify_all()
2. you need mutex to use condition variable.
3. if some thread want to wait on some condition then it has to do these things:
    a.acquire the mutex lock using std::unique_lock<std::mutex> lock(m)
    b.execute wait ,wait for, or wait_until. the wait operations atomatically release the mutex
      and suspend the execution of this thread if that condition is not true.
    c.when the condition variable is notified, the thread is awakended, and the mutex is atomically reacquired.
      the thread should then check the condition and resume waiting if the wake up was spurious.

note:
1.condition variables are used to sunchronize two or more threads.
2.best use case of condition variable is producer/consumer problem.
无论做什么，生产者总会首先启动。如果想在多线程中首先启动某个线程，这也是利用条件变量的好方法
*/
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>

std::mutex m;
std::condition_variable cv;
int balence = 0;

void addMoney(int& money) {
    std::unique_lock<std::mutex> uq(m);
    balence += money;
    std::cout << "add " << money <<  "success" << std::endl;
    std::cout << "balence : " << balence << std::endl;
    cv.notify_one();
}

void withDrawMoney(int& money) {
    std::unique_lock<std::mutex> uq(m);
    cv.wait(uq, []{return (balence != 0) ? true: false;});
    if (balence < money) {
        std::cout << "balence is not enough, balence :"  << balence << std::endl;
    }
    else {
        balence -= money;
        std::cout << "withdraw " << money << "success" << std::endl;
        std::cout << "balence : " << balence << std::endl;
    }
}

int main() {
    int addmoney = 300;
    int withdrawmoney = 500;
    std::thread t2(withDrawMoney, std::ref(withdrawmoney));
    std::thread t1(addMoney, std::ref(addmoney));
    t1.join();
    t2.join();
    return 0;
}