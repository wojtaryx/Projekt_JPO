/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "responseDataChanged",
        "",
        "isLoadingChanged",
        "hasErrorChanged",
        "errorMessageChanged",
        "stationsDataChanged",
        "isLoadingStationsChanged",
        "hasStationsErrorChanged",
        "stationsErrorMessageChanged",
        "sensorsDataChanged",
        "isLoadingSensorsChanged",
        "hasSensorsErrorChanged",
        "sensorsErrorMessageChanged",
        "chartDataChanged",
        "parameterNameChanged",
        "parameterFormulaChanged",
        "minValueChanged",
        "maxValueChanged",
        "hasChartDataChanged",
        "aqIndexDataChanged",
        "isLoadingAqIndexChanged",
        "hasAqIndexErrorChanged",
        "aqIndexErrorMessageChanged",
        "isUsingCachedDataChanged",
        "cachedDataMessageChanged",
        "allowSaveToFileChanged",
        "cacheFilesIdsChanged",
        "cacheFilesIds",
        "cacheFileContentChanged",
        "cacheFileContent",
        "cacheStatusMessageChanged",
        "cacheStatusMessage",
        "fetchData",
        "sensorId",
        "fetchStations",
        "cityName",
        "fetchStationSensors",
        "stationId",
        "fetchAqIndex",
        "isNetworkAvailable",
        "loadStationsFromCache",
        "loadSensorsFromCache",
        "loadSensorDataFromCache",
        "loadAqIndexFromCache",
        "loadCacheFilesList",
        "dataTypeIndex",
        "loadCacheFileContent",
        "fileId",
        "responseData",
        "isLoading",
        "hasError",
        "errorMessage",
        "stationsData",
        "isLoadingStations",
        "hasStationsError",
        "stationsErrorMessage",
        "sensorsData",
        "isLoadingSensors",
        "hasSensorsError",
        "sensorsErrorMessage",
        "chartData",
        "QVariantList",
        "parameterName",
        "parameterFormula",
        "minValue",
        "maxValue",
        "hasChartData",
        "aqIndexData",
        "isLoadingAqIndex",
        "hasAqIndexError",
        "aqIndexErrorMessage",
        "isUsingCachedData",
        "cachedDataMessage",
        "allowSaveToFile"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'responseDataChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isLoadingChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasErrorChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorMessageChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stationsDataChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isLoadingStationsChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasStationsErrorChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stationsErrorMessageChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sensorsDataChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isLoadingSensorsChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasSensorsErrorChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sensorsErrorMessageChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartDataChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'parameterNameChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'parameterFormulaChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'minValueChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxValueChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasChartDataChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'aqIndexDataChanged'
        QtMocHelpers::SignalData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isLoadingAqIndexChanged'
        QtMocHelpers::SignalData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasAqIndexErrorChanged'
        QtMocHelpers::SignalData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'aqIndexErrorMessageChanged'
        QtMocHelpers::SignalData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isUsingCachedDataChanged'
        QtMocHelpers::SignalData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cachedDataMessageChanged'
        QtMocHelpers::SignalData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'allowSaveToFileChanged'
        QtMocHelpers::SignalData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cacheFilesIdsChanged'
        QtMocHelpers::SignalData<void(QStringList)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 28 },
        }}),
        // Signal 'cacheFileContentChanged'
        QtMocHelpers::SignalData<void(QString)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 30 },
        }}),
        // Signal 'cacheStatusMessageChanged'
        QtMocHelpers::SignalData<void(QString)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 32 },
        }}),
        // Slot 'fetchData'
        QtMocHelpers::SlotData<void(const QString &)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'fetchStations'
        QtMocHelpers::SlotData<void(const QString &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Slot 'fetchStationSensors'
        QtMocHelpers::SlotData<void(const QString &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Slot 'fetchAqIndex'
        QtMocHelpers::SlotData<void(const QString &)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Method 'isNetworkAvailable'
        QtMocHelpers::MethodData<bool() const>(40, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'loadStationsFromCache'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadSensorsFromCache'
        QtMocHelpers::MethodData<void(const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Method 'loadSensorDataFromCache'
        QtMocHelpers::MethodData<void(const QString &)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Method 'loadAqIndexFromCache'
        QtMocHelpers::MethodData<void(const QString &)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Method 'loadCacheFilesList'
        QtMocHelpers::MethodData<void(int)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 46 },
        }}),
        // Method 'loadCacheFileContent'
        QtMocHelpers::MethodData<void(int, const QString &)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 46 }, { QMetaType::QString, 48 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'responseData'
        QtMocHelpers::PropertyData<QString>(49, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'isLoading'
        QtMocHelpers::PropertyData<bool>(50, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'hasError'
        QtMocHelpers::PropertyData<bool>(51, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'errorMessage'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'stationsData'
        QtMocHelpers::PropertyData<QString>(53, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'isLoadingStations'
        QtMocHelpers::PropertyData<bool>(54, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'hasStationsError'
        QtMocHelpers::PropertyData<bool>(55, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'stationsErrorMessage'
        QtMocHelpers::PropertyData<QString>(56, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'sensorsData'
        QtMocHelpers::PropertyData<QString>(57, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'isLoadingSensors'
        QtMocHelpers::PropertyData<bool>(58, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'hasSensorsError'
        QtMocHelpers::PropertyData<bool>(59, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'sensorsErrorMessage'
        QtMocHelpers::PropertyData<QString>(60, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'chartData'
        QtMocHelpers::PropertyData<QVariantList>(61, 0x80000000 | 62, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 12),
        // property 'parameterName'
        QtMocHelpers::PropertyData<QString>(63, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'parameterFormula'
        QtMocHelpers::PropertyData<QString>(64, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'minValue'
        QtMocHelpers::PropertyData<double>(65, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'maxValue'
        QtMocHelpers::PropertyData<double>(66, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'hasChartData'
        QtMocHelpers::PropertyData<bool>(67, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'aqIndexData'
        QtMocHelpers::PropertyData<QString>(68, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'isLoadingAqIndex'
        QtMocHelpers::PropertyData<bool>(69, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 19),
        // property 'hasAqIndexError'
        QtMocHelpers::PropertyData<bool>(70, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 20),
        // property 'aqIndexErrorMessage'
        QtMocHelpers::PropertyData<QString>(71, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 21),
        // property 'isUsingCachedData'
        QtMocHelpers::PropertyData<bool>(72, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 22),
        // property 'cachedDataMessage'
        QtMocHelpers::PropertyData<QString>(73, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 23),
        // property 'allowSaveToFile'
        QtMocHelpers::PropertyData<bool>(74, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 24),
        // property 'cacheFilesIds'
        QtMocHelpers::PropertyData<QStringList>(28, QMetaType::QStringList, QMC::DefaultPropertyFlags, 25),
        // property 'cacheFileContent'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags, 26),
        // property 'cacheStatusMessage'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags, 27),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->responseDataChanged(); break;
        case 1: _t->isLoadingChanged(); break;
        case 2: _t->hasErrorChanged(); break;
        case 3: _t->errorMessageChanged(); break;
        case 4: _t->stationsDataChanged(); break;
        case 5: _t->isLoadingStationsChanged(); break;
        case 6: _t->hasStationsErrorChanged(); break;
        case 7: _t->stationsErrorMessageChanged(); break;
        case 8: _t->sensorsDataChanged(); break;
        case 9: _t->isLoadingSensorsChanged(); break;
        case 10: _t->hasSensorsErrorChanged(); break;
        case 11: _t->sensorsErrorMessageChanged(); break;
        case 12: _t->chartDataChanged(); break;
        case 13: _t->parameterNameChanged(); break;
        case 14: _t->parameterFormulaChanged(); break;
        case 15: _t->minValueChanged(); break;
        case 16: _t->maxValueChanged(); break;
        case 17: _t->hasChartDataChanged(); break;
        case 18: _t->aqIndexDataChanged(); break;
        case 19: _t->isLoadingAqIndexChanged(); break;
        case 20: _t->hasAqIndexErrorChanged(); break;
        case 21: _t->aqIndexErrorMessageChanged(); break;
        case 22: _t->isUsingCachedDataChanged(); break;
        case 23: _t->cachedDataMessageChanged(); break;
        case 24: _t->allowSaveToFileChanged(); break;
        case 25: _t->cacheFilesIdsChanged((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 26: _t->cacheFileContentChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->cacheStatusMessageChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 28: _t->fetchData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 29: _t->fetchStations((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 30: _t->fetchStationSensors((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 31: _t->fetchAqIndex((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 32: { bool _r = _t->isNetworkAvailable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->loadStationsFromCache(); break;
        case 34: _t->loadSensorsFromCache((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 35: _t->loadSensorDataFromCache((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 36: _t->loadAqIndexFromCache((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 37: _t->loadCacheFilesList((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 38: _t->loadCacheFileContent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::responseDataChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::isLoadingChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::hasErrorChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::errorMessageChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::stationsDataChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::isLoadingStationsChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::hasStationsErrorChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::stationsErrorMessageChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::sensorsDataChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::isLoadingSensorsChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::hasSensorsErrorChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::sensorsErrorMessageChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::chartDataChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::parameterNameChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::parameterFormulaChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::minValueChanged, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::maxValueChanged, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::hasChartDataChanged, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::aqIndexDataChanged, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::isLoadingAqIndexChanged, 19))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::hasAqIndexErrorChanged, 20))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::aqIndexErrorMessageChanged, 21))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::isUsingCachedDataChanged, 22))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::cachedDataMessageChanged, 23))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::allowSaveToFileChanged, 24))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QStringList )>(_a, &MainWindow::cacheFilesIdsChanged, 25))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QString )>(_a, &MainWindow::cacheFileContentChanged, 26))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QString )>(_a, &MainWindow::cacheStatusMessageChanged, 27))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->responseData(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isLoading(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->hasError(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->errorMessage(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->stationsData(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->isLoadingStations(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->hasStationsError(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->stationsErrorMessage(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->sensorsData(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->isLoadingSensors(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->hasSensorsError(); break;
        case 11: *reinterpret_cast<QString*>(_v) = _t->sensorsErrorMessage(); break;
        case 12: *reinterpret_cast<QVariantList*>(_v) = _t->chartData(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->parameterName(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->parameterFormula(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->minValue(); break;
        case 16: *reinterpret_cast<double*>(_v) = _t->maxValue(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->hasChartData(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->aqIndexData(); break;
        case 19: *reinterpret_cast<bool*>(_v) = _t->isLoadingAqIndex(); break;
        case 20: *reinterpret_cast<bool*>(_v) = _t->hasAqIndexError(); break;
        case 21: *reinterpret_cast<QString*>(_v) = _t->aqIndexErrorMessage(); break;
        case 22: *reinterpret_cast<bool*>(_v) = _t->isUsingCachedData(); break;
        case 23: *reinterpret_cast<QString*>(_v) = _t->cachedDataMessage(); break;
        case 24: *reinterpret_cast<bool*>(_v) = _t->allowSaveToFile(); break;
        case 25: *reinterpret_cast<QStringList*>(_v) = _t->cacheFilesIds(); break;
        case 26: *reinterpret_cast<QString*>(_v) = _t->cacheFileContent(); break;
        case 27: *reinterpret_cast<QString*>(_v) = _t->cacheStatusMessage(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setResponseData(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setIsLoading(*reinterpret_cast<bool*>(_v)); break;
        case 2: _t->setHasError(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setErrorMessage(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setStationsData(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setIsLoadingStations(*reinterpret_cast<bool*>(_v)); break;
        case 6: _t->setHasStationsError(*reinterpret_cast<bool*>(_v)); break;
        case 7: _t->setStationsErrorMessage(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setSensorsData(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setIsLoadingSensors(*reinterpret_cast<bool*>(_v)); break;
        case 10: _t->setHasSensorsError(*reinterpret_cast<bool*>(_v)); break;
        case 11: _t->setSensorsErrorMessage(*reinterpret_cast<QString*>(_v)); break;
        case 12: _t->setChartData(*reinterpret_cast<QVariantList*>(_v)); break;
        case 13: _t->setParameterName(*reinterpret_cast<QString*>(_v)); break;
        case 14: _t->setParameterFormula(*reinterpret_cast<QString*>(_v)); break;
        case 15: _t->setMinValue(*reinterpret_cast<double*>(_v)); break;
        case 16: _t->setMaxValue(*reinterpret_cast<double*>(_v)); break;
        case 17: _t->setHasChartData(*reinterpret_cast<bool*>(_v)); break;
        case 18: _t->setAqIndexData(*reinterpret_cast<QString*>(_v)); break;
        case 19: _t->setIsLoadingAqIndex(*reinterpret_cast<bool*>(_v)); break;
        case 20: _t->setHasAqIndexError(*reinterpret_cast<bool*>(_v)); break;
        case 21: _t->setAqIndexErrorMessage(*reinterpret_cast<QString*>(_v)); break;
        case 22: _t->setIsUsingCachedData(*reinterpret_cast<bool*>(_v)); break;
        case 23: _t->setCachedDataMessage(*reinterpret_cast<QString*>(_v)); break;
        case 24: _t->setAllowSaveToFile(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 39;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::responseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::isLoadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::hasErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::errorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::stationsDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::isLoadingStationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::hasStationsErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::stationsErrorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::sensorsDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MainWindow::isLoadingSensorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MainWindow::hasSensorsErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MainWindow::sensorsErrorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MainWindow::chartDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void MainWindow::parameterNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MainWindow::parameterFormulaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void MainWindow::minValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void MainWindow::maxValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void MainWindow::hasChartDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void MainWindow::aqIndexDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void MainWindow::isLoadingAqIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void MainWindow::hasAqIndexErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void MainWindow::aqIndexErrorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void MainWindow::isUsingCachedDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void MainWindow::cachedDataMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void MainWindow::allowSaveToFileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void MainWindow::cacheFilesIdsChanged(QStringList _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 25, nullptr, _t1);
}

// SIGNAL 26
void MainWindow::cacheFileContentChanged(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 26, nullptr, _t1);
}

// SIGNAL 27
void MainWindow::cacheStatusMessageChanged(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 27, nullptr, _t1);
}
QT_WARNING_POP
