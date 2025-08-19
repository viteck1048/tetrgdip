# TetrGDIP

[English version below](#english)

## Опис

Курсова робота з програмування - гра з падаючими фігурами. Реалізовано на мові C++ з використанням WinAPI та GDI+.

## Вимоги

- Операційна система Windows
- Microsoft Visual C++ Build Tools або Visual Studio Build Tools
- Windows SDK
- .NET Framework 4.0 або вище

## Збірка проекту

1. Клонуйте репозиторій:
   ```
   git clone https://github.com/viteck1048/tetrgdip.git
   cd tetrgdip
   ```
2. Встановіть необхідні інструменти:
   - Microsoft Visual C++ Build Tools
   - Windows 7.1 SDK

3. Використовуйте надані скрипти для збірки:
   - `trans.bat` - компіляція вихідного коду
   - `link.bat` - лінковка об'єктних файлів
   - `run.bat` - запуск зібраного додатку

## Керування

- ← → - переміщення фігури вліво/вправо
- ↑ - обертання фігури
- ↓ - прискорити падіння
- Пробіл - негайно опустити фігуру
- P - пауза
- H - змінити шрифт (циклічно перемикає між доступними моноширинними шрифтами)
- Ctrl+↑ - збільшити масштаб шрифту
- Ctrl+↓ - зменшити масштаб шрифту
- Esc - вихід з гри

> **Примітка:** Гра повністю сумісна з Wine (Linux) - скомпільований .exe файл чудово працює під керуванням Wine без додаткових налаштувань.

## Інтеграція з Notepad++

1. Встановіть плагін NppExec для Notepad++ (якщо ще не встановлено)
   - Відкрийте Notepad++
   - Перейдіть до `Plugins` -> `Plugins Admin`
   - Знайдіть `NppExec` у списку та встановіть

2. Додайте скрипт NppExec:
   - Натисніть `F6` або `Plugins` -> `NppExec` -> `Execute...`
   - Вставте наступний скрипт та збережіть його (кнопка `Save...`):
   ```
  NPP_CONSOLE -	//unicod
NPP_SAVE
NPP_CONSOLE +
cmd.exe /c "SET FILE_NAME="$(FILE_NAME)" && SET FILE_D=$(CURRENT_DIRECTORY) && SET FILE_N=$(NAME_PART)&&trans.bat"
NPP_CONSOLE -
if "$(EXITCODE)" == "0"
    NPP_CONSOLE +
    cmd.exe /c "SET FILE_D=$(CURRENT_DIRECTORY) && SET FILE_N=$(NAME_PART)&&link.bat"
    NPP_CONSOLE -
endif
if "$(EXITCODE)" == "0"
//  NPP_CONSOLE +
    cmd.exe /c "SET FILE_D=$(CURRENT_DIRECTORY)&& SET FILE_N=$(NAME_PART)&&run.bat"
    NPP_CONSOLE -
endif
if "$(EXITCODE)" == "0"
NPP_CONSOLE 0
endif

   ```

3. Для зручності створіть гарячу клавішу (наприклад, `F9`):
   - `Plugins` -> `NppExec` -> `Advanced Options...`
   - У полі `Associated script` виберіть ваш збережений скрипт
   - Натисніть `Add/Modify`
   - Встановіть бажану гарячу клавішу
   - Перезапустіть Notepad++

## Автор

[Viktor Diachenko](https://github.com/viteck1048)

---

# TetrGDIP

## Description

Programming coursework - a falling blocks game. Implemented in C++ using WinAPI and GDI+.

## Requirements

- Windows OS
- Microsoft Visual C++ Build Tools or Visual Studio Build Tools
- Windows SDK
- .NET Framework 4.0 or higher

## Building the Project

1. Clone the repository:
   ```
   git clone https://github.com/viteck1048/tetrgdip.git
   cd tetrgdip
   ```
2. Install required tools:
   - Microsoft Visual C++ Build Tools
   - Windows 7.1 SDK

3. Use the provided build scripts:
   - `trans.bat` - compile source code
   - `link.bat` - link object files
   - `run.bat` - run the application

## Controls

- ← → - Move piece left/right
- ↑ - Rotate piece
- ↓ - Soft drop (faster fall)
- Space - Hard drop (instant drop)
- P - Pause game
- H - Change font (cycles through available monospace fonts)
- Ctrl+↑ - Increase font scale
- Ctrl+↓ - Decrease font scale
- Esc - Exit game

> **Note:** The game is fully compatible with Wine (Linux) - the compiled .exe works perfectly under Wine without additional configuration.

## Notepad++ Integration

1. Install NppExec plugin for Notepad++ (if not already installed)
   - Open Notepad++
   - Go to `Plugins` -> `Plugins Admin`
   - Find `NppExec` in the list and install it

2. Add NppExec script:
   - Press `F6` or go to `Plugins` -> `NppExec` -> `Execute...`
   - Paste the following script and save it (click `Save...`):
   ```
 NPP_CONSOLE -	//unicod
NPP_SAVE
NPP_CONSOLE +
cmd.exe /c "SET FILE_NAME="$(FILE_NAME)" && SET FILE_D=$(CURRENT_DIRECTORY) && SET FILE_N=$(NAME_PART)&&trans.bat"
NPP_CONSOLE -
if "$(EXITCODE)" == "0"
    NPP_CONSOLE +
    cmd.exe /c "SET FILE_D=$(CURRENT_DIRECTORY) && SET FILE_N=$(NAME_PART)&&link.bat"
    NPP_CONSOLE -
endif
if "$(EXITCODE)" == "0"
//  NPP_CONSOLE +
    cmd.exe /c "SET FILE_D=$(CURRENT_DIRECTORY)&& SET FILE_N=$(NAME_PART)&&run.bat"
    NPP_CONSOLE -
endif
if "$(EXITCODE)" == "0"
NPP_CONSOLE 0
endif

   ```

3. For convenience, create a hotkey (e.g., `F9`):
   - `Plugins` -> `NppExec` -> `Advanced Options...`
   - In `Associated script` field, select your saved script
   - Click `Add/Modify`
   - Set your preferred hotkey
   - Restart Notepad++

## Author

[Viktor Diachenko](https://github.com/viteck1048)
