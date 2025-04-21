#include "mainWindow.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QFileInfo>

MainWindow::MainWindow(QObject *parent) : QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)),
    m_responseData(""),
    m_isLoading(false),
    m_hasError(false),
    m_errorMessage(""),
    m_stationsData(""),
    m_isLoadingStations(false),
    m_hasStationsError(false),
    m_stationsErrorMessage(""),
    m_sensorsData(""),
    m_isLoadingSensors(false),
    m_hasSensorsError(false),
    m_sensorsErrorMessage(""),
    m_chartData(QVariantList()),
    m_parameterName(""),
    m_parameterFormula(""),
    m_minValue(0.0),
    m_maxValue(0.0),
    m_hasChartData(false),
    m_aqIndexData(""),
    m_isLoadingAqIndex(false),
    m_hasAqIndexError(false),
    m_aqIndexErrorMessage(""),
    m_isUsingCachedData(false),
    m_cachedDataMessage(""),
    m_allowSaveToFile(true)
{
}

bool MainWindow::allowSaveToFile() const
{
    return m_allowSaveToFile;
}

void MainWindow::setAllowSaveToFile(bool allow)
{
    if (m_allowSaveToFile != allow) {
        m_allowSaveToFile = allow;
        emit allowSaveToFileChanged();
    }
}

QString MainWindow::ensureDataDirectoryExists()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/cache";
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dataPath;
}

// Save stations data to file
void MainWindow::saveStationsDataToFile(const QJsonDocument &jsonData)
{
    // Exit if saving is not allowed
    if (!m_allowSaveToFile) {
        qDebug() << "Saving to file disabled by user preference";
        return;
    }

    QString filePath = ensureDataDirectoryExists() + "/stations.json";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData.toJson());
        file.close();
        qDebug() << "Stations data saved to" << filePath;
    } else {
        qDebug() << "Failed to save stations data:" << file.errorString();
    }
}

// Load stations data from file
QJsonDocument MainWindow::loadStationsDataFromFile()
{
    QString filePath = ensureDataDirectoryExists() + "/stations.json";
    QFile file(filePath);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull()) {
            qDebug() << "Stations data loaded from" << filePath;
            return jsonDoc;
        }
    }

    qDebug() << "Failed to load stations data from file";
    return QJsonDocument();
}

// Save sensors data to file
void MainWindow::saveSensorsDataToFile(const QString &stationId, const QJsonDocument &jsonData)
{
    // Exit if saving is not allowed
    if (!m_allowSaveToFile) {
        qDebug() << "Saving to file disabled by user preference";
        return;
    }

    QString filePath = ensureDataDirectoryExists() + "/sensors_" + stationId + ".json";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData.toJson());
        file.close();
        qDebug() << "Sensors data saved to" << filePath;
    } else {
        qDebug() << "Failed to save sensors data:" << file.errorString();
    }
}

// Load sensors data from file
QJsonDocument MainWindow::loadSensorsDataFromFile(const QString &stationId)
{
    QString filePath = ensureDataDirectoryExists() + "/sensors_" + stationId + ".json";
    QFile file(filePath);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull()) {
            qDebug() << "Sensors data loaded from" << filePath;
            return jsonDoc;
        }
    }

    qDebug() << "Failed to load sensors data from file";
    return QJsonDocument();
}

// Save sensor data to file
void MainWindow::saveSensorDataToFile(const QString &sensorId, const QJsonDocument &jsonData)
{
    // Exit if saving is not allowed
    if (!m_allowSaveToFile) {
        qDebug() << "Saving to file disabled by user preference";
        return;
    }

    QString filePath = ensureDataDirectoryExists() + "/sensor_" + sensorId + ".json";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData.toJson());
        file.close();
        qDebug() << "Sensor data saved to" << filePath;
    } else {
        qDebug() << "Failed to save sensor data:" << file.errorString();
    }
}

// Load sensor data from file
QJsonDocument MainWindow::loadSensorDataFromFile(const QString &sensorId)
{
    QString filePath = ensureDataDirectoryExists() + "/sensor_" + sensorId + ".json";
    QFile file(filePath);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull()) {
            qDebug() << "Sensor data loaded from" << filePath;
            return jsonDoc;
        }
    }

    qDebug() << "Failed to load sensor data from file";
    return QJsonDocument();
}

// Save air quality index data to file
void MainWindow::saveAqIndexDataToFile(const QString &stationId, const QJsonDocument &jsonData)
{
    // Exit if saving is not allowed
    if (!m_allowSaveToFile) {
        qDebug() << "Saving to file disabled by user preference";
        return;
    }

    QString filePath = ensureDataDirectoryExists() + "/aqindex_" + stationId + ".json";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData.toJson());
        file.close();
        qDebug() << "Air quality index data saved to" << filePath;
    } else {
        qDebug() << "Failed to save air quality index data:" << file.errorString();
    }
}

// Load air quality index data from file
QJsonDocument MainWindow::loadAqIndexDataFromFile(const QString &stationId)
{
    QString filePath = ensureDataDirectoryExists() + "/aqindex_" + stationId + ".json";
    QFile file(filePath);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull()) {
            qDebug() << "Air quality index data loaded from" << filePath;
            return jsonDoc;
        }
    }

    qDebug() << "Failed to load air quality index data from file";
    return QJsonDocument();
}

