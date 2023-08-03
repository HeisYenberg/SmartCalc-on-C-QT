#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  this->setWindowTitle("Credit Calculator");
  ui->annuity->setChecked(true);
}

Credit::~Credit() { delete ui; }

void Credit::on_buttonCalculate_clicked() {
  double loanAmount = ui->creditAmount->value();
  double interestRate = ui->interestRate->value();
  double monthlyRate = interestRate / 12 / 100;
  int loanTerm = ui->monthTerm->value();
  if (loanAmount && monthlyRate && loanTerm) {
    CreditValue data = {loanAmount, monthlyRate, loanTerm,
                        ui->differentiated->isChecked() ? 1 : 0};
    char *output = calculate_credit(data);
    if (output) {
      QString qOutput(output);
      ui->output->setText(qOutput);
      free(output);
    }
  } else {
    ui->output->setText("Invalid input");
  }
}
