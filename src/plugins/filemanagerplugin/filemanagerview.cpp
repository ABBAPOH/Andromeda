#include "filemanagerview.h"

#include <QtCore/QSettings>
#include <QtCore/QSignalMapper>
#include <QtGui/QAction>

#include <actionmanager.h>
#include <command.h>
#include <constants.h>
#include <pluginmanager.h>

#include "dualpanewidget.h"
#include "filemanagerwidget.h"
#include "filesystemmodel.h"

using namespace FileManagerPlugin;
using namespace GuiSystem;

FileManagerView::FileManagerView(QObject *parent) :
    IMainView(parent)
{
    QSettings settings;
    settings.beginGroup("FileManager");
    bool enableDualPane = settings.value("dualPaneModeEnabled").toBool();

    FileSystemModel *model = ExtensionSystem::PluginManager::instance()->object<FileSystemModel>("FileSystemModel");

    m_widget = new DualPaneWidget(model);
    m_widget->setDualPaneModeEnabled(enableDualPane);
    m_widget->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(m_widget, SIGNAL(currentPathChanged(QString)), SIGNAL(pathChanged(QString)));
    connect(m_widget, SIGNAL(openRequested(QString)), SIGNAL(openRequested(QString)));

    GuiSystem::ActionManager *actionManager = GuiSystem::ActionManager::instance();
    actionManager->command(Constants::Ids::Actions::Open)->action(m_widget, SLOT(open()));
    actionManager->command(Constants::Ids::Actions::NewFolder)->action(m_widget, SLOT(newFolder()));
    actionManager->command(Constants::Ids::Actions::Rename)->action(m_widget, SLOT(rename()));
    actionManager->command(Constants::Ids::Actions::Remove)->action(m_widget, SLOT(remove()));

    QAction *a = actionManager->command(Constants::Ids::Actions::DualPane)->action();
    a->setChecked(enableDualPane);
    m_widget->addAction(a);
    connect(a, SIGNAL(toggled(bool)), this, SLOT(setDualPaneModeEnabled(bool)));

//    actionManager->command(Constants::Ids::Actions::Cut)->action(m_widget, SLOT(cut()));
    actionManager->command(Constants::Ids::Actions::Copy)->action(m_widget, SLOT(copy()));
    actionManager->command(Constants::Ids::Actions::Paste)->action(m_widget, SLOT(paste()));
    actionManager->command(Constants::Ids::Actions::SelectAll)->action(m_widget, SLOT(selectAll()));

    actionManager->command(Constants::Ids::Actions::Up)->action(m_widget, SLOT(up()));

    QAction * showHiddenFilesAct = actionManager->command(Constants::Ids::Actions::ShowHiddenFiles)->action();
    m_widget->addAction(showHiddenFilesAct);
    connect(showHiddenFilesAct, SIGNAL(toggled(bool)), m_widget, SLOT(showHiddenFiles(bool)));

    int mode = settings.value("viewMode").toInt();
    mode = mode == 0 ? 1 : mode;
    mode = enableDualPane ? -1 : mode;
    if (!enableDualPane)
        setViewMode(mode);

    QAction *action = 0;
    QSignalMapper *viewMapper = new QSignalMapper(this);

    action = actionManager->command(Constants::Ids::Actions::IconMode)->action();
    viewMapper->setMapping(action, 1);
    connect(action, SIGNAL(toggled(bool)), viewMapper, SLOT(map()));
    m_widget->addAction(action);
    action->setChecked(mode == 1);

    action = actionManager->command(Constants::Ids::Actions::ColumnMode)->action();
    viewMapper->setMapping(action, 3);
    connect(action, SIGNAL(toggled(bool)), viewMapper, SLOT(map()));
    m_widget->addAction(action);
    action->setChecked(mode == 3);

    action = actionManager->command(Constants::Ids::Actions::TreeMode)->action();
    viewMapper->setMapping(action, 4);
    connect(action, SIGNAL(toggled(bool)), viewMapper, SLOT(map()));
    m_widget->addAction(action);
    action->setChecked(mode == 4);

    connect(viewMapper, SIGNAL(mapped(int)), SLOT(setViewMode(int)));

    settings.endGroup();
}

void FileManagerView::initialize()
{
}

QString FileManagerView::type() const
{
    return "filemanager";
}

QWidget * FileManagerView::widget() const
{
    return m_widget;
}

bool FileManagerView::open(const QString &path)
{
    m_widget->setCurrentPath(path);
    return true;
}

bool FileManagerView::open(const CorePlugin::HistoryItem &item)
{
    if (m_widget->leftWidget()->history()->items().contains(item)) {
        m_widget->leftWidget()->history()->goToItem(item);
    }
    if (m_widget->rightWidget()->history()->items().contains(item)) {
        m_widget->rightWidget()->history()->goToItem(item);
    }
    return true;
}

CorePlugin::HistoryItem FileManagerView::currentItem() const
{
    return m_widget->history()->currentItem();
}

void FileManagerView::setDualPaneModeEnabled(bool on)
{
    QSettings settings;
    settings.beginGroup("FileManager");
    settings.setValue("dualPaneModeEnabled", on);
    settings.endGroup();
    m_widget->setDualPaneModeEnabled(on);
}

void FileManagerPlugin::FileManagerView::setViewMode(int mode)
{
    setDualPaneModeEnabled(false);

    QSettings settings;
    settings.beginGroup("FileManager");
    settings.setValue("viewMode", mode);
    settings.endGroup();
    m_widget->setViewMode((FileManagerWidget::ViewMode)mode);
}

QString FileManagerFactory::id() const
{
    return "FileManager";
}

GuiSystem::IView * FileManagerPlugin::FileManagerFactory::createView() const
{
    return new FileManagerView;
}
