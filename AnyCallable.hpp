#pragma once

#include <any>
#include <functional>

template<typename Ret>
struct AnyCallable
{
    AnyCallable() = default;

    template<typename F>
    AnyCallable(F&& fun)
      : AnyCallable(std::function(fun))
    {
    }

    template<typename ... Args>
    AnyCallable(std::function<Ret(Args...)> fun)
      : anyM(fun)
    {
    }

    template<typename ... Args>
    Ret operator()(Args&& ... args)
    {
        return std::invoke(std::any_cast<std::function<Ret(Args...)>>(anyM), std::forward<Args>(args)...);
    }

    std::any anyM;
};

template<>
struct AnyCallable<void>
{
    AnyCallable() = default;

    template<typename F>
    AnyCallable(F&& fun)
      : AnyCallable(std::function(fun))
    {
    }

    template<typename ... Args>
    AnyCallable(std::function<void(Args...)> fun)
      : anyM(fun)
    {
    }

    template<typename ... Args>
    void operator()(Args&& ... args)
    {
        std::invoke(std::any_cast<std::function<void(Args...)>>(anyM), std::forward<Args>(args)...);
    }

    std::any anyM;
};
