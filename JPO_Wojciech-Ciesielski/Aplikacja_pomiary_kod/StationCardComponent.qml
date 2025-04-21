// StationCardComponent.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: stationCard
    width: parent ? parent.width : 100
    height: stationContent.height + 30
    color: "white"
    radius: 5
    border.color: borderColor
    border.width: 1

    // Properties
    property string stationId: ""
    property string calcDate: ""
    property string sourceDate: ""
    property string indexLevel: ""
    property int indexLevelId: -1

    Column {
        id: stationContent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 15
        spacing: 8

        Text {
            text: "ID stacji: " + stationId
            font.pixelSize: 16
            font.bold: true
            color: textColor
        }

        Text {
            text: "Data obliczenia indeksu: " + calcDate
            font.pixelSize: 14
            color: textColor
            visible: calcDate !== ""
        }

        Text {
            text: "Data pobrania danych źródłowych: " + sourceDate
            font.pixelSize: 14
            color: textColor
            visible: sourceDate !== ""
        }

        Text {
            text: "Ogólny indeks jakości powietrza:"
            font.pixelSize: 14
            font.bold: true
            color: textColor
            visible: indexLevel !== ""
        }

        // Status indicator
        Rectangle {
            visible: indexLevel !== ""
            width: parent.width
            height: 30
            radius: 4
            color: {
                switch(indexLevelId) {
                    case 0: return "#00CB35"; // Bardzo dobry
                    case 1: return "#84C500"; // Dobry
                    case 2: return "#FFFF00"; // Umiarkowany
                    case 3: return "#FF9D00"; // Dostateczny
                    case 4: return "#FF0000"; // Zły
                    case 5: return "#990055"; // Bardzo zły
                    default: return "#CCCCCC"; // Brak danych
                }
            }

            Text {
                anchors.centerIn: parent
                text: indexLevel || "Brak danych"
                font.pixelSize: 14
                font.bold: true
                color: (indexLevelId === 2 || indexLevelId === 3) ? "black" : "white"
            }
        }
    }
}
