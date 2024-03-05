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
            evaluatedTokens_.emplace_back(std::move(expToken_));
        }

        // put the separator to evaluator also            
        expToken_.push_back(elmChar);
        auto pImmediateResult = pEvaluator_->putToken(expToken_);
        evaluatedTokens_.emplace_back(std::move(expToken_));
        if(pImmediateResult) {
            auto resultStr = prettyResult(*pImmediateResult);
            setImmediateResult(resultStr);
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
            deleteInput();
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

    void Calculator::deleteInput() {
        try {
            if(replayInputs()) return;
        }
        catch(...) {
            setImmediateResult("internal error");
        }
    }

    // replay inputs except last character
    bool Calculator::replayInputs() {
        if(expToken_.empty() && evaluatedTokens_.empty()) {
            return false;
        }
        
        std::string backupTmpToken = std::move(expToken_);
        if(backupTmpToken.empty()) {
            backupTmpToken = evaluatedTokens_.back();            
            evaluatedTokens_.pop_back();
        }
        std::list<std::string> backupTokens = std::move(evaluatedTokens_);
        reset();
        for(auto& token: backupTokens) {
            for(auto input : token) {
                expression_elm_input(input);
            }
        }
        backupTmpToken.pop_back();
        for(auto input : backupTmpToken) {
            expression_elm_input(input);
        }
        return true;
    }
}
