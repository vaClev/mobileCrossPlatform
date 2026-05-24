cmake_minimum_required(VERSION 3.16)

project(lesson0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia Core)
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

# Явно укажем идентификатор бандла для macOS
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.lesson0")
set(CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.yourcompany.lesson0")

# Главный исполняемый файл
qt_add_executable(applesson0
    Source/main.cpp
    translations.qrc
)


# QML-модуль с перечислением всех файлов
qt_add_qml_module(applesson0
    URI lesson0
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/LoginScreen.qml
        qml/HomeScreen.qml
        qml/ProfileEditScreen.qml
        qml/tabsContent/MainContent.qml
        qml/tabsContent/Profile.qml
        qml/tabsContent/NewsScreen.qml
    RESOURCES
        qml/qmldir
	    qml/tabsContent/qmldir
    SOURCES
        Source/languagemanager.h
        Source/languagemanager.cpp
        Source/View/appcontext.h
        Source/View/appcontext.cpp
        Source/View/navigationmanager.h
        Source/View/navigationmanager.cpp
)

# Свойства цели
set_target_properties(applesson0 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Линковка
target_link_libraries(applesson0
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Multimedia
    PRIVATE Qt6::Core
)

# Исправление ошибки AGL на macOS
target_link_options(applesson0 PRIVATE -weak_framework AGL)

include(GNUInstallDirs)
install(TARGETS applesson0
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
