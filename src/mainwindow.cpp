#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pCalculator = new calc::Calculator();

    connect(ui->btn_del, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(calc::CalcFuncId::Del); });
    connect(ui->btn_ac, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(calc::CalcFuncId::AC); });
    connect(ui->btn_ms, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(calc::CalcFuncId::MS); });
    connect(ui->btn_mr, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(calc::CalcFuncId::MR); });
    connect(ui->btn_eval, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(calc::CalcFuncId::Eval); });

    connect(ui->btn_op_0, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('0'); });
    connect(ui->btn_op_1, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('1'); });
    connect(ui->btn_op_2, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('2'); });
    connect(ui->btn_op_3, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('3'); });
    connect(ui->btn_op_4, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('4'); });
    connect(ui->btn_op_5, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('5'); });
    connect(ui->btn_op_6, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('6'); });
    connect(ui->btn_op_7, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('7'); });
    connect(ui->btn_op_8, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('8'); });
    connect(ui->btn_op_9, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('9'); });
    connect(ui->btn_op_dot, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('.'); });

    connect(ui->btn_fn_div, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('/'); });
    connect(ui->btn_fn_mul, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('*'); });
    connect(ui->btn_fn_sub, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('-'); });
    connect(ui->btn_fn_add, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input('+'); });

    ui->tbRes->setAlignment(Qt::AlignRight);
    ui->tbHistory->setAlignment(Qt::AlignRight);

    pCalculator->setView(this);
}

MainWindow::~MainWindow()
{
    delete pCalculator;
    delete ui;    
}

//////////////////////////////////////////////////////////////////////////
/// ICalculatorView interfaces - START
//////////////////////////////////////////////////////////////////////////
void MainWindow::setResult(const std::string& resStr) {
    ui->tbRes->setText(QString::fromStdString(resStr));
    ui->tbRes->setAlignment(Qt::AlignRight);
}

void MainWindow::setHistory(const std::string& historyStr) {
    ui->tbHistory->setText(QString::fromStdString(historyStr));
    ui->tbHistory->setAlignment(Qt::AlignRight);
}
//////////////////////////////////////////////////////////////////////////
/// ICalculatorView interfaces - END
//////////////////////////////////////////////////////////////////////////
