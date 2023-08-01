#ifndef BANKING_CALCULATION_H
#define BANKING_CALCULATION_H

#include "calculate.h"

typedef struct credit_values {
  double credit_amount, interest_rate;
  int term, differentiated;
} CreditValue;

typedef struct deposit_values {
  double replenishment[600], withdrawals[600];
  double deposit_amount, interest_rate, tax_rate;
  int month_term, capitalisation, capitalisation_periodicity;
} DepositValue;

char* calculate_credit(CreditValue data);
char* differentiated_credit(CreditValue data);
int calculate_deposit(DepositValue* data, double* interest, double* taxes);
void deposit_capitalisation(DepositValue* data, double* capitalized,
                            double monthly_interest, int month);

#endif  // BANKING_CALCULATION_H