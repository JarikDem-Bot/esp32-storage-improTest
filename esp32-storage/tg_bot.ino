void tg_init() {
  bot.skipUpdates();
  bot.attach(new_message);
  bot.setTextMode(FB_MARKDOWN);
}

void new_message(FB_msg& msg) {
  bot.sendTyping(msg.chatID);
  String replyMsg = "";

  if (!user_id_in_list(msg.userID)) {
    replyMsg += bot_denied(msg);
  } else if (msg.text == "/help") {
    replyMsg = bot_help(msg);
  } else if(msg.text == "/web") {
     replyMsg = bot_web(msg);
  } else if (msg.text == "/list") {
    replyMsg = bot_list(msg);
  } else if (msg.text.startsWith("/delete ")) {
    replyMsg = bot_delete(msg);
  } else if (msg.text.startsWith("/download ")) {
    replyMsg = bot_download(msg);
  } else if (msg.isFile) {
    replyMsg = bot_upload(msg);
  } else {
    replyMsg = bot_unknown(msg);
  }

  replyMsg = msg_clear(replyMsg);
  bot.replyMessage(replyMsg, msg.messageID, msg.chatID);
}

bool user_id_in_list(String userId) {
  bool result = false;
  for(int i = 0; i < sizeof(allowedUsers) / sizeof(allowedUsers[0]); i++) {
    if (userId == allowedUsers[i]) {
      result = true;
    }
  }
  return result;
}

String bot_denied(FB_msg msg) {
  String replyMsg = "";

  replyMsg += "*--ACCESS DENIED--*\n\n";
  replyMsg += "Only users from the list are allowed to use this bot.\n";
  replyMsg += "To add this user, you need to add this userID to the `allowedUsers` array in `password.h` and update firmware.\n";
  replyMsg += "Your user ID: `";
  replyMsg += msg.userID;
  replyMsg += "`";

  return replyMsg;
}

String bot_help(FB_msg msg) {
  String replyMsg;
  replyMsg += "This is data storage based on ESP32 with micro SD card.\n";
  replyMsg += "\n__*General commands:*__\n";
  replyMsg += "Use command /list to get the list of all files stored on SD card.\n";
  replyMsg += "Use command /web to access web interface\n";
  replyMsg += "Use command /help to get this message.\n";
  replyMsg += "\n__*Commands with files:*__\n";
  replyMsg += "To run this command, you'll need to send comand and name of taget file after one space.";
  replyMsg += "If you click on the file name in response message to /list command, it will be copied to your clipboard.\n";
  replyMsg += "Use command `/delete text.txt` to delete file named text.txt\n";
  replyMsg += "Use command `/download text.txt` to upload file text.txt from SD card to this chat\n";
  replyMsg += "Just send any file to download it on SD card.\n";
  replyMsg += "\nMore info you can find in this [GitHub repository](https://github.com/JarikDem-Bot/esp32-storage-improTest).";

  return replyMsg;
}

String bot_web(FB_msg msg) {
  String replyMsg = "";

  replyMsg += "IP address: [";
  replyMsg += WiFi.localIP().toString();
  replyMsg += "](http://";
  replyMsg += WiFi.localIP().toString();
  replyMsg += ")\n\n";
  replyMsg += "Open this address in your browser to access WEB Interface.\n";
  replyMsg += "*NOTE:* you must be connected to the same network as ESP32 in order to access web interface";

  return replyMsg;
}

String bot_list(FB_msg msg) {
  String replyMsg = "";
  replyMsg = get_directories_msg(SD.open("/"));
  return replyMsg;
}

String bot_delete(FB_msg msg) {
  String replyMsg = "";
  String filename = msg.text.substring(String("/delete ").length());

  if (!filename.startsWith("/")) filename = "/" + filename;

  if (!SD.exists(filename)) {
    replyMsg += "File `";
    replyMsg += filename.substring(1);
    replyMsg += "` does not exist. Please, check file name once again";
  } else if (SD.remove(filename)) {
    replyMsg = "File `";
    replyMsg += filename.substring(1);
    replyMsg += "` deleted succussfuly!";
  } else {
    replyMsg += "Unable to delete file `";
    replyMsg += filename.substring(1);
    replyMsg += "`";
  }
  return replyMsg;
}

