#include "webserver.h"
#include "globals.h"

AsyncWebServer server(80);

void setup_server()
{
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(notFound);

  server.begin();
}

void handleRoot(AsyncWebServerRequest *request)
{
  request->send(200, "text/html", sendHTML((int)bpm, (int)spo2));
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

String sendHTML(int bpm, int spo2)
{
  String result_html = HTML_SRC;

  result_html.replace("{0}", (String)bpm);
  result_html.replace("{1}", (String)spo2);

  return result_html;
}