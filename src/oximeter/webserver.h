#ifndef OXIMETER_WEBSERVER_H
#define OXIMETER_WEBSERVER_H

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#define HTML_SRC "<!DOCTYPE html>"                                                                                                                                                                          \
                 "<html>"                                                                                                                                                                                   \
                 "<head>"                                                                                                                                                                                   \
                 "<title>Oximetro Monitor</title>"                                                                                                                                            \
                 "<meta name='viewport' content='width=device-width, initial-scale=1.0' http-equiv='Content-Type' content='text/html; charset=utf-8'>"                                                                                                                   \
                 "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.7.2/css/all.min.css'>"                                                                                 \
                 "<link rel='stylesheet' type='text/css' href='styles.css'>"                                                                                                                                \
                 "<style>"                                                                                                                                                                                  \
                 "body { background-color: #fff; color: #333333; font: 14px Helvetica, sans-serif; box-sizing: border-box;}"                                                                                \
                 "#page { margin: 20px; background-color: #fff;}"                                                                                                                                           \
                 ".container { height: inherit; padding-bottom: 20px;}"                                                                                                                                     \
                 ".header { padding: 20px;}"                                                                                                                                                                \
                 ".header h1 { padding-bottom: 0.3em; color: #008080; font: bold 45px Garmond, sans-serif; text-align: center;}"                                                                            \
                 "h2 { padding-bottom: 0.2em; border-bottom: 1px solid #eee; margin: 2px; text-align: left;}"                                                                                               \
                 ".header h3 { font: bold 17px Arial, sans-serif; color: #b6b6b6; text-align: center;}"                                                                                                     \
                 ".box-full { padding: 20px; border: 1px solid #ddd; border-radius: 1em 1em 1em 1em; box-shadow: 1px 7px 7px 1px rgba(0,0,0,0.4); background: #fff; margin: 20px; width: 300px;}"           \
                 "@media (max-width: 494px) { #page { width: inherit; margin: 5px auto; } #content { padding: 1px;} .box-full { margin: 8px 8px 12px 8px; padding: 10px; width: inherit;; float: none; } }" \
                 "@media (min-width: 494px) and (max-width: 980px) { #page { width: 465px; margin: 0 auto; } .box-full { width: 380px; } }"                                                                 \
                 "@media (min-width: 980px) { #page { width: 930px; margin: auto; } }"                                                                                                                      \
                 ".sensor { margin: 12px 0px; font-size: 2.5rem;}"                                                                                                                                          \
                 ".sensor-labels { font-size: 1rem; vertical-align: middle; padding-bottom: 15px;}"                                                                                                         \
                 ".units { font-size: 1.2rem;}"                                                                                                                                                             \
                 "hr { height: 1px; color: #eee; background-color: #eee; border: none;}"                                                                                                                    \
                 "</style>"                                                                                                                                                                                 \
                 "<!-- //Ajax Code Start -->"                                                                                                                                                               \
                 "<script>\n"                                                                                                                                                                                 \
                 "setInterval(loadDoc,1000);\n"                                                                                                                                                               \
                 "function loadDoc() {\n"                                                                                                                                                                     \
                 "var xhttp = new XMLHttpRequest();\n"                                                                                                                                                        \
                 "xhttp.onreadystatechange = function() {\n"                                                                                                                                                  \
                 "if (this.readyState == 4 && this.status == 200) {\n"                                                                                                                                        \
                 "document.body.innerHTML = this.responseText}\n"                                                                                                                                              \
                 "};\n"                                                                                                                                                                                       \
                 "xhttp.open(\"GET\", \"/\", true);\n"                                                                                                                                                      \
                 "xhttp.send();\n"                                                                                                                                                                            \
                 "}\n"                                                                                                                                                                                        \
                 "</script>\n"                                                                                                                                                                                \
                 "<!-- //Ajax Code END -->"                                                                                                                                                                 \
                 "</head>"                                                                                                                                                                                  \
                 "<body>"                                                                                                                                                                                   \
                 "<div id='page'>"                                                                                                                                                                          \
                 "<div class='header'>"                                                                                                                                                                     \
                 "<h1>Ox??metro Monitor</h1>"                                                                                                                                                        \
                 "</div>"                                                                                                                                                                                   \
                 "<div id='content' align='center'>"                                                                                                                                                        \
                 "<div class='box-full' align='left'>"                                                                                                                                                      \
                 "<h2>Sensor Readings</h2>"                                                                                                                                                                 \
                 "<div class='sensors-container'>"                                                                                                                                                          \
                 "<!-- //For Heart Rate -->"                                                                                                                                                                \
                 "<p class='sensor'>"                                                                                                                                                                       \
                 "<i class='fas fa-heartbeat' style='color:#cc3300'></i>"                                                                                                                                   \
                 "<span class='sensor-labels'> Heart Rate </span>"                                                                                                                                          \
                 "{0}"                                                                                                                                                                                      \
                 "<sup class='units'>BPM</sup>"                                                                                                                                                             \
                 "</p>"                                                                                                                                                                                     \
                 "<hr>"                                                                                                                                                                                     \
                 "<!-- //For Sp02 -->"                                                                                                                                                                      \
                 "<p class='sensor'>"                                                                                                                                                                       \
                 "<i class='fas fa-burn' style='color:#f7347a'></i>"                                                                                                                                        \
                 "<span class='sensor-labels'> Sp02 </span>"                                                                                                                                                \
                 "{1}  "                                                                                                                                                                                    \
                 "<sup class='units'>%</sup>"                                                                                                                                                               \
                 "</p>"                                                                                                                                                                                     \
                 "</div>"                                                                                                                                                                                   \
                 "</div>"                                                                                                                                                                                   \
                 "</div>"                                                                                                                                                                                   \
                 "</div>"                                                                                                                                                                                   \
                 "</body>"                                                                                                                                                                                  \
                 "</html>"

extern AsyncWebServer server;

void setup_server();
void handleRoot(AsyncWebServerRequest *request);
void notFound(AsyncWebServerRequest *request);
String sendHTML(int, int);
#endif