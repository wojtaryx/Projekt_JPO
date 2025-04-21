#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantList>
#include <QTimer>
#include <QEventLoop>

class MainWindow : public QObject
{
    Q_OBJECT

    // Oryginalne właściwości
    Q_PROPERTY(QString responseData READ responseData WRITE setResponseData NOTIFY responseDataChanged)
    Q_PROPERTY(bool isLoading READ isLoading WRITE setIsLoading NOTIFY isLoadingChanged)
    Q_PROPERTY(bool hasError READ hasError WRITE setHasError NOTIFY hasErrorChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged)

    // Właściwości stacji
    Q_PROPERTY(QString stationsData READ stationsData WRITE setStationsData NOTIFY stationsDataChanged)
    Q_PROPERTY(bool isLoadingStations READ isLoadingStations WRITE setIsLoadingStations NOTIFY isLoadingStationsChanged)
    Q_PROPERTY(bool hasStationsError READ hasStationsError WRITE setHasStationsError NOTIFY hasStationsErrorChanged)
    Q_PROPERTY(QString stationsErrorMessage READ stationsErrorMessage WRITE setStationsErrorMessage NOTIFY stationsErrorMessageChanged)

    // Właściwości czujników stacji
    Q_PROPERTY(QString sensorsData READ sensorsData WRITE setSensorsData NOTIFY sensorsDataChanged)
    Q_PROPERTY(bool isLoadingSensors READ isLoadingSensors WRITE setIsLoadingSensors NOTIFY isLoadingSensorsChanged)
    Q_PROPERTY(bool hasSensorsError READ hasSensorsError WRITE setHasSensorsError NOTIFY hasSensorsErrorChanged)
    Q_PROPERTY(QString sensorsErrorMessage READ sensorsErrorMessage WRITE setSensorsErrorMessage NOTIFY sensorsErrorMessageChanged)

    // Właściwości wykresu
    Q_PROPERTY(QVariantList chartData READ chartData WRITE setChartData NOTIFY chartDataChanged)
    Q_PROPERTY(QString parameterName READ parameterName WRITE setParameterName NOTIFY parameterNameChanged)
    Q_PROPERTY(QString parameterFormula READ parameterFormula WRITE setParameterFormula NOTIFY parameterFormulaChanged)
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(bool hasChartData READ hasChartData WRITE setHasChartData NOTIFY hasChartDataChanged)

    // Właściwości dla indeksu jakości powietrza
    Q_PROPERTY(QString aqIndexData READ aqIndexData WRITE setAqIndexData NOTIFY aqIndexDataChanged)
    Q_PROPERTY(bool isLoadingAqIndex READ isLoadingAqIndex WRITE setIsLoadingAqIndex NOTIFY isLoadingAqIndexChanged)
    Q_PROPERTY(bool hasAqIndexError READ hasAqIndexError WRITE setHasAqIndexError NOTIFY hasAqIndexErrorChanged)
    Q_PROPERTY(QString aqIndexErrorMessage READ aqIndexErrorMessage WRITE setAqIndexErrorMessage NOTIFY aqIndexErrorMessageChanged)

    //dane archiwalne
    Q_PROPERTY(bool isUsingCachedData READ isUsingCachedData WRITE setIsUsingCachedData NOTIFY isUsingCachedDataChanged)
    Q_PROPERTY(QString cachedDataMessage READ cachedDataMessage WRITE setCachedDataMessage NOTIFY cachedDataMessageChanged)
    Q_PROPERTY(bool allowSaveToFile READ allowSaveToFile WRITE setAllowSaveToFile NOTIFY allowSaveToFileChanged)

    // Dla przeglądarki plików cache
    Q_PROPERTY(QStringList cacheFilesIds READ cacheFilesIds NOTIFY cacheFilesIdsChanged)
    Q_PROPERTY(QString cacheFileContent READ cacheFileContent NOTIFY cacheFileContentChanged)
    Q_PROPERTY(QString cacheStatusMessage READ cacheStatusMessage NOTIFY cacheStatusMessageChanged)

public:
    explicit MainWindow(QObject *parent = nullptr);

