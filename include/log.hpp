#ifndef CAPTAL_DECORATORS_LOG_HPP
#define CAPTAL_DECORATORS_LOG_HPP

#include "decorator.hpp"

template <class> class Log;

template <class R, class ... Args>
class Log<R(Args...)> : public Decorator<R(Args...)> {
    public:
        Log(std::function<R(Args...)> f, std::function<void(R, Args...)> logfun)
            : Decorator<R(Args...)>([](){}, f, [](){}), logfun_(logfun) {}

        R operator() (Args... args)
        {
            auto retval = this->f_(args...);
            this->logfun_(retval, args...);
            return retval;
        }

    private:
        std::function<void(R, Args...)> logfun_;
};

// If you were going to use lambda expressions, you might as well just
// instantiate the Log directly.
template <class R, class ... Args>
Log<R(Args...)> log(R (*f)(Args...), void (*logfun)(R, Args...))
{
    return Log<R(Args...)>(f, logfun);
}

#endif

