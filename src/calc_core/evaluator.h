#pragma once

#include "eval.h"
#include "context.h"
#include <string>

namespace calc {

    enum class TokenType {
        NotSet,
        Operand,
        Functor
    };

    class Evaluator
    {
    private:
        TokenType lastTokenType_ = TokenType::NotSet;
        Context excutionContext_;
        bool justPerformEval_ = true;
    private:
        const double* putOperand(const std::string& token);
        const double* putFunctor(const std::string& token);
    public:
        Evaluator(/* args */);
        ~Evaluator();

        const double* putToken(const std::string& token);
        double eval();
    };
}