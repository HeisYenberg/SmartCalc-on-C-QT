#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  this->setWindowTitle("Credit Calculator");
  ui->creditAmount->setMaximum(9999999999999);
  ui->annuity->setChecked(true);
}

Credit::~Credit() { delete ui; }

void Credit::on_buttonCalculate_clicked() {
  double loanAmount = ui->creditAmount->value();
  double interestRate = ui->interestRate->value();
  double monthlyRate = interestRate / 12 / 100;
  int loanTerm = ui->monthTerm->value();
  double totalPayment = 0, overpayment = 0;
  char *output = (char *)calloc(4096, sizeof(char));
  if (ui->annuity->isChecked()) {
    double coeficent = (monthlyRate * pow(1 + monthlyRate, loanTerm)) /
                       (pow(1 + monthlyRate, loanTerm) - 1);
    double monthlyPayment = loanAmount * coeficent;
    totalPayment = monthlyPayment * loanTerm;
    overpayment = totalPayment - loanAmount;
    sprintf(output,
            "Annuity credit :\n\nMonthly payment: %.2lf\nOverpayment on "
            "Credit: %.2lf\nTotal payment: %.2lf\n",
            monthlyPayment, overpayment, totalPayment);
  } else {
    double monthlyPayment = loanAmount / loanTerm;
    double paymentLeft = loanAmount;
    strcat(output, "Differentiated credit :\n\n");
    for (int i = 1; i <= loanTerm; i++) {
      double monthIPayment = monthlyPayment + paymentLeft * monthlyRate;
      paymentLeft -= monthlyPayment;
      totalPayment += monthIPayment;
      char thisMonthPay[1000];
      sprintf(thisMonthPay, "%d) %.2lf\n", i, monthIPayment);
      strcat(output, thisMonthPay);
    }
    overpayment = totalPayment - loanAmount;
    char overpayAndTotalPay[2000];
    sprintf(overpayAndTotalPay,
            "Overpayment on Credit: %.2lf\nTotal payment: %.2lf\n", overpayment,
            totalPayment);
    strcat(output, overpayAndTotalPay);
  }
  QString qOutput(output);
  ui->output->setText(qOutput);
  if (output) free(output);
}
