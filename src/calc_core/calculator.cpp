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
                if(!lastRes_.empty()) {
                    // clear last result if user input first operand of the expression
                    lastRes_.clear();
                }
                // collect expression token
                expToken_.push_back(elmChar);
                if(pCalculatorView_) {
                    pCalculatorView_->setResult(expToken_);
                }
                updateHistory();
            }
            else {
                if(!lastRes_.empty()) {
                    // if there is last result, consider it an the first operand of the expression
                    expToken_ = lastRes_;
                    lastRes_.clear();
                }
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
                updateHistory();
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
            if(!pEvaluator_->isDirty()) return;

            if(!expToken_.empty()) {
                pEvaluator_->putToken(expToken_);
                evaluatedTokens_.emplace_back(std::move(expToken_));
            }
            auto finalRes = pEvaluator_->eval();
            lastRes_ = prettyResult(finalRes);
            if(pCalculatorView_) {
                pCalculatorView_->setResult(lastRes_);
            }

            evaluatedTokens_.clear();
            updateHistory();
        }
    }

    void Calculator::updateHistory() {
        if(!pCalculatorView_) return;

        std::string history;
        for(auto token : evaluatedTokens_) {
            history.append(token);
        }

        history.append(expToken_);
        pCalculatorView_->setHistory(history);
    }
}
