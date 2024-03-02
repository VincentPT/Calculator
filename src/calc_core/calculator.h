#pragma once

#include "calc.h"
#include "calculator_view.h"

class Evaluator;

class Calculator
{
private:
    Evaluator* pEvaluator_;
    ICalculatorView* pCalculatorView_ = nullptr;
public:
    Calculator(/* args */);
    ~Calculator();

    void expression_elm_input(ExpElmId id);
    void calculator_func_input(CalcFuncId functionId);

    void setView(ICalculatorView* pCalculatorView) {
        pCalculatorView_ = pCalculatorView;
    }
};