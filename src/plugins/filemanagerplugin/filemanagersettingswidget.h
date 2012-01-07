#ifndef FILEMANAGERSETTINGSWIDGET_H
#define FILEMANAGERSETTINGSWIDGET_H

#include <QtGui/QWidget>

class QSettings;

namespace FileManagerPlugin {
    class FileManagerSettings;
} // namespace FileManagerPlugin

namespace Ui {
    class FileManagerSettingsWidget;
}

class FileManagerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerSettingsWidget(QWidget *parent = 0);
    ~FileManagerSettingsWidget();

private slots:
    void onChecked(bool);
    void onIconSizeChanged(int);
    void onGridSizeChanged(int);
    void onFlowChanged(int);

private:
    void setupLeftPanel();
    void setupIconSize();
    void setupGridSize();
    void setupFlow();

private:
    Ui::FileManagerSettingsWidget *ui;

    QSettings *m_settings;
    FileManagerPlugin::FileManagerSettings *m_fileManagerSettings;
};

#endif // FILEMANAGERSETTINGSWIDGET_H
