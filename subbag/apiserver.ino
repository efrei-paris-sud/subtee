/**
 * All HTTP API calls are made through these helper methods.
 */
#include <HTTPClient.h>

#define API_ENDPOINT_TRANSLATE "http://83dd095b.ngrok.io/translate"

HTTPClient httpClient;

String apiTranslate(String string, String lang_src, String lang_dest) {
  string.trim();
  String postData = String("{\"string\": \"") + string + String("\", \"lang_src\": \"fr\", \"lang_dest\": \"en\"}");
  Serial.println(postData);
  httpClient.begin(API_ENDPOINT_TRANSLATE);
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
