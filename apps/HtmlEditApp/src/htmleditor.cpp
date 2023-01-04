#include "htmleditor.h"
#include "docker/docktoolbar.h"
#include "docker/draggablebuttonwidget.h"

const QString HtmlEditor::MIMETYPE=""; // TODO place actual value

HtmlEditor::HtmlEditor(BaseConfig* settings, QWidget* parent)
  : DockWidget(parent)
  , m_editor(new HtmlEdit(settings, this))
{
  installEventFilter(m_editor);
  //  m_editor->setFixedSize(10,10);

  auto toolbar = addToolbar(Docker::East);

  auto px = QPixmap(":/icon/Settings");
  auto btn = toolbar->addIconButton(
    Docker::WidgetPosition::End, px.scaled(QSize(32, 32)), tr("Options"));
  connect(
    btn, &ButtonWidget::widgetClicked, this, &HtmlEditor::settingsRequested);

  px = QPixmap(":/icon/Html");
  btn = toolbar->addDragIconButton(Docker::WidgetPosition::Start,
                                   px.scaled(QSize(32, 32)),
                                   tr("Insert html tag"));
  auto drag = qobject_cast<DraggableButtonWidget*>(btn);
  if (drag) {
    px = QPixmap(":/icon/HtmlDrag");
    drag->setDragPixmap(px);
    drag->setData(MIMETYPE, QByteArray::number(HtmlButtonType::HtmlType));
  }
  connect(btn, &ButtonWidget::widgetClicked, this, &HtmlEditor::insertHtmlTag);

  px = QPixmap(":/icon/Text");
  btn = toolbar->addDragIconButton(Docker::WidgetPosition::Start,
                                   px.scaled(QSize(32, 32)),
                                   tr("Insert text tag"));
  drag = qobject_cast<DraggableButtonWidget*>(btn);
  if (drag) {
    px = QPixmap(":/icon/TextDrag");
    drag->setDragPixmap(px);
    drag->setData(MIMETYPE, QByteArray::number(HtmlButtonType::TextType));
  }
  connect(btn, &ButtonWidget::widgetClicked, this, &HtmlEditor::insertTextTag);

  px = QPixmap(":/icon/Comment");
  btn = toolbar->addDragIconButton(Docker::WidgetPosition::Start,
                                   px.scaled(QSize(32, 32)),
                                   tr("Insert comment"));
  drag = qobject_cast<DraggableButtonWidget*>(btn);
  if (drag) {
    px = QPixmap(":/icon/CommentDrag");
    drag->setDragPixmap(px);
    drag->setData(MIMETYPE, QByteArray::number(HtmlButtonType::CommentType));
  }
  connect(btn, &ButtonWidget::widgetClicked, this, &HtmlEditor::insertTextTag);

  // pass through LNPlainTextEdit signals
  connect(m_editor,
          &LNPlainTextEdit::lineNumberChanged,
          this,
          &HtmlEditor::lineNumberChanged);
  connect(m_editor,
          &LNPlainTextEdit::lineCountChanged,
          this,
          &HtmlEditor::lineCountChanged);
  connect(m_editor,
          &LNPlainTextEdit::columnChanged,
          this,
          &HtmlEditor::columnChanged);
  connect(m_editor,
          &LNPlainTextEdit::locationChanged,
          this,
          &HtmlEditor::locationChanged);
}

void
HtmlEditor::settingsRequested()
{
  m_editor->optionsDialog();
}

void
HtmlEditor::insertHtmlTag()
{
  // TODO
}

void
HtmlEditor::insertTextTag()
{
  // TODO
}

void
HtmlEditor::insertCommentTag()
{
  // TODO
}

void
HtmlEditor::setText(const QString& text)
{
  m_editor->setText(text);
}

const QFont&
HtmlEditor::font() const
{
  return m_editor->font();
}

void
HtmlEditor::setFont(const QFont& font)
{
  m_editor->setFont(font);
}

int
HtmlEditor::addCustomPixmap(const QPixmap pixmap)
{
  return m_editor->addCustomPixmap(pixmap);
}

