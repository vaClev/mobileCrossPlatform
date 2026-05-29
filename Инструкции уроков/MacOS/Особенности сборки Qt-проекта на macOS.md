## Особенности сборки Qt-проекта на macOS

### 1. Критически важная политика Qt

Без указания политики `QTP0001` QML-модули могут не загружаться, и `loadFromModule` будет выдавать ошибку `module contains no type named Main`.

**Решение:** добавьте в `CMakeLists.txt` сразу после `find_package(Qt6 ...)`:

```cmake
qt_policy(SET QTP0001 NEW)
```

Также может потребоваться политика QTP0004 для вложенных папок с QML-файлами:

```cmake
qt_policy(SET QTP0004 NEW)
```

---

2. Файлы qmldir для вложенных папок

Если QML-файлы лежат в подпапках (например, tabsContent/), необходимо создать файлы qmldir и подключить их в CMakeLists.txt.

Структура проекта:

```
qml/
├── Main.qml
├── HomeScreen.qml
├── qmldir
└── tabsContent/
    ├── MainContent.qml
    ├── Profile.qml
    ├── NewsScreen.qml
    └── qmldir
```

Содержимое qml/qmldir:

```
module lesson0
Main 1.0 Main.qml
LoginScreen 1.0 LoginScreen.qml
HomeScreen 1.0 HomeScreen.qml
ProfileEditScreen 1.0 ProfileEditScreen.qml
```

Содержимое qml/tabsContent/qmldir:

```
module lesson0.tabsContent
MainContent 1.0 MainContent.qml
Profile 1.0 Profile.qml
NewsScreen 1.0 NewsScreen.qml
```

В CMakeLists.txt файлы qmldir добавляются в RESOURCES:

```cmake
qt_add_qml_module(applesson0
    URI lesson0
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/HomeScreen.qml
        ...
    RESOURCES
        qml/qmldir
        qml/tabsContent/qmldir
    ...
)
```

---

3. Импорт модуля в QML-файлах

Чтобы ссылаться на типы из своего модуля, нужно явно импортировать модуль в каждом QML-файле, который использует другие QML-типы:

```qml
import QtQuick
import QtQuick.Controls
import lesson0  // ← обязательно!
```