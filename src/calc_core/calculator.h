#pragma once

#include "calc.h"
#include "calculator_view.h"
#include <string>

namespace calc {
    class Evaluator;

    class Calculator
    {
    private:
        Evaluator* pEvaluator_;
        ICalculatorView* pCalculatorView_ = nullptr;
        std::string expToken_;

        static std::string prettyResult(double value);
    public:
        Calculator(/* args */);
        ~Calculator();

        void expression_elm_input(char elmChar);
        void calculator_func_input(CalcFuncId functionId);

        void setView(ICalculatorView* pCalculatorView) {
            pCalculatorView_ = pCalculatorView;
        }
    };
}