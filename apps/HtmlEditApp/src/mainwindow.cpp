#include "mainwindow.h"
#include "docker/docktoolbar.h"
#include "docker/dockwidget.h"
#include "html/htmledit.h"
#include "lnplaintext/lnstatusbar.h"
#include "markdown/markdowntextedit.h"
#include "qxml/xmledit.h"

//#include "CuteLogger/Logger.h"
//#include "CuteLogger/SignalAppender.h"

#include <QFileInfo>
#include "utilities/paths.h"
#include "config.h"

const QString MainWindow::SpecialBtnStyle =
  "QPushButton {"
  "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
  "      lightsteelblue, stop: 1 steelblue);"
  "    border-color: #8F8F91;"
  "    border-style: outset;"
  "    border-width: 4px;"
  "    border-radius: 10px;"
  "}"
  "QPushButton:flat {"
  "    border: none;" /* no border for a flat push button */
  "}"
  "QPushButton:default {"
  "    border-color: royalblue;" /* make the default button prominent */
  "}"
  "QPushButton:pressed {"
  "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
  "      royalblue, stop: 1 dodgerblue);"
  "    border-style: inset;"
  "}"
  "QPushButton:checked {"
  "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
  "      royalblue, stop: 1 dodgerblue);"
  "    border-style: inset;"
  "}";

const QString MainWindow::MIMETYPE = "application/x-dnd_htmleditbtn";

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  auto configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
  m_configFilename = Paths::join(configPath, "preferences.yaml");
  m_config = new Config(m_configFilename, this);

//  auto signalAppender = new SignalAppender();
//  signalAppender->setFormat(
//    "[%{file}] [%{type:-7}] <%{Function}> Line:%{line} %{message}");
//  signalAppender->setDetailsLevel(Logger::Debug);
//  cuteLogger->registerAppender(signalAppender);

//  auto xmlKeyMap = new KeyEventMap(this);
  m_xmlEdit = new XmlEdit(m_config, this);
  auto xmlWidget = new QWidget(this);
  auto xmlGrid = new QGridLayout;
  xmlWidget->setLayout(xmlGrid);
  auto xmlDocker = new DockWidget(this);
  xmlDocker->setCentralWidget(m_xmlEdit);
  auto xmlToolbar = xmlDocker->addToolbar(Docker::East);
  xmlGrid->addWidget(xmlDocker, 0, 0, 2, 1);
  //  auto xmlTree = new QTreeWidget(this);
  //  xmlTree->setColumnCount(1);
  //  xmlGrid->addWidget(xmlTree, 0, 1, 2, 1);
  auto xmlWarn = new QPlainTextEdit(this);
  xmlGrid->addWidget(xmlWarn, 0, 1);
  auto xmlError = new QPlainTextEdit(this);
  xmlGrid->addWidget(xmlError, 1, 1);

  m_htmlEdit = new HtmlEdit(m_config, this);
  auto htmlWidget = new QWidget(this);
  auto htmlGrid = new QGridLayout;
  htmlWidget->setLayout(htmlGrid);
  auto htmlDocker = new DockWidget(this);
  htmlDocker->setCentralWidget(m_htmlEdit);
  auto htmlToolbar = htmlDocker->addToolbar(Docker::East);
  htmlGrid->addWidget(htmlDocker, 0, 0, 2, 1);
  auto htmlWarn = new QPlainTextEdit(this);
  htmlGrid->addWidget(htmlWarn, 0, 1);
  auto htmlError = new QPlainTextEdit(this);
  htmlGrid->addWidget(htmlError, 1, 1);

  m_markEdit = new MarkdownTextEdit(this);
