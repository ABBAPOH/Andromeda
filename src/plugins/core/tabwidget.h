#ifndef TABCONTAINER_P_H
#define TABCONTAINER_P_H

#include <QtGui/QTabWidget>
#include <QtGui/QAbstractButton>

#include "tabbar.h"

class MyTabWidget : public QTabWidget
{
    Q_OBJECT
    Q_PROPERTY(bool tabBarVisible READ isTabBarVisible WRITE setTabBarVisible NOTIFY tabBarVisibleChanged)
public:
    explicit MyTabWidget(QWidget *parent = 0);

    bool isTabBarVisible() const;
    void setTabBarVisible(bool visible);

signals:
    void tabBarDoubleClicked();
    void tabBarVisibleChanged(bool visible);

protected:
    bool eventFilter(QObject *o, QEvent *e);
};

class TabBarButton : public QAbstractButton
{
public:
    TabBarButton() :
        QAbstractButton(),
        hovered(false),
        pressed(false)
    {
    }

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *e);

    void enterEvent(QEvent *) { hovered = true; update(); }
    void leaveEvent(QEvent *) { hovered = false; update(); }
    void mousePressEvent(QMouseEvent *e) { pressed = true; update(); QAbstractButton::mousePressEvent(e); }
    void mouseReleaseEvent(QMouseEvent *e) { pressed = false; update(); QAbstractButton::mouseReleaseEvent(e); }

private:
    // TODO: use style option to discover state
    bool hovered;
    bool pressed;
};

#endif // TABCONTAINER_P_H
