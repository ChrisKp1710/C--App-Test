#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <QObject>
#include <QString>
#include <QDateTime>

class DocumentModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(bool isModified READ isModified NOTIFY isModifiedChanged)
    Q_PROPERTY(QDateTime lastModified READ lastModified NOTIFY lastModifiedChanged)
    Q_PROPERTY(int wordCount READ wordCount NOTIFY wordCountChanged)

public:
    explicit DocumentModel(QObject *parent = nullptr);
    
    // Proprietà documento
    QString title() const { return m_title; }
    void setTitle(const QString &title);
    
    QString content() const { return m_content; }
    void setContent(const QString &content);
    
    QString filePath() const { return m_filePath; }
    void setFilePath(const QString &filePath);
    
    bool isModified() const { return m_isModified; }
    QDateTime lastModified() const { return m_lastModified; }
    int wordCount() const { return m_wordCount; }

public slots:
    // Operazioni file
    bool loadFromFile(const QString &filePath);
    bool saveToFile();
    bool saveToFile(const QString &filePath);
    
    // Operazioni contenuto
    void insertText(const QString &text, int position);
    void deleteText(int start, int length);
    void replaceText(int start, int length, const QString &replacement);
    
    // Utilità
    void markAsModified();
    void markAsSaved();
    QString getPreview(int maxLength = 100) const;

signals:
    void titleChanged();
    void contentChanged();
    void filePathChanged();
    void isModifiedChanged();
    void lastModifiedChanged();
    void wordCountChanged();

private:
    QString m_title;
    QString m_content;
    QString m_filePath;
    bool m_isModified;
    QDateTime m_lastModified;
    int m_wordCount;
    
    void updateWordCount();
    void updateLastModified();
};

#endif // DOCUMENTMODEL_H
