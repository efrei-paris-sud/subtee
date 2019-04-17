/**
 * All HTTP API calls are made through these helper methods.
 */
#include <HTTPClient.h>
#include "UDHttp.h"

HTTPClient httpClient;
File root;

String apiTranslate(String string, String lang_src, String lang_dest) {
  string.trim();
  lang_src.trim();
  lang_dest.trim();

  String postData = String("{\"string\": \"") + string + String("\", \"lang_src\": \"") + lang_src + String("\", \"lang_dest\": \"") + lang_dest + String("\"}");
  Serial.println(postData);

  String endpoint = String(API_ENDPOINT) + String("/translate");
  httpClient.begin(endpoint.c_str());
  httpClient.addHeader("Content-Type", "application/json");

  int httpResponseCode = httpClient.POST(postData);
  String response = httpClient.getString();

  Serial.print("Status code: ");
  Serial.println(httpResponseCode);
  Serial.print("Response: ");
  Serial.println(response);

  httpClient.end();

  if(httpResponseCode == 200) {
    response.remove(response.length() - 2, 1);
    response.remove(0, 1);
    return response; // Remove quotes
  } else {
    return "-error-";
  }
}

String apiMockSpeechToText(String filename) {
  String postData = String("");

  Serial.println("STT Request");
  String endpoint = String(API_ENDPOINT) + String("/speech-to-text");
  httpClient.begin(endpoint.c_str());
  int httpResponseCode = httpClient.POST(postData);
  String response = httpClient.getString();

  Serial.print("Status code: ");
  Serial.println(httpResponseCode);
  Serial.print("Response: ");
  Serial.println(response);

  httpClient.end();

  if(httpResponseCode == 200) {
    response.remove(response.length() - 2, 1);
    response.remove(0, 1);
    return response; // Remove quotes
  } else {
    return "Erreur";
  }
}

String apiSpeechToText(String filename) {
  UDHttp udh;
  root = SPIFFS.open(filename);
  if(!root) {
    Serial.println("Failed to open file for reading");
    return "erreur";
  }
  Serial.print("size:");
  Serial.println(root.size());
  String endpoint = String(API_ENDPOINT) + String("/speech-to-text");
  udh.upload((char*) endpoint.c_str(), "fr", root.size(), rdataf, progressf, responsef);
  root.close();
  Serial.printf("done uploading\n");

  return "ok";
}


/* UDHttp related code */
int responsef(uint8_t *buffer, int len){
  Serial.printf("%s\n", buffer);
  return 0;
}

int rdataf(uint8_t *buffer, int len){
  //read file to upload
  if (root.available()) {
    return root.read(buffer, len);
  }
  return 0;
}

void progressf(int percent){
  Serial.printf("%d\n", percent);
}
