#pragma once
#include "functor.h"

namespace calc {
    constexpr int stack_size = 256;
    class Context
    {
    private:
        double operandStack_[stack_size];
        int osp_ = -1; // operand stack pointer

        Functor* funcStack_[stack_size];
        int fsp_ = -1; // functor stack pointer
    public:
        Context(/* args */);
        ~Context();

        void makeCurrent();
        static Context* current();

        double popOperand();
        void putOperand(double operand);
        int operands() const { return osp_ + 1;}
        const double& topOperand() const;

        void putFunctor(Functor* pFunc);
        Functor* popFunctor();
        Functor* topFunctor() const;
        int functors() const { return fsp_ + 1;}
    };
}