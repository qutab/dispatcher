#pragma once

#include "AnyCallable.hpp"

#include <cassert>
#include <functional>
#include <map>
#include <tuple>

template <typename Type>
class Dispatcher
{
public:
    Dispatcher() = default;
    virtual ~Dispatcher() = default;

    template <typename HandlerFunc>
    void addHandler(Type typeP, HandlerFunc&& funcP)
    {
        handlerMapM.emplace(typeP, std::forward<HandlerFunc>(funcP));
    }

    template <typename Handler, typename ...Params>
    void addHandler(Type typeP, Handler& rHandlerP, void (Handler::*funcP)(Params...))
    {
        Handler* pHandlerP = &rHandlerP;
        auto lambda =
            [=](Params... pars)
            {
                (pHandlerP->*funcP)(pars...);
            };

        handlerMapM.emplace(typeP, lambda);
    }

    template <typename ...Args>
    void dispatch(Type typeP, Args&&... argsP)
    {
        auto it = handlerMapM.find(typeP);
        assert(it != handlerMapM.end());
        it->second(std::forward<Args>(argsP)...);
    }

private:
    std::map<Type, AnyCallable<void>> handlerMapM;
};
