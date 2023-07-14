#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("SmartCalc");
  ui->input->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  ui->output->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_buttonCredit_clicked() {
  Credit *newWindow = new Credit;
  newWindow->setAttribute(Qt::WA_DeleteOnClose);
  newWindow->show();
}

void MainWindow::on_buttonDeposit_clicked() {
  Deposit *newWindow = new Deposit;
  newWindow->setAttribute(Qt::WA_DeleteOnClose);
  newWindow->show();
}

void MainWindow::on_buttonGraph_clicked() {
  Graph *newWindow = new Graph();
  newWindow->setExpression(ui->input->text());
  newWindow->setAttribute(Qt::WA_DeleteOnClose);
  newWindow->show();
}

void MainWindow::on_buttonEqual_clicked() {
  QString input = ui->input->text();
  QByteArray byteArray = input.toLocal8Bit();
  char *expression = byteArray.data();
  double result = 0;
  int status = smart_calc(expression, 0, &result);
  if (!status) {
    ui->output->setText(QString::number(result, 'g', 15));
  } else if (status == INCORRECT_EXPRESSION) {
    ui->output->setText("INCORRECT EXPRESSION");
  } else if (status == CALCULATION_ERROR) {
    ui->output->setText("CALCULATION ERROR");
  } else if (status == DIVISION_BY_ZERO) {
    ui->output->setText("DIVISION BY ZERO");
  }
}

void MainWindow::on_input_editingFinished() { on_buttonEqual_clicked(); }

void MainWindow::on_buttonC_clicked() {
  ui->input->clear();
  ui->output->setText("0");
}

void MainWindow::on_buttonMod_clicked() {
  QString append = ui->input->text();
  append.append("mod");
  ui->input->setText(append);
}

void MainWindow::on_buttonPower_clicked() {
  QString append = ui->input->text();
  append.append("^");
  ui->input->setText(append);
}

void MainWindow::on_buttonCos_clicked() {
  QString append = ui->input->text();
  append.append("cos(");
  ui->input->setText(append);
}

void MainWindow::on_buttonAcos_clicked() {
  QString append = ui->input->text();
  append.append("acos(");
  ui->input->setText(append);
}

void MainWindow::on_buttonLn_clicked() {
  QString append = ui->input->text();
  append.append("ln(");
  ui->input->setText(append);
}

void MainWindow::on_buttonSin_clicked() {
  QString append = ui->input->text();
  append.append("sin(");
  ui->input->setText(append);
}

void MainWindow::on_buttonAsin_clicked() {
  QString append = ui->input->text();
  append.append("asin(");
  ui->input->setText(append);
}

void MainWindow::on_buttonLog_clicked() {
  QString append = ui->input->text();
  append.append("log(");
  ui->input->setText(append);
}

void MainWindow::on_buttonTan_clicked() {
  QString append = ui->input->text();
  append.append("tan(");
  ui->input->setText(append);
}

void MainWindow::on_buttonAtan_clicked() {
  QString append = ui->input->text();
  append.append("atan(");
  ui->input->setText(append);
}

void MainWindow::on_buttonSqrt_clicked() {
  QString append = ui->input->text();
  append.append("sqrt(");
  ui->input->setText(append);
}

void MainWindow::on_buttonBracketOpen_clicked() {
  QString append = ui->input->text();
  append.append("(");
  ui->input->setText(append);
}

void MainWindow::on_buttonBracketClose_clicked() {
  QString append = ui->input->text();
  append.append(")");
  ui->input->setText(append);
}

void MainWindow::on_buttonDel_clicked() {
  QString append = ui->input->text();
  append.chop(1);
  ui->input->setText(append);
}

void MainWindow::on_buttonDivide_clicked() {
  QString append = ui->input->text();
  append.append("/");
  ui->input->setText(append);
}

void MainWindow::on_button7_clicked() {
  QString append = ui->input->text();
  append.append("7");
  ui->input->setText(append);
}

void MainWindow::on_button8_clicked() {
  QString append = ui->input->text();
  append.append("8");
  ui->input->setText(append);
}

void MainWindow::on_button9_clicked() {
  QString append = ui->input->text();
  append.append("9");
  ui->input->setText(append);
}

void MainWindow::on_buttonMultiply_clicked() {
  QString append = ui->input->text();
  append.append("*");
  ui->input->setText(append);
}

void MainWindow::on_button4_clicked() {
  QString append = ui->input->text();
  append.append("4");
  ui->input->setText(append);
}

void MainWindow::on_button5_clicked() {
  QString append = ui->input->text();
  append.append("5");
  ui->input->setText(append);
}

void MainWindow::on_button6_clicked() {
  QString append = ui->input->text();
  append.append("6");
  ui->input->setText(append);
}

void MainWindow::on_buttonSubstruct_clicked() {
  QString append = ui->input->text();
  append.append("-");
  ui->input->setText(append);
}

void MainWindow::on_button1_clicked() {
  QString append = ui->input->text();
  append.append("1");
  ui->input->setText(append);
}

void MainWindow::on_button2_clicked() {
  QString append = ui->input->text();
  append.append("2");
  ui->input->setText(append);
}

void MainWindow::on_button3_clicked() {
  QString append = ui->input->text();
  append.append("3");
  ui->input->setText(append);
}

void MainWindow::on_buttonAdd_clicked() {
  QString append = ui->input->text();
  append.append("+");
  ui->input->setText(append);
}

void MainWindow::on_buttonX_clicked() {
  QString append = ui->input->text();
  append.append("x");
  ui->input->setText(append);
}

void MainWindow::on_button0_clicked() {
  QString append = ui->input->text();
  append.append("0");
  ui->input->setText(append);
}

void MainWindow::on_buttonDot_clicked() {
  QString append = ui->input->text();
  append.append(".");
  ui->input->setText(append);
}