const QPixmap
HtmlEditor::pixmap(int id)
{
  return m_editor->pixmap(id);
}

QPixmap
HtmlEditor::unfoldedPixmap(LNPlainTextEdit::Style style, int pixmap)
{
  return HtmlEdit::unfoldedPixmap(style, pixmap);
}

QPixmap
HtmlEditor::foldedPixmap(LNPlainTextEdit::Style style, int pixmap)
{
  return HtmlEdit::foldedPixmap(style, pixmap);
}

const QStringList&
HtmlEditor::getFontFamilies() const
{
  return m_editor->getFontFamilies();
}

bool
HtmlEditor::isHighlightLine() const
{
  return m_editor->isHighlightLine();
}

void
HtmlEditor::setHighlightLine(bool highlightLine)
{
  m_editor->setHighlightLine(highlightLine);
}

void
HtmlEditor::insertHoverItem(int lineNumber,
                            int icon,
                            const QString& title,
                            const QString& text)
{
  m_editor->insertHoverItem(lineNumber, icon, title, text);
}

bool
HtmlEditor::hasHoverItem(int lineNumber)
{
  return m_editor->hasHoverItem(lineNumber);
}

void
HtmlEditor::clearHoverItems()
{
  m_editor->clearHoverItems();
}

void
HtmlEditor::goToLine(int lineNumber)
{
  m_editor->goToLine(lineNumber);
}

bool
HtmlEditor::goToPreviousBookmark()
{
  return m_editor->goToPreviousBookmark();
}

bool
HtmlEditor::goToNextBookmark()
{
  return m_editor->goToNextBookmark();
}

void
HtmlEditor::goToBookmark(int bookmark)
{
  m_editor->goToBookmark(bookmark);
}

bool
HtmlEditor::hasFold(int lineNumber)
{
  return m_editor->hasFold(lineNumber);
}

bool
HtmlEditor::isFolded(int lineNumber)
{
  return m_editor->isFolded(lineNumber);
}

void
HtmlEditor::setFold(int lineNumber, bool folded)
{
  m_editor->setFold(lineNumber, folded);
}

void
HtmlEditor::enableBookmarks(bool enable)
{
  m_editor->enableBookmarks(enable);
}

bool
HtmlEditor::isBookmarksEnabled()
{
  return m_editor->isBookmarksEnabled();
}

void
HtmlEditor::enableLineNumbers(bool enable)
{
  m_editor->enableLineNumbers(enable);
}

bool
HtmlEditor::isLineNumbersEnabled()
{
  return m_editor->isLineNumbersEnabled();
}

void
HtmlEditor::enableFolds(bool enable)
{
  m_editor->enableFolds(enable);
}

bool
HtmlEditor::isFoldsEnabled()
{
  return m_editor->isFoldsEnabled();
}

LNPlainTextEdit::Style
HtmlEditor::foldStyle()
{
  return m_editor->foldStyle();
}

void
HtmlEditor::setFoldStyle(LNPlainTextEdit::Style foldStyle)
{
  m_editor->setFoldStyle(foldStyle);
}

const QList<int>
HtmlEditor::folds()
{
  return m_editor->folds();
}

void
HtmlEditor::setFolds(QList<int> folds)
{
  m_editor->setFolds(folds);
}

bool
HtmlEditor::setFolds(QList<int> folds, QList<bool> folded)
{
  return m_editor->setFolds(folds, folded);
}

void
HtmlEditor::insertFold(int lineNumber)
{
  m_editor->insertFold(lineNumber);
}

void
HtmlEditor::insertFold(int lineNumber, bool folded)
{
  m_editor->insertFold(lineNumber, folded);
}

void
HtmlEditor::clearFolds()
{
  m_editor->clearFolds();
}

bool
HtmlEditor::isShowNewline()
{
  return m_editor->isDisplayLineEnds();
}

void
HtmlEditor::setShowNewline(bool showNewline)
{
  m_editor->setDisplayLineEnds(showNewline);
  m_editor->rehighlight();
}

