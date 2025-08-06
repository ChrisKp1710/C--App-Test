import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import DevNotes 1.0

ApplicationWindow {
    id: mainWindow
    width: 1400
    height: 900
    visible: true
    title: "DevNotes - " + (applicationCore.currentWorkspace || "No Workspace")
    
    color: "#0e1013"
    
    // Tema Obsidian autentico
    property color primaryBg: "#0e1013"
    property color secondaryBg: "#131419"
    property color accentBg: "#1e1e1e"
    property color borderColor: "#2d2d2d"
    property color textPrimary: "#dcddde"
    property color textSecondary: "#b3b3b3"
    property color textMuted: "#6c7086"
    property color accent: "#7c3aed"
    property color accentHover: "#8b5cf6"
    
    // Layout principale a 3 pannelli
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // Sidebar sinistra - File Explorer
        Rectangle {
            id: leftSidebar
            Layout.preferredWidth: 280
            Layout.fillHeight: true
            color: secondaryBg
            border.color: borderColor
            border.width: 1
            
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 0
                
                // Header workspace
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    color: accentBg
                    border.color: borderColor
                    border.width: 1
                    
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        
                        Text {
                            text: "📁 WORKSPACE"
                            color: textPrimary
                            font.pixelSize: 11
                            font.weight: Font.Medium
                            font.family: "Segoe UI"
                            Layout.fillWidth: true
                        }
                        
                        Button {
                            text: "+"
                            font.pixelSize: 14
                            font.weight: Font.Bold
                            width: 24
                            height: 24
                            background: Rectangle {
                                color: parent.hovered ? accentHover : accent
                                radius: 4
                                border.color: borderColor
                            }
                            contentItem: Text {
                                text: parent.text
                                color: textPrimary
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font: parent.font
                            }
                            onClicked: applicationCore.openWorkspaceFolder()
                        }
                    }
                }
                
                // File tree
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    
                    ListView {
                        id: fileTree
                        anchors.fill: parent
                        model: applicationCore.fileSystem
                        
                        delegate: Rectangle {
                            width: fileTree.width
                            height: 32
                            color: mouseArea.containsMouse ? accentBg : "transparent"
                            border.color: mouseArea.containsMouse ? borderColor : "transparent"
                            border.width: 1
                            
                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    if (model && model.filePath) {
                                        applicationCore.openDocument(model.filePath)
                                    }
                                }
                            }
                            
                            Row {
                                anchors.left: parent.left
                                anchors.leftMargin: 8
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 6
                                
                                Text {
                                    text: model && model.isDirectory ? "📁" : "📄"
                                    color: textSecondary
                                    font.pixelSize: 12
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                
                                Text {
                                    text: model ? (model.name || "Unknown") : "Unknown"
                                    color: textPrimary
                                    font.pixelSize: 11
                                    font.family: "Segoe UI"
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                }
                
                // Azioni rapide
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                    color: accentBg
                    border.color: borderColor
                    border.width: 1
                    
                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 8
                        
                        Button {
                            text: "📄 Nuovo"
                            font.pixelSize: 10
                            background: Rectangle {
                                color: parent.hovered ? accentHover : accent
                                radius: 6
                                border.color: borderColor
                            }
                            contentItem: Text {
                                text: parent.text
                                color: textPrimary
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font: parent.font
                            }
                            onClicked: applicationCore.createNewDocument()
                        }
                        
                        Button {
                            text: "💾 Salva"
                            font.pixelSize: 10
                            background: Rectangle {
                                color: parent.hovered ? accentHover : accent
                                radius: 6
                                border.color: borderColor
                            }
                            contentItem: Text {
                                text: parent.text
                                color: textPrimary
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font: parent.font
                            }
                            onClicked: applicationCore.saveAllDocuments()
                        }
                    }
                }
            }
        }
        
        // Area centrale - Editor
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: primaryBg
            border.color: borderColor
            border.width: 1
            
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                
                // Tab bar documenti
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    color: accentBg
                    border.color: borderColor
                    border.width: 1
                    
                    ScrollView {
                        anchors.fill: parent
                        anchors.margins: 4
                        
                        RowLayout {
                            height: 32
                            spacing: 2
                            
                            Repeater {
                                model: applicationCore.documents
                                
                                Rectangle {
                                    width: Math.max(120, tabText.contentWidth + 60)
                                    height: 32
                                    color: accentBg
                                    border.color: borderColor
                                    border.width: 1
                                    radius: 6
                                    
                                    Text {
                                        id: tabText
                                        anchors.centerIn: parent
                                        text: modelData ? modelData.title : "Untitled"
                                        color: textPrimary
                                        font.pixelSize: 11
                                        font.family: "Segoe UI"
                                    }
                                    
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            // TODO: Set active document
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                // Area editor
                Rectangle {
                    id: editorArea
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: primaryBg
                    border.color: borderColor
                    border.width: 1
                    
                    property var currentDocument: null
                    
                    ScrollView {
                        anchors.fill: parent
                        anchors.margins: 20
                        
                        TextArea {
                            id: textEditor
                            
                            text: editorArea.currentDocument ? editorArea.currentDocument.content : ""
                            
                            color: textPrimary
                            selectionColor: "#7c3aed"
                            selectedTextColor: textPrimary
                            font.family: "Consolas, 'Courier New', monospace"
                            font.pixelSize: 14
                            
                            background: Rectangle {
                                color: "transparent"
                            }
                            
                            Text {
                                visible: !editorArea.currentDocument
                                anchors.centerIn: parent
                                text: "📝\n\nSeleziona un documento o creane uno nuovo\nper iniziare a scrivere"
                                color: textMuted
                                font.pixelSize: 16
                                font.family: "Segoe UI"
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }
            }
        }
        
        // Sidebar destra - Outline/Properties
        Rectangle {
            id: rightSidebar
            Layout.preferredWidth: 320
            Layout.fillHeight: true
            color: secondaryBg
            border.color: borderColor
            border.width: 1
            
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 0
                spacing: 0
                
                // Header outline
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    color: accentBg
                    border.color: borderColor
                    border.width: 1
                    
                    Text {
                        anchors.centerIn: parent
                        text: "📋 OUTLINE"
                        color: textPrimary
                        font.pixelSize: 11
                        font.weight: Font.Medium
                        font.family: "Segoe UI"
                    }
                }
                
                // Outline view
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    
                    Column {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 8
                        
                        Text {
                            text: editorArea.currentDocument ? "📋 OUTLINE" : "Nessun documento"
                            color: textMuted
                            font.pixelSize: 12
                            font.family: "Segoe UI"
                        }
                        
                        Text {
                            text: "Coming soon..."
                            color: textSecondary
                            font.pixelSize: 10
                            font.family: "Segoe UI"
                            font.italic: true
                        }
                    }
                }
                
                // Properties/Stats
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 120
                    color: accentBg
                    border.color: borderColor
                    border.width: 1
                    
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 8
                        
                        Text {
                            text: "📊 STATISTICHE"
                            color: textPrimary
                            font.pixelSize: 11
                            font.weight: Font.Medium
                            font.family: "Segoe UI"
                        }
                        
                        Text {
                            text: editorArea.currentDocument 
                                ? "Parole: " + editorArea.currentDocument.wordCount 
                                : "Nessun documento"
                            color: textSecondary
                            font.pixelSize: 10
                            font.family: "Segoe UI"
                        }
                        
                        Text {
                            text: editorArea.currentDocument && editorArea.currentDocument.isModified 
                                ? "⚠️ Non salvato" 
                                : "✅ Salvato"
                            color: editorArea.currentDocument && editorArea.currentDocument.isModified 
                                ? "#f59e0b" 
                                : "#10b981"
                            font.pixelSize: 10
                            font.family: "Segoe UI"
                        }
                    }
                }
            }
        }
    }
    
    // Collegamento segnali
    Connections {
        target: applicationCore
        function onDocumentOpened(document) {
            editorArea.currentDocument = document
        }
    }
}
