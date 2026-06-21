Генерация проекта Xcode для macOS

Выполните команду из корня проекта:

```bash
cd ~/mobileCrossPlatform/lesson0
rm -rf build-mac
mkdir build-mac && cd build-mac
cmake .. -G Xcode -DCMAKE_PREFIX_PATH="/Users/ваш_пользователь/Qt/6.8.3/clang_64"
```

Особенность для устранения ошибки AGL:
Добавьте в CMakeLists.txt после блока target_link_libraries строку:

```cmake
target_link_options(applesson0 PRIVATE -weak_framework AGL)
```

Если ошибка AGL сохраняется, откройте lesson0.xcodeproj/project.pbxproj в текстовом редакторе и удалите все строки, содержащие AGL.framework.

```

----
ios
----
1. Создать папку ios-build и перейти в нее.
```
mkdir build-mac && cd build-mac
```
2.
```bash
cmake .. -G Xcode \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_SYSROOT=iphoneos \
  -DCMAKE_PREFIX_PATH="/Users/aleksandravasileva/Qt/6.8.3/ios" \
  -DQT_HOST_PATH="/Users/aleksandravasileva/Qt/6.8.3/macos" \
  -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=NEVER
```
