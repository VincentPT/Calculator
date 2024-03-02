#include "calculator.h"
#include "evaluator.h"
#include <algorithm>

namespace calc {
    Calculator::Calculator(/* args */)
    {
        pEvaluator_ = new Evaluator();
    }

    Calculator::~Calculator()
    {
        delete pEvaluator_;
    }

    std::string Calculator::prettyResult(double value) {
        auto numberInStr = std::to_string(value);
        auto dotPos = numberInStr.find('.');
        if(dotPos != std::string::npos) {
            auto it = numberInStr.begin();
            bool res = std::all_of(it + dotPos + 1, numberInStr.end(), [](char c){
                return c == '0';
            });

            if(res) {
                return numberInStr.substr(0, dotPos);
            }
        }
        return numberInStr;
    }

    void Calculator::expression_elm_input(char elmChar) {
        try {
            if ((elmChar >= '0' &&  elmChar <= '9') || 
                (elmChar >= 'A' &&  elmChar <= 'Z') ||
                (elmChar >= 'a' &&  elmChar <= 'z') ||
                elmChar == '.'
            ) {
                // collect expression token
                expToken_.push_back(elmChar);
                if(pCalculatorView_) {
                    pCalculatorView_->setResult(expToken_);
                }
            }
            else {
                // separator detected => put the token to evaluator
                if(!expToken_.empty()) {
                    pEvaluator_->putToken(expToken_);
                    evaluatedTokens_.emplace_back(std::move(expToken_));
                }

                // put the separator to evaluator also            
                expToken_.push_back(elmChar);
                auto pImmediateResult = pEvaluator_->putToken(expToken_);
                evaluatedTokens_.emplace_back(std::move(expToken_));
                if(pCalculatorView_) {
                    if(pImmediateResult) {
                        auto resultStr = prettyResult(*pImmediateResult);
                        pCalculatorView_->setResult(resultStr);
                    }
                }
            }
        }
        catch (const std::exception& e) {
            if(pCalculatorView_) {
                pCalculatorView_->setResult(e.what());
            }
        }
    }

    void Calculator::calculator_func_input(CalcFuncId functionId) {
        if(functionId == CalcFuncId::Eval) {
            if(!expToken_.empty()) {
                pEvaluator_->putToken(expToken_);
                evaluatedTokens_.emplace_back(std::move(expToken_));
            }
            auto finalRes = pEvaluator_->eval();
            if(pCalculatorView_) {
                auto resultStr = prettyResult(finalRes);
                pCalculatorView_->setResult(resultStr);
            }
        }
    }
}
