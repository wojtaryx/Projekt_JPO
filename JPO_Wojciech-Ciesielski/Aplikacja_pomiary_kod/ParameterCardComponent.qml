// ParameterCardComponent.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: parameterCard
    width: parent ? parent.width : 100
    height: parameterContent.height + 30
    color: "white"
    radius: 5
    border.color: borderColor
    border.width: 1

    // Properties
    property string stationId: ""
    property string paramName: ""
    property string paramCode: ""
    property string paramId: ""
    property string indexLevel: ""
    property int indexLevelId: -1
    property string calcDate: ""
    property string sourceDate: ""

    Column {
        id: parameterContent
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
            text: "Parametr: " + paramName + " (" + paramCode + ")"
            font.pixelSize: 14
            color: textColor
        }

        Text {
            text: "Kod parametru: " + paramCode
            font.pixelSize: 14
            color: textColor
        }

        Text {
            text: "ID parametru: " + (paramId !== "" ? paramId : "N/A")
            font.pixelSize: 14
            color: textColor
            visible: paramId !== ""
        }

        Text {
            text: "Data obliczenia: " + calcDate
            font.pixelSize: 14
            color: textColor
            visible: calcDate !== ""
        }

        Text {
            text: "Data danych źródłowych: " + sourceDate
            font.pixelSize: 14
            color: textColor
            visible: sourceDate !== ""
        }

        // Status indicator
        Rectangle {
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
