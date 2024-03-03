#include "calculator.h"
#include "evaluator.h"

namespace calc {
    extern bool isNumber(const std::string& s);

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
        auto lastNotZero = numberInStr.find_last_not_of('0');
        if(lastNotZero > dotPos) {
            return numberInStr.substr(0, lastNotZero + 1);
        }
        if(lastNotZero == dotPos) {
            return numberInStr.substr(0, dotPos);
        }
        return numberInStr;
    }

    void Calculator::expression_token_input(char elmChar) {
        if(!lastRes_.empty()) {
            // clear last result if user input first operand of the expression
            lastRes_.clear();
        }
        // collect expression token
        expToken_.push_back(elmChar);
        setImmediateResult(expToken_);
    }

    void Calculator::expression_operator_input(char elmChar) {
        if(!lastRes_.empty()) {
            // if there is last result, consider it an the first operand of the expression
            expToken_ = lastRes_;
            lastRes_.clear();
        }
        // separator detected => put the token to evaluator
        if(!expToken_.empty()) {
            pEvaluator_->putToken(expToken_);
            if(isNumber(expToken_)) {
                // an operand is always does not trigger evaluation process. So, it keeps the expression undoable
                deletableLists.push(false); // mark the operand canbe deleted
            }

            evaluatedTokens_.emplace_back(std::move(expToken_));
        }

        // put the separator to evaluator also            
        expToken_.push_back(elmChar);
        auto pImmediateResult = pEvaluator_->putToken(expToken_);
        evaluatedTokens_.emplace_back(std::move(expToken_));
        if(pImmediateResult) {
            auto resultStr = prettyResult(*pImmediateResult);
            setImmediateResult(resultStr);
            // an operator triggers evaluation process make the expression non undoable
            clearDeletableList();
        }
        else {
            // an operator does not trigger evaluation process keep the expression undoable
            deletableLists.push(true); // mark the functor canbe deleted
        }
    }

    void Calculator::expression_elm_input(char elmChar) {
        try {
            if ((elmChar >= '0' &&  elmChar <= '9') || 
                (elmChar >= 'A' &&  elmChar <= 'Z') ||
                (elmChar >= 'a' &&  elmChar <= 'z') ||
                elmChar == '.'
            ) {
                expression_token_input(elmChar);
            }
            else {
                expression_operator_input(elmChar);                
            }
            updateHistory();
        }
        catch (const std::exception& e) {
            setImmediateResult(e.what());
        }
    }

    void Calculator::calculator_func_input(CalcFuncId functionId) {
        switch (functionId)
        {
        case CalcFuncId::Eval:
            eval();
            break;
        case CalcFuncId::AC:
            reset();
            break;
        case CalcFuncId::MS:
            memorySet();
            break;
        case CalcFuncId::MR:
            memoryRecorver();
            break;
        case CalcFuncId::Del:
            deleteTempInput();
            break;
        default:
            break;
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

    void Calculator::setImmediateResult(const std::string& resStr) {
        immediateRes_ = resStr;
        if(pCalculatorView_) {
            pCalculatorView_->setResult(resStr);
        }
    }

    void Calculator::eval() {
        if(!pEvaluator_->isDirty()) return;

        if(!expToken_.empty()) {
            pEvaluator_->putToken(expToken_);
            evaluatedTokens_.emplace_back(std::move(expToken_));
        }
        try {
            auto finalRes = pEvaluator_->eval();
            lastRes_ = prettyResult(finalRes);
            setImmediateResult(lastRes_);
        }
        catch (const std::exception& e) {
            setImmediateResult(e.what());
        }
        // evaluated expression cannot be undo
        clearDeletableList();
        evaluatedTokens_.clear();
        updateHistory();
    }

    void Calculator::reset() {
        lastRes_ = "0";
        expToken_.clear();
        evaluatedTokens_.clear();
        pEvaluator_->reset();
        setImmediateResult(lastRes_);
        updateHistory();
    }

    void Calculator::memorySet() {
        if(isNumber(immediateRes_)) {
            temporaryMem_ = immediateRes_;
        }
    }

    void Calculator::memoryRecorver() {
        if(!temporaryMem_.empty()) {
            setImmediateResult(temporaryMem_);
            expToken_ = temporaryMem_;
            lastRes_ = temporaryMem_;
            updateHistory();
        }
    }

    void Calculator::deleteTempInput() {
        if(deleteTmpToken()) return;

        deletePendingEvaluationInput();
    }

    bool Calculator::deleteTmpToken() {
        if(expToken_.empty()) {
            return false;
        }
        expToken_.pop_back();
        if(expToken_.empty()) {
            if(evaluatedTokens_.empty()) {
                reset();
            }
            else {
                // don't let the result in caculator show empty
                // it should be a latest number token
                for(auto it = evaluatedTokens_.rbegin(); it != evaluatedTokens_.rend(); it++) {
                    if(isNumber(*it)) {
                        setImmediateResult(*it);
                        updateHistory();
                        break; 
                    }
                }
            }
        }
        else {
            setImmediateResult(expToken_);
            updateHistory();
        }
        return true;
    }

    bool Calculator::deletePendingEvaluationInput() {
        if(!deletableLists.size()) {
            return false;
        }

        bool shouldDeleteFunctor = deletableLists.top();
        deletableLists.pop();

        if(shouldDeleteFunctor) {
            pEvaluator_->popFunctor();
            evaluatedTokens_.pop_back();
            expToken_.clear();

            // check if the last token...
            if(evaluatedTokens_.size()) {
                // ...if not, then if the previous token is a number...
                if(isNumber(evaluatedTokens_.back())) {
                    // ...then consider it and a temporary token
                    // and pop the related data for it
                    deletableLists.pop();
                    pEvaluator_->popOperand();
                    expToken_ = evaluatedTokens_.back();
                    evaluatedTokens_.pop_back();
                }
            }
            else {
                // ...then reset the caculato
                reset();
            }
        }
        else {
            pEvaluator_->popOperand();
            expToken_ = evaluatedTokens_.back();
            evaluatedTokens_.pop_back();

            // call to delete character in expToken_
            deleteTmpToken();
        }
        updateHistory();

        return true;
    }

    void Calculator::clearDeletableList() {
        while(deletableLists.size()) {
            deletableLists.pop();
        }
    }
}
