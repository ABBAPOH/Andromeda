#ifndef FILESYSTEMTOOLMODEL_H
#define FILESYSTEMTOOLMODEL_H

#include <QtCore/QUrl>
#include <GuiSystem/ToolModel>

namespace FileManager {

class FileSystemModel;

class FileSystemToolModel : public GuiSystem::ToolModel
{
    Q_OBJECT
    Q_DISABLE_COPY(FileSystemToolModel)

    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)

public:
    explicit FileSystemToolModel(QObject *parent = 0);

    FileSystemModel *fileSystemModel() const;

    QUrl url() const;

    void setDocument(GuiSystem::AbstractDocument *document);

signals:
    void urlChanged(const QUrl &url);

protected:
    FileSystemModel *m_model;
};

} // namespace FileManager

#endif // FILESYSTEMTOOLMODEL_H
