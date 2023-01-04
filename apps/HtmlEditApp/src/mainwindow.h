#pragma once

#include <QApplication>
#include <QComboBox>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextStream>
#include <QTreeWidgetItem>

class HtmlEdit;
class XmlEdit;
class HtmlEditSettings;
class MarkdownTextEdit;
class SettingsDialog;
class Node;
class Config;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void logToEdit(const QString& message);
  void setLogMessage(const QString& message);
  void setPosition(int line, int lineCount, int column);

signals:

private:
  HtmlEdit* m_htmlEdit = nullptr;
  MarkdownTextEdit* m_markEdit = nullptr;
  XmlEdit* m_xmlEdit;
  QPlainTextEdit* m_messages = nullptr;
  QPlainTextEdit* m_logEdit = nullptr;
  QLabel* m_posLbl = nullptr;
  QPushButton* m_nlBtn = nullptr;
  QPushButton* m_tabBtn = nullptr;
  QComboBox* m_familyBox = nullptr;
  //  SettingsDialog *m_settingsDlg;
  //  HtmlScanner *m_scanner;
  Config* m_config;
  QString m_configFilename;

  void showNL();
  void showTabs();
  void changeFamily(int index);
  void settingsRequested();
  void insertHtmlTag();
  void insertTextTag();
  void insertCommentTag();

  static const QString SpecialBtnStyle;
  static const QString MIMETYPE;
  void addNode(Node* node, QTreeWidgetItem* base);
};
