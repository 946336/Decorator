#include "decorator.hpp"
#include "memoize.hpp"

#include <map>

#include <stdio.h>

int fib(int n)
{
    if (n == 0) {
        return 1;
    }
    return n * fib(n- 1);
}

int main()
{
    auto fib_memoized = memoize<Hashable<int(int)>>(fib);

    for (int i = 0; i < 20; ++i) {
        fib_memoized(i);
    }

    for (int i = 0; i < 20; ++i) {
        fib_memoized(i);
    }

    return 0;
}