String bot_download(FB_msg msg) {
  String replyMsg = "";
  String filename = msg.text.substring(String("/download ").length());

  if (!filename.startsWith("/")) filename = "/" + filename;

  if (!SD.exists(filename)) {
    replyMsg += "File `";
    replyMsg += filename.substring(1);
    replyMsg += "` does not exist. Please, check file name once again";
  } else {
    File file = SD.open(filename, "r");
    bot.sendFile(file, FB_DOC, filename.substring(1), msg.chatID);
    file.close();
    replyMsg += "File `";
    replyMsg += filename.substring(1);
    replyMsg += "` downloaded successfuly!";
  }
  return replyMsg;
}

String bot_upload(FB_msg msg) {
  String replyMsg = "";

  String filename = msg.fileName;
  if (!filename.startsWith("/")) filename = "/" + filename;
  SD.remove(filename);
  
  bool uploadStatus = false;
  File file = SD.open(filename, FILE_WRITE);
  if (file) {
    HTTPClient http;
    http.begin(msg.fileUrl);
    if (http.GET() == HTTP_CODE_OK) {
      if (http.writeToStream(&file) > 0) uploadStatus = true;
    }
    http.end();
    file.close();
  }

  replyMsg += "File `";
  replyMsg += filename.substring(1);
  if (uploadStatus) {
    replyMsg += "` uploaded successfuly!";
  } else {
    replyMsg += "` haven't been uploaded";
  }

  return replyMsg;
}

String bot_unknown(FB_msg msg) {
  String replyMsg = "";

  replyMsg += "This command is unknown to me. Please, check:\n";
  replyMsg += "-spelling of the command\n";
  replyMsg += "-file name must be one space after command itself in the same message\n";
  replyMsg += "\nYou can use /help command to get list of all available commands.";

  return replyMsg;
}

String msg_clear(String message) { //Fast bot doesn't send message if it contsins "!" or "#"
  while (message.indexOf("!") != -1) {
    message.replace("!", ".");
  }
  while (message.indexOf("#") != -1) {
    message.replace("#", ".");
  }
  return message;
}

String return_file_size(uint64_t bytes) {
  String result = "";
  float value;
  if (bytes >= 1073741824) {
    value = bytes / 1073741824;
    result += String(value, 1);
    result += " GB";
  } else if (bytes >= 1048576) {
    value = bytes / 1048576;
    result += String(value, 1);
    result += " MB";
  } else if (bytes >= 1024) {
    value = bytes / 1024;
    result += String(value, 1);
    result += " KB";
  } else if (bytes < 1024) {
    result += String((int)bytes, (unsigned char)DEC);
    result += " bytes";
  }
  return result;
}

String get_directories_msg(File root) {
  String result = "*SD storage:*\n";
  result += "_used: ";
  uint64_t usedSpace = SD.usedBytes();
  result += return_file_size(usedSpace);
  result += " / ";

  uint64_t cardSize = SD.cardSize();
  result += return_file_size(cardSize);
  result += "_\n";

  if (!root) {
    Serial.println("Failed to open directory");
    result += "\nFailed to open directory";
    return result;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      if ((String)file.name() != "/System Volume Information")result += get_directory_list(file);
    } else {
      result += "\n`";
      result += String(file.name()).substring(1);
      result += "` - ";
      result += return_file_size(file.size());
    }
    file = root.openNextFile();
  }

  result += "\n\nTo delete or download file, use one of the following commands. Instead of text.txt paste desired file name.";
  result += "\n`/delete text.txt`";
  result += "\n`/download text.txt`";
  return result;
}
