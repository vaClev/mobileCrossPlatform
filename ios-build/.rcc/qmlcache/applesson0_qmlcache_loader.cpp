#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_lesson0_qml_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_HomeScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_LoginScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_ProfileEditScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_tabsContent_MainContent_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_tabsContent_Profile_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_lesson0_qml_tabsContent_NewsScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/HomeScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_HomeScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/LoginScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_LoginScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/ProfileEditScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_ProfileEditScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/tabsContent/MainContent.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_tabsContent_MainContent_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/tabsContent/Profile.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_tabsContent_Profile_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/lesson0/qml/tabsContent/NewsScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_lesson0_qml_tabsContent_NewsScreen_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_applesson0)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_applesson0))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_applesson0)() {
    return 1;
}
