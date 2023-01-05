#pragma once

#include <QDrag>
#include <QWidget>

#include "docker/dockwidget.h"
#include "config/baseconfig.h"
#include "html/htmledit.h"
#include "utilities/keymap.h"

class HtmlEditor : public DockWidget
{
  Q_OBJECT
public:
  HtmlEditor(BaseConfig *settings, QWidget* parent);

  HtmlEdit* editor() { return m_editor; }

  void settingsRequested();
  void insertHtmlTag();
  void insertTextTag();
  void insertCommentTag();

  void setText(const QString&text);

  const QFont &font() const;
  void setFont(const QFont &font);

  int addCustomPixmap(const QPixmap pixmap);
  const QPixmap pixmap(int id);

  static QPixmap unfoldedPixmap(LNPlainTextEdit::Style style, int pixmap = -1);

  static QPixmap foldedPixmap(LNPlainTextEdit::Style style, int pixmap = -1);

  //! returns all known fixed width font families
  const QStringList& getFontFamilies() const;

  //! Returns the value of the highlight line flag.
  bool isHighlightLine() const;
  //! Sets the value of the highlight line flag.
  void setHighlightLine(bool highlightLine);

  /*!
   * \brief Inserts a hoveritem into the bookmark area.
   *
   * Hover items place an icon into the bookmark area and displays
   * the supplied text as a hover item when the cursor hovers over
   * the icon.
   */
  void insertHoverItem(int lineNumber,
                       int icon,
                       const QString& title,
                       const QString& text);
  //! Checks whether there is an hover item at thte supplied line number.
  bool hasHoverItem(int lineNumber);
  //! Clears the hover items from the bookmark area.
  //!
  //! \note There is no checking before deletion. This is up to the programmer.
  void clearHoverItems();


  //! Enables or disables the bookmark area.
  //!
  //! If enable is true the bookmark area is displayed, otherwise it is hidden.
  void enableBookmarks(bool enable);
  //! Returns the value of the bookmark area enablement flag.
  bool isBookmarksEnabled();

  //! Enables or disables the linenumber area.
  //!
  //! If enable is true the linenumber area is displayed, otherwise it is
  //! hidden.m_bookmarkArea
  void enableLineNumbers(bool enable);
  //! Returns the value of the linenumber area enablement flag.
  bool isLineNumbersEnabled();

  //! Move the cursor to the selected line.
  void goToLine(int lineNumber);
  //! Move the cursor to the previous bookmark
  bool goToPreviousBookmark();
  //! Move the cursor to the next bookmark
  bool goToNextBookmark();
  //! Move the cursor to the indicateed bookmark if it exists, else nothing happens.
  void goToBookmark(int bookmark = -1);

  //! Sets the key map for the current editor.
  void setKeyMap(const QMap<KeyEvent, KeyMapper>& KeyMap);

  //! Returns true if there is a fold set at this line.
  //!
  //! \note This does not indicate that it is folde or unfolded. To get
  //! the folded flag use isFolded(int).
  bool hasFold(int lineNumber);
  //! Returns true if there is a is folded, otherwise false.
  //!
  //! \note If no fold at this linenumber then this returns false.
  bool isFolded(int lineNumber);
  //! Set the folded flag fo a linenumber. If there is no fold at
  //! this lineNumber it is created.
  void setFold(int lineNumber, bool folded);

  //! Enables or disables the fold area.
  //!
  //! If enable is true the fold area is displayed, otherwise it is hidden.
  void enableFolds(bool enable);
  //! Returns the value of the fold area enablement flag.
  bool isFoldsEnabled();

  LNPlainTextEdit::Style foldStyle();
  void setFoldStyle(LNPlainTextEdit::Style foldStyle);

  /*!
   * \brief Returns a list of the fold line numbers.
   */
  const QList<int> folds();
  /*!
   * \brief Sets a list of the fold line numbers.
   *
   * \note This does not set the folded flag, all folds are set to
   * false (unfolded). To set the folded flag to folded use either
   * the setFolds(QList<int>, QList<bool>) method to block set or
   * use setFold(int, bool) to set individual folds.
   */
  void setFolds(QList<int> folds);
  /*!
   * \brief Sets a list of the fold line numbers with attacted set of folded
   * flags.
   *
   * \note Both lists must be the same size otherwise this returns with a value
   * of false.
   */
  bool setFolds(QList<int> folds, QList<bool> folded);
  //! Add a single fold, unfolded by default.
  void insertFold(int lineNumber);
  //! Add a single fold, with a folded flag value.
  void insertFold(int lineNumber, bool folded);
  //! Clears all folds.
  //!
  //! \note There is no checking before deletion. This is up to the programmer.
  void clearFolds();

  bool isShowNewline();
  void setShowNewline(bool showNewline);

  bool isShowTabs();
  void setShowTabs(bool showTabs);
  void showTabs();
  void clearTabs();

  //! Returns the background color for the current line number.
  const QColor &lnAreaBackColor() const;
  //! Sets the background color for the current line number.
  void setLineNumberBackColor(const QColor& color);
  //! Returns the foreground color for the current line number.
  const QColor& lnAreaTextColor() const;
  //! Sets the foreground color for the current line number.
  void setLNAreaTextColor(const QColor& color);
  //! Returns the background color for the selected
  //! line.https://cpp.hotexamples.com/examples/-/QFont/setWeight/cpp-qfont-setweight-method-examples.html
  const QColor& lnAreaSelectedBackColor() const;
  //! Sets the background color for the current line number.
  void setLNAreaSelectedBackColor(const QColor& color);
  //! Returns the foreground color for selected text.
  const QColor& lnAreaSelectedTextColor() const;
  //! Sets the foreground color for selected text.
  void setLNAreaSelectedTextColor(const QColor& color);

signals:
  //! This signal is emitted
  void lineNumberChanged(int);
  void lineCountChanged(int);
  void columnChanged(int);
  void locationChanged(int line, int lineCount, int column);

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
//  void dragEnterEvent(QDragEnterEvent* event) override;
//  void dragMoveEvent(QDragMoveEvent* event) override;
//  void dropEvent(QDropEvent* event) override;

private:
  HtmlEdit* m_editor;

  void fold(int lineNumber);
  void unfold(int lineNumber);

  static const QString MIMETYPE;

};

