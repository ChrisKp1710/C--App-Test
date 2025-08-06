import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: outlineView
    
    property var document: null
    
    // Tema
    property color primaryBg: "#0e1013"
    property color secondaryBg: "#131419"
    property color accentBg: "#1e1e1e"
    property color borderColor: "#2d2d2d"
    property color textPrimary: "#dcddde"
    property color textSecondary: "#b3b3b3"
    property color textMuted: "#6c7086"
    property color accent: "#7c3aed"
    
    color: "transparent"
    
    ScrollView {
        anchors.fill: parent
        anchors.margins: 12
        
        Column {
            width: parent.width
            spacing: 8
            
            // Messaggio quando nessun documento
            Text {
                visible: !document
                width: parent.width
                text: "Nessun documento\nselezionato"
                color: textMuted
                font.pixelSize: 12
                font.family: "Segoe UI"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
            
            // Outline headings
            Repeater {
                model: document ? parseMarkdownHeadings(document.content) : []
                
                Rectangle {
                    width: parent.width
                    height: 32
                    color: mouseArea.containsMouse ? accentBg : "transparent"
                    border.color: mouseArea.containsMouse ? borderColor : "transparent"
                    border.width: 1
                    radius: 4
                    
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            // TODO: Scorri al heading nel documento
                            console.log("Navigate to heading:", modelData.text)
                        }
                    }
                    
                    Row {
                        anchors.left: parent.left
                        anchors.leftMargin: modelData.level * 12 + 8
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 6
                        
                        Text {
                            text: getHeadingIcon(modelData.level)
                            color: textSecondary
                            font.pixelSize: 10
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        
                        Text {
                            text: modelData.text
                            color: textPrimary
                            font.pixelSize: 11
                            font.family: "Segoe UI"
                            font.weight: modelData.level <= 2 ? Font.Medium : Font.Normal
                            anchors.verticalCenter: parent.verticalCenter
                            elide: Text.ElideRight
                            maximumLineCount: 1
                        }
                    }
                }
            }
            
            // Sezione link/riferimenti (placeholder)
            Rectangle {
                visible: document
                width: parent.width
                height: 1
                color: borderColor
            }
            
            Text {
                visible: document
                text: "🔗 LINK"
                color: textMuted
                font.pixelSize: 10
                font.weight: Font.Medium
                font.family: "Segoe UI"
            }
            
            Text {
                visible: document
                text: "Nessun link trovato"
                color: textMuted
                font.pixelSize: 10
                font.family: "Segoe UI"
                font.style: Font.Italic
            }
        }
    }
    
    function parseMarkdownHeadings(content) {
        if (!content) return []
        
        const lines = content.split('\n')
        const headings = []
        
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim()
            
            // Cerca headings in formato # ## ### etc.
            const match = line.match(/^(#{1,6})\s+(.+)$/)
            if (match) {
                headings.push({
                    level: match[1].length,
                    text: match[2],
                    line: i + 1
                })
            }
        }
        
        return headings
    }
    
    function getHeadingIcon(level) {
        switch (level) {
            case 1: return "📚"
            case 2: return "📖"
            case 3: return "📄"
            case 4: return "📝"
            case 5: return "🔹"
            case 6: return "🔸"
            default: return "•"
        }
    }
}
