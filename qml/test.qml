import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 800
    height: 600
    visible: true
    title: "DevNotes - Test"
    
    color: "#0e1013"
    
    Text {
        anchors.centerIn: parent
        text: "🎉 DevNotes Qt6 Funziona!"
        color: "#dcddde"
        font.pixelSize: 24
        font.family: "Segoe UI"
    }
    
    Rectangle {
        width: 200
        height: 50
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 50
        color: "#7c3aed"
        radius: 8
        
        Text {
            anchors.centerIn: parent
            text: "DevNotes Ready!"
            color: "white"
            font.pixelSize: 14
            font.weight: Font.Bold
        }
    }
}
