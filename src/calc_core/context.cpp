#include "context.h"
#include <stdexcept>

namespace calc {

    // change to thread specific data to run multiple expression at the same time
    // now it is only support 1 expression excution at a time
    static Context* gCurrentContext = nullptr;

    Context::Context() {
        if(gCurrentContext == nullptr) {
            gCurrentContext = this;
        }
    }

    Context::~Context() {
        if(gCurrentContext == this) {
            gCurrentContext = nullptr;
        }
    }

    void Context::makeCurrent() {
        gCurrentContext = this;
    }

    Context* Context::current() {
        return gCurrentContext;
    }

    double Context::popOperand() {
        if(osp_ < 0) {
            throw std::runtime_error("invalid stack operation");
        }
        return operandStack_[osp_--];
    }

    void Context::putOperand(double operand) {
        if(osp_ >= stack_size) {
            throw std::runtime_error("stack overflow");
        }
        operandStack_[++osp_] = operand;
    }

    const double& Context::topOperand() const {
        if(osp_ < 0) {
            throw std::runtime_error("invalid stack operation");
        }
        return operandStack_[osp_];
    }

    void Context::putFunctor(Functor* pFunc) {   
        if(fsp_ >= stack_size) {
            throw std::runtime_error("stack overflow");
        }
        funcStack_[++fsp_] = pFunc;
    }

    Functor* Context::popFunctor() {
        if(fsp_ < 0) {
            throw std::runtime_error("invalid stack operation");
        }
        return funcStack_[fsp_--]; 
    }

    Functor* Context::topFunctor() const {
        if(fsp_ < 0) {
            throw std::runtime_error("invalid stack operation");
        }
        return funcStack_[fsp_]; 
    }
}