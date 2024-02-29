//topic:mutex in c++ threading | why us mutex | what is race condition and how to solve it? |what is critial section
//mutex: mutual ecxlusion

//RACE CONDITION 竞争条件  意味着至少有两个操作数或多于两个，除非修改数据，否则不存在竞争
//0 race condition is a situation where two or more threads/process happend to chage a common data at the same time
//1.if there is a race condition then we have to protect it and the protected setion is called critical section/region

//mutex:
//0. mutex is used to avoid race condition
//1 .wu use lock() ,unlock() on mutex to avoid race condition
/*
对数据的操作  1.load 2.change 3 save


*/
#include <iostream>
#include <thread>
#include <mutex>

int count = 0;
std::mutex m;

// 关键区域critical section 出现关键区域可以使用互斥体mutex
// 访问关键部分前，必须锁定互斥锁，完成后需要解锁它，以便如果有任何线程等待这个锁，该线程将被解锁并开始使用这个锁
// 能保证两个线程不会同时在这个地方工作，保证没有race condition
void addcount() {
    m.lock();
    for(int i = 0; i < 10000; i++) {
        count ++;
    }
    m.unlock();
}
int main() {
    std::thread thread1(addcount);
    std::thread thread2(addcount);
    
    thread1.join();
    thread2.join();
    std::cout << "count: " << count << std::endl;
    return 0;
}