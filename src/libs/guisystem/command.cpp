#include "command.h"

#include <QtGui/QAction>
#include <QtGui/QKeySequence>

#include "actionmanager.h"

namespace GuiSystem {

class CommandPrivate
{
public:
    QAction *action;
    QAction *realAction;

    Command::Attributes attributes;

    bool alwaysEnabled;

    QKeySequence defaultShortcut;
    QIcon defaultIcon;
    QString defaultText;

    QString id;
};

} // namespace GuiSystem

using namespace GuiSystem;

Command::Command(const QString &id, QObject *parent) :
    QObject(parent),
    d_ptr(new CommandPrivate)
{
    Q_D(Command);

    d->id = id;
    d->action = new QAction(this);
    d->action->setEnabled(false);
    d->realAction = 0;

    connect(d->action, SIGNAL(triggered(bool)), SLOT(onTrigger(bool)));

    ActionManager::instance()->registerCommand(this);

    setAttributes(AttributeNonConfigurable);
}

Command::~Command()
{
    ActionManager::instance()->unregisterCommand(this);

    delete d_ptr;
}

/*!
    \brief Creates new action with objectName equal to command's id.

    Also command sets action's text, icon and shortcut default values (as passed to setDefault* methods).
    This action can be used in widgets and will be automatically triggered when widget have focus.
*/
QAction * Command::action()
{
    QAction *a = new QAction(this);
    a->setObjectName(id());
    a->setIcon(defaultIcon());
    a->setShortcut(defaultShortcut());
    a->setShortcutContext(Qt::WidgetShortcut);
    a->setText(defaultText());
    return a;
}

QAction * Command::action(QWidget *w, const char *slot)
{
    QAction * a = action();
    w->addAction(a);
    connect(a, SIGNAL(triggered()), w, slot);
    return a;
}

/*!
    \brief Returns inner Command's action which is used in menus and menubars.
*/
QAction * Command::commandAction() const
{
    return d_func()->action;
}


bool GuiSystem::Command::alwaysEnabled() const
{
    return d_func()->alwaysEnabled;
}

void GuiSystem::Command::setAlwaysEnabled(bool b)
{
    Q_D(Command);

    if (d->alwaysEnabled != b) {
        d->alwaysEnabled = b;
        d->action->setEnabled(b);

        emit changed();
    }
}

Command::Attributes Command::attributes() const
{
    return d_func()->attributes;
}

void Command::setAttributes(Attributes attrs)
{
    Q_D(Command);

    if (d->attributes != attrs) {
        d->attributes = attrs;

        emit changed();
    }
}


bool Command::isCheckable() const
{
    return d_func()->action->isCheckable();
}

void Command::setCheckable(bool b)
{
    Q_D(Command);

    if (d->action->isCheckable() != b) {
        d->action->setCheckable(b);

        emit changed();
    }
}

QKeySequence Command::defaultShortcut() const
{
    return d_func()->defaultShortcut;
}

void Command::setDefaultShortcut(const QKeySequence &key)
{
    Q_D(Command);

    if (d->defaultShortcut != key) {
        d->defaultShortcut = key;
        if (!d->realAction)
            d->action->setShortcut(key);

        emit changed();
    }
}

QIcon Command::defaultIcon() const
{
    return d_func()->defaultIcon;
}

void Command::setDefaultIcon(const QIcon &icon)
{
    Q_D(Command);

    if (d->defaultIcon != icon) {
        d->defaultIcon = icon;
        if (!d->realAction)
            d->action->setIcon(icon);

        emit changed();
    }
}

QString Command::defaultText() const
{
    return d_func()->defaultText;
}

void Command::setDefaultText(const QString &text)
{
    Q_D(Command);

    if (d->defaultText != text) {
        d->defaultText = text;
        if (!d->realAction)
            d->action->setText(text);

        emit changed();
    }
}

bool Command::isSeparator() const
{
    return d_func()->action->isSeparator();
}

void Command::setSeparator(bool b)
{
    d_func()->action->setSeparator(b);
}

/*!
    \brief Returns id of this command.

    When widget that have focus (or one of this parents) has action with objectName equal to id,
    actionmanager enables this command in all menus. When command action is triggered, Command
    automatically triggers action in focus widget.
*/
QString Command::id() const
{
    return d_func()->id;
}

void Command::onTrigger(bool checked)
{
    Q_D(Command);

    if (d->realAction) {
        if (d->realAction->isCheckable())
            d->realAction->setChecked(checked);
        else
            d->realAction->trigger();
    }
}

void Command::setRealAction(QAction *action)
{
    Q_D(Command);

    d->realAction = action;
    if (d->attributes & AttributeHide)
        d->action->setVisible((bool)action);
    if (d->attributes & AttributeUpdateText)
        d->action->setText(action ? action->text() : d->defaultText);
    if (d->attributes & AttributeUpdateIcon)
        d->action->setIcon(action ? action->icon() : d->defaultIcon);
    if (!(d->attributes & AttributeNonConfigurable)) {
        d->action->setShortcut(action ? action->shortcut() : d->defaultShortcut);
    }

    bool checkable = action ? action->isCheckable() : false;
    d->action->setCheckable(checkable);
    if (checkable)
        d->action->setChecked(action->isChecked());
    d->action->setEnabled(d->alwaysEnabled || (action ? action->isEnabled() : false));
}
