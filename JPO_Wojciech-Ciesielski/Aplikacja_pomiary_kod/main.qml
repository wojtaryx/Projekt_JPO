import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material 2.15
Window {
    id: appWindow
    width: 1080
    height: 1080
    visible: true
    title: "Monitor jakości powietrza - GIOŚ API"
    color: "#f5f5f5"

    // Kolory aplikacji
    readonly property color accentColor: "#3498db"
    readonly property color textColor: "#333333"
    readonly property color lightGray: "#e0e0e0"
    readonly property color borderColor: "#cccccc"
    readonly property color chartBarColor: "#3498db"
    readonly property color chartBarBorder: "#2980b9"
    readonly property color errorColor: "#e74c3c"

    function formatDate(date) {
        var year = date.getFullYear()
        var month = (date.getMonth() + 1).toString().padStart(2, '0')
        var day = date.getDate().toString().padStart(2, '0')
        return year + "-" + month + "-" + day
    }

    function formatTime(date) {
        var hours = date.getHours().toString().padStart(2, '0')
        var minutes = date.getMinutes().toString().padStart(2, '0')
        return hours + ":" + minutes
    }

    function formatDateDisplay(date) {
        return date.getDate() + "." + (date.getMonth() + 1) + "." + date.getFullYear() +
               " " + date.getHours() + ":" + (date.getMinutes() < 10 ? "0" : "") + date.getMinutes()
    }
    function filterDateRange() {
        try {
            // Połącz datę i czas
            var startDateTimeStr = startDateField.text + "T" + startTimeField.text + ":00"
            var endDateTimeStr = endDateField.text + "T" + endTimeField.text + ":00"

            // Konwersja na obiekty Date
            var startDateTime = new Date(startDateTimeStr)
            var endDateTime = new Date(endDateTimeStr)

            // Sprawdź poprawność dat
            if (isNaN(startDateTime.getTime()) || isNaN(endDateTime.getTime())) {
                mainWindow.hasError = true
                mainWindow.errorMessage = "Niepoprawny format daty"
                dateFilterActive.checked = false
                return
            }

            if (startDateTime >= endDateTime) {
                mainWindow.hasError = true
                mainWindow.errorMessage = "Data początkowa musi być wcześniejsza niż końcowa"
                dateFilterActive.checked = false
                return
            }

            // Aktualizacja tekstu z zakresem
            chartRangeDisplay.text = "Zakres: " + formatDateDisplay(startDateTime) + " - " + formatDateDisplay(endDateTime)

            // Tutaj zmodyfikujemy istniejącą właściwość w canvas, aby uwzględniała daty
            chartCanvas.startDate = startDateTime.getTime()
            chartCanvas.endDate = endDateTime.getTime()
            chartCanvas.useCustomDateRange = true
            chartCanvas.requestPaint()

            mainWindow.hasError = false
            mainWindow.errorMessage = ""

        } catch (e) {
            mainWindow.hasError = true
            mainWindow.errorMessage = "Błąd: " + e.toString()
            dateFilterActive.checked = false
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Nagłówek aplikacji
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: accentColor
            radius: 5

            Text {
                anchors.centerIn: parent
                text: "Monitor jakości powietrza - GIOŚ API"
                font.pixelSize: 22
                font.bold: true
                color: "white"
            }
        }

        // Zakładki w zmienionej kolejności
        TabBar {
            id: tabBar
            Layout.fillWidth: true
            position: TabBar.Header

            background: Rectangle {
                color: lightGray
                radius: 5
            }

            TabButton {
                text: "Stacje pomiarowe"
                font.pixelSize: 14

                background: Rectangle {
                    color: tabBar.currentIndex === 0 ? "white" : lightGray
                    border.color: tabBar.currentIndex === 0 ? accentColor : "transparent"
                    border.width: tabBar.currentIndex === 0 ? 2 : 0
                    radius: 5

                }
            }

            TabButton {
                text: "Czujniki stacji"
                font.pixelSize: 14

                background: Rectangle {
                    color: tabBar.currentIndex === 1 ? "white" : lightGray
                    border.color: tabBar.currentIndex === 1 ? accentColor : "transparent"
                    border.width: tabBar.currentIndex === 1 ? 2 : 0
                    radius: 5
                }
            }

            TabButton {
                text: "Dane z sensora"
                font.pixelSize: 14

                background: Rectangle {
                    color: tabBar.currentIndex === 2 ? "white" : lightGray
                    border.color: tabBar.currentIndex === 2 ? accentColor : "transparent"
                    border.width: tabBar.currentIndex === 2 ? 2 : 0
                    radius: 5
                }
            }
            TabButton {
                text: "Indeks jakości powietrza"
                font.pixelSize: 14

                background: Rectangle {
                    color: tabBar.currentIndex === 3 ? "white" : lightGray
                    border.color: tabBar.currentIndex === 3 ? accentColor : "transparent"
                    border.width: tabBar.currentIndex === 3 ? 2 : 0
                    radius: 5
                }
            }
            TabButton {
                text: "Cache"
                width: implicitWidth
                height: tabBar.height

                background: Rectangle {
                    color: tabBar.currentIndex === 3 ? "white" : lightGray
                    border.color: tabBar.currentIndex === 3 ? accentColor : "transparent"
                    border.width: tabBar.currentIndex === 3 ? 2 : 0
                    radius: 5
                }
            }
            TabButton{
                CheckBox {
                    id: saveToFileCheckBox
                    text: qsTr("Zezwalaj na zapis do pliku")
                    checked: mainWindow.allowSaveToFile  // Bind to C++ property
                    onCheckedChanged: {
                        mainWindow.allowSaveToFile = checked  // Update C++ property when changed
                    }
                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Gdy zaznaczone, zapis do pliku jest aktywny")
                }

            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Tab 1: Stacje pomiarowe
            ColumnLayout {
                spacing: 20

                // Panel z instrukcjami
                Rectangle {
                    Layout.fillWidth: true
                    height: 70
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: "Wyszukaj stacje pomiarowe"
                            font.pixelSize: 16
                            font.bold: true
                            color: textColor
                        }

                        Text {
                            text: "Wpisz nazwę miasta, aby znaleźć stacje lub pozostaw puste pole, aby wyświetlić wszystkie stacje"
                            font.pixelSize: 12
                            color: Qt.darker(textColor, 1.3)
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }

                    }
                }

                // Panel wyszukiwania
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        TextField {
                            id: cityNameInput
                            Layout.fillWidth: true
                            placeholderText: "Wpisz nazwę miasta (puste pole = wszystkie stacje)"
                            selectByMouse: true
                            font.pixelSize: 14

                            background: Rectangle {
                                border.color: cityNameInput.activeFocus ? accentColor : borderColor
                                border.width: cityNameInput.activeFocus ? 2 : 1
                                radius: 4
                            }

                            Keys.onReturnPressed: {
                                searchStationsButton.clicked()
                            }
                        }

                        Button {
                            id: searchStationsButton
                            text: "Szukaj"
                            enabled: !mainWindow.isLoadingStations

                            contentItem: Text {
                                text: searchStationsButton.text
                                font.pixelSize: 14
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: searchStationsButton.enabled ? (searchStationsButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor) : Qt.lighter(accentColor, 1.4)
                                radius: 4
                            }

                            onClicked: {
                                mainWindow.fetchStations(cityNameInput.text.trim())
                            }
                        }

                    }
                }

                // Status panel
                RowLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    height: 30
                    visible: mainWindow.isLoadingStations || mainWindow.hasStationsError

                    BusyIndicator {
                        running: mainWindow.isLoadingStations
                        visible: mainWindow.isLoadingStations
                        width: 24
                        height: 24

                        contentItem: Item {
                            implicitWidth: 24
                            implicitHeight: 24



                            RotationAnimator {
                                target: busyIndicator
                                from: 0
                                to: 360
                                duration: 1000
                                running: true
                                loops: Animation.Infinite
                            }
                        }
                    }

                    Text {
                        visible: mainWindow.isLoadingStations
                        text: "Ładowanie stacji..."
                        font.pixelSize: 14
                        color: textColor
                    }

                    Text {
                        visible: mainWindow.hasStationsError
                        text: mainWindow.stationsErrorMessage
                        color: errorColor
                        font.pixelSize: 14
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                }

                // Wyniki wyszukiwania
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ScrollView {
                        anchors.fill: parent
                        anchors.margins: 15
                        clip: true
                        ScrollBar.vertical.policy: ScrollBar.AsNeeded

                        ListView {
                            id: stationsListView
                            width: parent.width
                            height: parent.height
                            model: parseStationsData(mainWindow.stationsData)
                            spacing: 10

                            header: Text {
                                width: stationsListView.width
                                text: {
                                    if (stationsListView.model.length > 0) {
                                        if (mainWindow.stationsData.startsWith("Wszystkie stacje"))
                                            return "Wszystkie stacje pomiarowe:";
                                        else if (mainWindow.stationsData.indexOf("Stacje pomiarowe w mieście") === 0)
                                            return mainWindow.stationsData.split("\n\n")[0];
                                    }
                                    return "";
                                }
                                visible: text !== ""
                                font.pixelSize: 16
                                font.bold: true
                                color: textColor
                                wrapMode: Text.WordWrap
                                bottomPadding: 15
                            }

                            delegate: Rectangle {
                                id: stationItem
                                width: stationsListView.width
                                height: contentColumn.height + 24
                                border.color: "#cccccc"
                                border.width: 1
                                radius: 4
                                color: "white"

                                // Dodanie efektu cienia
                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 0
                                    verticalOffset: 2
                                    radius: 8.0
                                    samples: 17
                                    color: "#30000000"
                                }

                                // Efekt podświetlenia przy najechaniu
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: stationItem.color = "#f8f8f8"
                                    onExited: stationItem.color = "white"
                                    onClicked: {
                                        onStationSelected: {
                                            tabBar.currentIndex = 1 // Przełącz na Tab 2
                                            stationIdInput.text = modelData.id // Ustaw ID stacji
                                        }
                                    }
                                }

                                ColumnLayout {
                                    id: contentColumn
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    anchors.top: parent.top
                                    anchors.margins: 12
                                    spacing: 6

                                    // Pierwsza linia: ID || Nazwa || Miasto
                                    Text {
                                        Layout.fillWidth: true
                                        text: modelData.id + " || " + modelData.name + " || " + modelData.city
                                        font.pixelSize: 15
                                        font.bold: true
                                        color: "#333333"
                                        wrapMode: Text.WordWrap
                                    }

                                    // Linia oddzielająca
                                    Rectangle {
                                        Layout.fillWidth: true
                                        height: 1
                                        color: "#eeeeee"
                                        visible: true
                                    }

                                    // Druga linia: Dane adresowe
                                    Text {
                                        Layout.fillWidth: true
                                        text: modelData.province + ", " + modelData.district + ", " + modelData.city + ", " + modelData.address
                                        font.pixelSize: 12
                                        color: "#666666"
                                        wrapMode: Text.WordWrap
                                    }
                                }
                            }

                            footer: Text {
                                width: stationsListView.width
                                text: {
                                    if (mainWindow.stationsData.indexOf("Znaleziono ") >= 0) {
                                        var lines = mainWindow.stationsData.split("\n");
                                        for (var i = lines.length - 1; i >= 0; i--) {
                                            if (lines[i].startsWith("Znaleziono "))
                                                return lines[i];
                                        }
                                    }
                                    return "";
                                }
                                visible: text !== ""
                                font.pixelSize: 14
                                color: textColor
                                wrapMode: Text.WordWrap
                                topPadding: 15
                            }

                            // Funkcja parsująca dane tekstowe z mainWindow.stationsData
                            function parseStationsData(text) {
                                if (!text || text.trim() === "")
                                    return [];

                                if (text.startsWith("Nie znaleziono"))
                                    return [];

                                var result = [];
                                var lines = text.split("\n");
                                var currentStation = null;

                                for (var i = 0; i < lines.length; i++) {
                                    var line = lines[i].trim();

                                    if (line.startsWith("ID: ")) {
                                        // Rozpoczynamy nową stację
                                        if (currentStation !== null) {
                                            result.push(currentStation);
                                        }
                                        currentStation = {
                                            id: line.substring(4).trim(),
                                            name: "",
                                            city: "",
                                            address: "",
                                            commune: "",
                                            district: "",
                                            province: ""
                                        };
                                    } else if (currentStation !== null) {
                                        if (line.startsWith("Nazwa: ")) {
                                            currentStation.name = line.substring(7).trim();
                                        } else if (line.startsWith("Miasto: ")) {
                                            currentStation.city = line.substring(8).trim();
                                        } else if (line.startsWith("Adres: ")) {
                                            currentStation.address = line.substring(7).trim();
                                        } else if (line.startsWith("Gmina: ")) {
                                            currentStation.commune = line.substring(7).trim();
                                        } else if (line.startsWith("Powiat: ")) {
                                            currentStation.district = line.substring(8).trim();
                                        } else if (line.startsWith("Województwo: ")) {
                                            currentStation.province = line.substring(13).trim();
                                        }
                                    }

                                    // Jeśli napotkamy separator lub informację o liczbie stacji
                                    if ((line === "---------------------------" || line.startsWith("Znaleziono ")) && currentStation !== null) {
                                        result.push(currentStation);
                                        currentStation = null;
                                    }
                                }

                                // Dodajemy ostatnią stację, jeśli istnieje
                                if (currentStation !== null) {
                                    result.push(currentStation);
                                }

                                return result;
                            }
                        }

                        // Komunikat, gdy nie znaleziono stacji
                        Text {
                            anchors.centerIn: parent
                            text: {
                                if (mainWindow.stationsData.startsWith("Nie znaleziono"))
                                    return mainWindow.stationsData;
                                return "";
                            }
                            visible: text !== ""
                            font.pixelSize: 14
                            color: textColor
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WordWrap
                        }
                    }
                }
                // Informacje o API
                Rectangle {
                    Layout.fillWidth: true
                    height: 30
                    color: "#f8f8f8"
                    radius: 3
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 5



                        Text {
                            text: "API: https://api.gios.gov.pl/pjp-api/rest/station/findAll"
                            font.pixelSize: 12
                            color: "#555555"
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // Tab 2: Czujniki stacji
            ColumnLayout {
                spacing: 20

                // Panel z instrukcjami
                Rectangle {
                    Layout.fillWidth: true
                    height: 70
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: "Informacje o czujnikach stacji"
                            font.pixelSize: 16
                            font.bold: true
                            color: textColor
                        }

                        Text {
                            text: "Wprowadź ID stacji, aby wyświetlić listę wszystkich czujników tej stacji"
                            font.pixelSize: 12
                            color: Qt.darker(textColor, 1.3)
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                    }
                }

                // Panel wyszukiwania
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        TextField {
                            id: stationIdInput
                            Layout.fillWidth: true
                            placeholderText: "Wpisz ID stacji (np. 14)"
                            selectByMouse: true
                            font.pixelSize: 14
                            validator: IntValidator { bottom: 1 }

                            background: Rectangle {
                                border.color: stationIdInput.activeFocus ? accentColor : borderColor
                                border.width: stationIdInput.activeFocus ? 2 : 1
                                radius: 4
                            }

                            Keys.onReturnPressed: {
                                fetchSensorsButton.clicked()
                            }
                        }

                        Button {
                            id: fetchSensorsButton
                            text: "Pobierz czujniki"
                            enabled: !mainWindow.isLoadingSensors

                            contentItem: Text {
                                text: fetchSensorsButton.text
                                font.pixelSize: 14
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: fetchSensorsButton.enabled ? (fetchSensorsButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor) : Qt.lighter(accentColor, 1.4)
                                radius: 4
                            }

                            onClicked: {
                                mainWindow.fetchStationSensors(stationIdInput.text.trim())
                            }
                        }
                    }
                }

                // Status panel
                RowLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    height: 30
                    visible: mainWindow.isLoadingSensors || mainWindow.hasSensorsError

                    BusyIndicator {
                        running: mainWindow.isLoadingSensors
                        visible: mainWindow.isLoadingSensors
                        width: 24
                        height: 24

                        contentItem: Item {
                            implicitWidth: 24
                            implicitHeight: 24




                            RotationAnimator {
                                target: sensorsBusyIndicator
                                from: 0
                                to: 360
                                duration: 1000
                                running: true
                                loops: Animation.Infinite
                            }
                        }
                    }

                    Text {
                        visible: mainWindow.isLoadingSensors
                        text: "Ładowanie czujników..."
                        font.pixelSize: 14
                        color: textColor
                    }

                    Text {
                        visible: mainWindow.hasSensorsError
                        text: mainWindow.sensorsErrorMessage
                        color: errorColor
                        font.pixelSize: 14
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                }

                // Wyniki wyszukiwania - w formie kafelków
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ScrollView {
                        anchors.fill: parent
                        anchors.margins: 15
                        clip: true
                        ScrollBar.vertical.policy: ScrollBar.AsNeeded

                        ListView {
                            id: sensorsListView
                            width: parent.width
                            height: parent.height
                            model: parseSensorsData(mainWindow.sensorsData)
                            spacing: 10

                            header: Text {
                                width: sensorsListView.width
                                text: {
                                    var headerText = extractHeaderText(mainWindow.sensorsData);
                                    return headerText !== "" ? headerText : "";
                                }
                                visible: text !== ""
                                font.pixelSize: 16
                                font.bold: true
                                color: textColor
                                wrapMode: Text.WordWrap
                                bottomPadding: 15
                            }

                            delegate: Rectangle {
                                id: sensorItem
                                width: sensorsListView.width
                                height: sensorContentColumn.height + 24
                                border.color: "#cccccc"
                                border.width: 1
                                radius: 4
                                color: "white"

                                // Dodanie efektu cienia
                                layer.enabled: true
                                layer.effect: DropShadow {
                                    horizontalOffset: 0
                                    verticalOffset: 2
                                    radius: 8.0
                                    samples: 17
                                    color: "#30000000"
                                }

                                // Efekt podświetlenia przy najechaniu
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: sensorItem.color = "#f8f8f8"
                                    onExited: sensorItem.color = "white"
                                    onClicked: {
                                        onSensorSelected: {
                                            tabBar.currentIndex = 2 // Przełącz na Tab 2
                                            // Ustaw ID stacji
                                            sensorIdInput.text = modelData.id
                                        }
                                    }
                                }

                                ColumnLayout {
                                    id: sensorContentColumn
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    anchors.top: parent.top
                                    anchors.margins: 12
                                    spacing: 8

                                    // Pierwsza linia: ID czujnika
                                    Text {
                                        Layout.fillWidth: true
                                        text: "ID czujnika: " + modelData.id
                                        font.pixelSize: 15
                                        font.bold: true
                                        color: "#333333"
                                    }

                                    // Linia oddzielająca
                                    Rectangle {
                                        Layout.fillWidth: true
                                        height: 1
                                        color: "#eeeeee"
                                    }

                                    // Druga linia: Parametr i wzór
                                    Text {
                                        Layout.fillWidth: true
                                        text: "Parametr: " + modelData.paramName + (modelData.paramFormula ? " (" + modelData.paramFormula + ")" : "")
                                        font.pixelSize: 14
                                        color: "#444444"
                                        wrapMode: Text.WordWrap
                                    }

                                    // Trzecia linia: Kod parametru
                                    Text {
                                        Layout.fillWidth: true
                                        text: "Kod parametru: " + modelData.paramCode
                                        font.pixelSize: 13
                                        color: "#555555"
                                    }

                                    // Czwarta linia: ID parametru (z jednostką)
                                    RowLayout {
                                        Layout.fillWidth: true
                                        spacing: 10

                                        Text {
                                            text: "ID parametru: " + modelData.paramId
                                            font.pixelSize: 13
                                            color: "#555555"
                                        }

                                        Rectangle {
                                            Layout.preferredWidth: 1
                                            Layout.preferredHeight: 14
                                            color: "#dddddd"
                                            visible: getUnitByParamId(modelData.paramId) !== "-"
                                        }

                                        Text {
                                            text: "Jednostka: " + getUnitByParamId(modelData.paramId)
                                            font.pixelSize: 13
                                            color: "#555555"
                                            visible: getUnitByParamId(modelData.paramId) !== "-"
                                        }
                                    }
                                }
                            }

                            footer: Text {
                                width: sensorsListView.width
                                text: extractFooterText(mainWindow.sensorsData)
                                visible: text !== ""
                                font.pixelSize: 14
                                color: textColor
                                wrapMode: Text.WordWrap
                                topPadding: 15
                            }

                            // Funkcja do wyodrębnienia tekstu nagłówka
                            function extractHeaderText(text) {
                                if (!text || text.trim() === "")
                                    return "";

                                if (text.startsWith("Nie znaleziono czujników"))
                                    return "";

                                var headerMatch = text.match(/Czujniki dla stacji \(ID: \d+\):/);
                                return headerMatch ? headerMatch[0] : "";
                            }

                            // Funkcja do wyodrębnienia tekstu stopki
                            function extractFooterText(text) {
                                if (!text || text.trim() === "")
                                    return "";

                                var footerMatch = text.match(/Znaleziono \d+ czujników/);
                                return footerMatch ? footerMatch[0] : "";
                            }

                            // Funkcja parsująca dane tekstowe z mainWindow.sensorsData
                            function parseSensorsData(text) {
                                if (!text || text.trim() === "")
                                    return [];

                                if (text.startsWith("Nie znaleziono"))
                                    return [];

                                var result = [];
                                var lines = text.split("\n");
                                var currentSensor = null;

                                for (var i = 0; i < lines.length; i++) {
                                    var line = lines[i].trim();

                                    if (line.startsWith("ID czujnika: ")) {
                                        // Rozpoczynamy nowy czujnik
                                        if (currentSensor !== null) {
                                            result.push(currentSensor);
                                        }
                                        currentSensor = {
                                            id: line.substring(13).trim(),
                                            paramName: "",
                                            paramFormula: "",
                                            paramCode: "",
                                            paramId: ""
                                        };
                                    } else if (currentSensor !== null) {
                                        if (line.startsWith("Parametr: ")) {
                                            var paramData = line.substring(10).trim();
                                            var formulaMatch = paramData.match(/^(.*) \((.*)\)$/);
                                            if (formulaMatch) {
                                                currentSensor.paramName = formulaMatch[1];
                                                currentSensor.paramFormula = formulaMatch[2];
                                            } else {
                                                currentSensor.paramName = paramData;
                                            }
                                        } else if (line.startsWith("Kod parametru: ")) {
                                            currentSensor.paramCode = line.substring(15).trim();
                                        } else if (line.startsWith("ID parametru: ")) {
                                            currentSensor.paramId = line.substring(14).trim();
                                        }
                                    }

                                    // Jeśli napotkamy separator
                                    if (line === "---------------------------" && currentSensor !== null) {
                                        result.push(currentSensor);
                                        currentSensor = null;
                                    }
                                }

                                // Dodajemy ostatni czujnik, jeśli istnieje
                                if (currentSensor !== null) {
                                    result.push(currentSensor);
                                }

                                return result;
                            }

                            // Funkcja do określania jednostek na podstawie ID parametru
                            function getUnitByParamId(paramId) {
                                // Mapowanie ID parametrów na jednostki
                                var units = {
                                    "1": "μg/m³",   // PM10
                                    "2": "μg/m³",   // PM2.5
                                    "3": "μg/m³",   // O3
                                    "4": "μg/m³",   // NO2
                                    "5": "μg/m³",   // SO2
                                    "6": "μg/m³",   // C6H6
                                    "7": "μg/m³",   // CO
                                    "8": "%",       // Wilgotność względna
                                    "9": "°C",      // Temperatura
                                    "10": "hPa",    // Ciśnienie atmosferyczne
                                    "11": "m/s",    // Prędkość wiatru
                                    "12": "°",      // Kierunek wiatru
                                };

                                return units[paramId] || "-";
                            }
                        }

                        // Komunikat, gdy nie znaleziono czujników
                        Text {
                            anchors.centerIn: parent
                            text: {
                                if (mainWindow.sensorsData.startsWith("Nie znaleziono"))
                                    return mainWindow.sensorsData;
                                return "";
                            }
                            visible: text !== "" && sensorsListView.model.length === 0
                            font.pixelSize: 14
                            color: textColor
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WordWrap
                        }
                    }
                }

                // Informacje o API
                Rectangle {
                    Layout.fillWidth: true
                    height: 30
                    color: "#f8f8f8"
                    radius: 3
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 5

                        Text {
                            text: "API: https://api.gios.gov.pl/pjp-api/rest/station/sensors/{stationId}"
                            font.pixelSize: 12
                            color: "#555555"
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // Tab 3: Dane z sensora (wcześniej Tab 1)
            ColumnLayout {
                spacing: 20

                // Panel z instrukcjami
                Rectangle {
                    Layout.fillWidth: true
                    height: 70
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: "Dane pomiarowe z wybranego sensora"
                            font.pixelSize: 16
                            font.bold: true
                            color: textColor
                        }

                        Text {
                            text: "Wprowadź ID sensora, aby pobrać najnowsze dane pomiarowe"
                            font.pixelSize: 12
                            color: Qt.darker(textColor, 1.3)
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                    }
                }

                // Panel wyszukiwania
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        TextField {
                            id: sensorIdInput
                            Layout.fillWidth: true
                            placeholderText: "Wpisz ID sensora (np. 92)"
                            selectByMouse: true
                            font.pixelSize: 14
                            validator: IntValidator { bottom: 1 }

                            background: Rectangle {
                                border.color: sensorIdInput.activeFocus ? accentColor : borderColor
                                border.width: sensorIdInput.activeFocus ? 2 : 1
                                radius: 4
                            }

                            Keys.onReturnPressed: {
                                fetchButton.clicked()
                            }
                        }

                        Button {
                            id: fetchButton
                            text: "Pobierz dane"
                            enabled: !mainWindow.isLoading

                            contentItem: Text {
                                text: fetchButton.text
                                font.pixelSize: 14
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: fetchButton.enabled ? (fetchButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor) : Qt.lighter(accentColor, 1.4)
                                radius: 4
                            }

                            onClicked: {
                                mainWindow.fetchData(sensorIdInput.text.trim())
                            }
                        }
                    }
                }

                // Status panel
                RowLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    height: 30
                    visible: mainWindow.isLoading || mainWindow.hasError

                    BusyIndicator {
                        running: mainWindow.isLoading
                        visible: mainWindow.isLoading
                        width: 24
                        height: 24
                    }

                    Text {
                        visible: mainWindow.isLoading
                        text: "Ładowanie danych..."
                        font.pixelSize: 14
                        color: textColor
                    }

                    Text {
                        visible: mainWindow.hasError
                        text: mainWindow.errorMessage
                        color: errorColor
                        font.pixelSize: 14
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                }
                // Panel wyboru przedziału czasowego
                Rectangle {
                    Layout.fillWidth: true
                    height: 120
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1
                    visible: mainWindow.responseData !== "" // Widoczny tylko gdy mamy dane

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: "Wybierz przedział czasowy"
                            font.pixelSize: 14
                            font.bold: true
                            color: textColor
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            // Data początkowa
                            ColumnLayout {
                                spacing: 2

                                Text {
                                    text: "Od:"
                                    font.pixelSize: 12
                                    color: textColor
                                }

                                RowLayout {
                                    spacing: 5

                                    TextField {
                                        id: startDateField
                                        placeholderText: "YYYY-MM-DD"
                                        Layout.preferredWidth: 120
                                        selectByMouse: true
                                        font.pixelSize: 12
                                        property string lastValidText: ""

                                        background: Rectangle {
                                            border.color: startDateField.activeFocus ? accentColor : borderColor
                                            border.width: startDateField.activeFocus ? 2 : 1
                                            radius: 4
                                        }

                                        onTextChanged: {
                                            // Prosta walidacja - zachowaj ostatnią poprawną wartość
                                            if (/^\d{4}-\d{2}-\d{2}$/.test(text) || text === "") {
                                                lastValidText = text
                                            } else if (text.length > lastValidText.length) {
                                                // Automatyczne dodawanie myślników
                                                if (text.length === 4) {
                                                    text = text + "-"
                                                    lastValidText = text
                                                } else if (text.length === 7) {
                                                    text = text + "-"
                                                    lastValidText = text
                                                }
                                            }
                                        }
                                    }

                                    TextField {
                                        id: startTimeField
                                        placeholderText: "HH:MM"
                                        Layout.preferredWidth: 80
                                        selectByMouse: true
                                        font.pixelSize: 12
                                        property string lastValidText: ""

                                        background: Rectangle {
                                            border.color: startTimeField.activeFocus ? accentColor : borderColor
                                            border.width: startTimeField.activeFocus ? 2 : 1
                                            radius: 4
                                        }

                                        onTextChanged: {
                                            // Prosta walidacja - zachowaj ostatnią poprawną wartość
                                            if (/^([01]?[0-9]|2[0-3]):[0-5][0-9]$/.test(text) || text === "") {
                                                lastValidText = text
                                            } else if (text.length > lastValidText.length) {
                                                // Automatyczne dodawanie dwukropka
                                                if (text.length === 2) {
                                                    text = text + ":"
                                                    lastValidText = text
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // Data końcowa
                            ColumnLayout {
                                spacing: 2

                                Text {
                                    text: "Do:"
                                    font.pixelSize: 12
                                    color: textColor
                                }

                                RowLayout {
                                    spacing: 5

                                    TextField {
                                        id: endDateField
                                        placeholderText: "YYYY-MM-DD"
                                        Layout.preferredWidth: 120
                                        selectByMouse: true
                                        font.pixelSize: 12
                                        property string lastValidText: ""

                                        background: Rectangle {
                                            border.color: endDateField.activeFocus ? accentColor : borderColor
                                            border.width: endDateField.activeFocus ? 2 : 1
                                            radius: 4
                                        }

                                        onTextChanged: {
                                            // Prosta walidacja - zachowaj ostatnią poprawną wartość
                                            if (/^\d{4}-\d{2}-\d{2}$/.test(text) || text === "") {
                                                lastValidText = text
                                            } else if (text.length > lastValidText.length) {
                                                // Automatyczne dodawanie myślników
                                                if (text.length === 4) {
                                                    text = text + "-"
                                                    lastValidText = text
                                                } else if (text.length === 7) {
                                                    text = text + "-"
                                                    lastValidText = text
                                                }
                                            }
                                        }
                                    }

                                    TextField {
                                        id: endTimeField
                                        placeholderText: "HH:MM"
                                        Layout.preferredWidth: 80
                                        selectByMouse: true
                                        font.pixelSize: 12
                                        property string lastValidText: ""

                                        background: Rectangle {
                                            border.color: endTimeField.activeFocus ? accentColor : borderColor
                                            border.width: endTimeField.activeFocus ? 2 : 1
                                            radius: 4
                                        }

                                        onTextChanged: {
                                            // Prosta walidacja - zachowaj ostatnią poprawną wartość
                                            if (/^([01]?[0-9]|2[0-3]):[0-5][0-9]$/.test(text) || text === "") {
                                                lastValidText = text
                                            } else if (text.length > lastValidText.length) {
                                                // Automatyczne dodawanie dwukropka
                                                if (text.length === 2) {
                                                    text = text + ":"
                                                    lastValidText = text
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // Przyciski szybkiego wyboru
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 5

                                Text {
                                    text: "Szybki wybór:"
                                    font.pixelSize: 12
                                    color: textColor
                                }

                                Flow {
                                    Layout.fillWidth: true
                                    spacing: 5

                                    Button {
                                        text: "24h"
                                        width: 50
                                        height: 25
                                        contentItem: Text {
                                            text: parent.text
                                            font.pixelSize: 12
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        background: Rectangle {
                                            color: parent.pressed ? Qt.darker(accentColor, 1.2) : accentColor
                                            radius: 3
                                        }
                                        onClicked: {
                                            var now = new Date()
                                            var yesterday = new Date(now)
                                            yesterday.setDate(now.getDate() - 1)

                                            // Format dates
                                            startDateField.text = formatDate(yesterday)
                                            startTimeField.text = formatTime(yesterday)
                                            endDateField.text = formatDate(now)
                                            endTimeField.text = formatTime(now)
                                        }
                                    }

                                    Button {
                                        text: "7 dni"
                                        width: 50
                                        height: 25
                                        contentItem: Text {
                                            text: parent.text
                                            font.pixelSize: 12
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        background: Rectangle {
                                            color: parent.pressed ? Qt.darker(accentColor, 1.2) : accentColor
                                            radius: 3
                                        }
                                        onClicked: {
                                            var now = new Date()
                                            var sevenDaysAgo = new Date(now)
                                            sevenDaysAgo.setDate(now.getDate() - 7)

                                            // Format dates
                                            startDateField.text = formatDate(sevenDaysAgo)
                                            startTimeField.text = formatTime(sevenDaysAgo)
                                            endDateField.text = formatDate(now)
                                            endTimeField.text = formatTime(now)
                                        }
                                    }

                                    Button {
                                        text: "30 dni"
                                        width: 50
                                        height: 25
                                        contentItem: Text {
                                            text: parent.text
                                            font.pixelSize: 12
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        background: Rectangle {
                                            color: parent.pressed ? Qt.darker(accentColor, 1.2) : accentColor
                                            radius: 3
                                        }
                                        onClicked: {
                                            var now = new Date()
                                            var thirtyDaysAgo = new Date(now)
                                            thirtyDaysAgo.setDate(now.getDate() - 30)

                                            // Format dates
                                            startDateField.text = formatDate(thirtyDaysAgo)
                                            startTimeField.text = formatTime(thirtyDaysAgo)
                                            endDateField.text = formatDate(now)
                                            endTimeField.text = formatTime(now)
                                        }
                                    }

                                    Button {
                                        text: "Wszystko"
                                        width: 70
                                        height: 25
                                        contentItem: Text {
                                            text: parent.text
                                            font.pixelSize: 12
                                            color: "white"
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        background: Rectangle {
                                            color: parent.pressed ? Qt.darker(accentColor, 1.2) : accentColor
                                            radius: 3
                                        }
                                        onClicked: {
                                            startDateField.text = ""
                                            startTimeField.text = ""
                                            endDateField.text = ""
                                            endTimeField.text = ""
                                            chartRangeDisplay.text = "Zakres: wszystkie dane"

                                            // Reset do oryginalnych danych
                                            if (dateFilterActive.checked) {
                                                dateFilterActive.checked = false
                                            }
                                        }
                                    }
                                }

                                RowLayout {
                                    spacing: 5

                                    CheckBox {
                                        id: dateFilterActive
                                        text: "Filtruj dane"
                                        checked: false

                                        contentItem: Text {
                                            text: dateFilterActive.text
                                            font.pixelSize: 12
                                            color: textColor
                                            leftPadding: dateFilterActive.indicator.width + dateFilterActive.spacing
                                            verticalAlignment: Text.AlignVCenter
                                        }

                                        indicator: Rectangle {
                                            implicitWidth: 16
                                            implicitHeight: 16
                                            x: dateFilterActive.leftPadding
                                            y: parent.height / 2 - height / 2
                                            radius: 3
                                            border.color: dateFilterActive.checked ? accentColor : borderColor

                                            Rectangle {
                                                width: 10
                                                height: 10
                                                x: 3
                                                y: 3
                                                radius: 2
                                                color: accentColor
                                                visible: dateFilterActive.checked
                                            }
                                        }

                                        onCheckedChanged: {
                                            if (checked) {
                                                // Sprawdź czy wszystkie pola są wypełnione
                                                if (startDateField.text === "" || startTimeField.text === "" ||
                                                    endDateField.text === "" || endTimeField.text === "") {
                                                    mainWindow.hasError = true
                                                    mainWindow.errorMessage = "Wypełnij wszystkie pola daty i czasu"
                                                    checked = false
                                                    return
                                                }

                                                // Próba przefiltrowania danych
                                                filterDateRange()
                                            } else {
                                                // Pokazanie wszystkich danych
                                                chartRangeDisplay.text = "Zakres: wszystkie dane"
                                                mainWindow.hasError = false
                                                mainWindow.errorMessage = ""
                                            }
                                        }
                                    }

                                    Text {
                                        id: chartRangeDisplay
                                        text: "Zakres: wszystkie dane"
                                        font.pixelSize: 12
                                        color: textColor
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                        }
                    }

                    // Funkcja do filtrowania danych według wybranego zakresu dat
                    function filterDateRange() {
                        try {
                            // Połącz datę i czas
                            var startDateTimeStr = startDateField.text + "T" + startTimeField.text + ":00"
                            var endDateTimeStr = endDateField.text + "T" + endTimeField.text + ":00"

                            // Konwersja na obiekty Date
                            var startDateTime = new Date(startDateTimeStr)
                            var endDateTime = new Date(endDateTimeStr)

                            // Sprawdź poprawność dat
                            if (isNaN(startDateTime.getTime()) || isNaN(endDateTime.getTime())) {
                                mainWindow.hasError = true
                                mainWindow.errorMessage = "Niepoprawny format daty"
                                dateFilterActive.checked = false
                                return
                            }

                            if (startDateTime >= endDateTime) {
                                mainWindow.hasError = true
                                mainWindow.errorMessage = "Data początkowa musi być wcześniejsza niż końcowa"
                                dateFilterActive.checked = false
                                return
                            }

                            // Aktualizacja tekstu z zakresem
                            chartRangeDisplay.text = "Zakres: " + formatDateDisplay(startDateTime) + " - " + formatDateDisplay(endDateTime)

                            // Tutaj zmodyfikujemy istniejącą właściwość w canvas, aby uwzględniała daty
                            chartCanvas.startDate = startDateTime.getTime()
                            chartCanvas.endDate = endDateTime.getTime()
                            chartCanvas.useCustomDateRange = true
                            chartCanvas.requestPaint()

                            mainWindow.hasError = false
                            mainWindow.errorMessage = ""

                        } catch (e) {
                            mainWindow.hasError = true
                            mainWindow.errorMessage = "Błąd: " + e.toString()
                            dateFilterActive.checked = false
                        }
                    }

                    // Funkcje pomocnicze formatujące datę i czas
                    function formatDate(date) {
                        var year = date.getFullYear()
                        var month = (date.getMonth() + 1).toString().padStart(2, '0')
                        var day = date.getDate().toString().padStart(2, '0')
                        return year + "-" + month + "-" + day
                    }

                    function formatTime(date) {
                        var hours = date.getHours().toString().padStart(2, '0')
                        var minutes = date.getMinutes().toString().padStart(2, '0')
                        return hours + ":" + minutes
                    }

                    function formatDateDisplay(date) {
                        return date.getDate() + "." + (date.getMonth() + 1) + "." + date.getFullYear() +
                               " " + date.getHours() + ":" + (date.getMinutes() < 10 ? "0" : "") + date.getMinutes()
                    }
                }
                // Zakładki dla widoku danych
                TabBar {
                    id: sensorDataTabBar
                    Layout.fillWidth: true

                    background: Rectangle {
                        color: lightGray
                        radius: 3
                    }

                    TabButton {
                        text: "Dane tekstowe"
                        font.pixelSize: 14

                        background: Rectangle {
                            color: sensorDataTabBar.currentIndex === 0 ? "white" : lightGray
                            border.color: sensorDataTabBar.currentIndex === 0 ? accentColor : "transparent"
                            border.width: sensorDataTabBar.currentIndex === 0 ? 2 : 0
                            radius: 3
                        }
                    }

                    TabButton {
                        text: "Wykres słupkowy"
                        font.pixelSize: 14

                        background: Rectangle {
                            color: sensorDataTabBar.currentIndex === 1 ? "white" : lightGray
                            border.color: sensorDataTabBar.currentIndex === 1 ? accentColor : "transparent"
                            border.width: sensorDataTabBar.currentIndex === 1 ? 2 : 0
                            radius: 3
                        }
                    }
                }

                // Dane tekstowe / wykres
                StackLayout {
                    currentIndex: sensorDataTabBar.currentIndex
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    // Zakładka z danymi tekstowymi
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"
                        radius: 5
                        border.color: borderColor
                        border.width: 1

                        ScrollView {
                            id: scrollView
                            anchors.fill: parent
                            anchors.margins: 15
                            clip: true
                            ScrollBar.vertical.policy: ScrollBar.AsNeeded

                            TextArea {
                                id: responseTextArea
                                text: mainWindow.responseData
                                readOnly: true
                                wrapMode: TextEdit.Wrap
                                font.family: "Courier"
                                font.pixelSize: 14
                                selectByMouse: true
                                background: null
                            }
                        }
                    }

                    // Zakładka z wykresem słupkowym
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"
                        radius: 5
                        border.color: borderColor
                        border.width: 1

                        // Modyfikacja Canvas dla obsługi filtrowania dat - zmodyfikuj istniejący Canvas

                        Canvas {
                            id: chartCanvas
                            anchors.fill: parent
                            anchors.margins: 15
                            visible: mainWindow.hasChartData

                            property int leftMargin: 80
                            property int rightMargin: 30
                            property int topMargin: 60
                            property int bottomMargin: 150
                            property int tickLength: 6
                            property int barSpacing: 5
                            // Dodane właściwości dla filtrowania dat
                            property bool useCustomDateRange: false
                            property var startDate: 0
                            property var endDate: 0

                            // Update the canvas when data changes
                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.reset()

                                if (!mainWindow.hasChartData || mainWindow.chartData.length === 0) return

                                drawBarChart(ctx)
                            }

                            // Fragment kodu odpowiedzialny za rysowanie wykresu - zmodyfikowany dla obsługi filtrowania dat
                            function drawBarChart(ctx) {
                                // Chart dimensions
                                var chartWidth = width - leftMargin - rightMargin
                                var chartHeight = height - topMargin - bottomMargin

                                // Draw title
                                ctx.font = "bold 18px Arial"
                                ctx.textAlign = "center"
                                ctx.fillStyle = textColor
                                var titleText = "Pomiary - " + mainWindow.parameterName + " (" + mainWindow.parameterFormula + ")"
                                // Dodaj informację o filtrze jeśli jest aktywny
                                if (useCustomDateRange) {
                                    var startDateObj = new Date(startDate)
                                    var endDateObj = new Date(endDate)
                                    titleText += "\nFiltr: " + startDateObj.toLocaleDateString() + " - " + endDateObj.toLocaleDateString()
                                }
                                ctx.fillText(titleText, width / 2, 30)

                                // Set up Y-axis (values)
                                var minValue = 0
                                var maxValue = mainWindow.maxValue
                                var valueRange = maxValue - minValue

                                // Add 10% padding to the max value for better visualization
                                maxValue += valueRange * 0.1
                                valueRange = maxValue - minValue

                                // If values are too close, set a minimum range
                                if (valueRange < 0.1) {
                                    maxValue = minValue + 1
                                    valueRange = 1
                                }

                                // Filtruj dane jeśli potrzeba
                                var displayData = mainWindow.chartData.slice().reverse()
                                if (useCustomDateRange) {
                                    displayData = displayData.filter(function(point) {
                                        return point.x >= startDate && point.x <= endDate
                                    })
                                }

                                // Sprawdź czy mamy dane do wyświetlenia
                                if (displayData.length === 0) {
                                    ctx.font = "16px Arial"
                                    ctx.textAlign = "center"
                                    ctx.fillStyle = "#666666"
                                    ctx.fillText("Brak danych w wybranym zakresie dat", width / 2, height / 2)
                                    return
                                }

                                // Draw chart background grid
                                ctx.strokeStyle = "#e0e0e0"
                                ctx.lineWidth = 1

                                // Horizontal grid lines
                                var yTickCount = 5
                                for (var i = 0; i <= yTickCount; i++) {
                                    var y = topMargin + (chartHeight * (yTickCount - i) / yTickCount)

                                    ctx.beginPath()
                                    ctx.moveTo(leftMargin, y)
                                    ctx.lineTo(width - rightMargin, y)
                                    ctx.stroke()
                                }

                                // Draw Y-axis
                                ctx.beginPath()
                                ctx.strokeStyle = textColor
                                ctx.lineWidth = 2
                                ctx.moveTo(leftMargin, topMargin)
                                ctx.lineTo(leftMargin, height - bottomMargin)
                                ctx.stroke()

                                // Draw Y-axis ticks and labels
                                ctx.font = "12px Arial"
                                ctx.textAlign = "right"
                                ctx.textBaseline = "middle"
                                ctx.fillStyle = textColor

                                for (var i = 0; i <= yTickCount; i++) {
                                    var y = topMargin + (chartHeight * (yTickCount - i) / yTickCount)
                                    var value = minValue + (valueRange * i / yTickCount)

                                    // Draw tick
                                    ctx.beginPath()
                                    ctx.moveTo(leftMargin - tickLength, y)
                                    ctx.lineTo(leftMargin, y)
                                    ctx.stroke()

                                    // Draw label
                                    ctx.fillText(value.toFixed(2), leftMargin - 10, y)
                                }

                                // Draw Y-axis label
                                ctx.save()
                                ctx.translate(20, height / 2)
                                ctx.rotate(-Math.PI / 2)
                                ctx.font = "14px Arial"
                                ctx.textAlign = "center"
                                ctx.fillText(mainWindow.parameterFormula, 0, 0)
                                ctx.restore()

                                // Draw X-axis
                                ctx.beginPath()
                                ctx.strokeStyle = textColor
                                ctx.lineWidth = 2
                                ctx.moveTo(leftMargin, height - bottomMargin)
                                ctx.lineTo(width - rightMargin, height - bottomMargin)
                                ctx.stroke()

                                // Calculate bar width based on data points and available space
                                var dataLength = displayData.length
                                var barWidth = Math.max(5, Math.min(30, (chartWidth / dataLength) - barSpacing))

                                // Draw data bars
                                for (var j = 0; j < displayData.length; j++) {
                                    var dataPoint = displayData[j]
                                    var barValue = dataPoint.y

                                    // Calculate bar position and height
                                    var barHeight = (barValue - minValue) / valueRange * chartHeight
                                    var barX = leftMargin + j * (barWidth + barSpacing)
                                    var barY = height - bottomMargin - barHeight

                                    // Create gradient for bars
                                    var gradient = ctx.createLinearGradient(barX, barY, barX, height - bottomMargin)
                                    gradient.addColorStop(0, chartBarColor)
                                    gradient.addColorStop(1, Qt.lighter(chartBarColor, 1.2))

                                    // Draw bar
                                    ctx.fillStyle = gradient
                                    ctx.fillRect(barX, barY, barWidth, barHeight)

                                    // Draw bar border
                                    ctx.strokeStyle = chartBarBorder
                                    ctx.lineWidth = 1
                                    ctx.strokeRect(barX, barY, barWidth, barHeight)

                                    // Draw X-axis label (date) - zmodyfikuj gęstość etykiet w zależności od liczby słupków
                                    var labelFrequency = Math.ceil(displayData.length / 10) // Maksymalnie 10 etykiet na osi X
                                    if (j % labelFrequency === 0 || j === displayData.length - 1) {
                                        var date = new Date(dataPoint.x)
                                        var dateLabel = date.getDate() + "." +
                                                      (date.getMonth() + 1) + " " +
                                                      date.getHours() + ":" +
                                                      (date.getMinutes() < 10 ? "0" : "") + date.getMinutes()

                                        ctx.save()
                                        ctx.translate(barX + barWidth / 2, height - bottomMargin + 15)
                                        ctx.rotate(Math.PI / 4)
                                        ctx.font = "11px Arial"
                                        ctx.textAlign = "left"
                                        ctx.fillStyle = textColor
                                        ctx.fillText(dateLabel, 0, 0)
                                        ctx.restore()
                                    }
                                }

                                // Draw X-axis label
                                ctx.font = "14px Arial"
                                ctx.textAlign = "center"
                                ctx.fillText("Data pomiaru", width / 2, height - 15)
                            }

                            // Update canvas when data changes
                            Connections {
                                target: mainWindow
                                function onChartDataChanged() { chartCanvas.requestPaint() }
                                function onMinValueChanged() { chartCanvas.requestPaint() }
                                function onMaxValueChanged() { chartCanvas.requestPaint() }
                                function onParameterNameChanged() { chartCanvas.requestPaint() }
                                function onParameterFormulaChanged() { chartCanvas.requestPaint() }
                                function onHasChartDataChanged() { chartCanvas.requestPaint() }
                            }
                        }
                        Text {
                            anchors.centerIn: parent
                            text: "Brak danych do wyświetlenia wykresu"
                            visible: !mainWindow.hasChartData && !mainWindow.isLoading
                            font.pixelSize: 16
                            color: "#666666"
                        }
                    }
                    // Place this after the statisticsContainer, at the same level
                    Text {
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: -40 // Adjust as needed
                        text: "Brak danych do wyświetlenia wykresu"
                        visible: !mainWindow.hasChartData && !mainWindow.isLoading
                        font.pixelSize: 16
                        color: "#666666"
                    }
                    // Dostosuj położenie tekstu "Brak danych" tak, aby był nad blokiem statystyk
                    Text {
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: -40 // Przesuń tekst wyżej, aby nie kolidował z blokiem statystyk
                        text: "Brak danych do wyświetlenia wykresu"
                        visible: !mainWindow.hasChartData && !mainWindow.isLoading
                        font.pixelSize: 16
                        color: "#666666"
                    }
                    // Statystyki Container - modyfikacja, aby używał tych samych przefiltrowanych danych co wykres
                    Item {
                        id: statisticsContainer
                        anchors {
                            left: parent.left
                            right: parent.right
                            bottom: parent.bottom
                            top: chartCanvas.bottom
                            topMargin: 10
                        }

                        visible: mainWindow.hasChartData

                        // Helper functions for stats calculations
                        function findMinValue(data) {
                            if (!data || data.length === 0) return null;

                            var minItem = data[0];
                            for (var i = 1; i < data.length; i++) {
                                if (data[i].y < minItem.y) {
                                    minItem = data[i];
                                }
                            }
                            return minItem;
                        }

                        function findMaxValue(data) {
                            if (!data || data.length === 0) return null;

                            var maxItem = data[0];
                            for (var i = 1; i < data.length; i++) {
                                if (data[i].y > maxItem.y) {
                                    maxItem = data[i];
                                }
                            }
                            return maxItem;
                        }

                        function calculateAverage(data) {
                            if (!data || data.length === 0) return 0;

                            var sum = 0;
                            var count = 0;

                            for (var i = 0; i < data.length; i++) {
                                if (data[i].y !== null && data[i].y !== undefined) {
                                    sum += data[i].y;
                                    count++;
                                }
                            }

                            return count > 0 ? sum / count : 0;
                        }

                        function formatDate(dateValue) {
                            var date = new Date(dateValue);
                            return date.getDate() + "." + (date.getMonth()+1) + " " +
                                   date.getHours() + ":" +
                                   (date.getMinutes() < 10 ? "0" : "") + date.getMinutes();
                        }

                        // Przefiltrowane dane bazujące na tych samych kryteriach co wykres
                        function getFilteredData() {
                            var displayData = mainWindow.chartData.slice().reverse();
                            if (chartCanvas.useCustomDateRange) {
                                displayData = displayData.filter(function(point) {
                                    return point.x >= chartCanvas.startDate && point.x <= chartCanvas.endDate;
                                });
                            }
                            return displayData;
                        }

                        // Statistics Block
                        Rectangle {
                            id: statisticsBlock
                            anchors {
                                left: parent.left
                                right: parent.right
                                bottom: parent.bottom
                                margins: 15
                            }
                            height: 80
                            color: "#f8f8f8"
                            border.color: borderColor
                            border.width: 1
                            radius: 5

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 10
                                spacing: 2

                                Text {
                                    text: "Statystyki pomiarów:" + (chartCanvas.useCustomDateRange ? " (filtrowane)" : "")
                                    font.pixelSize: 14
                                    font.bold: true
                                    color: textColor
                                }

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 10

                                    // Minimalna wartość
                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 40
                                        color: Qt.lighter(accentColor, 1.8)
                                        radius: 3
                                        border.color: Qt.lighter(accentColor, 1.5)
                                        border.width: 1

                                        RowLayout {
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            spacing: 5

                                            Text {
                                                text: "Min:"
                                                font.pixelSize: 12
                                                font.bold: true
                                                color: textColor
                                            }

                                            Text {
                                                id: minValueText
                                                text: {
                                                    if (!mainWindow.hasChartData) return "N/A";

                                                    var filteredData = statisticsContainer.getFilteredData();
                                                    if (filteredData.length === 0) return "N/A";

                                                    var minData = statisticsContainer.findMinValue(filteredData);
                                                    if (!minData) return "N/A";

                                                    return minData.y.toFixed(2) + " μg/m3 " + " (" + statisticsContainer.formatDate(minData.x) + ")";
                                                }
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }

                                    // Maksymalna wartość
                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 40
                                        color: Qt.lighter("#e74c3c", 1.7)
                                        radius: 3
                                        border.color: Qt.lighter("#e74c3c", 1.5)
                                        border.width: 1

                                        RowLayout {
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            spacing: 5

                                            Text {
                                                text: "Max:"
                                                font.pixelSize: 12
                                                font.bold: true
                                                color: textColor
                                            }

                                            Text {
                                                id: maxValueText
                                                text: {
                                                    if (!mainWindow.hasChartData) return "N/A";

                                                    var filteredData = statisticsContainer.getFilteredData();
                                                    if (filteredData.length === 0) return "N/A";

                                                    var maxData = statisticsContainer.findMaxValue(filteredData);
                                                    if (!maxData) return "N/A";

                                                    return maxData.y.toFixed(2) + " μg/m3 " + " (" + statisticsContainer.formatDate(maxData.x) + ")";
                                                }
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }

                                    // Średnia wartość
                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 40
                                        color: Qt.lighter("#2ecc71", 1.7)
                                        radius: 3
                                        border.color: Qt.lighter("#2ecc71", 1.5)
                                        border.width: 1

                                        RowLayout {
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            spacing: 5

                                            Text {
                                                text: "Średnia:"
                                                font.pixelSize: 12
                                                font.bold: true
                                                color: textColor
                                            }

                                            Text {
                                                id: avgValueText
                                                text: {
                                                    if (!mainWindow.hasChartData) return "N/A";

                                                    var filteredData = statisticsContainer.getFilteredData();
                                                    if (filteredData.length === 0) return "N/A";

                                                    return statisticsContainer.calculateAverage(filteredData).toFixed(2) + " μg/m3";
                                                }
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // Connections to update statistics when chart data or filter changes
                        Connections {
                            target: chartCanvas
                            function onUseCustomDateRangeChanged() { updateStatisticsBindings() }
                            function onStartDateChanged() { if (chartCanvas.useCustomDateRange) updateStatisticsBindings() }
                            function onEndDateChanged() { if (chartCanvas.useCustomDateRange) updateStatisticsBindings() }
                        }

                        Connections {
                            target: mainWindow
                            function onChartDataChanged() { updateStatisticsBindings() }
                            function onHasChartDataChanged() { updateStatisticsBindings() }
                        }

                        // Funkcja do aktualizacji wiązań statystyk
                        function updateStatisticsBindings() {
                            // To wymusi ponowne obliczenie wartości tekstów
                            minValueText.text = Qt.binding(function() {
                                if (!mainWindow.hasChartData) return "N/A";

                                var filteredData = statisticsContainer.getFilteredData();
                                if (filteredData.length === 0) return "N/A";

                                var minData = statisticsContainer.findMinValue(filteredData);
                                if (!minData) return "N/A";

                                return minData.y.toFixed(2) + " μg/m3 " + " (" + statisticsContainer.formatDate(minData.x) + ")";
                            });

                            maxValueText.text = Qt.binding(function() {
                                if (!mainWindow.hasChartData) return "N/A";

                                var filteredData = statisticsContainer.getFilteredData();
                                if (filteredData.length === 0) return "N/A";

                                var maxData = statisticsContainer.findMaxValue(filteredData);
                                if (!maxData) return "N/A";

                                return maxData.y.toFixed(2) + " μg/m3 " + " (" + statisticsContainer.formatDate(maxData.x) + ")";
                            });

                            avgValueText.text = Qt.binding(function() {
                                if (!mainWindow.hasChartData) return "N/A";

                                var filteredData = statisticsContainer.getFilteredData();
                                if (filteredData.length === 0) return "N/A";

                                return statisticsContainer.calculateAverage(filteredData).toFixed(2) + " μg/m3";
                            });
                        }

                        // Inicjalizacja wiązań po załadowaniu komponentu
                        Component.onCompleted: {
                            updateStatisticsBindings();
                        }
                    }
                }

                // Informacje o API
                Rectangle {
                    Layout.fillWidth: true
                    height: 30
                    color: "#f8f8f8"
                    radius: 3
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 5

                        Text {
                            text: "API: https://api.gios.gov.pl/pjp-api/rest/data/getData/{sensorId}"
                            font.pixelSize: 12
                            color: "#555555"
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // Tab 4: Indeks jakości powietrza
            ColumnLayout {
                spacing: 20

                // Panel z instrukcjami
                Rectangle {
                    Layout.fillWidth: true
                    height: 70
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 5

                        Text {
                            text: "Indeks jakości powietrza dla stacji"
                            font.pixelSize: 16
                            font.bold: true
                            color: textColor
                        }

                        Text {
                            text: "Wprowadź ID stacji, aby pobrać aktualny indeks jakości powietrza i poziom zanieczyszczeń"
                            font.pixelSize: 12
                            color: Qt.darker(textColor, 1.3)
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                    }
                }

                // Panel wyszukiwania
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        TextField {
                            id: aqIndexStationIdInput
                            Layout.fillWidth: true
                            placeholderText: "Wpisz ID stacji (np. 14)"
                            selectByMouse: true
                            font.pixelSize: 14
                            validator: IntValidator { bottom: 1 }

                            background: Rectangle {
                                border.color: aqIndexStationIdInput.activeFocus ? accentColor : borderColor
                                border.width: aqIndexStationIdInput.activeFocus ? 2 : 1
                                radius: 4
                            }

                            Keys.onReturnPressed: {
                                fetchAqIndexButton.clicked()
                            }
                        }

                        Button {
                            id: fetchAqIndexButton
                            text: "Pobierz indeks"
                            enabled: !mainWindow.isLoadingAqIndex

                            contentItem: Text {
                                text: fetchAqIndexButton.text
                                font.pixelSize: 14
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: fetchAqIndexButton.enabled ?
                                       (fetchAqIndexButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor) :
                                       Qt.lighter(accentColor, 1.4)
                                radius: 4
                            }

                            onClicked: {
                                mainWindow.fetchAqIndex(aqIndexStationIdInput.text.trim())
                            }
                        }
                    }
                }

                // Status panel
                RowLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    height: 30
                    visible: mainWindow.isLoadingAqIndex || mainWindow.hasAqIndexError

                    BusyIndicator {
                        running: mainWindow.isLoadingAqIndex
                        visible: mainWindow.isLoadingAqIndex
                        width: 24
                        height: 24
                    }

                    Text {
                        visible: mainWindow.isLoadingAqIndex
                        text: "Ładowanie indeksu jakości powietrza..."
                        font.pixelSize: 14
                        color: textColor
                    }

                    Text {
                        visible: mainWindow.hasAqIndexError
                        text: mainWindow.aqIndexErrorMessage
                        color: errorColor
                        font.pixelSize: 14
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                }

                // Panel wyników
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    // Kolorowa legenda wskaźników
                    Rectangle {
                        id: indexLegend
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 15
                        height: 50
                        color: "transparent"
                        visible: mainWindow.aqIndexData !== ""

                        Row {
                            anchors.fill: parent
                            spacing: 10

                            // Bardzo dobry
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#00CB35"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Bardzo dobry"
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }

                            // Dobry
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#84C500"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Dobry"
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }

                            // Umiarkowany
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#FFFF00"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Umiarkowany"
                                    color: "black"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }

                            // Dostateczny
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#FF9D00"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Dostateczny"
                                    color: "black"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }

                            // Zły
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#FF0000"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Zły"
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }

                            // Bardzo zły
                            Rectangle {
                                width: (parent.width - 50) / 6
                                height: parent.height
                                color: "#990055"
                                radius: 5

                                Text {
                                    anchors.centerIn: parent
                                    text: "Bardzo zły"
                                    color: "white"
                                    font.bold: true
                                    font.pixelSize: 11
                                }
                            }
                        }
                    }

                    // Właściwy obszar z kartami parametrów
                    ScrollView {
                        id: resultsScrollView
                        anchors.fill: parent
                        anchors.topMargin: mainWindow.aqIndexData !== "" ? indexLegend.height + 20 : 15
                        anchors.leftMargin: 15
                        anchors.rightMargin: 15
                        anchors.bottomMargin: 15
                        clip: true
                        ScrollBar.vertical.policy: ScrollBar.AsNeeded

                        // Używamy kontenera Column do układania kart parametrów
                        Column {
                            width: resultsScrollView.width
                            spacing: 15

                            // Komunikat gdy brak danych
                            Rectangle {
                                visible: mainWindow.aqIndexData === "" && !mainWindow.isLoadingAqIndex
                                width: parent.width
                                height: 100
                                color: "white"
                                radius: 5
                                border.color: borderColor
                                border.width: 1

                                Text {
                                    anchors.centerIn: parent
                                    text: "Brak danych indeksu jakości powietrza.\nWprowadź ID stacji i kliknij 'Pobierz indeks'."
                                    horizontalAlignment: Text.AlignHCenter
                                    font.pixelSize: 14
                                    color: textColor
                                }
                            }

                            // Parser tekstu do kart parametrów
                            Item {
                                id: cardsContainer
                                width: parent.width
                                height: cardsLoader.height
                                visible: mainWindow.aqIndexData !== ""

                                // Loader do tworzenia kart na podstawie aqIndexData
                                Loader {
                                    id: cardsLoader
                                    width: parent.width

                                    // Sygnał do ponownego wczytania kart przy zmianie danych
                                    Connections {
                                        target: mainWindow
                                        function onAqIndexDataChanged() {
                                            cardsLoader.active = false
                                            cardsLoader.active = true
                                        }
                                    }

                                    active: mainWindow.aqIndexData !== ""
                                    sourceComponent: Item {
                                        id: parsedCards
                                        width: cardsLoader.width
                                        height: cardsColumn.height

                                        // Główny kontener kart
                                        Column {
                                            id: cardsColumn
                                            width: parent.width
                                            spacing: 15

                                            // Funkcja parsująca tekst i tworząca karty parametrów
                                            Component.onCompleted: {
                                                // Zmienne do przechowywania informacji o stacji
                                                let stationId = ""
                                                let stationCalcDate = ""
                                                let stationSourceDataDate = ""
                                                let stationIndexLevel = ""
                                                let stationIndexLevelId = -1

                                                // Obiekty parametrów
                                                let parameters = {
                                                    "so2": { name: "Dwutlenek siarki", code: "SO2", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "no2": { name: "Dwutlenek azotu", code: "NO2", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "co": { name: "Tlenek węgla", code: "CO", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "pm10": { name: "Pył zawieszony PM10", code: "PM10", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "pm25": { name: "Pył zawieszony PM2.5", code: "PM2.5", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "o3": { name: "Ozon", code: "O3", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" },
                                                    "c6h6": { name: "Benzen", code: "C6H6", id: "", level: "", levelId: -1, calcDate: "", sourceDate: "" }
                                                }

                                                // Parsowanie tekstu z aqIndexData
                                                let lines = mainWindow.aqIndexData.split('\n')
                                                let currentParameter = null

                                                for (let i = 0; i < lines.length; i++) {
                                                    let line = lines[i].trim()

                                                    // Parsowanie ID stacji
                                                    if (line.startsWith("ID stacji:")) {
                                                        stationId = line.split(":")[1].trim()
                                                    }
                                                    // Parsowanie daty obliczenia indeksu
                                                    else if (line.startsWith("Data obliczenia indeksu:")) {
                                                        stationCalcDate = line.split(":")[1].trim()
                                                    }
                                                    // Parsowanie daty źródłowej
                                                    else if (line.startsWith("Data pobrania danych źródłowych:")) {
                                                        stationSourceDataDate = line.split(":")[1].trim()
                                                    }
                                                    // Parsowanie ogólnego indeksu jakości
                                                    else if (line.startsWith("Ogólny indeks jakości powietrza:")) {
                                                        let parts = line.split(":")
                                                        if (parts.length > 1) {
                                                            let levelParts = parts[1].trim().split("(poziom")
                                                            stationIndexLevel = levelParts[0].trim()
                                                            if (levelParts.length > 1) {
                                                                stationIndexLevelId = parseInt(levelParts[1].replace(")", "").trim())
                                                            }
                                                        }
                                                    }
                                                    // Wykrywanie parametrów
                                                    else if (line.toLowerCase().includes("(so2):")) {
                                                        currentParameter = "so2"
                                                    }
                                                    else if (line.toLowerCase().includes("(no2):")) {
                                                        currentParameter = "no2"
                                                    }
                                                    else if (line.toLowerCase().includes("(co):")) {
                                                        currentParameter = "co"
                                                    }
                                                    else if (line.toLowerCase().includes("(pm10):")) {
                                                        currentParameter = "pm10"
                                                    }
                                                    else if (line.toLowerCase().includes("(pm2.5):") || line.toLowerCase().includes("(pm2,5):") || line.toLowerCase().includes("(pm25):")) {
                                                        currentParameter = "pm25"
                                                    }
                                                    else if (line.toLowerCase().includes("(o3):")) {
                                                        currentParameter = "o3"
                                                    }
                                                    else if (line.toLowerCase().includes("(c6h6):") || line.toLowerCase().includes("benzen") || line.toLowerCase().includes("benzene")) {
                                                        currentParameter = "c6h6"
                                                    }
                                                    // Parsowanie wartości parametrów
                                                    else if (currentParameter && line.startsWith("- Data obliczenia:")) {
                                                        parameters[currentParameter].calcDate = line.split(":")[1].trim()
                                                    }
                                                    else if (currentParameter && line.startsWith("- Poziom jakości:")) {
                                                        let parts = line.split(":")
                                                        if (parts.length > 1) {
                                                            let levelParts = parts[1].trim().split("(poziom")
                                                            parameters[currentParameter].level = levelParts[0].trim()
                                                            if (levelParts.length > 1) {
                                                                parameters[currentParameter].levelId = parseInt(levelParts[1].replace(")", "").trim())
                                                            }
                                                        }
                                                    }
                                                    else if (currentParameter && line.startsWith("- Data danych źródłowych:")) {
                                                        parameters[currentParameter].sourceDate = line.split(":")[1].trim()
                                                    }
                                                }

                                                // Tworzenie karty dla stacji
                                                if (stationId) {
                                                    createStationCard(stationId, stationCalcDate, stationSourceDataDate, stationIndexLevel, stationIndexLevelId)
                                                }

                                                // Tworzenie kart dla parametrów
                                                for (let paramKey in parameters) {
                                                    if (parameters[paramKey].level) {
                                                        createParameterCard(stationId, paramKey, parameters[paramKey])
                                                    }
                                                }
                                            }

                                            // Funkcja tworząca kartę dla stacji
                                            function createStationCard(id, calcDate, sourceDate, level, levelId) {
                                                let component = Qt.createComponent("StationCardComponent.qml")
                                                if (component.status === Component.Ready) {
                                                    let card = component.createObject(cardsColumn, {
                                                        "stationId": id,
                                                        "calcDate": calcDate,
                                                        "sourceDate": sourceDate,
                                                        "indexLevel": level,
                                                        "indexLevelId": levelId
                                                    })
                                                }
                                            }

                                            // Funkcja tworząca kartę dla parametru
                                            function createParameterCard(stationId, paramKey, paramObj) {
                                                let component = Qt.createComponent("ParameterCardComponent.qml")
                                                if (component.status === Component.Ready) {
                                                    let card = component.createObject(cardsColumn, {
                                                        "stationId": stationId,
                                                        "paramName": paramObj.name,
                                                        "paramCode": paramObj.code,
                                                        "paramId": paramObj.id,
                                                        "indexLevel": paramObj.level,
                                                        "indexLevelId": paramObj.levelId,
                                                        "calcDate": paramObj.calcDate,
                                                        "sourceDate": paramObj.sourceDate
                                                    })
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Informacje o API
                Rectangle {
                    Layout.fillWidth: true
                    height: 30
                    color: "#f8f8f8"
                    radius: 3
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 5

                        Text {
                            text: "API: https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/{stationId}"
                            font.pixelSize: 12
                            color: "#555555"
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // Tab 5: Przeglądarka plików cache
            ColumnLayout {
                spacing: 15

                // Panel z instrukcjami
                Rectangle {
                    Layout.fillWidth: true
                    height: 60
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 3

                        Text {
                            text: "Przeglądarka plików cache"
                            font.pixelSize: 16
                            font.bold: true
                            color: textColor
                        }

                        Text {
                            text: "Wybierz rodzaj danych i identyfikator, aby przeglądać zapisane informacje"
                            font.pixelSize: 12
                            color: Qt.darker(textColor, 1.3)
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                    }
                }

                // Panel wyboru pliku - zoptymalizowany
                Rectangle {
                    Layout.fillWidth: true
                    height: 160
                    color: "white"
                    radius: 5
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 10

                        // Lewa strona - wybór danych
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            // Rodzaj danych
                            RowLayout {
                                Layout.fillWidth: true
                                spacing: 10

                                Text {
                                    text: "Dane:"
                                    font.pixelSize: 14
                                    color: textColor
                                    Layout.preferredWidth: 50
                                }

                                ComboBox {
                                    id: dataTypeCombo
                                    Layout.fillWidth: true
                                    model: ["Stacje pomiarowe", "Czujniki stacji", "Dane czujnika", "Indeks jakości powietrza"]

                                    onCurrentIndexChanged: {
                                        mainWindow.loadCacheFilesList(dataTypeCombo.currentIndex)
                                        idCombo.model = mainWindow.cacheFilesIds
                                    }
                                }
                            }

                            // Identyfikator
                            RowLayout {
                                Layout.fillWidth: true
                                spacing: 10

                                Text {
                                    text: "ID:"
                                    font.pixelSize: 14
                                    color: textColor
                                    Layout.preferredWidth: 50
                                }

                                ComboBox {
                                    id: idCombo
                                    Layout.fillWidth: true
                                    model: mainWindow.cacheFilesIds
                                    enabled: count > 0
                                }
                            }
                        }

                        // Prawa strona - przycisk
                        Button {
                            id: loadCacheButton
                            text: "Wczytaj"
                            Layout.preferredWidth: 90
                            Layout.preferredHeight: 60
                            enabled: idCombo.count > 0

                            contentItem: Text {
                                text: loadCacheButton.text
                                font.pixelSize: 14
                                font.bold: true
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: loadCacheButton.enabled ? (loadCacheButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor) : Qt.lighter(accentColor, 1.4)
                                radius: 4
                            }

                            onClicked: {
                                mainWindow.loadCacheFileContent(dataTypeCombo.currentIndex, idCombo.currentText)
                            }
                        }
                    }
                }

                // Status bar z przyciskiem odświeżania
                Rectangle {
                    Layout.fillWidth: true
                    height: 30
                    color: "#f8f8f8"
                    radius: 3
                    border.color: borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        spacing: 10

                        Text {
                            id: cacheStatusText
                            text: mainWindow.cacheStatusMessage
                            font.pixelSize: 12
                            color: "#555555"
                            Layout.fillWidth: true
                        }

                        Button {
                            id: refreshCacheListButton
                            text: "Odśwież"
                            Layout.preferredWidth: 80
                            implicitHeight: 30

                            contentItem: Text {
                                text: refreshCacheListButton.text
                                font.pixelSize: 12
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            background: Rectangle {
                                color: refreshCacheListButton.pressed ? Qt.darker(accentColor, 1.2) : accentColor
                                radius: 3
                            }

                            onClicked: {
                                mainWindow.loadCacheFilesList(dataTypeCombo.currentIndex)
                                idCombo.model = mainWindow.cacheFilesIds
                            }
                        }
                    }
                }
            }

        }

    }
}
