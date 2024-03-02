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
    try {
        pEvaluator_->process_input(id);
    }
    catch (const std::exception& e) {
        if(pCalculatorView_) {
            pCalculatorView_->setResult(e.what());
        }
    }
}

void Calculator::calculator_func_input(CalcFuncId functionId) {

}
