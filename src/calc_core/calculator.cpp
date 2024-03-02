#include "calculator.h"
#include "evaluator.h"

calculator::calculator(/* args */)
{
    pEvaluator = new evaluator();
}

calculator::~calculator()
{
    delete pEvaluator;
}

void calculator::expression_elm_input(ExpElmId id) {
    pEvaluator->process_input(id);
}

void calculator::calculator_func_input(CalcFuncId functionId) {

}