    // Oryginalne gettery
    QString responseData() const;
    bool isLoading() const;
    bool hasError() const;
    QString errorMessage() const;

    // Gettery dla stacji
    QString stationsData() const;
    bool isLoadingStations() const;
    bool hasStationsError() const;
    QString stationsErrorMessage() const;

    // Gettery dla czujników stacji
    QString sensorsData() const;
    bool isLoadingSensors() const;
    bool hasSensorsError() const;
    QString sensorsErrorMessage() const;

    // Gettery dla wykresu
    QVariantList chartData() const;
    QString parameterName() const;
    QString parameterFormula() const;
    double minValue() const;
    double maxValue() const;
    bool hasChartData() const;

    // Gettery dla indeksu jakości powietrza
    QString aqIndexData() const;
    bool isLoadingAqIndex() const;
    bool hasAqIndexError() const;
    QString aqIndexErrorMessage() const;


    bool isUsingCachedData() const;
    QString cachedDataMessage() const;

    bool allowSaveToFile() const;
    void setAllowSaveToFile(bool allow);

    QStringList cacheFilesIds() const { return m_cacheFilesIds; }
    QString cacheFileContent() const { return m_cacheFileContent; }
    QString cacheStatusMessage() const { return m_cacheStatusMessage; }


    // Oryginalne settery
    void setResponseData(const QString &data);
    void setIsLoading(bool loading);
    void setHasError(bool hasError);
    void setErrorMessage(const QString &message);

    // Settery dla stacji
    void setStationsData(const QString &data);
    void setIsLoadingStations(bool loading);
    void setHasStationsError(bool hasError);
    void setStationsErrorMessage(const QString &message);

    // Settery dla czujników stacji
    void setSensorsData(const QString &data);
    void setIsLoadingSensors(bool loading);
    void setHasSensorsError(bool hasError);
    void setSensorsErrorMessage(const QString &message);

    // Settery dla wykresu
    void setChartData(const QVariantList &data);
    void setParameterName(const QString &name);
    void setParameterFormula(const QString &formula);
    void setMinValue(double value);
    void setMaxValue(double value);
    void setHasChartData(bool hasData);

    // Settery dla indeksu jakości powietrza
    void setAqIndexData(const QString &data);
    void setIsLoadingAqIndex(bool loading);
    void setHasAqIndexError(bool hasError);
    void setAqIndexErrorMessage(const QString &message);

    Q_INVOKABLE bool isNetworkAvailable() const;

    // Methods for loading from cache
    Q_INVOKABLE void loadStationsFromCache();
    Q_INVOKABLE void loadSensorsFromCache(const QString &stationId);
    Q_INVOKABLE void loadSensorDataFromCache(const QString &sensorId);
    Q_INVOKABLE void loadAqIndexFromCache(const QString &stationId);

    Q_INVOKABLE void loadCacheFilesList(int dataTypeIndex);
    Q_INVOKABLE void loadCacheFileContent(int dataTypeIndex, const QString &fileId);

public slots:
    // Oryginalne sloty
    void fetchData(const QString &sensorId);
    void fetchStations(const QString &cityName);
    void fetchStationSensors(const QString &stationId);

    // Nowy slot dla indeksu jakości powietrza
    void fetchAqIndex(const QString &stationId);

private:
    // Obsługa odpowiedzi sieciowych
    void onNetworkReply(QNetworkReply *reply, const QString &sensorId);;
    void onStationsNetworkReply(QNetworkReply *reply, const QString &cityFilter);
    void onSensorsNetworkReply(QNetworkReply *reply, const QString &stationId);
    void onAqIndexNetworkReply(QNetworkReply *reply, const QString &stationId);

