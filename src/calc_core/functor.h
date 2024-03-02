#pragma once

namespace calc {
    //////////////////////////////////////////////////////////////////////////
    /// base class of all expression functions and operators
    /////////////////////////////////////////////////////////////////////////
    class Functor
    {
    private:
    public:
        Functor();
        virtual ~Functor();
        virtual void execute() = 0;
        virtual int priority() = 0;
    };
}