void MainWindow::setCacheFilesIds(const QStringList &ids)
{
    if (m_cacheFilesIds != ids) {
        m_cacheFilesIds = ids;
        emit cacheFilesIdsChanged(m_cacheFilesIds);
    }
}

void MainWindow::setCacheFileContent(const QString &content)
{
    if (m_cacheFileContent != content) {
        m_cacheFileContent = content;
        emit cacheFileContentChanged(m_cacheFileContent);
    }
}

void MainWindow::setCacheStatusMessage(const QString &message)
{
    if (m_cacheStatusMessage != message) {
        m_cacheStatusMessage = message;
        emit cacheStatusMessageChanged(m_cacheStatusMessage);
    }
}

// Ładowanie listy plików cache
void MainWindow::loadCacheFilesList(int dataTypeIndex)
{
    QString cacheDir = ensureDataDirectoryExists();
    QDir dir(cacheDir);
    QStringList filters;
    QString prefix;

    switch (dataTypeIndex) {
    case 0: // Stacje pomiarowe
        filters << "stations.json";
        prefix = "";
        break;
    case 1: // Czujniki stacji
        filters << "sensors_*.json";
        prefix = "sensors_";
        break;
    case 2: // Dane czujnika
        filters << "sensor_*.json";
        prefix = "sensor_";
        break;
    case 3: // Indeks jakości powietrza
        filters << "aqindex_*.json";
        prefix = "aqindex_";
        break;
    default:
        setCacheStatusMessage("Nieznany typ danych");
        setCacheFilesIds(QStringList());
        return;
    }

    QStringList files = dir.entryList(filters, QDir::Files, QDir::Name);
    QStringList ids;

    if (prefix.isEmpty()) {
        // Dla stacji pomiarowych zwracamy "all"
        if (!files.isEmpty()) {
            ids << "wszystkie";
        }
    } else {
        // Dla innych typów wycinamy prefiks i rozszerzenie
        for (const QString &file : files) {
            QString id = file;
            id.remove(0, prefix.length()); // Usuń prefiks
            id.chop(5); // Usuń rozszerzenie ".json"
            ids << id;
        }
    }

    if (ids.isEmpty()) {
        setCacheStatusMessage("Nie znaleziono plików cache dla wybranego typu danych");
    } else {
        setCacheStatusMessage(QString("Znaleziono %1 plików").arg(ids.count()));
    }

    setCacheFilesIds(ids);
}

// Ładowanie zawartości pliku cache
void MainWindow::loadCacheFileContent(int dataTypeIndex, const QString &fileId)
{
    QString cacheDir = ensureDataDirectoryExists();
    QString filePath;

    // Debugowanie
    qDebug() << "Ładowanie pliku cache, typ:" << dataTypeIndex << "ID:" << fileId;

    // Ustalanie ścieżki pliku
    switch (dataTypeIndex) {
    case 0: // Stacje pomiarowe
        filePath = cacheDir + "/stations.json";
        break;
    case 1: // Czujniki stacji
        filePath = cacheDir + "/sensors_" + fileId + ".json";
        break;
    case 2: // Dane czujnika
        filePath = cacheDir + "/sensor_" + fileId + ".json";
        break;
    case 3: // Indeks jakości powietrza
        filePath = cacheDir + "/aqindex_" + fileId + ".json";
        break;
    default:
        setCacheStatusMessage("Nieznany typ danych");
        setCacheFileContent("");
        return;
    }

    qDebug() << "Próba otwarcia pliku:" << filePath;

    QFile file(filePath);
    if (file.exists()) {
        qDebug() << "Plik istnieje";

        if (file.open(QIODevice::ReadOnly)) {
            qDebug() << "Plik otwarty pomyślnie";
            QByteArray data = file.readAll();
            qDebug() << "Przeczytano" << data.size() << "bajtów";
            file.close();

            QJsonParseError error;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
            if (!jsonDoc.isNull()) {
                qDebug() << "Pomyślnie sparsowano JSON";
                QString formattedJson = formatJsonForDisplay(jsonDoc);
                qDebug() << "Długość sformatowanego JSON:" << formattedJson.length();
                setCacheFileContent(formattedJson);
                setCacheStatusMessage(QString("Wczytano dane z pliku: %1").arg(QFileInfo(filePath).fileName()));
            } else {
                qDebug() << "Błąd parsowania JSON:" << error.errorString();
                setCacheFileContent(QString("Błąd parsowania JSON: %1").arg(error.errorString()));
                setCacheStatusMessage(QString("Błąd parsowania JSON z pliku: %1").arg(QFileInfo(filePath).fileName()));
            }
        } else {
            qDebug() << "Nie można otworzyć pliku:" << file.errorString();
            setCacheFileContent(QString("Nie można otworzyć pliku: %1").arg(file.errorString()));
            setCacheStatusMessage(QString("Nie można otworzyć pliku: %1").arg(QFileInfo(filePath).fileName()));
        }
    } else {
        qDebug() << "Plik nie istnieje:" << filePath;
        setCacheFileContent("Plik nie istnieje");
        setCacheStatusMessage(QString("Nie znaleziono pliku: %1").arg(QFileInfo(filePath).fileName()));
    }
}

