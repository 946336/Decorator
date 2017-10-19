
#include "decorator.hpp"
#include "log.hpp"

#include <iostream>

bool divisibleBy(int dividend, int divisor)
{
    return dividend % divisor == 0;
}

void logfun(bool isDivisible, int dividend, int divisor)
{
    std::cout << dividend << (isDivisible ? " is" : " is not")
              << " divisible by " << divisor << std::endl;
}

int main()
{
    auto stateDivisibility = log(divisibleBy, logfun);

    for (int dividends = 0; dividends <= 10; ++dividends) {
        for (int divisors = 1; divisors <= dividends; ++divisors) {
            stateDivisibility(dividends, divisors);
        }
    }

    return 0;
}

