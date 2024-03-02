#include "calculator.h"
#include "evaluator.h"

Calculator::Calculator(/* args */)
{
    pEvaluator = new Evaluator();
}

Calculator::~Calculator()
{
    delete pEvaluator;
}

void Calculator::expression_elm_input(ExpElmId id) {
    pEvaluator->process_input(id);
}

void Calculator::calculator_func_input(CalcFuncId functionId) {

}
