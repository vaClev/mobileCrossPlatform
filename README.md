# lesson0

Первое кроссплатформенное приложение на Qt Quick с камерой.

## Сборка

### Android (Windows)
*Qt установлен локально через Online installer. 
*qt/6.8.3 MINGW 64bit  + Android
*дополнительно установлен Android NDK 26.1.10909125
*развернут эмулятор Android Pixel_7a API 36.1
```
Открыть проект в Qt Creator → выбрать Android-кит → Собрать
```

### iOS (macOS)
```bash
# Установка зависимостей (только первый раз)
brew install cmake conan

# Клонирование репозитория
git clone https://github.com/vaClev/mobileCrossPlatform.git
cd lesson0

# Сборка через Conan
conan install . -pr:h profiles/ios -pr:b default --build=missing -of build/ios
cd build/ios
cmake --preset conan-release
cmake --build --preset conan-release