// Formatowanie JSON do czytelnej postaci
QString MainWindow::formatJsonForDisplay(const QJsonDocument &jsonDoc)
{
    // Dodajmy debugowanie
    qDebug() << "Formatowanie JSON do wyświetlenia, rozmiar danych:" << jsonDoc.toJson().size();

    // Sprawdźmy czy mamy do czynienia z obiektem czy tablicą
    if (jsonDoc.isObject()) {
        qDebug() << "JSON jest obiektem";
    } else if (jsonDoc.isArray()) {
        qDebug() << "JSON jest tablicą";
    } else {
        qDebug() << "JSON jest pusty lub nieprawidłowy";
    }

    // Zwracamy sformatowany JSON
    return jsonDoc.toJson(QJsonDocument::Indented);
}


// Original getters
QString MainWindow::responseData() const
{
    return m_responseData;
}

bool MainWindow::isLoading() const
{
    return m_isLoading;
}

bool MainWindow::hasError() const
{
    return m_hasError;
}

QString MainWindow::errorMessage() const
{
    return m_errorMessage;
}

// Getters for station data
QString MainWindow::stationsData() const
{
    return m_stationsData;
}

bool MainWindow::isLoadingStations() const
{
    return m_isLoadingStations;
}

bool MainWindow::hasStationsError() const
{
    return m_hasStationsError;
}

QString MainWindow::stationsErrorMessage() const
{
    return m_stationsErrorMessage;
}

// Getters for station sensors data
QString MainWindow::sensorsData() const
{
    return m_sensorsData;
}

bool MainWindow::isLoadingSensors() const
{
    return m_isLoadingSensors;
}

bool MainWindow::hasSensorsError() const
{
    return m_hasSensorsError;
}

QString MainWindow::sensorsErrorMessage() const
{
    return m_sensorsErrorMessage;
}

// New getters for chart data
QVariantList MainWindow::chartData() const
{
    return m_chartData;
}

QString MainWindow::parameterName() const
{
    return m_parameterName;
}

QString MainWindow::parameterFormula() const
{
    return m_parameterFormula;
}

double MainWindow::minValue() const
{
    return m_minValue;
}

double MainWindow::maxValue() const
{
    return m_maxValue;
}

bool MainWindow::hasChartData() const
{
    return m_hasChartData;
}

// Gettery dla indeksu jakości powietrza
QString MainWindow::aqIndexData() const
{
    return m_aqIndexData;
}

bool MainWindow::isLoadingAqIndex() const
{
    return m_isLoadingAqIndex;
}

bool MainWindow::hasAqIndexError() const
{
    return m_hasAqIndexError;
}

QString MainWindow::aqIndexErrorMessage() const
{
    return m_aqIndexErrorMessage;
}


bool MainWindow::isUsingCachedData() const
{
    return m_isUsingCachedData;
}

QString MainWindow::cachedDataMessage() const
{
    return m_cachedDataMessage;
}


// Original setters
void MainWindow::setResponseData(const QString &data)
{
    if (m_responseData != data) {
        m_responseData = data;
        emit responseDataChanged();
    }
}

void MainWindow::setIsLoading(bool loading)
{
    if (m_isLoading != loading) {
        m_isLoading = loading;
        emit isLoadingChanged();
    }
}

void MainWindow::setHasError(bool hasError)
{
    if (m_hasError != hasError) {
        m_hasError = hasError;
        emit hasErrorChanged();
    }
}

void MainWindow::setErrorMessage(const QString &message)
{
    if (m_errorMessage != message) {
        m_errorMessage = message;
        emit errorMessageChanged();
    }
}

// Setters for station data
void MainWindow::setStationsData(const QString &data)
{
    if (m_stationsData != data) {
        m_stationsData = data;
        emit stationsDataChanged();
    }
}

void MainWindow::setIsLoadingStations(bool loading)
{
    if (m_isLoadingStations != loading) {
        m_isLoadingStations = loading;
        emit isLoadingStationsChanged();
    }
}

void MainWindow::setHasStationsError(bool hasError)
{
    if (m_hasStationsError != hasError) {
        m_hasStationsError = hasError;
        emit hasStationsErrorChanged();
    }
}

void MainWindow::setStationsErrorMessage(const QString &message)
{
    if (m_stationsErrorMessage != message) {
        m_stationsErrorMessage = message;
        emit stationsErrorMessageChanged();
    }
}

// Setters for station sensors data
void MainWindow::setSensorsData(const QString &data)
{
    if (m_sensorsData != data) {
        m_sensorsData = data;
        emit sensorsDataChanged();
    }
}

void MainWindow::setIsLoadingSensors(bool loading)
{
    if (m_isLoadingSensors != loading) {
        m_isLoadingSensors = loading;
        emit isLoadingSensorsChanged();
    }
}

void MainWindow::setHasSensorsError(bool hasError)
{
    if (m_hasSensorsError != hasError) {
        m_hasSensorsError = hasError;
        emit hasSensorsErrorChanged();
    }
}

