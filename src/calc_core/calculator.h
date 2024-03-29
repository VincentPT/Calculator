#pragma once

#include "calc.h"
#include "calculator_view.h"
#include <string>
#include <list>
#include <stack>

namespace calc {
    class Evaluator;

    class Calculator
    {
    private:
        Evaluator* pEvaluator_;
        ICalculatorView* pCalculatorView_ = nullptr;
        std::string expToken_;
        std::string lastRes_;
        std::string immediateRes_;
        std::string temporaryMem_;
        std::list<std::string> evaluatedTokens_;
        std::stack<bool> deletableLists;

    private:
        static std::string prettyResult(double value);
        void updateHistory();
        void expression_token_input(char elmChar);
        void expression_operator_input(char elmChar);
        void setImmediateResult(const std::string& resStr);
        bool deleteTmpToken();
        bool deletePendingEvaluationInput();
    public:
        Calculator(/* args */);
        ~Calculator();

        void expression_elm_input(char elmChar);
        void calculator_func_input(CalcFuncId functionId);

        void setView(ICalculatorView* pCalculatorView) {
            pCalculatorView_ = pCalculatorView;
        }

        void eval();
        void reset();
        void deleteTempInput();
        void memorySet();
        void memoryRecorver();
        void clearDeletableList();
    };
}