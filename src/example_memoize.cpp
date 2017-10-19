#include "decorator.hpp"
#include "memoize.hpp"

#include <map>

#include <stdio.h>

int fact(int n)
{
    if (n == 0) {
        return 1;
    }
    return n * fact(n- 1);
}

int main()
{
    auto fact_memoized = memoize<Hashable<int(int)>>(fact);

    for (int i = 0; i < 20; ++i) {
        fact_memoized(i);
    }

    for (int i = 0; i < 20; ++i) {
        fact_memoized(i);
    }

    return 0;
}