    // Formattery odpowiedzi
    QString formatJsonResponse(const QJsonDocument &doc) const;
    QString formatStationsJsonResponse(const QJsonDocument &doc, const QString &cityFilter) const;
    QString formatSensorsJsonResponse(const QJsonDocument &doc) const;
    QString formatAqIndexJsonResponse(const QJsonDocument &doc) const;

    // Przetwarzanie danych wykresu
    void processChartData(const QJsonDocument &doc);

    // Menedżer połączeń sieciowych
    QNetworkAccessManager *m_networkManager;

    // Dane odpowiedzi
    QString m_responseData;
    bool m_isLoading;
    bool m_hasError;
    QString m_errorMessage;

    // Dane stacji
    QString m_stationsData;
    bool m_isLoadingStations;
    bool m_hasStationsError;
    QString m_stationsErrorMessage;

    // Dane czujników
    QString m_sensorsData;
    bool m_isLoadingSensors;
    bool m_hasSensorsError;
    QString m_sensorsErrorMessage;

    // Dane wykresu
    QVariantList m_chartData;
    QString m_parameterName;
    QString m_parameterFormula;
    double m_minValue;
    double m_maxValue;
    bool m_hasChartData;

    // Dane indeksu jakości powietrza
    QString m_aqIndexData;
    bool m_isLoadingAqIndex;
    bool m_hasAqIndexError;
    QString m_aqIndexErrorMessage;


    bool m_isUsingCachedData;
    QString m_cachedDataMessage;

    //pobieranie do pliku
    QString ensureDataDirectoryExists();
    QJsonDocument loadStationsDataFromFile();
    QJsonDocument loadSensorsDataFromFile(const QString &stationId);
    QJsonDocument loadSensorDataFromFile(const QString &sensorId);
    QJsonDocument loadAqIndexDataFromFile(const QString &stationId);

    QStringList m_cacheFilesIds;
    QString m_cacheFileContent;
    QString m_cacheStatusMessage;
    QString formatJsonForDisplay(const QJsonDocument &jsonDoc);

    void saveStationsDataToFile(const QJsonDocument &jsonData);
    void saveSensorsDataToFile(const QString &stationId, const QJsonDocument &jsonData);
    void saveSensorDataToFile(const QString &sensorId, const QJsonDocument &jsonData);
    void saveAqIndexDataToFile(const QString &stationId, const QJsonDocument &jsonData);


    void setIsUsingCachedData(bool usingCached);
    void setCachedDataMessage(const QString &message);
    bool m_allowSaveToFile;

    void setCacheFilesIds(const QStringList &ids);
    void setCacheFileContent(const QString &content);
    void setCacheStatusMessage(const QString &message);

signals:
    // Oryginalne sygnały
    void responseDataChanged();
    void isLoadingChanged();
    void hasErrorChanged();
    void errorMessageChanged();

    // Sygnały dla stacji
    void stationsDataChanged();
    void isLoadingStationsChanged();
    void hasStationsErrorChanged();
    void stationsErrorMessageChanged();

    // Sygnały dla czujników
    void sensorsDataChanged();
    void isLoadingSensorsChanged();
    void hasSensorsErrorChanged();
    void sensorsErrorMessageChanged();

    // Sygnały dla wykresu
    void chartDataChanged();
    void parameterNameChanged();
    void parameterFormulaChanged();
    void minValueChanged();
    void maxValueChanged();
    void hasChartDataChanged();

    // Sygnały dla indeksu jakości powietrza
    void aqIndexDataChanged();
    void isLoadingAqIndexChanged();
    void hasAqIndexErrorChanged();
    void aqIndexErrorMessageChanged();

    void isUsingCachedDataChanged();
    void cachedDataMessageChanged();
    void allowSaveToFileChanged();

    void cacheFilesIdsChanged(QStringList cacheFilesIds);
    void cacheFileContentChanged(QString cacheFileContent);
    void cacheStatusMessageChanged(QString cacheStatusMessage);
};

#endif // MAINWINDOW_H
