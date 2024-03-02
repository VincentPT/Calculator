#include "calculator.h"
#include "evaluator.h"

Calculator::Calculator(/* args */)
{
    pEvaluator_ = new Evaluator();
}

Calculator::~Calculator()
{
    delete pEvaluator_;
}

void Calculator::expression_elm_input(ExpElmId id) {
    pEvaluator_->process_input(id);

    if(pCalculatorView_) {
        pCalculatorView_->setResult("Set OK");
    }
}

void Calculator::calculator_func_input(CalcFuncId functionId) {

}