void MainWindow::setSensorsErrorMessage(const QString &message)
{
    if (m_sensorsErrorMessage != message) {
        m_sensorsErrorMessage = message;
        emit sensorsErrorMessageChanged();
    }
}

// New setters for chart data
void MainWindow::setChartData(const QVariantList &data)
{
    if (m_chartData != data) {
        m_chartData = data;
        emit chartDataChanged();
    }
}

void MainWindow::setParameterName(const QString &name)
{
    if (m_parameterName != name) {
        m_parameterName = name;
        emit parameterNameChanged();
    }
}

void MainWindow::setParameterFormula(const QString &formula)
{
    if (m_parameterFormula != formula) {
        m_parameterFormula = formula;
        emit parameterFormulaChanged();
    }
}

void MainWindow::setMinValue(double value)
{
    if (m_minValue != value) {
        m_minValue = value;
        emit minValueChanged();
    }
}

void MainWindow::setMaxValue(double value)
{
    if (m_maxValue != value) {
        m_maxValue = value;
        emit maxValueChanged();
    }
}

void MainWindow::setHasChartData(bool hasData)
{
    if (m_hasChartData != hasData) {
        m_hasChartData = hasData;
        emit hasChartDataChanged();
    }
}

// Settery dla indeksu jakości powietrza
void MainWindow::setAqIndexData(const QString &data)
{
    if (m_aqIndexData != data) {
        m_aqIndexData = data;
        emit aqIndexDataChanged();
    }
}

void MainWindow::setIsLoadingAqIndex(bool loading)
{
    if (m_isLoadingAqIndex != loading) {
        m_isLoadingAqIndex = loading;
        emit isLoadingAqIndexChanged();
    }
}

void MainWindow::setHasAqIndexError(bool hasError)
{
    if (m_hasAqIndexError != hasError) {
        m_hasAqIndexError = hasError;
        emit hasAqIndexErrorChanged();
    }
}

void MainWindow::setAqIndexErrorMessage(const QString &message)
{
    if (m_aqIndexErrorMessage != message) {
        m_aqIndexErrorMessage = message;
        emit aqIndexErrorMessageChanged();
    }
}

void MainWindow::setIsUsingCachedData(bool usingCached)
{
    if (m_isUsingCachedData != usingCached) {
        m_isUsingCachedData = usingCached;
        emit isUsingCachedDataChanged();
    }
}

void MainWindow::setCachedDataMessage(const QString &message)
{
    if (m_cachedDataMessage != message) {
        m_cachedDataMessage = message;
        emit cachedDataMessageChanged();
    }
}

// Original fetchData method
void MainWindow::fetchData(const QString &sensorId)
{
    if (sensorId.isEmpty()) {
        setHasError(true);
        setErrorMessage("ID sensora nie może być puste");
        setResponseData("");
        setHasChartData(false);
        return;
    }

    setIsLoading(true);
    setHasError(false);
    setErrorMessage("");
    setHasChartData(false);

    QString urlString = QString("https://api.gios.gov.pl/pjp-api/rest/data/getData/%1").arg(sensorId);
    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, sensorId]() {
        this->onNetworkReply(reply, sensorId);
    });
}

// Method for fetching stations
void MainWindow::fetchStations(const QString &cityName)
{
    setIsLoadingStations(true);
    setHasStationsError(false);
    setStationsErrorMessage("");

    QString urlString = "https://api.gios.gov.pl/pjp-api/rest/station/findAll";
    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, cityName]() {
        this->onStationsNetworkReply(reply, cityName);
    });
}

// Method for fetching station sensors
void MainWindow::fetchStationSensors(const QString &stationId)
{
    if (stationId.isEmpty()) {
        setHasSensorsError(true);
        setSensorsErrorMessage("ID stacji nie może być puste");
        setSensorsData("");
        return;
    }

    setIsLoadingSensors(true);
    setHasSensorsError(false);
    setSensorsErrorMessage("");

    QString urlString = QString("https://api.gios.gov.pl/pjp-api/rest/station/sensors/%1").arg(stationId);
    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, stationId]() {
        this->onSensorsNetworkReply(reply, stationId);
    });
}

