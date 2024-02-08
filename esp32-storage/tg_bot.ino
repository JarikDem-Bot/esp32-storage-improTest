void tg_init() {
  bot.attach(newMessage);
  bot.setTextMode(FB_MARKDOWN);
}

void newMessage(FB_msg& msg) {
  bot.sendTyping(msg.chatID);

  if (msg.text == "/list") {
    bot.replyMessage(get_directories_msg(SD.open("/")), msg.messageID, msg.chatID);
  }
}

String MBdisplay(float mbytes) {
  String result = "";
  if (mbytes >= 1024) {
    mbytes /= 1024;
    result += String(mbytes, 1);
    result += "GB";
  } else {
    result += String(mbytes, 1);
    result += "MB";
  }
  return result;
}

String get_directories_msg(File root) {
  String result = "*SD storage:*\n";
  result += "_used: ";
  float usedSpace = SD.usedBytes() / (1024 * 1024);
  result += MBdisplay(usedSpace);
  result += " / ";

  float cardSize = SD.cardSize() / (1024 * 1024);
  result += MBdisplay(cardSize);
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
  result += "\n`/upload text.txt`";
  return result;
}
