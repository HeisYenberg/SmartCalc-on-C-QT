#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QLineEdit>
#include <QMainWindow>
#include <QString>

#include "credit.h"
#include "deposit.h"
#include "graph.h"

extern "C" {
#include "../backend/calculate.h"
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_buttonCredit_clicked();

  void on_buttonDeposit_clicked();

  void on_buttonGraph_clicked();

  void on_buttonEqual_clicked();

  void on_input_editingFinished();

  void on_buttonC_clicked();

  void on_buttonMod_clicked();

  void on_buttonPower_clicked();

  void on_buttonCos_clicked();

  void on_buttonAcos_clicked();

  void on_buttonLn_clicked();

  void on_buttonSin_clicked();

  void on_buttonAsin_clicked();

  void on_buttonLog_clicked();

  void on_buttonTan_clicked();

  void on_buttonAtan_clicked();

  void on_buttonSqrt_clicked();

  void on_buttonBracketOpen_clicked();

  void on_buttonBracketClose_clicked();

  void on_buttonDel_clicked();

  void on_buttonDivide_clicked();

  void on_button7_clicked();

  void on_button8_clicked();

  void on_button9_clicked();

  void on_buttonMultiply_clicked();

  void on_button4_clicked();

  void on_button5_clicked();

  void on_button6_clicked();

  void on_buttonSubstruct_clicked();

  void on_button1_clicked();

  void on_button2_clicked();

  void on_button3_clicked();

  void on_buttonAdd_clicked();

  void on_buttonX_clicked();

  void on_button0_clicked();

  void on_buttonDot_clicked();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
