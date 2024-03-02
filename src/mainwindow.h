#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calc_core/calculator.h"
#include "calc_core/calculator_view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public ICalculatorView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //////////////////////////////////////////////////////////////////////////
    /// ICalculatorView interfaces - START
    //////////////////////////////////////////////////////////////////////////
    void setResult(const std::string& resStr) override;
    void setHistory(const std::string& historyStr) override;
    //////////////////////////////////////////////////////////////////////////
    /// ICalculatorView interfaces - END
    //////////////////////////////////////////////////////////////////////////
private slots:


private:
    Ui::MainWindow *ui;
    Calculator* pCalculator;
};
#endif // MAINWINDOW_H
