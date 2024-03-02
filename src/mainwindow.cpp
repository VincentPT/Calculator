#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pCalculator = new Calculator();

    connect(ui->btn_del, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(CalcFuncId::Del); });
    connect(ui->btn_ac, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(CalcFuncId::AC); });
    connect(ui->btn_ms, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(CalcFuncId::MS); });
    connect(ui->btn_mr, &QPushButton::clicked, this,[this](){ pCalculator->calculator_func_input(CalcFuncId::MR); });

    connect(ui->btn_op_0, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_0); });
    connect(ui->btn_op_1, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_1); });
    connect(ui->btn_op_2, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_2); });
    connect(ui->btn_op_3, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_3); });
    connect(ui->btn_op_4, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_4); });
    connect(ui->btn_op_5, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_5); });
    connect(ui->btn_op_6, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_6); });
    connect(ui->btn_op_7, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_7); });
    connect(ui->btn_op_8, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_8); });
    connect(ui->btn_op_9, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Ditgit_9); });
    connect(ui->btn_op_dot, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Dot); });

    connect(ui->btn_fn_div, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Div); });
    connect(ui->btn_fn_mul, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Mul); });
    connect(ui->btn_fn_sub, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Sub); });
    connect(ui->btn_fn_add, &QPushButton::clicked, this,[this](){ pCalculator->expression_elm_input(ExpElmId::Add); });

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
}

void MainWindow::setHistory(const std::string& historyStr) {
    ui->tbHistory->setText(QString::fromStdString(historyStr));
}
//////////////////////////////////////////////////////////////////////////
/// ICalculatorView interfaces - END
//////////////////////////////////////////////////////////////////////////