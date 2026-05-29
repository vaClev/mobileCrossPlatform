## Установка Qt 6.8.3 на macOS через aqtinstall

1. Создайте и активируйте виртуальное окружение Python:
   ```bash
   python3 -m venv ~/venv_aqt
   source ~/venv_aqt/bin/activate
```

1. Установите aqtinstall:
   ```bash
   pip install aqtinstall
   ```
2. Установите десктопную версию Qt (хост-инструменты):
   ```bash
   aqt install-qt mac desktop 6.8.3 clang_64 --outputdir ~/Qt/6.8.3
   ```
3. Установите iOS-версию Qt (опционально):
   ```bash
   aqt install-qt mac ios 6.8.3 ios_arm64 --outputdir ~/Qt/6.8.3
   ```
4. После завершения деактивируйте окружение:
   ```bash
   deactivate
   ```