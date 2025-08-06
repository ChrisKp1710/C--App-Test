#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QQmlListProperty>
#include "DocumentModel.h"
#include "FileSystemModel.h"

class ApplicationCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentWorkspace READ currentWorkspace WRITE setCurrentWorkspace NOTIFY currentWorkspaceChanged)
    Q_PROPERTY(QQmlListProperty<DocumentModel> documents READ documentsProperty NOTIFY documentsChanged)
    Q_PROPERTY(FileSystemModel* fileSystem READ fileSystem CONSTANT)

public:
    explicit ApplicationCore(QObject *parent = nullptr);
    
    // Proprietà workspace
    QString currentWorkspace() const { return m_currentWorkspace; }
    void setCurrentWorkspace(const QString &workspace);
    
    // Gestione documenti
    QQmlListProperty<DocumentModel> documentsProperty();
    FileSystemModel* fileSystem() const { return m_fileSystem; }

public slots:
    // Operazioni file
    void createNewDocument(const QString &title = "Untitled");
    void openDocument(const QString &filePath);
    void saveDocument(DocumentModel *document);
    void saveAllDocuments();
    
    // Operazioni workspace
    void openWorkspaceFolder();
    void createFolder(const QString &name);
    void deleteFile(const QString &filePath);
    
    // Ricerca e navigazione
    void searchInAllDocuments(const QString &query);
    void navigateToDocument(const QString &documentId);

signals:
    void currentWorkspaceChanged();
    void documentsChanged();
    void documentOpened(DocumentModel *document);
    void searchResultsReady(const QStringList &results);

private:
    QString m_currentWorkspace;
    QList<DocumentModel*> m_documents;
    FileSystemModel *m_fileSystem;
    
    void initializeWorkspace();
    void loadWorkspaceDocuments();
};

#endif // APPLICATIONCORE_H
