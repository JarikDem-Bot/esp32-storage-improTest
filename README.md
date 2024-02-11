<p align="center"><img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/ac07a276-8e76-4b7d-922b-1c6ccc658aaa"  width="40%"></p>
<h1 align="center">ESP32 Storage</h1>

File storage with WEB Interface and telegram bot to upload/download/delete files. Based on ESP32 with connected micro SD card.

## Features

- 🌐 Web Interface
  - Simple interface
  - Upload files
  - View list of stored files
  - Check used and total SD card space
  - List auto-update every 30 seconds and after every action
  - Download or delete files

- 🤖 Telegram Bot
  - Secure - only users specified in program are able to use bot
  - Get link to the Web Interface
  - Get list of all stored files
  - Check used and total SD card space
  - Delete/download any file by name
  - Upload any file just by sending it to the chat

- 🛜 Over The Air updates
  - Automaticaly updates firmware through the Internet
  - Binary file with firmware stored on GitHub repository
  - Uploads only newer version
  - Checks for updates every 30 minutes

## Installation

1. Clone this repository using `git clone https://github.com/JarikDem-Bot/esp32-storage-improTest.git`

2. Connect micro SD card adapter to ESP32:

| Micro Sd Adapter  | ESP32 |
| ------------- | ------------- |
| CS  | D5  |
| SCK | D18  |
| MOSI  | D23  |
| MISO  | D19  |
| VCC  | VIN  |
| GND  | GND  |

3. Set up Arduino IDE for work with ESP boards. [More info here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

4. Open `esp32-storage.ino` in `esp32-storage/` folder

5. Select `ESP32 Wrover Module` board
 <img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/7c173446-3014-4dc0-afc5-7f885d02aefb" width="40%">

6. Install required libraries if they aren't installed already

- [WiFi.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [WiFiClient.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [WebServer.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
- [SPI.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/SPI)
- [SD.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD)
- [FastBot.h](https://github.com/GyverLibs/FastBot)
- [HttpsOTAUpdate.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Update)
- [Preferences.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences)
- [Ticker.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker)

7. Open password.h and change values if needed: 
- BOT_TOKEN - token of your telegram bot
- allowedUsers - array of telegram userIDs of users allowed to use your bot
- otaUrl - link to [binary file](https://randomnerdtutorials.com/bin-binary-files-sketch-arduino-ide/) on your GitHub repository in format `https://raw.githubusercontent.com/username/repoName/branch/pathToFile/filename.bin`
- [server_certificate](https://github.com/RadialDevGroup/esp32-ota-https-example/blob/master/README.md#step-3-create-the-server-certificates-file) - certificate

8. Select board and upload program

9. If board will be unable to connect to WiFi, it will create Access Point named "ESP32 Storage". By clicking on it, you will be redirected to the web page, where you can select WiFi credential.

10. Enjoy:)

## Showcase

### Web Interface

- Upload file
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/613f0d76-e58f-4ca9-940b-2c8a7b7fb2ab" width="40%">

- View files
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/03587921-da02-442b-94d8-39e37c8a4048" width="40%">

- Download files
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/f5fac00e-d1eb-479c-91de-824a66b28439" width="40%">

- Delete files
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/546975d0-e268-4836-a328-ef0fcbdd048e" width="40%">

- Looks surprisingly good on phones
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/c182ea27-d5cf-4803-8012-12874f8a30e0" width="40%">


### Telegram Bot

- Access granted only for scpecified users
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/41e12d1d-a4c8-484f-ae87-db1e12016012" width="40%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/b4c9ef96-e3e8-4300-a5b5-98d65b7a996b" width="40%">

- View files
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/9d6dfec7-b184-4f72-8cd3-6fdb3a24313e" width="40%">

- Download file by name
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/f8a2b525-d607-4c3d-969b-92d0d8201807" width="40%">

- Delete file by name
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/4e6172ab-b54a-437d-a339-1236d6c668e9" width="40%">

- Upload file by sending to the chat
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/669a5ffe-1691-4d91-a685-04fcab5bdd8f" width="40%">

- Get link to the Web Interface
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/0c55aeb6-586e-48dd-8887-a99a635b23fe" width="40%">

- Help message
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/1a1a6160-0aaf-4dd0-9c6c-35e4fb061f67" width="40%">

### WiFi setup through AP

- If board is unable to connect to previous WiFi, it will start AP
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/ac84980b-403f-4b0c-8a42-fcb01289edf4" width="30%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/84340d9c-44ae-4b8e-b102-7c90a8657ce8" width="30%">
<img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/bb2824b0-3f3b-4cb1-a48e-cc4a1c7c1861" width="30%">



### OTA

- Automatic firmware update
- Binary file stored on GitHub
- Compares version with current
- Checks for update every 30 minutes

## TODO
- [ ] Get allowed users list for TG Bot from file on SD card
- [ ] Add folders on the SD
- [ ] Web Interface authentification
