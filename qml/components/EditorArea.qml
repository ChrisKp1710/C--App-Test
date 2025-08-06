import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: editorArea
    
    property var currentDocument: null
    
    // Tema
    property color primaryBg: "#0e1013"
    property color secondaryBg: "#131419"
    property color accentBg: "#1e1e1e"
    property color borderColor: "#2d2d2d"
    property color textPrimary: "#dcddde"
    property color textSecondary: "#b3b3b3"
    property color textMuted: "#6c7086"
    
    color: primaryBg
    
    // Editor di testo principale
    ScrollView {
        anchors.fill: parent
        anchors.margins: 20
        
        TextArea {
            id: textEditor
            
            text: currentDocument ? currentDocument.content : ""
            
            // Styling moderno
            color: textPrimary
            selectionColor: "#7c3aed"
            selectedTextColor: textPrimary
            font.family: "Consolas, 'Courier New', monospace"
            font.pixelSize: 14
            lineHeight: 1.6
            
            background: Rectangle {
                color: "transparent"
                border.color: "transparent"
            }
            
            // Placeholder quando nessun documento
            Text {
                visible: !currentDocument
                anchors.centerIn: parent
                text: "📝\n\nSeleziona un documento o creane uno nuovo\nper iniziare a scrivere"
                color: textMuted
                font.pixelSize: 16
                font.family: "Segoe UI"
                horizontalAlignment: Text.AlignHCenter
                lineHeight: 1.5
            }
            
            // Auto-save durante la digitazione
            onTextChanged: {
                if (currentDocument && currentDocument.content !== text) {
                    currentDocument.content = text
                }
            }
            
            // Evidenziazione sintassi Markdown (base)
            Component.onCompleted: {
                // Configura l'editor per Markdown
                wrapMode = TextArea.Wrap
                selectByMouse = true
                selectByKeyboard = true
            }
            
            // Gestione shortcuts
            Keys.onPressed: function(event) {
                // Ctrl+S per salvare
                if (event.modifiers & Qt.ControlModifier && event.key === Qt.Key_S) {
                    if (currentDocument) {
                        applicationCore.saveDocument(currentDocument)
                    }
                    event.accepted = true
                }
                
                // Ctrl+N per nuovo documento
                if (event.modifiers & Qt.ControlModifier && event.key === Qt.Key_N) {
                    applicationCore.createNewDocument()
                    event.accepted = true
                }
                
                // Ctrl+O per aprire
                if (event.modifiers & Qt.ControlModifier && event.key === Qt.Key_O) {
                    applicationCore.openWorkspaceFolder()
                    event.accepted = true
                }
            }
        }
    }
    
    // Toolbar floating (opzionale)
    Rectangle {
        visible: currentDocument !== null
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        
        width: 200
        height: 40
        color: accentBg
        border.color: borderColor
        border.width: 1
        radius: 8
        opacity: 0.9
        
        Row {
            anchors.centerIn: parent
            spacing: 12
            
            Text {
                text: "📝"
                color: textSecondary
                font.pixelSize: 14
                anchors.verticalCenter: parent.verticalCenter
            }
            
            Text {
                text: currentDocument ? currentDocument.title : ""
                color: textPrimary
                font.pixelSize: 11
                font.family: "Segoe UI"
                font.weight: Font.Medium
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
            }
            
            Text {
                visible: currentDocument && currentDocument.isModified
                text: "●"
                color: "#f59e0b"
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
    
    // Status bar in basso
    Rectangle {
        visible: currentDocument !== null
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        color: accentBg
        border.color: borderColor
        border.width: 1
        
        Row {
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20
            
            Text {
                text: currentDocument ? "Parole: " + currentDocument.wordCount : ""
                color: textSecondary
                font.pixelSize: 10
                font.family: "Segoe UI"
            }
            
            Text {
                text: currentDocument ? "Caratteri: " + currentDocument.content.length : ""
                color: textSecondary
                font.pixelSize: 10
                font.family: "Segoe UI"
            }
            
            Text {
                text: "Markdown"
                color: textMuted
                font.pixelSize: 10
                font.family: "Segoe UI"
            }
        }
        
        Text {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: currentDocument && currentDocument.lastModified 
                ? "Modificato: " + Qt.formatDateTime(currentDocument.lastModified, "hh:mm")
                : ""
            color: textMuted
            font.pixelSize: 10
            font.family: "Segoe UI"
        }
    }
}
