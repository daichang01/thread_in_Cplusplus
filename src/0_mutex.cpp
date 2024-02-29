//topic:mutex in c++ threading | why us mutex | what is race condition and how to solve it? |what is critial section
//mutex: mutual ecxlusion

//RACE CONDITION 竞争条件  意味着至少有两个操作数或多于两个，除非修改数据，否则不存在竞争
//0 race condition is a situation where two or more threads/process happend to chage a common data at the same time
//1.if there is a race condition then we have to protect it and the protected setion is called critical section/region

/*
对数据的操作  1.load 2.change 3 save











*/
#include <iostream>
#include <thread>

int count = 0;

void addcount() {
    count ++;
}
int main() {
    std::thread thread1(addcount);
    std::thread thread2(addcount);

    thread1.join();
    thread2.join();
    std::cout << "count: " << count << std::endl;
    return 0;
}