//  m_markEdit->setKeyMap(markKeyMap);
  auto markWidget = new QWidget(this);
  auto markGrid = new QGridLayout;
  markWidget->setLayout(markGrid);
  auto markDocker = new DockWidget(this);
  markDocker->setCentralWidget(m_markEdit);
  auto markToolbar = markDocker->addToolbar(Docker::East);
  markGrid->addWidget(markDocker, 0, 0, 2, 1);
  auto markWarn = new QPlainTextEdit(this);
  markGrid->addWidget(markWarn, 0, 1);
  auto markError = new QPlainTextEdit(this);
  markGrid->addWidget(markError, 1, 1);

  auto tabs = new QTabWidget(this);
  tabs->addTab(xmlWidget, "XML");
  tabs->addTab(htmlWidget, "HTML");
  tabs->addTab(markWidget, "Markdown");

  //  setCentralWidget(docker);
  setCentralWidget(tabs);
  // TODO remove fixed size.
  setFixedSize(1200, 800);

  auto statusBar = new LNStatusBar(this);
  setStatusBar(statusBar);
  connect(m_xmlEdit,
          &LNPlainTextEdit::locationChanged,
          statusBar,
          &LNStatusBar::setLocation);
  connect(statusBar,
          &LNStatusBar::settingsRequested,
          this,
          &MainWindow::settingsRequested);

  m_familyBox = new QComboBox(this);
  m_familyBox->addItems(m_htmlEdit->getFontFamilies());
  m_familyBox->setCurrentText("Source Code Pro");
  statusBar->addPermanentWidget(m_familyBox);
  connect(m_familyBox,
          &QComboBox::currentIndexChanged,
          this,
          &MainWindow::changeFamily);

  m_nlBtn = new QPushButton(tr(" NL "), this);
  m_nlBtn->setStyleSheet(SpecialBtnStyle);
  m_nlBtn->setCheckable(true);
  statusBar->addPermanentWidget(m_nlBtn);
  connect(m_nlBtn, &QPushButton::clicked, this, &MainWindow::showNL);

  m_tabBtn = new QPushButton(tr(" TAB "), this);
  m_tabBtn->setStyleSheet(SpecialBtnStyle);
  m_tabBtn->setCheckable(true);
  statusBar->addPermanentWidget(m_tabBtn);
  connect(m_tabBtn, &QPushButton::clicked, this, &MainWindow::showTabs);

  auto px = QPixmap(":/icons/icons/document-open-recent.png");
  m_htmlEdit->addCustomPixmap(px);

  QFile htmlFile("/home/simonmeaden/workspace/HtmlScannerTest/test.htm");
  if (htmlFile.exists()) {
    if (htmlFile.open(QTextStream::ReadOnly)) {
      QTextStream streamin(&htmlFile);
      QString text = streamin.readAll();

      m_htmlEdit->setText(text);
      setWindowTitle(htmlFile.fileName());
    }
  }

  QFile markFile("/home/simonmeaden/workspace/HtmlScannerTest/README.md");
  if (markFile.exists()) {
    if (markFile.open(QTextStream::ReadOnly)) {
      QTextStream streamin(&markFile);
      QString text = streamin.readAll();

      m_markEdit->setText(text);
      setWindowTitle(markFile.fileName());
    }
  }

  auto filename = "/home/simonmeaden/workspace/HtmlScannerTest/test.xml";
  m_xmlEdit->loadFile(filename);
  //  auto info = new QFileInfo(filename);
  //  auto xmlFile = QFile(info->absoluteFilePath());

  //  if (info->exists()) {
  //    if (xmlFile.open(QFile::ReadWrite)) {
  //      QTextStream stream(&xmlFile);
  //      auto text = stream.readAll();
  //      //      xml::tree_parser parser(text.toStdString().c_str());
  //      //      xml::document& doc = parser.get_document();
  //      m_xmlEdit->setText(text);
  //      setWindowTitle(xmlFile.fileName());
  //    }
  //  }
}

MainWindow::~MainWindow()
{
//    m_xmlEdit->savePreferences();
    m_config->save(m_configFilename);
}

// void
// MainWindow::addNode(Node* node, QTreeWidgetItem* base)
//{
//   for (auto &child : node->children) {
//     auto newItem = new QTreeWidgetItem(base);
//     switch (child->type) {
//       case Node::Start: {
//         auto start = dynamic_cast<StartNode*>(child);
//         if (start) {
//           auto col = 0;
//           newItem->setText(0, start->name);
//           for (auto attr : start->attributes) {
//             QString s;
//             if (attr->hasValue()) {
//               s = QString("%1 = %2").arg(attr->name, attr->value);

//            } else {
//              s = attr->name;
//            }
//            newItem->setText(++col, s);
//          }
//        }
//        break;
//      }

//      case Node::End:
//        newItem->setText(0, dynamic_cast<StartNode*>(child)->name);
//        break;

//      case Node::Text:
//        newItem->setText(0, dynamic_cast<TextNode*>(child)->text);
//        break;

//      case Node::CData:
//        newItem->setText(0, dynamic_cast<CDataNode*>(child)->data);
//        break;

//      case Node::Instruction: {
//        auto inst = dynamic_cast<ProcessingInstruction*>(child);
//        newItem->setText(0, inst->target);
//        newItem->setText(1, inst->data);
//        break;
//      }

//      case Node::Comment:
//        newItem->setText(0, dynamic_cast<CommentNode*>(child)->text);
//        break;

//      default:
//        break;
//    }
//    // recurse up tree.
//    if (child->hasChildren()) {
//      addNode(child, newItem);
//    }
//  }
//}

void
MainWindow::logToEdit(const QString& message)
{
  if (message.contains("Should no longer be called"))
    return;
  if (message.contains("Paint device returned engine == 0"))
    return;
  m_messages->appendPlainText(message);
}

void
MainWindow::setLogMessage(const QString& message /*, int timeout*/)
{
  statusBar()->showMessage(message, 4000);
}

void
MainWindow::setPosition(int line, int lineCount, int column)
{
  m_posLbl->setText(
    tr("Line: %1 of %2: Col %3").arg(line).arg(lineCount).arg(column));
}

void
MainWindow::settingsRequested()
{
  m_htmlEdit->optionsDialog();
}

void
MainWindow::insertHtmlTag()
{
  // TODO
}

void
MainWindow::insertTextTag()
{
  // TODO
}

void
MainWindow::insertCommentTag()
{
  // TODO
}

void
MainWindow::showNL()
{
  if (m_nlBtn->isChecked()) {
    m_htmlEdit->setDisplayLineEnds(true);
  } else {
    m_htmlEdit->setDisplayLineEnds(false);
  }
}

void
MainWindow::showTabs()
{
  if (m_tabBtn->isChecked()) {
    m_htmlEdit->displayTabs();
  } else {
    m_htmlEdit->clearTabs();
  }
}

void
MainWindow::changeFamily(int index)
{
  auto text = m_familyBox->itemText(index);
  auto oldFont = font();
  auto size = oldFont.pointSize();
  auto weight = oldFont.weight();
  auto italic = oldFont.italic();
  QFont font(text, size, weight, italic);
  m_htmlEdit->setFont(font);
}
