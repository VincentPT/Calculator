#include "evaluator.h"
#include "funcs/functions.h"
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <memory>


///////////////////////////////////////////////////////////////////
/// function ids
///////////////////////////////////////////////////////////////////
#define FUNCTION_ID_ADD "+"
#define FUNCTION_ID_SUB "-"
#define FUNCTION_ID_MUL "*"
#define FUNCTION_ID_DIV "/"
#define FUNCTION_ID_NEGATIVE "__NEGATIVE__"
#define FUNCTION_ID_POSITIVE "__POSITIVE__"

#define IS_PRIORITY_HIGHER(func1, func2) ((func1)->priority() < (func2)->priority())

namespace calc {
    static std::map<std::string, std::unique_ptr<Functor>> functorDict_;

    bool isNumber(const std::string& s) {
        if(s.empty()) return false;

        auto it = s.begin();
        if(*it == '-' || *it == '+') {
            if(s.size() < 2) return false;

            it++;            
        }
        bool hasDot = false;

        auto start = it;
        for(; it != s.end(); ++it) {
            if(*it == '.') {
                if(hasDot) return false;      // dot should has only one
                if(start == it) return false; // dot is not allow to be first character
                hasDot = true;
            }
            else if(*it < '0' || *it > '9') {
                return false;
            }
        }

        return true;
    }

    void buildDictionary() {
        functorDict_[FUNCTION_ID_ADD] = std::make_unique<AdditiveFunctor>();
        functorDict_[FUNCTION_ID_SUB] = std::make_unique<SubstractiveFunctor>();
        functorDict_[FUNCTION_ID_MUL] = std::make_unique<MultiplicativeFunctor>();
        functorDict_[FUNCTION_ID_DIV] = std::make_unique<DivisiveFunctor>();
        functorDict_[FUNCTION_ID_NEGATIVE] = std::make_unique<NegativeFunctor>();
        functorDict_[FUNCTION_ID_POSITIVE] = std::make_unique<PositiveFunctor>();
    }

    Evaluator::Evaluator(/* args */)
    {
        if(functorDict_.size() == 0) {
            buildDictionary();
        }
    }

    Evaluator::~Evaluator()
    {
    }

    const double* Evaluator::putToken(const std::string& token) {
        if(token.empty()) {
            throw std::runtime_error("invalid token");
        }
        bool isNumericToken = isNumber(token);
        TokenType tokenType;
        if(isNumericToken) {
            tokenType = TokenType::Operand;
        }
        else {
            if(token[0] >= '0' && token[0] <= '9') {
                // functor is not allow leading by a digit
                throw std::runtime_error("invalid function");
            }
            tokenType = TokenType::Functor;
        }

        const double* imediateResult = nullptr;
        if(tokenType == TokenType::Functor) {
            imediateResult = putFunctor(token);
        }
        else {
            imediateResult = putOperand(token);
        }

        lastTokenType_ = tokenType;
        return imediateResult;
    }

    const double* Evaluator::putOperand(const std::string& token) {
        bool isNumericToken = isNumber(token);

        if(!isNumericToken) {
            throw std::runtime_error("token is not a number");
        }

        double operand = atof(token.c_str());
        excutionContext_.putOperand(operand);

        return nullptr;
    }

    const double* Evaluator::putFunctor(const std::string& token) {
        std::string tokenTmp;
        if(lastTokenType_ == TokenType::Functor) {
            if(token == "-") {
                tokenTmp = FUNCTION_ID_NEGATIVE;
            }
            else if(token == "+") {
                tokenTmp = FUNCTION_ID_POSITIVE;
            }
            else {
                tokenTmp = token;
            }
        }
        else {
            tokenTmp = token;
        }

        auto it = functorDict_.find(tokenTmp);
        if(it == functorDict_.end()) {
            throw std::runtime_error("invalid function");
        }

        const double* imediateResult = nullptr;
        auto currentFunctor = it->second.get();
        if(excutionContext_.functors() > 0) {
            // take away the top functor of the stack
            auto topInQueueFunctor = excutionContext_.popFunctor();

            // check priority of the top functor with current functor...
            if(IS_PRIORITY_HIGHER(currentFunctor, topInQueueFunctor)) {
                // ...no need to perform the top functor, then put it to the stack again
                excutionContext_.putFunctor(topInQueueFunctor);
            }
            else {
                // ...need to perform the top functor then just execute it
                // and it just has been removed from the stack
                excutionContext_.makeCurrent();
                topInQueueFunctor->execute();
                imediateResult = &excutionContext_.topOperand();
            }
        }
        // put the current functor to the stack
        excutionContext_.putFunctor(currentFunctor);
        return imediateResult;
    }

    double Evaluator::eval() {
        if(excutionContext_.operands() == 0) {
            throw std::runtime_error("empty expression");
        }

        excutionContext_.makeCurrent();
        while (excutionContext_.functors() > 0) {
            auto topInQueueFunctor = excutionContext_.popFunctor();
            topInQueueFunctor->execute();
        }
        if(excutionContext_.operands() > 1) {
            throw std::runtime_error("incompleted expression");
        }
        if(excutionContext_.operands() == 0) {
            throw std::runtime_error("not support slient function");
        }
        double finaResult = excutionContext_.popOperand();
        return finaResult;
    }

    bool Evaluator::isDirty() {
        return excutionContext_.operands() != 0;
    }

    void Evaluator::reset() {
        excutionContext_.reset();
        lastTokenType_ = TokenType::NotSet;
    }

    void Evaluator::popFunctor() {
        excutionContext_.popFunctor();
    }

    void Evaluator::popOperand() {
        excutionContext_.popOperand();
    }
}