bool
HtmlEditor::isShowTabs()
{
  return m_editor->isDisplayTabs();
}

void
HtmlEditor::setShowTabs(bool showTabs)
{
  m_editor->setDisplayTabs(showTabs);
}

void
HtmlEditor::showTabs()
{
  m_editor->displayTabs();
  m_editor->rehighlight();
}

void
HtmlEditor::clearTabs()
{
  m_editor->clearTabs();
  m_editor->rehighlight();
}

const QColor&
HtmlEditor::lnAreaBackColor() const
{
  return m_editor->lnAreaBackColor();
}

void
HtmlEditor::setLineNumberBackColor(const QColor& color)
{
  m_editor->setLineNumberBackColor(color);
}

const QColor&
HtmlEditor::lnAreaTextColor() const
{
  return m_editor->lnAreaTextColor();
}

void
HtmlEditor::setLNAreaTextColor(const QColor& color)
{
  m_editor->setLNAreaTextColor(color);
}

const QColor&
HtmlEditor::lnAreaSelectedBackColor() const
{
  return m_editor->lnAreaSelectedBackColor();
}

void
HtmlEditor::setLNAreaSelectedBackColor(const QColor& color)
{
  m_editor->setLNAreaSelectedBackColor(color);
}

const QColor&
HtmlEditor::lnAreaSelectedTextColor() const
{
  return m_editor->lnAreaSelectedTextColor();
}

void
HtmlEditor::setLNAreaSelectedTextColor(const QColor& color)
{
  m_editor->setLNAreaSelectedTextColor(color);
}

void
HtmlEditor::fold(int lineNumber)
{
  // TODO
  qWarning() << "Not implemented yet";
}

void
HtmlEditor::unfold(int lineNumber)
{
  // TODO
  qWarning() << "Not implemented yet";
}

void
HtmlEditor::mousePressEvent(QMouseEvent* event)
{
  DockWidget::mousePressEvent(event);
}

void
HtmlEditor::mouseMoveEvent(QMouseEvent* event)
{
  // TODO
  //  if (!(event->buttons() & Qt::LeftButton))
  //    return;

  //  if (d_ptr->m_currentItem) {
  //    auto dragBtn =
  //    qobject_cast<DraggableButtonWidget*>(d_ptr->m_currentItem); if (dragBtn)
  //    {
  //      auto hotSpot = event->position().toPoint();
  //      auto drag = new QDrag(d_ptr->m_parent);
  //      auto mimeData = new HtmlDragData;
  //      mimeData->setData(
  //        dragBtn->data(QStringLiteral("application/x-dnd_htmleditbtn")));
  //      drag->setMimeData(mimeData);
  //      auto px = dragBtn->pixmap();
  //      drag->setPixmap(px);
  //      drag->setHotSpot(hotSpot);
  //      drag->exec(Qt::MoveAction);
  //    }
  //  }
  DockWidget::mouseMoveEvent(event);
}

void
HtmlEditor::mouseReleaseEvent(QMouseEvent* event)
{
  DockWidget::mouseReleaseEvent(event);
}

// void
// HtmlEditor::dragEnterEvent(QDragEnterEvent* event)
//{
//   if (event->mimeData()->hasFormat(
//         QStringLiteral("application/x-dnd_htmleditbtn"))) {
//     event->acceptProposedAction();
//   }
// }

// void
// HtmlEditor::dragMoveEvent(QDragMoveEvent* event)
//{
//   if (event->mimeData()->hasFormat(
//         QStringLiteral("application/x-dnd_htmleditbtn"))) {
//     if (event->source() == d_ptr->m_parent) {
//       event->acceptProposedAction();
//     }
//   } else {
//     event->ignore();
//   }
// }

// void
// HtmlEditor::dropEvent(QDropEvent* event)
//{
//   auto mimeData = event->mimeData();
//   if (mimeData->hasFormat(QStringLiteral("application/x-dnd_htmleditbtn"))) {
//     event->acceptProposedAction();
//   } else {
//     event->ignore();
//   }
// }
