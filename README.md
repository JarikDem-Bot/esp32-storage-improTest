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

2. Set up Arduino IDE for work with ESP boards. [More info here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

3. Open `esp32-storage.ino` in `esp32-storage/` folder

4. Select `ESP32 Wrover Module` board
 <img src="https://github.com/JarikDem-Bot/esp32-storage-improTest/assets/73791422/2aaa9429-f0a9-4b6f-bb54-6d7ba475cd0a" width="40%">

5. Install required libraries if they aren't installed already

6. Select board port and upload program

7. Enjoy

## Showcase

### Web Interface

- Upload file
- View files
- Download files
- Delete files
- Looks urprisingly good on phones

### Telegram Bot

- Access only to scpecified users
- View files
- Download file by name
- Delete file by name
- Upload file by sending to the chat
- Get link to the Web Interface
- Help message

### OTA

- Automatic firmware update
- Binary file stored on GitHub
- Compares version with current
- Checks for update every 30 minutes

ToDo:
- describe ssid, password, url, allowedUsers and sertificate
- Add tags and/or image?
- How to connect micro SD module 
