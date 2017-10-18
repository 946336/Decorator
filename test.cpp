#include "decorator.hpp"

#include <mutex>
#include <thread>

#include <stdio.h>

const int nThreads = 10;
const int splitPersonalities = 100000;

template <class R, class ... Args>
Decorator<R(Args...)> atomic(R (*f)(Args...), std::mutex *mtx)
{
    return Decorator<R(Args...)>(
              [mtx]() { mtx->lock(); }
            , f
            , [mtx]() { mtx->unlock(); }
            );
}

int count = 0;

void clock_in()
{
    ++count;
}

int check_clock()
{
    return count;
}

std::mutex clock_lock;
auto centralized_clock = atomic(clock_in, &clock_lock);
auto check_clock_safely = atomic(check_clock, &clock_lock);

void clock_in_a_lot()
{
    for (int i = 0; i < splitPersonalities; ++i) {
        clock_in();
    }
}

void clock_in_safely()
{
    for (int i = 0; i < splitPersonalities; ++i) {
        centralized_clock();
    }
}

#include <vector>

void do_unsafe()
{
    printf("Beginning unprotected run\n");
    std::vector<std::thread> threads;

    count = 0;

    for (int i = 0; i < nThreads; ++i) {
        threads.emplace_back(clock_in_a_lot);
    }

    for (auto &Thread : threads) {
        Thread.join();
    }

    printf("People checked in: %d, expected %d people\n",
            check_clock_safely(), nThreads * splitPersonalities);
}

void do_safe()
{
    printf("Beginning protected run\n");
    std::vector<std::thread> threads;

    count = 0;

    for (int i = 0; i < nThreads; ++i) {
        threads.emplace_back(clock_in_safely);
    }

    for (auto &Thread : threads) {
        Thread.join();
    }

    printf("People checked in: %d, expected %d people\n",
            check_clock_safely(), nThreads * splitPersonalities);
}

int main()
{
    do_unsafe();
    do_safe();

    return 0;
}


