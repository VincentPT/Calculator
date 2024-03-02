#pragma once

#include "calc.h"

class Evaluator;

class Calculator
{
private:
    Evaluator* pEvaluator;
public:
    Calculator(/* args */);
    ~Calculator();

    void expression_elm_input(ExpElmId id);
    void calculator_func_input(CalcFuncId functionId);
};