// Original network reply handler with added chart data processing
void MainWindow::onNetworkReply(QNetworkReply *reply, const QString &sensorId)
{
    reply->deleteLater();
    setIsLoading(false);

    if (reply->error() != QNetworkReply::NoError) {
        setHasError(true);
        setErrorMessage(QString("Błąd sieciowy: %1").arg(reply->errorString()));

        // Try to load data from file
        QJsonDocument cachedData = loadSensorDataFromFile(sensorId);
        if (!cachedData.isNull()) {
            setResponseData(formatJsonResponse(cachedData));
            processChartData(cachedData);
            setHasError(false);
            setErrorMessage("Połączenie nieudane, wyświetlono dane z pamięci podręcznej");
        } else {
            setResponseData("");
            setHasChartData(false);
        }
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (jsonResponse.isNull() || jsonResponse.isEmpty()) {
        setHasError(true);
        setErrorMessage("Otrzymano nieprawidłową odpowiedź JSON");

        // Try to load data from file
        QJsonDocument cachedData = loadSensorDataFromFile(sensorId);
        if (!cachedData.isNull()) {
            setResponseData(formatJsonResponse(cachedData));
            processChartData(cachedData);
            setHasError(false);
            setErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setResponseData("");
            setHasChartData(false);
        }
        return;
    }

    // Save data to file
    saveSensorDataToFile(sensorId, jsonResponse);

    // Format JSON response and process chart data
    setResponseData(formatJsonResponse(jsonResponse));
    processChartData(jsonResponse);
}
// Handler for stations network reply
void MainWindow::onStationsNetworkReply(QNetworkReply *reply, const QString &cityFilter)
{
    reply->deleteLater();
    setIsLoadingStations(false);

    if (reply->error() != QNetworkReply::NoError) {
        setHasStationsError(true);
        setStationsErrorMessage(QString("Błąd sieciowy: %1").arg(reply->errorString()));

        // Try to load data from file when network error occurs
        QJsonDocument cachedData = loadStationsDataFromFile();
        if (!cachedData.isNull()) {
            setStationsData(formatStationsJsonResponse(cachedData, cityFilter));
            setHasStationsError(false);
            setStationsErrorMessage("Połączenie nieudane, wyświetlono dane z pamięci podręcznej");
        } else {
            setStationsData("");
        }
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (jsonResponse.isNull()) {
        setHasStationsError(true);
        setStationsErrorMessage("Otrzymano nieprawidłową odpowiedź JSON");

        // Try to load data from file
        QJsonDocument cachedData = loadStationsDataFromFile();
        if (!cachedData.isNull()) {
            setStationsData(formatStationsJsonResponse(cachedData, cityFilter));
            setHasStationsError(false);
            setStationsErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setStationsData("");
        }
        return;
    }

    if (!jsonResponse.isArray()) {
        setHasStationsError(true);
        setStationsErrorMessage("Oczekiwano tablicy stacji");

        // Try to load data from file
        QJsonDocument cachedData = loadStationsDataFromFile();
        if (!cachedData.isNull()) {
            setStationsData(formatStationsJsonResponse(cachedData, cityFilter));
            setHasStationsError(false);
            setStationsErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setStationsData("");
        }
        return;
    }

    // Save data to file
    saveStationsDataToFile(jsonResponse);

    // Format and set the stations data
    setStationsData(formatStationsJsonResponse(jsonResponse, cityFilter));
}

// Handler for sensors network reply
void MainWindow::onSensorsNetworkReply(QNetworkReply *reply, const QString &stationId)
{
    reply->deleteLater();
    setIsLoadingSensors(false);

    if (reply->error() != QNetworkReply::NoError) {
        setHasSensorsError(true);
        setSensorsErrorMessage(QString("Błąd sieciowy: %1").arg(reply->errorString()));

        // Try to load data from file
        QJsonDocument cachedData = loadSensorsDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setSensorsData(formatSensorsJsonResponse(cachedData));
            setHasSensorsError(false);
            setSensorsErrorMessage("Połączenie nieudane, wyświetlono dane z pamięci podręcznej");
        } else {
            setSensorsData("");
        }
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (jsonResponse.isNull()) {
        setHasSensorsError(true);
        setSensorsErrorMessage("Otrzymano nieprawidłową odpowiedź JSON");

        // Try to load data from file
        QJsonDocument cachedData = loadSensorsDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setSensorsData(formatSensorsJsonResponse(cachedData));
            setHasSensorsError(false);
            setSensorsErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setSensorsData("");
        }
        return;
    }

    if (!jsonResponse.isArray()) {
        setHasSensorsError(true);
        setSensorsErrorMessage("Oczekiwano tablicy czujników");

        // Try to load data from file
        QJsonDocument cachedData = loadSensorsDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setSensorsData(formatSensorsJsonResponse(cachedData));
            setHasSensorsError(false);
            setSensorsErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setSensorsData("");
        }
        return;
    }

    // Save data to file
    saveSensorsDataToFile(stationId, jsonResponse);

    // Format and set the sensors data
    setSensorsData(formatSensorsJsonResponse(jsonResponse));
}

// Original JSON formatter
QString MainWindow::formatJsonResponse(const QJsonDocument &doc) const
{
    QJsonObject jsonObject = doc.object();
    QString formattedOutput;

    // Sprawdzamy czy mamy oczekiwaną strukturę
    if (jsonObject.contains("key") && jsonObject.contains("values")) {
        QString key = jsonObject["key"].toString();
        formattedOutput += "Parametr: " + key + "\n\n";

        QJsonArray values = jsonObject["values"].toArray();
        formattedOutput += "Pomiary:\n";

        for (int i = 0; i < values.size(); ++i) {
            QJsonObject measurement = values[i].toObject();
            QString date = measurement["date"].toString();

            // Sprawdzamy czy wartość istnieje i nie jest null
            if (measurement.contains("value") && !measurement["value"].isNull()) {
                double value = measurement["value"].toDouble();
                formattedOutput += QString("Data: %1, Wartość: %2\n").arg(date).arg(value);
            } else {
                formattedOutput += QString("Data: %1, Wartość: brak danych\n").arg(date);
            }
        }
    } else {
        // Jeśli struktura jest inna, wyświetlamy cały JSON
        formattedOutput = QString(doc.toJson(QJsonDocument::Indented));
    }

    return formattedOutput;
}

