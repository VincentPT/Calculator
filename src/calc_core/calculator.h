#pragma once

#include "calc.h"
#include "calculator_view.h"
#include <string>
#include <list>

namespace calc {
    class Evaluator;

    class Calculator
    {
    private:
        Evaluator* pEvaluator_;
        ICalculatorView* pCalculatorView_ = nullptr;
        std::string expToken_;
        std::string lastRes_;
        std::list<std::string> evaluatedTokens_;

    private:
        static std::string prettyResult(double value);
        void updateHistory();

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
    };
}