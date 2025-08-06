#include "DocumentModel.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>
#include <QStringConverter>

DocumentModel::DocumentModel(QObject *parent)
    : QObject(parent)
    , m_isModified(false)
    , m_wordCount(0)
{
    updateLastModified();
}

void DocumentModel::setTitle(const QString &title)
{
    if (m_title == title)
        return;
    
    m_title = title;
    markAsModified();
    emit titleChanged();
}

void DocumentModel::setContent(const QString &content)
{
    if (m_content == content)
        return;
    
    m_content = content;
    updateWordCount();
    markAsModified();
    emit contentChanged();
}

void DocumentModel::setFilePath(const QString &filePath)
{
    if (m_filePath == filePath)
        return;
    
    m_filePath = filePath;
    
    // Aggiorna titolo dal nome file se necessario
    if (m_title.isEmpty() || m_title == "Untitled") {
        QFileInfo fileInfo(filePath);
        setTitle(fileInfo.baseName());
    }
    
    emit filePathChanged();
}

bool DocumentModel::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Impossibile aprire il file:" << filePath;
        return false;
    }
    
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    
    QString content = in.readAll();
    file.close();
    
    // Aggiorna proprietà
    setFilePath(filePath);
    setContent(content);
    
    // Segna come non modificato (appena caricato)
    markAsSaved();
    
    return true;
}

bool DocumentModel::saveToFile()
{
    if (m_filePath.isEmpty()) {
        qWarning() << "Nessun percorso file specificato per il salvataggio";
        return false;
    }
    
    return saveToFile(m_filePath);
}

bool DocumentModel::saveToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Impossibile aprire il file per la scrittura:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << m_content;
    file.close();
    
    // Aggiorna percorso se diverso
    if (m_filePath != filePath) {
        setFilePath(filePath);
    }
    
    markAsSaved();
    return true;
}

void DocumentModel::insertText(const QString &text, int position)
{
    if (position < 0 || position > m_content.length()) {
        position = m_content.length();
    }
    
    QString newContent = m_content;
    newContent.insert(position, text);
    setContent(newContent);
}

void DocumentModel::deleteText(int start, int length)
{
    if (start < 0 || start >= m_content.length() || length <= 0) {
        return;
    }
    
    QString newContent = m_content;
    newContent.remove(start, length);
    setContent(newContent);
}

void DocumentModel::replaceText(int start, int length, const QString &replacement)
{
    if (start < 0 || start >= m_content.length() || length < 0) {
        return;
    }
    
    QString newContent = m_content;
    newContent.replace(start, length, replacement);
    setContent(newContent);
}

void DocumentModel::markAsModified()
{
    if (!m_isModified) {
        m_isModified = true;
        updateLastModified();
        emit isModifiedChanged();
    }
}

void DocumentModel::markAsSaved()
{
    if (m_isModified) {
        m_isModified = false;
        updateLastModified();
        emit isModifiedChanged();
    }
}

QString DocumentModel::getPreview(int maxLength) const
{
    if (m_content.length() <= maxLength) {
        return m_content;
    }
    
    QString preview = m_content.left(maxLength);
    
    // Trova l'ultimo spazio per non tagliare parole a metà
    int lastSpace = preview.lastIndexOf(' ');
    if (lastSpace > maxLength * 0.8) { // Se lo spazio è ragionevolmente vicino
        preview = preview.left(lastSpace);
    }
    
    return preview + "...";
}

void DocumentModel::updateWordCount()
{
    // Conta parole nel contenuto
    QStringList words = m_content.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int newCount = words.size();
    
    if (m_wordCount != newCount) {
        m_wordCount = newCount;
        emit wordCountChanged();
    }
}

void DocumentModel::updateLastModified()
{
    m_lastModified = QDateTime::currentDateTime();
    emit lastModifiedChanged();
}