// Formatter for stations data
QString MainWindow::formatStationsJsonResponse(const QJsonDocument &doc, const QString &cityFilter) const
{
    QJsonArray stations = doc.array();
    QString formattedOutput;
    int count = 0;

    formattedOutput += cityFilter.isEmpty()
                           ? "Wszystkie stacje pomiarowe:\n\n"
                           : QString("Stacje pomiarowe w mieście '%1':\n\n").arg(cityFilter);

    for (int i = 0; i < stations.size(); ++i) {
        QJsonObject station = stations[i].toObject();

        // Filter by city name if provided
        if (!cityFilter.isEmpty()) {
            QJsonObject city = station["city"].toObject();
            QString cityName = city["name"].toString();

            // Skip if city name doesn't match the filter (case insensitive)
            if (!cityName.toLower().contains(cityFilter.toLower())) {
                continue;
            }
        }

        int id = station["id"].toInt();
        QString stationName = station["stationName"].toString();
        QString lat = station["gegrLat"].toString();
        QString lon = station["gegrLon"].toString();

        QJsonObject city = station["city"].toObject();
        QString cityName = city["name"].toString();

        QJsonObject commune = city["commune"].toObject();
        QString communeName = commune["communeName"].toString();
        QString districtName = commune["districtName"].toString();
        QString provinceName = commune["provinceName"].toString();

        QString address = station["addressStreet"].toString();
        if (address.isEmpty()) {
            address = "brak danych";
        }

        formattedOutput += QString("ID: %1\n").arg(id);
        formattedOutput += QString("Nazwa: %1\n").arg(stationName);
        formattedOutput += QString("Miasto: %1\n").arg(cityName);
        formattedOutput += QString("Adres: %1\n").arg(address);
        formattedOutput += QString("Współrzędne: %1, %2\n").arg(lat).arg(lon);
        formattedOutput += QString("Gmina: %1\n").arg(communeName);
        formattedOutput += QString("Powiat: %1\n").arg(districtName);
        formattedOutput += QString("Województwo: %1\n").arg(provinceName);
        formattedOutput += "\n---------------------------\n\n";

        count++;
    }

    // Add count information at the end
    if (count == 0) {
        formattedOutput = QString("Nie znaleziono stacji pomiarowych %1")
        .arg(cityFilter.isEmpty() ? "" : QString("w mieście '%1'").arg(cityFilter));
    } else {
        formattedOutput += QString("Znaleziono %1 stacji pomiarowych").arg(count);
    }

    return formattedOutput;
}

// Formatter for station sensors data
QString MainWindow::formatSensorsJsonResponse(const QJsonDocument &doc) const
{
    QJsonArray sensors = doc.array();
    QString formattedOutput;

    if (sensors.isEmpty()) {
        return "Nie znaleziono czujników dla podanej stacji.";
    }

    formattedOutput += QString("Czujniki dla stacji (ID: %1):\n\n").arg(sensors[0].toObject()["stationId"].toInt());

    for (int i = 0; i < sensors.size(); ++i) {
        QJsonObject sensor = sensors[i].toObject();
        int sensorId = sensor["id"].toInt();
        int stationId = sensor["stationId"].toInt();

        QJsonObject param = sensor["param"].toObject();
        QString paramName = param["paramName"].toString();
        QString paramFormula = param["paramFormula"].toString();
        QString paramCode = param["paramCode"].toString();
        int paramId = param["idParam"].toInt();

        formattedOutput += QString("ID czujnika: %1\n").arg(sensorId);
        formattedOutput += QString("Parametr: %1 (%2)\n").arg(paramName).arg(paramFormula);
        formattedOutput += QString("Kod parametru: %1\n").arg(paramCode);
        formattedOutput += QString("ID parametru: %1\n").arg(paramId);
        formattedOutput += "\n---------------------------\n\n";
    }

    formattedOutput += QString("Znaleziono %1 czujników").arg(sensors.size());
    return formattedOutput;
}

// Process data for chart
void MainWindow::processChartData(const QJsonDocument &doc)
{
    QJsonObject jsonObject = doc.object();

    // Reset chart data
    QVariantList chartPoints;
    setHasChartData(false);

    // Check if structure is as expected
    if (!jsonObject.contains("key") || !jsonObject.contains("values")) {
        return;
    }

    // Get parameter information
    QString key = jsonObject["key"].toString();
    setParameterName(key);

    // We would need to map key to formula, for now just use the key
    setParameterFormula(key);

    QJsonArray values = jsonObject["values"].toArray();

    // Check if we have any values
    if (values.isEmpty()) {
        return;
    }

    double minVal = 9999999.0;
    double maxVal = -9999999.0;

    // Process each measurement
    for (int i = 0; i < values.size(); ++i) {
        QJsonObject measurement = values[i].toObject();
        QString dateStr = measurement["date"].toString();

        // Check if value exists and is not null
        if (measurement.contains("value") && !measurement["value"].isNull()) {
            double value = measurement["value"].toDouble();

            // Parse date string to QDateTime
            QDateTime date = QDateTime::fromString(dateStr, Qt::ISODate);

            // Create chart point object
            QVariantMap point;
            point["x"] = date.toMSecsSinceEpoch();
            point["y"] = value;
            point["date"] = dateStr;

            chartPoints.append(point);

            // Update min and max values
            if (value < minVal) minVal = value;
            if (value > maxVal) maxVal = value;
        }
    }

    // Check if we have any valid data points
    if (!chartPoints.isEmpty()) {
        setChartData(chartPoints);
        setMinValue(minVal);
        setMaxValue(maxVal);
        setHasChartData(true);
    }
}

