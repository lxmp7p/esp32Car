# ESP32 Machine Firmware

This firmware is designed for remote control of a machine via a website and includes several features.

## ToDo Checklist:
- [ ] Implement remote control via the web interface
- [ ] Add functionality to enable/disable internal network
- [ ] Implement pre-programmed driving capability

## Installation and Setup:
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/esp32-project.git
   ```
2. Create a file `src/creds.h` and set up Wi-Fi connection parameters.
   ```cpp
   const char* WIFI_SSID     = "************";
   const char* WIFI_PASSWORD = "************";
   ```
3. Upload the firmware to ESP32 using PlatformIO or Arduino IDE.

# Прошивка для машины ESP32

Эта прошивка предназначена для управления машинкой через сайт и включает в себя несколько функций.

## ToDo чеклист:
- [ ] Реализовать управление через пульт
- [ ] Добавить функцию включения/выключения внутренней сети
- [ ] Реализовать возможность езды по предпрограмме

## Установка и настройка:
1. Склонируйте репозиторий:
   ```bash
   git clone https://github.com/yourusername/esp32-project.git
   ```
3. Создайте файл `src/creds.h` и настройте параметры подключения к Wi-Fi.
    const char* WIFI_SSID     = "************";
    const char* WIFI_PASSWORD = "************";
4. Загрузите прошивку на ESP32 с помощью PlatformIO или Arduino IDE.
