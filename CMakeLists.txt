cmake_minimum_required(VERSION 3.16)

project(lesson0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick Core LinguistTools Network Svg Sql)
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

#настройки для iOS
if(IOS)
    set(CMAKE_OSX_SYSROOT iphoneos)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
    set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "")
    set(CMAKE_XCODE_ATTRIBUTE_PROVISIONING_PROFILE_SPECIFIER "")
endif()

# Явно укажем идентификатор бандла для macOS
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.lesson0")
set(CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.yourcompany.lesson0")

# Главный исполняемый файл + ресурсы
qt_add_executable(applesson0
    Source/main.cpp
)

# QML-модуль
qt_add_qml_module(applesson0
    URI lesson0
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/HomeScreen.qml
        qml/LoginScreen.qml
        qml/ProfileEditScreen.qml
        qml/SettingsScreen.qml
        # контент внутри SwipeView Tab'ов главной страницы
        qml/tabsContent/MainContent.qml
        qml/tabsContent/Profile.qml
        qml/tabsContent/NewsScreen.qml
        # Компоненты для повторного использования
        qml/components/PageWithBackButton.qml
        qml/components/MainDrawer.qml
    RESOURCES
        qml/qmldir
        qml/tabsContent/qmldir
        qml/components/qmldir
    SOURCES
      Source/languagemanager.h
      Source/languagemanager.cpp
      Source/View/appcontext.h
      Source/View/appcontext.cpp
      Source/View/navigationmanager.h
      Source/View/navigationmanager.cpp
      # модели для списков
      Source/View/ListModels/newslistmodel.h
      Source/View/ListModels/newslistmodel.cpp
      # сервисы
      Source/Services/deepseekclient.h
      Source/Services/deepseekclient.cpp
      Source/Services/settingsstore.h
      Source/Services/settingsstore.cpp
      # работа с Базой данных
      Source/Database/IDatabaseManager.h
      Source/Database/Impl/DatabaseManagerQtSqlite.h
      Source/Database/Impl/DatabaseManagerQtSqlite.cpp
      SOURCES Source/Database/settingsdb.h Source/Database/settingsdb.cpp
)

#Добавление ресурсов - иконки
qt_add_resources(applesson0 "assets"
    PREFIX "/"
    FILES
        assets/icons/home.svg
        assets/icons/profile.svg
        assets/icons/news.svg
        assets/icons/menu.svg
)
# ===================================================================
# Добавление готового .qm файла в ресурсы (для всех платформ)
# ===================================================================
# Файл applesson0_ru.qm должен существовать в корне проекта НА МОМЕНТ СБОРКИ.
# Поэтому перед Android-сборкой обязательно один раз соберите проект на Windows,
# или просто положите файл вручную, если он ещё не создан.
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/applesson0_ru.qm)
    qt_add_resources(applesson0 "translations"
        PREFIX "/i18n"
        FILES applesson0_ru.qm
    )
else()
    message(WARNING "applesson0_ru.qm not found. Run a Desktop build first or generate it manually.")
endif()

# Свойства цели (для iOS/macOS/Windows)
set_target_properties(applesson0 PROPERTIES
    #QT_ANDROID_MIN_SDK_VERSION 26
    #QT_ANDROID_TARGET_SDK_VERSION 36
    #QT_ANDROID_COMPILE_SDK_VERSION "android-36"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Линковка
target_link_libraries(applesson0
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Network
    PRIVATE Qt6::Svg
    PRIVATE Qt6::Sql
)

# Для macOS – слабая линковка AGL (не особо помогает)
if(APPLE AND NOT IOS)
    target_link_options(applesson0 PRIVATE -weak_framework AGL)
endif()

include(GNUInstallDirs)
install(TARGETS applesson0
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
