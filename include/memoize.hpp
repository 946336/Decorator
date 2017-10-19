#ifndef CAPTAL_DECORATORS_MEMOIZE_HPP
#define CAPTAL_DECORATORS_MEMOIZE_HPP

#include "decorator.hpp"

#include <utility>

#include <map>
#include <unordered_map>

// ==========================================================================
// Container for hashables
// ==========================================================================

template <class R, class ... Args> class Hashable;

template <class R, class ... Args>
class Hashable<R(Args...)> {
    public:
        Hashable() {}
        ~Hashable() {}

        using Memo = std::map<std::tuple<Args...>, R>;

        typename Memo::iterator find(std::tuple<Args...> args)
        {
            return this->memo_.find(args);
        }

        R& operator[](std::tuple<Args...> args)
        {
            return memo_[args];
        }

    private:
        Memo memo_;

};

// ==========================================================================
// Container for comparables
// ==========================================================================

template <class> class Comparable;

template <class R, class ... Args>
class Comparable<R(Args...)> {
    public:
        Comparable() {}
        ~Comparable() {}

        using Memo = std::unordered_map<std::tuple<Args...>, R>;

        typename Memo::iterator find(std::tuple<Args...> args)
        {
            return this->memo_.find(args);
        }

        R& operator[](std::tuple<Args...> args)
        {
            return memo_[args];
        }

    private:
        Memo memo_;

};

// ==========================================================================
// Memoizer
// ==========================================================================

template <class, class> class Memoize;

template <class Associative, class R, class ... Args>
class Memoize<R(Args...), Associative> : public Decorator<R(Args...)> {
    protected:
        std::map<std::tuple<Args...>, R> memo_;

    public:
        Memoize(std::function<R(Args...)> f) : Decorator<R(Args...)>([](){}, f, [](){}) {}

        R operator() (Args ...args)
        {
            typename Decorator<R(Args...)>::Context_Manager
                mgr(this->before_, this->after_);

            auto it = memo_.find(std::make_tuple(args...));
            if (it != memo_.end()) {
#ifdef DEBUG
                printf("Memoized result found\n");
#endif
                return it->second;
            } else {
#ifdef DEBUG
                printf("Memoized result not found\n");
#endif
                R retval;
                memo_[std::make_tuple(args...)] = retval = this->f_(args...);
                return retval;
            }
        }
};

// Factory function
template <class Associative, class R, class ... Args>
Memoize<R(Args...), Associative> memoize(R (*f)(Args...))
{
    return Memoize<R(Args...), Associative>(f);
}

#endif

