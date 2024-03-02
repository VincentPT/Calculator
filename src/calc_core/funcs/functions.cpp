#include "functions.h"
#include "../context.h"

namespace calc {
    //////////////////////////////////////////////////////////////////////////
    /// base class of functions and operators have only one parameter
    /////////////////////////////////////////////////////////////////////////
    UnaryFunctor::UnaryFunctor() {}
    UnaryFunctor::~UnaryFunctor() {}
    void UnaryFunctor::execute() {
        auto ctx = Context::current();
        auto arg = ctx->popOperand();
        auto res = perform(arg);
        ctx->putOperand(res);
    }

    //////////////////////////////////////////////////////////////////////////
    /// base class of functions and operators have two parameters
    /////////////////////////////////////////////////////////////////////////
    BinaryFunctor::BinaryFunctor() {}
    BinaryFunctor::~BinaryFunctor() {}
    void BinaryFunctor::execute() {
        auto ctx = Context::current();
        auto arg2 = ctx->popOperand();
        auto arg1 = ctx->popOperand();
        auto res = perform(arg1, arg2);
        ctx->putOperand(res);
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator +
    /////////////////////////////////////////////////////////////////////////
    AdditiveFunctor::AdditiveFunctor() {}
    AdditiveFunctor::~AdditiveFunctor() {}

    double AdditiveFunctor::perform(double arg1, double arg2) {
        return arg1 + arg2;
    }

    int AdditiveFunctor::priority() {
        return 5;
    }
}