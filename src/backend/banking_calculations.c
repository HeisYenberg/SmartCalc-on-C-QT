#include "banking_calculations.h"

char *calculate_credit(CreditValue data) {
  char *output = NULL;
  if (!data.differentiated) {
    output = (char *)calloc(500, sizeof(char));
    if (output) {
      double coefficient =
          (data.interest_rate * pow(1 + data.interest_rate, data.term)) /
          (pow(1 + data.interest_rate, data.term) - 1);
      double monthlyPayment = data.credit_amount * coefficient;
      double totalPayment = monthlyPayment * data.term;
      double overpayment = totalPayment - data.credit_amount;
      sprintf(output,
              "Monthly payment: %.2lf\nOverpayment on Credit: %.2lf\nTotal "
              "payment: %.2lf\n",
              monthlyPayment, overpayment, totalPayment);
    }
  } else {
    output = differentiated_credit(data);
  }
  return output;
}

char *differentiated_credit(CreditValue data) {
  char *output = calloc(500 * data.term, sizeof(char));
  if (output) {
    double total_payment = 0;
    double monthly_payment = data.credit_amount / data.term;
    double payment_left = data.credit_amount;
    strcat(output, "Monthly payments:\n");
    for (int i = 1; i <= data.term; i++) {
      double month_i_payment =
          monthly_payment + payment_left * data.interest_rate;
      payment_left -= monthly_payment;
      total_payment += month_i_payment;
      char thisMonthPay[1000];
      sprintf(thisMonthPay, "%d) %.2lf\n", i, month_i_payment);
      strcat(output, thisMonthPay);
    }
    double overpayment = total_payment - data.credit_amount;
    char overpay_and_total_pay[500];
    sprintf(overpay_and_total_pay,
            "Overpayment on Credit: %.2lf\nTotal payment: %.2lf\n", overpayment,
            total_payment);
    strcat(output, overpay_and_total_pay);
  }
  return output;
}

int calculate_deposit(DepositValue *data, double *interest, double *taxes) {
  int status = OK;
  double capitalized = 0;
  for (int i = 0; i < data->month_term && !status; i++) {
    data->deposit_amount += data->replenishment[i];
    if (data->deposit_amount > data->withdrawals[i])
      data->deposit_amount -= data->withdrawals[i];
    else
      status = INCORRECT_EXPRESSION;
    double monthly_interest =
        data->deposit_amount * data->interest_rate / 12 / 100;
    if (data->capitalisation) {
      deposit_capitalisation(data, &capitalized, monthly_interest, i);
    }
    *interest += monthly_interest;
  }
  if (!data->capitalisation) data->deposit_amount += *interest;
  data->deposit_amount += capitalized;
  *taxes = *interest * data->tax_rate / 100;
  data->deposit_amount -= *taxes;
  return status;
}

void deposit_capitalisation(DepositValue *data, double *capitalized,
                            double monthly_interest, int month) {
  *capitalized += monthly_interest;
  if (!data->capitalisation_periodicity) {
    data->deposit_amount += *capitalized;
    *capitalized = 0;
  } else if (data->capitalisation_periodicity == 1) {
    if (!(month % 4)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  } else if (data->capitalisation_periodicity == 2) {
    if (!(month % 6)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  } else {
    if (!(month % 12)) {
      data->deposit_amount += *capitalized;
      *capitalized = 0;
    }
  }
}