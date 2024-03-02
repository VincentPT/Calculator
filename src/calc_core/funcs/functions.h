#pragma once
#include "../functor.h"

namespace calc {
    //////////////////////////////////////////////////////////////////////////
    /// base class of functions and operators have only one parameter
    /////////////////////////////////////////////////////////////////////////
    class UnaryFunctor : public Functor
    {
    private:
    public:
        UnaryFunctor();
        virtual ~UnaryFunctor();
        void execute() override;
        virtual double perform(double arg) = 0;
    };

    //////////////////////////////////////////////////////////////////////////
    /// base class of functions and operators have two parameters
    /////////////////////////////////////////////////////////////////////////
    class BinaryFunctor : public Functor
    {
    private:
    public:
        BinaryFunctor();
        virtual ~BinaryFunctor();
        void execute() override;
        virtual double perform(double arg1, double arg2) = 0;
    };

    //////////////////////////////////////////////////////////////////////////
    /// operator +
    /////////////////////////////////////////////////////////////////////////
    class AdditiveFunctor : public BinaryFunctor
    {
    private:
    public:
        AdditiveFunctor();
        virtual ~AdditiveFunctor();
        double perform(double arg1, double arg2) override;
        int priority() override;
    };
}
