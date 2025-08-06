#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractItemModel>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>

class FileSystemModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

public:
    explicit FileSystemModel(QObject *parent = nullptr);
    
    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    
    // Proprietà
    QString rootPath() const { return m_rootPath; }
    void setRootPath(const QString &path);

public slots:
    void refresh();
    QString filePath(const QModelIndex &index) const;
    bool isDir(const QModelIndex &index) const;
    QModelIndex indexFromPath(const QString &path) const;

signals:
    void rootPathChanged();
    void directoryChanged();

private slots:
    void onDirectoryChanged(const QString &path);
    void onFileChanged(const QString &path);

private:
    struct FileNode {
        QString name;
        QString path;
        bool isDirectory;
        QList<FileNode*> children;
        FileNode *parent;
        
        FileNode(const QString &n = "", const QString &p = "", bool dir = false, FileNode *par = nullptr)
            : name(n), path(p), isDirectory(dir), parent(par) {}
        
        ~FileNode() {
            qDeleteAll(children);
        }
    };
    
    QString m_rootPath;
    FileNode *m_rootNode;
    QFileSystemWatcher *m_watcher;
    
    void buildTree();
    void populateNode(FileNode *node);
    FileNode *nodeFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromNode(FileNode *node) const;
};

#endif // FILESYSTEMMODEL_H
