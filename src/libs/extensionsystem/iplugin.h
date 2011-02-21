#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "extensionsystem_global.h"
#include "pluginspec.h"

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace ExtensionSystem {
class IPluginPrivate;
class PluginSpec;

class EXTENSIONSYSTEM_EXPORT IPlugin : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IPlugin)

public:
    IPlugin();
    virtual ~IPlugin();

    virtual bool initialize() = 0;
    virtual void shutdown() {}

    void addObject(QObject * object, const QString &name = "");
    void removeObject(QObject * object);

protected:
    IPluginPrivate *d_ptr;
};

} // namespace ExtensionSystem

#endif // IPLUGIN_H
