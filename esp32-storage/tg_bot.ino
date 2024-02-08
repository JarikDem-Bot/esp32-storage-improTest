void tg_init() {
  bot.skipUpdates();
  bot.attach(newMessage);
  bot.setTextMode(FB_MARKDOWN);
}

void newMessage(FB_msg& msg) {
  bot.sendTyping(msg.chatID);
  String replyMsg = "";

  if (msg.text == "/list") {
    replyMsg = bot_list(msg);
  }
  else if (msg.text.startsWith("/delete ")) {
    replyMsg = bot_delete(msg);
  } else if (msg.text.startsWith("/download ")) {
    replyMsg = bot_download(msg);
  } else if (msg.isFile) {
    replyMsg = bot_upload(msg);
  }

  replyMsg = msgClear(replyMsg);
  bot.replyMessage(replyMsg, msg.messageID, msg.chatID);
}

String bot_list(FB_msg msg) {
  String replyMsg;
  replyMsg = get_directories_msg(SD.open("/"));
  return replyMsg;
}

String bot_delete(FB_msg msg) {
  String replyMsg;
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
  String replyMsg;
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
  String replyMsg;

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


String msgClear(String message) { //Fast bot doesn't send message if it contsins "!" or "#"
  while (message.indexOf("!") != -1) {
    message.replace("!", ".");
  }
  while (message.indexOf("#") != -1) {
    message.replace("#", ".");
  }
  return message;
}

String returnFileSize(uint64_t bytes) {
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
  result += returnFileSize(usedSpace);
  result += " / ";

  uint64_t cardSize = SD.cardSize();
  result += returnFileSize(cardSize);
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
      result += returnFileSize(file.size());
    }
    file = root.openNextFile();
  }

  result += "\n\nTo delete or download file, use one of the following commands. Instead of text.txt paste desired file name.";
  result += "\n`/delete text.txt`";
  result += "\n`/download text.txt`";
  return result;
}
