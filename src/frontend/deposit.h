#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

extern "C" {
#include "../backend/calculate.h"
};

namespace Ui {
class Deposit;
}

class Deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_replenishmentAddButton_clicked();
  void on_withdrawalsAddButton_clicked();
  void on_calculateButton_clicked();
  void on_depositAmount_valueChanged(double arg1);
  void on_mothlyTerm_valueChanged(int arg1);
  void on_pereodicetyComboBox_currentIndexChanged(int index);
  void on_capitatlizationCheckBox_stateChanged(int arg1);

 private:
  Ui::Deposit *ui;
  DepositValue data = {{0}, {0}, 0, 0, 0, 0, 0, 0};
};

#endif  // DEPOSIT_H