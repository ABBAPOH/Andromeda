#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <guisystem/settingspage.h>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtGui/QWidget>

class QSettings;

namespace FileManager {
    class FileManagerSettings;
    class NavigationPanelSettings;
} // namespace FileManager

namespace Ui {
    class GlobalSettingsWidget;
}

class GlobalSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingsWidget(QWidget *parent = 0);
    ~GlobalSettingsWidget();

private slots:
    void onFileRemoveToggled(bool);
    void onExtensionChangeToggled(bool);

private:

private:
    Ui::GlobalSettingsWidget *ui;

    QSettings *m_settings;
    FileManager::FileManagerSettings *m_fileManagerSettings;
};

namespace FileManager {

class GlobalSettingsPage : public GuiSystem::SettingsPage
{
    Q_OBJECT

public:
    explicit GlobalSettingsPage(QObject *parent = 0);

    QString name() const;
    QIcon icon() const;

    QString categoryName() const;
    QIcon categoryIcon() const;

    QWidget *createPage(QWidget *parent);
};

} // namespace FileManager

#endif // GLOBALSETTINGS_H 
