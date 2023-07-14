#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  this->setWindowTitle("Deposit Calculator");
  ui->doubleSpinBox->setMaximum(9999999999999);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
}

Deposit::~Deposit() { delete ui; }
