import QtQuick 2.15
import QtQuick.Controls 2.15

TreeView {
    id: treeView
    
    signal fileSelected(string filePath)
    
    // Tema coerente
    property color primaryBg: "#0e1013"
    property color secondaryBg: "#131419"
    property color accentBg: "#1e1e1e"
    property color borderColor: "#2d2d2d"
    property color textPrimary: "#dcddde"
    property color textSecondary: "#b3b3b3"
    property color textMuted: "#6c7086"
    property color accent: "#7c3aed"
    property color accentHover: "#8b5cf6"
    
    delegate: Item {
        id: treeDelegate
        
        required property TreeView treeView
        required property bool isTreeNode
        required property bool expanded
        required property int hasChildren
        required property int depth
        
        width: treeView.width
        height: 32
        
        Rectangle {
            id: background
            anchors.fill: parent
            color: mouseArea.containsMouse ? accentBg : "transparent"
            border.color: mouseArea.containsMouse ? borderColor : "transparent"
            border.width: 1
            
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                
                onClicked: {
                    if (model.isDirectory) {
                        treeView.toggleExpanded(row)
                    } else {
                        fileSelected(model.filePath)
                    }
                }
                
                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: depth * 20 + 8
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 6
                    
                    // Indicatore espansione per cartelle
                    Text {
                        visible: model.isDirectory
                        text: expanded ? "📂" : "📁"
                        color: textSecondary
                        font.pixelSize: 12
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    
                    // Icona file
                    Text {
                        visible: !model.isDirectory
                        text: getFileIcon(model.name)
                        color: textSecondary
                        font.pixelSize: 12
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    
                    // Nome file/cartella
                    Text {
                        text: model.name || ""
                        color: textPrimary
                        font.pixelSize: 11
                        font.family: "Segoe UI"
                        anchors.verticalCenter: parent.verticalCenter
                        
                        // Evidenzia file markdown
                        font.weight: (model.name && model.name.endsWith(".md")) 
                            ? Font.Medium : Font.Normal
                    }
                }
            }
        }
    }
    
    function getFileIcon(fileName) {
        if (!fileName) return "📄"
        
        const ext = fileName.split('.').pop().toLowerCase()
        
        switch (ext) {
            case 'md':
            case 'markdown':
                return "📝"
            case 'txt':
                return "📄"
            case 'js':
            case 'ts':
                return "⚡"
            case 'html':
                return "🌐"
            case 'css':
                return "🎨"
            case 'json':
                return "🔧"
            case 'png':
            case 'jpg':
            case 'jpeg':
            case 'gif':
                return "🖼️"
            case 'pdf':
                return "📕"
            default:
                return "📄"
        }
    }
}
