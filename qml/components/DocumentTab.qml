import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: documentTab
    
    property var document: null
    property bool isActive: false
    
    signal clicked()
    signal closeRequested()
    
    // Tema
    property color primaryBg: "#0e1013"
    property color secondaryBg: "#131419"
    property color accentBg: "#1e1e1e"
    property color borderColor: "#2d2d2d"
    property color textPrimary: "#dcddde"
    property color textSecondary: "#b3b3b3"
    property color accent: "#7c3aed"
    property color accentHover: "#8b5cf6"
    
    width: Math.max(120, titleText.contentWidth + 60)
    height: 32
    
    color: isActive ? accentBg : (mouseArea.containsMouse ? secondaryBg : "transparent")
    border.color: isActive ? accent : (mouseArea.containsMouse ? borderColor : "transparent")
    border.width: 1
    radius: 6
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: documentTab.clicked()
    }
    
    Row {
        anchors.centerIn: parent
        spacing: 8
        
        // Indicatore modifica
        Text {
            visible: document && document.isModified
            text: "●"
            color: "#f59e0b"
            font.pixelSize: 12
            anchors.verticalCenter: parent.verticalCenter
        }
        
        // Titolo documento
        Text {
            id: titleText
            text: document ? document.title : "Untitled"
            color: textPrimary
            font.pixelSize: 11
            font.family: "Segoe UI"
            font.weight: isActive ? Font.Medium : Font.Normal
            anchors.verticalCenter: parent.verticalCenter
            
            // Limita lunghezza
            elide: Text.ElideRight
            maximumLineCount: 1
        }
        
        // Pulsante chiusura
        Rectangle {
            width: 16
            height: 16
            radius: 2
            color: closeMouseArea.containsMouse ? "#ef4444" : "transparent"
            border.color: closeMouseArea.containsMouse ? "#dc2626" : borderColor
            border.width: 1
            anchors.verticalCenter: parent.verticalCenter
            
            Text {
                text: "×"
                color: textPrimary
                font.pixelSize: 10
                font.weight: Font.Bold
                anchors.centerIn: parent
            }
            
            MouseArea {
                id: closeMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    mouse.accepted = true
                    closeRequested()
                }
            }
        }
    }
}
