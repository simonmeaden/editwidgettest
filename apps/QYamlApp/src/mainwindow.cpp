#include "mainwindow.h"
#include "qyaml/qyamledit.h"

#include <QGridLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  auto widget = new QWidget(this);
  auto layout = new QGridLayout;
  widget->setLayout(layout);
  setCentralWidget(widget);
  // TODO remove fixed size.
  setFixedSize(1200, 800);

  auto yamledit = new QYamlEdit(this);
  layout->addWidget(yamledit, 0, 0);

  QString filename = "/home/simonmeaden/workspace/editwidgettest/test.yaml";
//  auto cUtf8 = filename.toUtf8().constData();
//  auto empty = filename.isEmpty();
  yamledit->loadFile(filename);
}

MainWindow::~MainWindow() {}
