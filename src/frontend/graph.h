#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>

extern "C" {
#include "../backend/calculate.h"
};

#include "mainwindow.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void setExpression(QString expression);

 private slots:
  void on_buttonGraph_clicked();

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
