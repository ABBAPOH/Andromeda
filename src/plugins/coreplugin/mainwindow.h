#ifndef MAINWINDOWPLUGIN_MAINWINDOW_H
#define MAINWINDOWPLUGIN_MAINWINDOW_H

#include <QtGui/QMainWindow>

class QSettings;

namespace CorePlugin {

class MainWindowPrivate;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void restoreSession(QSettings &s);
    void saveSession(QSettings &s);

public slots:
    void back();
    void forward();

    void open(const QString &path);
    void openNewTab(const QString &path);
    static void openNewWindow(const QString &path);

    void newTab();
    static void newWindow();
    void closeTab(int index = -1);

protected:
    MainWindowPrivate * d_ptr;
};

} // namespace CorePlugin

#endif // MAINWINDOWPLUGIN_MAINWINDOW_H
