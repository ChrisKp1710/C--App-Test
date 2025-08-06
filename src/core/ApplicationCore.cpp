#include "ApplicationCore.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

ApplicationCore::ApplicationCore(QObject *parent)
    : QObject(parent)
    , m_fileSystem(new FileSystemModel(this))
{
    // Inizializza workspace di default
    QString defaultWorkspace = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/DevNotes";
    setCurrentWorkspace(defaultWorkspace);
}

void ApplicationCore::setCurrentWorkspace(const QString &workspace)
{
    if (m_currentWorkspace == workspace)
        return;
    
    m_currentWorkspace = workspace;
    
    // Crea directory se non esiste
    QDir dir;
    if (!dir.exists(workspace)) {
        dir.mkpath(workspace);
    }
    
    // Aggiorna il filesystem model
    m_fileSystem->setRootPath(workspace);
    
    // Carica documenti esistenti
    loadWorkspaceDocuments();
    
    emit currentWorkspaceChanged();
}

QQmlListProperty<DocumentModel> ApplicationCore::documentsProperty()
{
    return QQmlListProperty<DocumentModel>(this, &m_documents);
}

void ApplicationCore::createNewDocument(const QString &title)
{
    DocumentModel *document = new DocumentModel(this);
    document->setTitle(title.isEmpty() ? "Untitled" : title);
    document->setContent("# " + document->title() + "\n\n");
    
    m_documents.append(document);
    emit documentsChanged();
    emit documentOpened(document);
}

void ApplicationCore::openDocument(const QString &filePath)
{
    // Verifica se il documento è già aperto
    for (DocumentModel *doc : m_documents) {
        if (doc->filePath() == filePath) {
            emit documentOpened(doc);
            return;
        }
    }
    
    // Carica nuovo documento
    DocumentModel *document = new DocumentModel(this);
    if (document->loadFromFile(filePath)) {
        m_documents.append(document);
        emit documentsChanged();
        emit documentOpened(document);
    } else {
        delete document;
        qWarning() << "Impossibile aprire il file:" << filePath;
    }
}

void ApplicationCore::saveDocument(DocumentModel *document)
{
    if (!document) return;
    
    if (document->filePath().isEmpty()) {
        // Nuovo documento - richiedi dove salvarlo
        QString fileName = QFileDialog::getSaveFileName(
            nullptr,
            "Salva Documento",
            m_currentWorkspace + "/" + document->title() + ".md",
            "Markdown Files (*.md);;Text Files (*.txt);;All Files (*)"
        );
        
        if (!fileName.isEmpty()) {
            document->setFilePath(fileName);
        } else {
            return; // Cancellato dall'utente
        }
    }
    
    document->saveToFile();
}

void ApplicationCore::saveAllDocuments()
{
    for (DocumentModel *document : m_documents) {
        if (document->isModified()) {
            saveDocument(document);
        }
    }
}

void ApplicationCore::openWorkspaceFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Seleziona Cartella Workspace",
        m_currentWorkspace
    );
    
    if (!folderPath.isEmpty()) {
        setCurrentWorkspace(folderPath);
    }
}

void ApplicationCore::createFolder(const QString &name)
{
    QDir dir(m_currentWorkspace);
    if (dir.mkdir(name)) {
        m_fileSystem->refresh();
    }
}

void ApplicationCore::deleteFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.remove()) {
        // Rimuovi documento dalla lista se aperto
        for (int i = 0; i < m_documents.size(); ++i) {
            if (m_documents[i]->filePath() == filePath) {
                m_documents[i]->deleteLater();
                m_documents.removeAt(i);
                emit documentsChanged();
                break;
            }
        }
        m_fileSystem->refresh();
    }
}

void ApplicationCore::searchInAllDocuments(const QString &query)
{
    QStringList results;
    
    for (DocumentModel *document : m_documents) {
        if (document->content().contains(query, Qt::CaseInsensitive)) {
            results.append(document->title() + " - " + document->filePath());
        }
    }
    
    emit searchResultsReady(results);
}

void ApplicationCore::navigateToDocument(const QString &documentId)
{
    for (DocumentModel *document : m_documents) {
        if (document->title() == documentId || document->filePath().endsWith(documentId)) {
            emit documentOpened(document);
            break;
        }
    }
}

void ApplicationCore::loadWorkspaceDocuments()
{
    // Pulisci documenti esistenti
    qDeleteAll(m_documents);
    m_documents.clear();
    
    // Scansiona cartella workspace per file markdown
    QDir dir(m_currentWorkspace);
    QStringList filters;
    filters << "*.md" << "*.txt" << "*.markdown";
    
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);
    
    for (const QFileInfo &fileInfo : files) {
        DocumentModel *document = new DocumentModel(this);
        if (document->loadFromFile(fileInfo.absoluteFilePath())) {
            m_documents.append(document);
        } else {
            delete document;
        }
    }
    
    emit documentsChanged();
}
