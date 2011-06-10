#ifndef STATE_H
#define STATE_H

#include <QtCore/QObject>

namespace GuiSystem {

class IView;
class MainWindow;
class PerspectiveInstance;

class StatePrivate;
class State : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(State)
public:
    explicit State(QObject *parent = 0);
    ~State();

    PerspectiveInstance *currentInstance() const;

    void setCurrentPerspective(const QString &id);
//    void closeInstance(const QString &id);

    QStringList perspectiveIds() const;
    QStringList availablePerspectives() const;

    void hideViews();
    void showViews();

    MainWindow *window() const;
    void setWindow(MainWindow *window);

    void setProperty(const char *name, const QVariant &value);

    IView *view(const QString &id) const;

    void addObject(QObject *object, const QString &name = QString());
    void removeObject(QObject *object);

    QObject *object(const QString &name) const;
    QObjectList objects(const QString &name) const;

    template <class T>
    inline T *object(const QString &name) const
    {
        return qobject_cast<T *>(object(name));
    }

    int index() const;
    void setIndex(int index);

signals:
    void currentPerspectiveChanged(const QString &id);
    void propertyChanged(const char *name, const QVariant &value);

public slots:

private slots:
    void onFactoryRemoved(const QString &id);

protected:
    StatePrivate *d_ptr;
};

} // namespace GuiSystem

#endif // STATE_H
