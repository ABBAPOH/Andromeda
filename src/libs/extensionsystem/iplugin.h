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
    enum Properties { Name, Version, CompatibilityVersion, Vendor, Category,
                      Copyright, License, Description, Url };
    IPlugin();
    virtual ~IPlugin();

    virtual bool initialize() = 0;
    virtual QString property(Properties property) = 0;
    virtual QList<PluginDependency> dependencies() { return QList<PluginDependency>(); }
    virtual void shutdown() {}

    void addObject(QObject * object, const QString &type = "");
    void removeObject(QObject * object);

protected:
    IPluginPrivate *d_ptr;
    friend class PluginSpec;
};

} // namespace ExtensionSystem

#endif // IPLUGIN_H
