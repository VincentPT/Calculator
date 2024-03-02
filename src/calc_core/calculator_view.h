#pragma once

#include <string>
namespace calc {
    class ICalculatorView
    {
    private:
        /* data */
    public:
        ICalculatorView();
        virtual ~ICalculatorView();

        virtual void setResult(const std::string& resStr) = 0;
        virtual void setHistory(const std::string& historyStr) = 0;
    };
}