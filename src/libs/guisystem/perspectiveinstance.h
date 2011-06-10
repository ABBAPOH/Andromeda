#ifndef PERSPECTIVEINSTANCE_H
#define PERSPECTIVEINSTANCE_H

#include "guisystem_global.h"

#include <QtCore/QObject>

namespace GuiSystem {

class IView;
class Perspective;
class PerspectiveInstancePrivate;
class GUISYSTEM_EXPORT PerspectiveInstance : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(PerspectiveInstance)
public:
    explicit PerspectiveInstance(QObject *parent = 0);
    ~PerspectiveInstance();

    Perspective *perspective() const;
    void setPerspective(Perspective *perspective);

    QList<IView *> views();
    void addView(IView *view);
    void removeView(IView *view);
    void removeView(const QString &id);
    IView *view(const QString &id) const;

    int index() const;
    void setIndex(int index);

signals:

public slots:

protected:
    PerspectiveInstancePrivate *d_ptr;
};

} // namespace GuiSystem

#endif // PERSPECTIVEINSTANCE_H
