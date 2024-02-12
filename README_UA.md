<p align="center"><img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/ac07a276-8e76-4b7d-922b-1c6ccc658aaa"  width="40%"></p>
<h1 align="center">ESP32 Storage</h1>

Файлове сховище з Веб інтерфейсом та телеграм ботом для завантаження/збереження/видалення файлів. Основане на  ESP32 з під'єднанною мікро SD карткою.

[README in English](https://github.com/JarikDem-Bot/esp32-storage-improTest/blob/master/README.md)

## Features

- 🌐 Веб інтерфейс
  - Профстий внтерфейс
  - Завантаження файлів
  - Перегляд файлів на картці
  - Переевірка зайнятого та загального місця на картці
  - Автоматичне оновлення списку кожні 30 секунд та після кожної дії 
  - Скачування та видалення файлів

- 🤖 Telegram бот
  - Безпечний - тільки зазначені в програмі користувачі можуть використовувати бота
  - Отримання посилання на веб інтерфейс
  - Перегляд файлів на картці
  - Переевірка зайнятого та загального місця на картці
  - Видалення/скачення будь-якого файлу за ім'ям
  - Завантаження файлів при надчиланні його в чат з ботом

- 🛜 Оновлення "по повітрю"
  - Автоматичне оновлення програми через інтернет
  - Бінарний файл з програмою зберігається в GitHub репозиорії
  - Завантажує тільки нові версії
  - Перевірка наявності оновлення кожні 30 хвилин

## Інсталяція

1. Клонуйте репозиторій за допомогою команди `git clone https://github.com/JarikDem-Bot/esp32-storage-improTest.git`

2. Під'єднайте [адаптер мікро SD картки](https://arduino.ua/ru/prod1601-modyl-micro-sdtf-card) до ESP32:

| Micro Sd Adapter  | ESP32 |
| ------------- | ------------- |
| CS  | D5  |
| SCK | D18  |
| MOSI  | D23  |
| MISO  | D19  |
| VCC  | VIN  |
| GND  | GND  |

3. Налаштуйте Arduino IDE для роботи з плаьтами ESP. [Більше інформації тут](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

4. Відкрийте файл `esp32-storage.ino` в теці `esp32-storage/`

5. Оберіть плату `ESP32 Wrover Module`
 <img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/7c173446-3014-4dc0-afc5-7f885d02aefb" width="40%">

6. За необхідності, встановіть відсутні бібліотеки

- [WiFi.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [WiFiClient.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [WebServer.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
- [SPI.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/SPI)
- [SD.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD)
- [FastBot.h](https://github.com/GyverLibs/FastBot)
- [HttpsOTAUpdate.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Update)
- [Preferences.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences)
- [Ticker.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker)

7. Відкрийте password.h та за необхідністю змініть наступні значення: 
- BOT_TOKEN - токен телеграм боту
- allowedUsers - список userID користувачів телеграму, які можуть писати боту
- otaUrl - посилання до [бінарного файлу](https://randomnerdtutorials.com/bin-binary-files-sketch-arduino-ide/) на Вашому GitHub репозиторії у форматі `https://raw.githubusercontent.com/username/repoName/branch/pathToFile/filename.bin`
- [server_certificate](https://github.com/RadialDevGroup/esp32-ota-https-example/blob/master/README.md#step-3-create-the-server-certificates-file) - сертификат

8. Оберіть COM порт та завантажте програму

9. Якщо плата не зможе під'єднатися до WiFi, то вона створить точку роздачі без паролю з назвою "ESP32 Storage". Обравши її, Ви будете перенаправлені до веб сторінки, де можна налаштувати дані WiFi.

10. Насолоджуйтесь пристроєм:)

## Демонстрація

### Веб інтерфейс

- Завантаження файлів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/613f0d76-e58f-4ca9-940b-2c8a7b7fb2ab" width="40%">

- Перегляд файлів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/03587921-da02-442b-94d8-39e37c8a4048" width="40%">

- Скачування файлів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/f5fac00e-d1eb-479c-91de-824a66b28439" width="40%">

- Видалення файлів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/546975d0-e268-4836-a328-ef0fcbdd048e" width="40%">

- Непогано виглядає і на телефоні
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/c182ea27-d5cf-4803-8012-12874f8a30e0" width="40%">


### Telegram Бот

- Доступ надається тільки для зазначених користувачів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/41e12d1d-a4c8-484f-ae87-db1e12016012" width="40%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/b4c9ef96-e3e8-4300-a5b5-98d65b7a996b" width="40%">

- Перегляд файлів
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/9d6dfec7-b184-4f72-8cd3-6fdb3a24313e" width="40%">

- Скачування файлу за ім'ям
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/f8a2b525-d607-4c3d-969b-92d0d8201807" width="40%">

- Видалення файлу за ім'ям
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/4e6172ab-b54a-437d-a339-1236d6c668e9" width="40%">

- Завантаження файлу при надсиланні його у чат
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/669a5ffe-1691-4d91-a685-04fcab5bdd8f" width="40%">

- Отримання посилання на веб інтерфейс
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/0c55aeb6-586e-48dd-8887-a99a635b23fe" width="40%">

- Команда з допоміжною інформацією
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/1a1a6160-0aaf-4dd0-9c6c-35e4fb061f67" width="40%">

### Налаштування WiFi через точку доступу

- Якщо плата не може під'єднатися до попереднього WiFi, вона створить точку доступу
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/ac84980b-403f-4b0c-8a42-fcb01289edf4" width="30%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/84340d9c-44ae-4b8e-b102-7c90a8657ce8" width="30%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/bb2824b0-3f3b-4cb1-a48e-cc4a1c7c1861" width="30%">



### Прошивка "по повітрю"

- Автоматичне оновлення прошивки
- Бінарний файл на GitHub репозиторії
- Порівнює версію з поточною
- Перевіряє наявність оновлення кожні 30 хвилин

## TODO
- [ ] Зберігати список допущенних користувачів на SD картці
- [ ] Додавання тек на SD картці
- [ ] Вхід з паролем на веб інтерфейс