void MainWindow::fetchAqIndex(const QString &stationId)
{
    if (stationId.isEmpty()) {
        setHasAqIndexError(true);
        setAqIndexErrorMessage("ID stacji nie może być puste");
        setAqIndexData("");
        return;
    }

    setIsLoadingAqIndex(true);
    setHasAqIndexError(false);
    setAqIndexErrorMessage("");

    QString urlString = QString("https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/%1").arg(stationId);
    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, stationId]() {
        this->onAqIndexNetworkReply(reply, stationId);
    });
}

// Obsługa odpowiedzi z API dla indeksu jakości powietrza
void MainWindow::onAqIndexNetworkReply(QNetworkReply *reply, const QString &stationId)
{
    reply->deleteLater();
    setIsLoadingAqIndex(false);

    if (reply->error() != QNetworkReply::NoError) {
        setHasAqIndexError(true);
        setAqIndexErrorMessage(QString("Błąd sieciowy: %1").arg(reply->errorString()));

        // Try to load data from file
        QJsonDocument cachedData = loadAqIndexDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setAqIndexData(formatAqIndexJsonResponse(cachedData));
            setHasAqIndexError(false);
            setAqIndexErrorMessage("Połączenie nieudane, wyświetlono dane z pamięci podręcznej");
        } else {
            setAqIndexData("");
        }
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (jsonResponse.isNull()) {
        setHasAqIndexError(true);
        setAqIndexErrorMessage("Otrzymano nieprawidłową odpowiedź JSON");

        // Try to load data from file
        QJsonDocument cachedData = loadAqIndexDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setAqIndexData(formatAqIndexJsonResponse(cachedData));
            setHasAqIndexError(false);
            setAqIndexErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setAqIndexData("");
        }
        return;
    }

    if (!jsonResponse.isObject()) {
        setHasAqIndexError(true);
        setAqIndexErrorMessage("Oczekiwano obiektu JSON");

        // Try to load data from file
        QJsonDocument cachedData = loadAqIndexDataFromFile(stationId);
        if (!cachedData.isNull()) {
            setAqIndexData(formatAqIndexJsonResponse(cachedData));
            setHasAqIndexError(false);
            setAqIndexErrorMessage("Nieprawidłowe dane, wyświetlono dane z pamięci podręcznej");
        } else {
            setAqIndexData("");
        }
        return;
    }

    // Save data to file
    saveAqIndexDataToFile(stationId, jsonResponse);

    // Format and set the data
    setAqIndexData(formatAqIndexJsonResponse(jsonResponse));
}

// Formatowanie odpowiedzi JSON dla indeksu jakości powietrza
QString MainWindow::formatAqIndexJsonResponse(const QJsonDocument &doc) const
{
    QJsonObject data = doc.object();
    QString formattedOutput;

    // Sprawdź czy mamy dane indeksu
    if (data.isEmpty()) {
        return "Nie znaleziono danych indeksu jakości powietrza dla podanej stacji.";
    }

    // Informacje ogólne
    formattedOutput += "INDEKS JAKOŚCI POWIETRZA\n";
    formattedOutput += "=========================\n\n";

    // ID stacji
    int id = data["id"].toInt();
    formattedOutput += QString("ID stacji: %1\n\n").arg(id);

    // Data obliczenia indeksu
    QString stCalcDate = data["stCalcDate"].toString();
    formattedOutput += QString("Data obliczenia indeksu: %1\n").arg(stCalcDate);

    // Data pobrania danych źródłowych
    QString stSourceDataDate = data["stSourceDataDate"].toString();
    formattedOutput += QString("Data pobrania danych źródłowych: %1\n\n").arg(stSourceDataDate);

    // Indeks jakości powietrza dla stacji
    QJsonObject stIndexLevel = data["stIndexLevel"].toObject();
    if (!stIndexLevel.isEmpty()) {
        int indexId = stIndexLevel["id"].toInt();
        QString indexName = stIndexLevel["indexLevelName"].toString();
        formattedOutput += QString("Ogólny indeks jakości powietrza: %1 (poziom %2)\n\n").arg(indexName).arg(indexId);
    } else {
        formattedOutput += "Ogólny indeks jakości powietrza: brak danych\n\n";
    }

    formattedOutput += "INDEKSY POSZCZEGÓLNYCH ZANIECZYSZCZEŃ\n";
    formattedOutput += "=====================================\n\n";

    // Funkcja pomocnicza do formatowania indeksu dla zanieczyszczenia
    auto formatPollutantIndex = [&data, &formattedOutput](const QString &pollutant, const QString &pollutantName) {
        QString calcDateKey = pollutant + "CalcDate";
        QString indexLevelKey = pollutant + "IndexLevel";
        QString sourceDataDateKey = pollutant + "SourceDataDate";

        if (data.contains(calcDateKey)) {
            QString calcDate = data[calcDateKey].toString();
            formattedOutput += QString("%1 (%2):\n").arg(pollutantName).arg(pollutant.toUpper());
            formattedOutput += QString("- Data obliczenia: %1\n").arg(calcDate);

            QJsonObject indexLevel = data[indexLevelKey].toObject();
            if (!indexLevel.isEmpty()) {
                int indexId = indexLevel["id"].toInt();
                QString indexName = indexLevel["indexLevelName"].toString();
                formattedOutput += QString("- Poziom jakości: %1 (poziom %2)\n").arg(indexName).arg(indexId);
            } else {
                formattedOutput += "- Poziom jakości: brak danych\n";
            }

            QString sourceDataDate = data[sourceDataDateKey].toString();
            if (!sourceDataDate.isEmpty() && !sourceDataDate.isNull()) {
                formattedOutput += QString("- Data danych źródłowych: %1\n").arg(sourceDataDate);
            } else {
                formattedOutput += "- Data danych źródłowych: brak danych\n";
            }

            formattedOutput += "\n";
        }
    };

    // Formatuj dane dla każdego zanieczyszczenia
    formatPollutantIndex("so2", "Dwutlenek siarki");
    formatPollutantIndex("no2", "Dwutlenek azotu");
    formatPollutantIndex("co", "Tlenek węgla");
    formatPollutantIndex("pm10", "Pył zawieszony PM10");
    formatPollutantIndex("pm25", "Pył zawieszony PM2.5");
    formatPollutantIndex("o3", "Ozon");
    formatPollutantIndex("c6h6", "Benzen");

    return formattedOutput;
}

