#include "functions.h"
#include "../context.h"

//refer from http://en.cppreference.com/w/cpp/language/operator_precedence
#define FUNCTION_PRIORITY_FUNCTIONCALL		2	/* () */
#define FUNCTION_PRIORITY_UNARY_PREFIX		3	/*~, !, +, -, *, & */
#define FUNCTION_PRIORITY_USER_FUNCTION		4 /*sin, cos, sum, mid, ...*/
#define FUNCTION_PRIORITY_MULTIPLICATIVE	5 /* % */
#define FUNCTION_PRIORITY_ADDITIVE			6 /*+ -*/
#define FUNCTION_PRIORITY_SHIFT				7 /*<<   >>*/
#define FUNCTION_PRIORITY_BITWISE_AND		11 /* & */
#define FUNCTION_PRIORITY_BITWISE_XOR		12 /* ^ */
#define FUNCTION_PRIORITY_BITWISE_OR		13 /* | */
#define FUNCTION_PRIORITY_LOGICAL_AND		14 /* && */
#define FUNCTION_PRIORITY_LOGICAL_OR		15 /* || */


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
        return FUNCTION_PRIORITY_ADDITIVE;
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator -
    /////////////////////////////////////////////////////////////////////////
    SubstractiveFunctor::SubstractiveFunctor() {}
    SubstractiveFunctor::~SubstractiveFunctor() {}

    double SubstractiveFunctor::perform(double arg1, double arg2) {
        return arg1 - arg2;
    }

    int SubstractiveFunctor::priority() {
        return FUNCTION_PRIORITY_ADDITIVE;
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator *
    /////////////////////////////////////////////////////////////////////////
    MultiplicativeFunctor::MultiplicativeFunctor() {}
    MultiplicativeFunctor::~MultiplicativeFunctor() {}

    double MultiplicativeFunctor::perform(double arg1, double arg2) {
        return arg1 * arg2;
    }

    int MultiplicativeFunctor::priority() {
        return FUNCTION_PRIORITY_MULTIPLICATIVE;
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator /
    /////////////////////////////////////////////////////////////////////////
    DivisiveFunctor::DivisiveFunctor() {}
    DivisiveFunctor::~DivisiveFunctor() {}

    double DivisiveFunctor::perform(double arg1, double arg2) {
        return arg1 / arg2;
    }

    int DivisiveFunctor::priority() {
        return FUNCTION_PRIORITY_MULTIPLICATIVE;
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator - (negative)
    /////////////////////////////////////////////////////////////////////////
    NegativeFunctor::NegativeFunctor() {}
    NegativeFunctor::~NegativeFunctor() {}

    double NegativeFunctor::perform(double arg) {
        return -arg;
    }

    int NegativeFunctor::priority() {
        return FUNCTION_PRIORITY_UNARY_PREFIX;
    }

    //////////////////////////////////////////////////////////////////////////
    /// operator + (positive)
    /////////////////////////////////////////////////////////////////////////
    PositiveFunctor::PositiveFunctor() {}
    PositiveFunctor::~PositiveFunctor() {}

    double PositiveFunctor::perform(double arg) {
        return arg;
    }

    int PositiveFunctor::priority() {
        return FUNCTION_PRIORITY_UNARY_PREFIX;
    }
}