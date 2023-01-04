//#define COMMANDLINE

#if defined(COMMANDLINE)
#include <QCoreApplication>
#else
#include <QApplication>
#endif

#include <QDir>
#include <QFile>
#include <QStringView>
#include <QTextStream>

#include "mainwindow.h"

int
main(int argc, char* argv[])
{
#if defined(COMMANDLINE)

  QCoreApplication a(argc, argv);

  //  QFile file("../0743435710__p__split_006.htm");
  QFile file("/home/simonmeaden/workspace/HtmlScannerTest/test.htm");
  if (file.exists()) {
    if (file.open(QTextStream::ReadOnly)) {
      QTextStream streamin(&file);

      HtmlScanner scanner;
      scanner.scan(streamin);
    }
  }

#else

  QApplication a(argc, argv);
  MainWindow w;


   w.show();
  return a.exec();

#endif
  return a.exec();
}