bool MainWindow::isNetworkAvailable() const
{
    // This is a simplified check - in a real application, you might want to use
    // QNetworkConfigurationManager or another approach for a more robust check
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("http://www.google.com"));
    QNetworkReply *reply = manager.get(request);

    // Wait for response with a timeout
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QTimer::singleShot(3000, &loop, &QEventLoop::quit);  // 3-second timeout
    loop.exec();

    bool isAvailable = (reply->error() == QNetworkReply::NoError);
    reply->deleteLater();

    return isAvailable;
}

// New method to force an update from cached data (for the "Pobierz dane" button)
void MainWindow::loadStationsFromCache()
{
    QJsonDocument cachedData = loadStationsDataFromFile();
    if (!cachedData.isNull()) {
        setStationsData(formatStationsJsonResponse(cachedData, ""));
        setHasStationsError(false);
        setStationsErrorMessage("Załadowano dane z pamięci podręcznej");
    } else {
        setHasStationsError(true);
        setStationsErrorMessage("Brak danych w pamięci podręcznej");
        setStationsData("");
    }
}

void MainWindow::loadSensorsFromCache(const QString &stationId)
{
    if (stationId.isEmpty()) {
        setHasSensorsError(true);
        setSensorsErrorMessage("ID stacji nie może być puste");
        setSensorsData("");
        return;
    }

    QJsonDocument cachedData = loadSensorsDataFromFile(stationId);
    if (!cachedData.isNull()) {
        setSensorsData(formatSensorsJsonResponse(cachedData));
        setHasSensorsError(false);
        setSensorsErrorMessage("Załadowano dane z pamięci podręcznej");
    } else {
        setHasSensorsError(true);
        setSensorsErrorMessage("Brak danych w pamięci podręcznej");
        setSensorsData("");
    }
}

void MainWindow::loadSensorDataFromCache(const QString &sensorId)
{
    if (sensorId.isEmpty()) {
        setHasError(true);
        setErrorMessage("ID sensora nie może być puste");
        setResponseData("");
        setHasChartData(false);
        return;
    }

    QJsonDocument cachedData = loadSensorDataFromFile(sensorId);
    if (!cachedData.isNull()) {
        setResponseData(formatJsonResponse(cachedData));
        processChartData(cachedData);
        setHasError(false);
        setErrorMessage("Załadowano dane z pamięci podręcznej");
    } else {
        setHasError(true);
        setErrorMessage("Brak danych w pamięci podręcznej");
        setResponseData("");
        setHasChartData(false);
    }
}

void MainWindow::loadAqIndexFromCache(const QString &stationId)
{
    if (stationId.isEmpty()) {
        setHasAqIndexError(true);
        setAqIndexErrorMessage("ID stacji nie może być puste");
        setAqIndexData("");
        return;
    }

    QJsonDocument cachedData = loadAqIndexDataFromFile(stationId);
    if (!cachedData.isNull()) {
        setAqIndexData(formatAqIndexJsonResponse(cachedData));
        setHasAqIndexError(false);
        setAqIndexErrorMessage("Załadowano dane z pamięci podręcznej");
    } else {
        setHasAqIndexError(true);
        setAqIndexErrorMessage("Brak danych w pamięci podręcznej");
        setAqIndexData("");
    }
}


