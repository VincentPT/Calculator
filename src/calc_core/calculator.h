#pragma once

#include "calc.h"

class evaluator;

class calculator
{
private:
    evaluator* pEvaluator;
public:
    calculator(/* args */);
    ~calculator();

    void expression_elm_input(ExpElmId id);
    void calculator_func_input(CalcFuncId functionId);
};