#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    setWordWrapMode(QTextOption::NoWrap);

    createActions();
}

void TextEdit::createActions()
{
    actions[TextEdit::New] = new QAction(this);
    actions[TextEdit::New]->setObjectName("actionNew");
    actions[TextEdit::New]->setShortcut(QKeySequence::New);
    actions[TextEdit::New]->setText(tr("New"));
    actions[TextEdit::New]->setIcon(QIcon::fromTheme("document-new"));
    connect(actions[TextEdit::New], SIGNAL(triggered()), this, SLOT(clear()));

    actions[TextEdit::Save] = new QAction(this);
    actions[TextEdit::Save]->setObjectName("actionSave");
    actions[TextEdit::Save]->setShortcut(QKeySequence::Save);
    actions[TextEdit::Save]->setText(tr("Save"));
    actions[TextEdit::Save]->setIcon(QIcon::fromTheme("document-save"));

    actions[TextEdit::SaveAs] = new QAction(this);
    actions[TextEdit::SaveAs]->setObjectName("actionSaveAs");
    actions[TextEdit::SaveAs]->setShortcut(QKeySequence::SaveAs);
    actions[TextEdit::SaveAs]->setText(tr("Save As"));
    actions[TextEdit::SaveAs]->setIcon(QIcon::fromTheme("document-save-as"));

    actions[TextEdit::Undo] = new QAction(this);
    actions[TextEdit::Undo]->setObjectName("actionUndo");
    actions[TextEdit::Undo]->setShortcut(QKeySequence::Undo);
    actions[TextEdit::Undo]->setText(tr("Undo"));
    actions[TextEdit::Undo]->setIcon(QIcon::fromTheme("edit-undo"));
    connect(actions[TextEdit::Undo], SIGNAL(triggered()), this, SLOT(undo()));
    connect(this, SIGNAL(undoAvailable(bool)), actions[TextEdit::Undo], SLOT(setEnabled(bool)));
    actions[TextEdit::Undo]->setEnabled(false);

    actions[TextEdit::Redo] = new QAction(this);
    actions[TextEdit::Redo]->setObjectName("actionRedo");
    actions[TextEdit::Redo]->setShortcut(QKeySequence::Redo);
    actions[TextEdit::Redo]->setText(tr("Redo"));
    actions[TextEdit::Redo]->setIcon(QIcon::fromTheme("edit-redo"));
    connect(actions[TextEdit::Redo], SIGNAL(triggered()), this, SLOT(redo()));
    connect(this, SIGNAL(redoAvailable(bool)), actions[TextEdit::Redo], SLOT(setEnabled(bool)));
    actions[TextEdit::Redo]->setEnabled(false);

    actions[TextEdit::Copy] = new QAction(this);
    actions[TextEdit::Copy]->setObjectName("actionCopy");
    actions[TextEdit::Copy]->setShortcut(QKeySequence::Copy);
    actions[TextEdit::Copy]->setText(tr("Copy"));
    actions[TextEdit::Copy]->setIcon(QIcon::fromTheme("edit-copy"));
    connect(actions[TextEdit::Copy], SIGNAL(triggered()), this, SLOT(copy()));
    connect(this, SIGNAL(copyAvailable(bool)), actions[TextEdit::Copy], SLOT(setEnabled(bool)));
    actions[TextEdit::Copy]->setEnabled(false);

    actions[TextEdit::Cut] = new QAction(this);
    actions[TextEdit::Cut]->setObjectName("actionCut");
    actions[TextEdit::Cut]->setShortcut(QKeySequence::Cut);
    actions[TextEdit::Cut]->setText(tr("Cut"));
    actions[TextEdit::Cut]->setIcon(QIcon::fromTheme("edit-cut"));
    connect(actions[TextEdit::Cut], SIGNAL(triggered()), this, SLOT(cut()));
    connect(this, SIGNAL(copyAvailable(bool)), actions[TextEdit::Cut], SLOT(setEnabled(bool)));
    actions[TextEdit::Cut]->setEnabled(false);

    actions[TextEdit::Paste] = new QAction(this);
    actions[TextEdit::Paste]->setObjectName("actionPaste");
    actions[TextEdit::Paste]->setShortcut(QKeySequence::Paste);
    actions[TextEdit::Paste]->setText(tr("Paste"));
    actions[TextEdit::Paste]->setIcon(QIcon::fromTheme("edit-paste"));
    connect(actions[TextEdit::Paste], SIGNAL(triggered()), this, SLOT(paste()));

    actions[TextEdit::ZoomIn] = new QAction(this);
    actions[TextEdit::ZoomIn]->setObjectName("actionZoomIn");
    actions[TextEdit::ZoomIn]->setShortcut(QKeySequence::ZoomIn);
    actions[TextEdit::ZoomIn]->setText(tr("Zoom In"));
    actions[TextEdit::ZoomIn]->setIcon(QIcon::fromTheme("zoom-in"));
    connect(actions[TextEdit::ZoomIn], SIGNAL(triggered()), this, SLOT(zoomIn()));

    actions[TextEdit::ZoomOut] = new QAction(this);
    actions[TextEdit::ZoomOut]->setObjectName("actionZoomOut");
    actions[TextEdit::ZoomOut]->setShortcut(QKeySequence::ZoomOut);
    actions[TextEdit::ZoomOut]->setText(tr("Zoom Out"));
    actions[TextEdit::ZoomOut]->setIcon(QIcon::fromTheme("zoom-out"));
    connect(actions[TextEdit::ZoomOut], SIGNAL(triggered()), this, SLOT(zoomOut()));
}

void TextEdit::zoomIn()
{
    QFont font(this->font());
    font.setPointSize(font.pointSize() + 3);
    this->setFont(font);
}

void TextEdit::zoomOut()
{
    QFont font(this->font());
    font.setPointSize(font.pointSize() - 3);
    this->setFont(font);
}

QAction * TextEdit::action(TextEdit::Action action) const
{
    if (action < 0 || action >= ActionsCount)
        return 0;

    return actions[action];
}
