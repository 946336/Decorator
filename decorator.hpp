#ifndef CAPTAL_GEN_DECORATOR_HPP
#define CAPTAL_GEN_DECORATOR_HPP

#include <functional>

template <class> class Decorator;

template <class R, class ...Args>
class Decorator<R(Args...)> {
    private:
        // RAII guarantees that the destructor will run if an exception is
        // thrown.
        struct Context_Manager {
            using Op = std::function<void()>;
            Context_Manager(Op on_enter, Op on_leave)
                : on_enter_(on_enter), on_leave_(on_leave)
            {
                on_enter_();
            }

            ~Context_Manager()
            {
                on_leave_();
            }

            Op on_enter_;
            Op on_leave_;
        };

    public:
        Decorator(
                std::function<void()> before,
                std::function<R(Args...)> f,
                std::function<void()> after
                )
            : before_(before), f_(f), after_(after) {}

        R operator() (Args... args)
        {
            Context_Manager mgr(before_, after_);
            return f_(args...);
        }

    protected:
        std::function<void()> before_;
        std::function<R(Args...)> f_;
        std::function<void()> after_;
};

#endif

