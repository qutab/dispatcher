#include "Dispatcher.hpp"

#include <iostream>

void funcWithNoArg()
{
    std::cout << "funcWithNoArg" << std::endl;
}

void funcWithOneArg(int a)
{
    std::cout << "funcWithOneArg: " << a << std::endl;
}

class Handler
{
public:
    void handleWithOneArg(int a)
    {
        std::cout << "handleWithOneArg: " << a << std::endl;
    }

    void handleWithTwoArgs(int a, int b)
    {
        std::cout << "handleWithTwoArgs: " << a << b << std::endl;
    }
};
int main()
{
    // test code here
    enum class Status
    {
        START,
        STOP,
        EXIT
    };

    Dispatcher<Status> dispatcher;
    Handler handler;

    dispatcher.addHandler(Status::START, &funcWithNoArg);
    dispatcher.addHandler(Status::STOP, handler, &Handler::handleWithTwoArgs);
    dispatcher.addHandler(Status::EXIT, handler, &Handler::handleWithOneArg);

    dispatcher.dispatch(Status::START);
    dispatcher.dispatch(Status::STOP, 11, 21);
    dispatcher.dispatch(Status::EXIT, 22);

    return 0;
}
