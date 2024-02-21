File uploadFile;

void handle_root() {
  String html = HTML_HOME_PAGE;
  server.send(200, "text/html", html);
}

String get_directory_list(File root) {
  String result = "{\"files\": [";
  
  if (!root) {
    Serial.println("Failed to open directory");
    result += "]}";
    return result;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      if ((String)file.name() != "/System Volume Information") result += get_directory_list(file);
    } else {
      result += "\n{\"name\": \"";
      result += file.name();
      result += "\",\n\"size\": ";
      result += file.size();
      result += "},";
    }
    file = root.openNextFile();
  }
  if (result.endsWith(",")) {
    result.remove(result.length() - 1);
  }
  result += "],";
  
  result += "\n\"used\": ";
  uint64_t usedMBytes = SD.usedBytes() / (1024 * 1024);
  result += String((int)usedMBytes, (unsigned char)DEC);
  result += ",\n\"total\": ";
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  result += String((int)cardSize, (unsigned char)DEC);
  
  result += "}";
  return result;
}

void handle_list() {
  String response = get_directory_list(SD.open("/"));
  server.send(200, "application/json", response);
}

void handle_delete() {
  if (server.uri() != "/delete") {
    return;
  }

  String filename = server.arg(0);
  if (!filename.startsWith("/")) filename = "/" + filename;

  SD.remove(filename);

  String response = get_directory_list(SD.open("/"));
  server.send(200, "application/json", response);
}

void handle_download() {
  if (server.uri() != "/download") {
    return;
  }
  String filename = server.arg(0);
  if (!filename.startsWith("/")) filename = "/" + filename;

  File file = SD.open(filename);
  if (file) {
    server.streamFile(file, "form-data");
  }
  file.close();
}

void handle_upload() {
  if (server.uri() != "/upload") {
    return;
  }

  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    Serial.print("Upload File Name: "); Serial.println(filename);
    SD.remove(filename);
    uploadFile = SD.open(filename, FILE_WRITE);
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    if (uploadFile) {
      uploadFile.write(upload.buf, upload.currentSize);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (uploadFile)
    {
      uploadFile.close();
      Serial.print("Upload Size: "); Serial.println(upload.totalSize);
      String response = get_directory_list(SD.open("/"));
      server.send(200, "application/json", response);
    }
    else
    {
      Serial.println("Unable to close file");
    }
  }
}

void handle_not_found() {
  String html = HTML_NOTFOUND_PAGE;
  server.send(404, "text/html", html);
}

void server_route() {
  server.on("/", handle_root);
  server.on("/list", HTTP_GET, handle_list);
  server.on("/delete", HTTP_DELETE, handle_delete);
  server.on("/download", HTTP_POST, handle_download);
  server.on("/upload", HTTP_POST, []() {
    server.send(200);
  }, handle_upload);
  server.onNotFound(handle_not_found);
}
