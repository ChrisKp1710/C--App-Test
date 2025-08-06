#include "FileSystemModel.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileSystemModel::FileSystemModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootNode(new FileNode())
    , m_watcher(new QFileSystemWatcher(this))
{
    connect(m_watcher, &QFileSystemWatcher::directoryChanged,
            this, &FileSystemModel::onDirectoryChanged);
    connect(m_watcher, &QFileSystemWatcher::fileChanged,
            this, &FileSystemModel::onFileChanged);
}

void FileSystemModel::setRootPath(const QString &path)
{
    if (m_rootPath == path)
        return;
    
    beginResetModel();
    
    // Rimuovi watchers precedenti
    if (!m_watcher->directories().isEmpty()) {
        m_watcher->removePaths(m_watcher->directories());
    }
    if (!m_watcher->files().isEmpty()) {
        m_watcher->removePaths(m_watcher->files());
    }
    
    m_rootPath = path;
    buildTree();
    
    endResetModel();
    emit rootPathChanged();
}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    
    FileNode *parentNode = parent.isValid() ? nodeFromIndex(parent) : m_rootNode;
    
    if (row >= parentNode->children.size())
        return QModelIndex();
    
    return createIndex(row, column, parentNode->children[row]);
}

QModelIndex FileSystemModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();
    
    FileNode *childNode = nodeFromIndex(child);
    FileNode *parentNode = childNode->parent;
    
    if (!parentNode || parentNode == m_rootNode)
        return QModelIndex();
    
    return indexFromNode(parentNode);
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    FileNode *parentNode = parent.isValid() ? nodeFromIndex(parent) : m_rootNode;
    return parentNode->children.size();
}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1; // Solo nome file per ora
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    FileNode *node = nodeFromIndex(index);
    
    switch (role) {
    case Qt::DisplayRole:
        return node->name;
    case Qt::DecorationRole:
        return QVariant(); // Rimuoviamo icone per semplicità
    case Qt::UserRole: // FilePath
        return node->path;
    case Qt::UserRole + 1: // IsDirectory
        return node->isDirectory;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FileSystemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Qt::DecorationRole] = "icon";
    roles[Qt::UserRole] = "filePath";
    roles[Qt::UserRole + 1] = "isDirectory";
    return roles;
}

void FileSystemModel::refresh()
{
    setRootPath(m_rootPath); // Ricostruisce tutto il tree
}

QString FileSystemModel::filePath(const QModelIndex &index) const
{
    if (!index.isValid())
        return QString();
    
    FileNode *node = nodeFromIndex(index);
    return node->path;
}

bool FileSystemModel::isDir(const QModelIndex &index) const
{
    if (!index.isValid())
        return false;
    
    FileNode *node = nodeFromIndex(index);
    return node->isDirectory;
}

QModelIndex FileSystemModel::indexFromPath(const QString &path) const
{
    // Implementazione semplificata - potrebbe essere ottimizzata
    std::function<QModelIndex(FileNode*, const QString&)> findPath;
    findPath = [&](FileNode *node, const QString &targetPath) -> QModelIndex {
        if (node->path == targetPath) {
            return indexFromNode(node);
        }
        
        for (FileNode *child : node->children) {
            QModelIndex result = findPath(child, targetPath);
            if (result.isValid()) {
                return result;
            }
        }
        
        return QModelIndex();
    };
    
    return findPath(m_rootNode, path);
}

void FileSystemModel::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path)
    // Per semplicità, ricostruiamo tutto
    refresh();
    emit directoryChanged();
}

void FileSystemModel::onFileChanged(const QString &path)
{
    Q_UNUSED(path)
    // Potresti implementare aggiornamenti più granulari qui
    emit directoryChanged();
}

void FileSystemModel::buildTree()
{
    // Pulisci albero esistente
    delete m_rootNode;
    m_rootNode = new FileNode("", m_rootPath, true);
    
    if (!m_rootPath.isEmpty() && QDir(m_rootPath).exists()) {
        populateNode(m_rootNode);
        
        // Aggiungi watcher per la directory root
        m_watcher->addPath(m_rootPath);
    }
}

void FileSystemModel::populateNode(FileNode *node)
{
    QDir dir(node->path);
    if (!dir.exists())
        return;
    
    // Aggiungi watcher per questa directory
    if (!m_watcher->directories().contains(node->path)) {
        m_watcher->addPath(node->path);
    }
    
    // Ottieni lista entry
    QFileInfoList entries = dir.entryInfoList(
        QDir::AllEntries | QDir::NoDotAndDotDot,
        QDir::DirsFirst | QDir::Name
    );
    
    for (const QFileInfo &info : entries) {
        FileNode *childNode = new FileNode(
            info.fileName(),
            info.absoluteFilePath(),
            info.isDir(),
            node
        );
        
        node->children.append(childNode);
        
        // Se è una directory, popolala ricorsivamente (solo primo livello per performance)
        if (info.isDir()) {
            populateNode(childNode);
        }
    }
}

FileSystemModel::FileNode *FileSystemModel::nodeFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return m_rootNode;
    
    return static_cast<FileNode*>(index.internalPointer());
}

QModelIndex FileSystemModel::indexFromNode(FileNode *node) const
{
    if (!node || node == m_rootNode)
        return QModelIndex();
    
    FileNode *parent = node->parent;
    if (!parent)
        return QModelIndex();
    
    int row = parent->children.indexOf(node);
    return createIndex(row, 0, node);
}
