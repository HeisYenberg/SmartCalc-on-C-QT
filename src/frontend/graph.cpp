#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  this->setWindowTitle("Graph of function");
  ui->xMax->setMaximum(1000000);
  ui->xMax->setMinimum(0.5);
  ui->xMin->setMaximum(-0.5);
  ui->xMin->setMinimum(-1000000);
  ui->xMax->setValue(10);
  ui->xMin->setValue(-10.0);
  ui->yMax->setMaximum(1000000);
  ui->yMax->setMinimum(0.5);
  ui->yMin->setMaximum(-0.5);
  ui->yMin->setMinimum(-1000000);
  ui->yMax->setValue(10);
  ui->yMin->setValue(-10.0);
}

Graph::~Graph() { delete ui; }

void Graph::setExpression(QString expression) {
  ui->result->setText(expression);
}

void Graph::on_buttonGraph_clicked() {
  double x_min = ui->xMin->value();
  double x_max = ui->xMax->value();
  double y_min = ui->yMin->value();
  double y_max = ui->yMax->value();
  double h = ((x_max - x_min) + (y_max - y_min)) > 400000 ? 0.1 : 0.01;
  QVector<double> xVector, yVector;
  QString result = ui->result->text();
  QByteArray byteArray = result.toLocal8Bit();
  char *str = byteArray.data();
  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(y_min, y_max);
  for (double x = x_min; x <= x_max; x += h) {
    double y = NAN;
    int res = smart_calc(str, x, &y);
    if (res == 0) {
      xVector.push_back(x);
      yVector.push_back(y);
    } else if (res == INCORRECT_EXPRESSION) {
      ui->result->setText("INCORRECT EXPRESSION");
      break;
    }
  }
  ui->widget->addGraph();
  ui->widget->graph()->addData(xVector, yVector);
  ui->widget->graph()->setLineStyle(QCPGraph::lsNone);
  QCPScatterStyle myScatter;
  myScatter.setShape(QCPScatterStyle::ssDisc);
  myScatter.setSize(2);
  ui->widget->graph()->setScatterStyle(myScatter);
  ui->widget->replot();
}
