#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QDebug>
#include "core/ApplicationCore.h"
#include "models/DocumentModel.h"
#include "models/FileSystemModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qDebug() << "🚀 DevNotes Starting...";
    
    // Configurazione applicazione
    app.setApplicationName("DevNotes");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Windows Helper Solutions");
    
    qDebug() << "📝 Registering QML types...";
    
    // Registrazione tipi QML
    qmlRegisterType<DocumentModel>("DevNotes", 1, 0, "DocumentModel");
    qmlRegisterType<FileSystemModel>("DevNotes", 1, 0, "FileSystemModel");
    
    // Creazione core dell'applicazione
    ApplicationCore core;
    
    qDebug() << "🔧 Creating QML engine...";
    
        // Imposta il motore QML
    QQmlApplicationEngine engine;
    
    // Imposta lo stile QML per evitare avvertimenti di personalizzazione
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    
    // Esposizione del core al QML
    engine.rootContext()->setContextProperty("applicationCore", &core);
    
    qDebug() << "📱 Loading QML...";
    
    // Caricamento interfaccia principale
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "❌ Failed to load QML!";
        return -1;
    }
    
    qDebug() << "✅ QML loaded successfully!";
    qDebug() << "🎬 Starting event loop...";
    
    return app.exec();
}
