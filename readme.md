# Decorator

A small decorator library targeting C++14, providing decorators for functions.

This library provides one class for client use: `Decorator`. `Decorator` has
the following interface:

```c++
Decorator<R(Args...)>(
        std::function<void()> before,
        std::function<R(Args...)> function,
        std::function<void()> after
        )
```
Constructs a decorator.

```c++
R operator() (Args...)
```

Invokes `function`. `before` is run once before `function` is executed, and
`after` is executed after `function` is executed.

&nbsp;

For ease of use, it is recommended that clients create their own factory
functions. For example, if there was a shared resource that should be
protected by a mutex, then, the following factory function may be useful:

```c++
template <class R, class ... Args>
Decorator<R(Args...)> atomic(R (*f)(Args...), std::mutex *mtx)
{
    return Decorator<R(Args...)>(
              [mtx]() { mtx->lock(); }
            , f
            , [mtx]() { mtx->unlock(); }
            );
}
```
