/*
topic: introduction to thread in c++(c++ 11)

qustions
1.what do you understand by thread and give one example in C++

answer:
0. in every application there is a default thread which is main
1. a thread is also known as lightweight process. Idea is achieve parallelism by dividing a process into multipule threads.
    for example:
        the browser has multiple tabs that can be different threads.
        MS Word must be using multiple threads, one thread to format the text, another thread to process inputs（spell checker)
        visual studio code editor would be using threading for auto completing the code.(Intellicence)

ways to create threads in c++11
1. function pointers
2.lambda functions
3.functors
4.member funcitons
5.static member functions

Requirement
find the addition of all odd number from 1 to 1900000000 and all even number from 1 to 1900000000

*/

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

typedef unsigned long long ull;

void addEvenSum(int start, int end, ull& sum_even) {
    for (ull i = start; i < end; i++) {
        if (i % 2 == 0) {
            sum_even += i;
        }
    }
}
void addOddSum(int start, int end, ull& sum_odd) {
    for (ull i = start; i < end; i++) {
        if (i % 2 == 1) {
            sum_odd += i;
        }
    }
}

int main() {
    int start = 0;
    int end = 2000000000;
    ull sum_even = 0, sum_odd = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread t1(addEvenSum, start, end, std::ref(sum_even));
    std::thread t2(addOddSum, start, end, std::ref(sum_odd));

    t1.join();
    t2.join();

    // addOddSum(start, end, sum_odd);
    // addEvenSum(start, end, sum_even);

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << "sum_odd:" << sum_odd << std::endl;
    std::cout << "sum_even:" << sum_even << std::endl;

    std::cout << "duration time :" << static_cast<ull>(duration.count()) << "millsec" << std::endl;

}