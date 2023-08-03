#include "deposit.h"

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  this->setWindowTitle("Deposit Calculator");
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_replenishmentAddButton_clicked() {
  double amount = ui->replenishmentAmount->value();
  int mounth = ui->replenishmentMonth->value();
  if (amount && mounth) {
    data.replenishment[mounth] += amount;
    QString item = QString::number(mounth, 'd', 0) + ") " +
                   QString::number(amount, 'f', 2);
    ui->replenishmentList->insertItem(ui->replenishmentMonth->value(), item);
  }
}

void Deposit::on_withdrawalsAddButton_clicked() {
  double amount = ui->withdrawalAmount->value();
  int mounth = ui->withdrawalMonth->value();
  if (amount && mounth) {
    data.withdrawals[mounth] += amount;
    QString item = QString::number(mounth, 'd', 0) + ") " +
                   QString::number(amount, 'f', 2);
    ui->withdrawalList->insertItem(mounth, item);
  }
}

void Deposit::on_depositAmount_valueChanged(double arg1) {
  ui->withdrawalAmount->setMaximum(arg1);
}

void Deposit::on_mothlyTerm_valueChanged(int arg1) {
  if (arg1) {
    ui->replenishmentMonth->setMaximum(arg1 - 1);
    ui->withdrawalMonth->setMaximum(arg1 - 1);
  }
}

void Deposit::on_calculateButton_clicked() {
  data.deposit_amount = ui->depositAmount->value();
  data.interest_rate = ui->interestRate->value();
  data.tax_rate = ui->taxRate->value();
  data.month_term = ui->mothlyTerm->value();
  double interest = 0, taxes = 0;
  if (!calculate_deposit(&data, &interest, &taxes)) {
    QString accruedInterest =
        "Accrued interest: " + QString::number(interest, 'f', 2) + "\n";
    QString taxAmount = "Tax amount: " + QString::number(taxes, 'f', 2) + "\n";
    QString endTermsAmount = "Deposit amount by the end of the term :\n" +
                             QString::number(data.deposit_amount, 'f', 2);
    QString result = accruedInterest + taxAmount + endTermsAmount;
    ui->result->setText(result);
  } else {
    ui->result->setText("Incorrect input");
  }
}

void Deposit::on_pereodicetyComboBox_currentIndexChanged(int index) {
  data.capitalisation_periodicity = index;
}

void Deposit::on_capitatlizationCheckBox_stateChanged(int arg1) {
  data.capitalisation = arg1;
}