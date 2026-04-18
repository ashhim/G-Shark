/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#include "wifi.h"

extern "C" {
    #include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "language.h"
#include "debug.h"
#include "settings.h"
#include "CLI.h"
#include "Attack.h"
#include "Scan.h"
#include "DisplayUI.h"
#include "CapAdPage.h"
#include "NameMePages.h"

extern bool progmemToSpiffs(const char* adr, int len, String path);
extern void setWifiChannel(uint8_t ch, bool force);

#include "webfiles.h"

extern Scan   scan;
extern CLI    cli;
extern Attack attack;
extern DisplayUI displayUI;

typedef enum wifi_mode_t {
    off = 0,
    ap  = 1,
    st  = 2
} wifi_mode_t;

typedef struct ap_settings_t {
    char    path[33];
    char    ssid[33];
    char    password[65];
    uint8_t channel;
    bool    hidden;
    bool    captive_portal;
} ap_settings_t;

namespace wifi {
    // ===== PRIVATE ===== //
    wifi_mode_t   mode;
    ap_settings_t ap_settings;
    bool          serverStarted          = false;
    bool          attackPortalEnabled    = false;
    bool          attackPortalShowsNameMe = false;
    wifi_mode_t   attackPortalPreviousMode = wifi_mode_t::off;
    ap_settings_t attackPortalPreviousSettings;
    String        nameMeValue;
    uint8_t       nameMeTemplateIndex = 0;
    const char* const nameMeTemplateFileNames[12] = {
        "Astra.html",
        "Breach.html",
        "Brimstone.html",
        "Chamber.html",
        "Clove.html",
        "Cypher.html",
        "Deadlock.html",
        "Fade.html",
        "Gekko.html",
        "Harbor.html",
        "Iso.html",
        "Jett.html"
    };

    // Server and other global objects
    ESP8266WebServer server(80);
    DNSServer dns;
    IPAddress ip WEB_IP_ADDR;
    IPAddress    netmask(255, 255, 255, 0);

    void setPath(String path) {
        if (path.charAt(0) != '/') {
            path = '/' + path;
        }

        if (path.length() > 32) {
            debuglnF("ERROR: Path longer than 32 characters");
        } else {
            strncpy(ap_settings.path, path.c_str(), 32);
            ap_settings.path[32] = '\0';
        }
    }

    void setSSID(String ssid) {
        if (ssid.length() > 32) {
            debuglnF("ERROR: SSID longer than 32 characters");
        } else {
            strncpy(ap_settings.ssid, ssid.c_str(), 32);
            ap_settings.ssid[32] = '\0';
        }
    }

    void setPassword(String password) {
        if (password.length() > 64) {
            debuglnF("ERROR: Password longer than 64 characters");
        } else if (password.length() < 8) {
            debuglnF("ERROR: Password must be at least 8 characters long");
        } else {
            strncpy(ap_settings.password, password.c_str(), 64);
            ap_settings.password[64] = '\0';
        }
    }

    void clearPassword() {
        ap_settings.password[0] = '\0';
    }

    void setChannel(uint8_t ch) {
        if ((ch < 1) || (ch > 14)) {
            debuglnF("ERROR: Channel must be withing the range of 1-14");
        } else {
            ap_settings.channel = ch;
        }
    }

    void setHidden(bool hidden) {
        ap_settings.hidden = hidden;
    }

    void setCaptivePortal(bool captivePortal) {
        ap_settings.captive_portal = captivePortal;
    }

    const char* getPassword() {
        return ap_settings.password[0] ? ap_settings.password : NULL;
    }

    void handleFileList() {
        if (!server.hasArg("dir")) {
            server.send(500, str(W_TXT), str(W_BAD_ARGS));
            return;
        }

        String path = server.arg("dir");
        // debugF("handleFileList: ");
        // debugln(path);

        Dir dir = SPIFFS.openDir(path);

        String output = String('{'); // {
        File   entry;
        bool   first = true;

        while (dir.next()) {
            entry = dir.openFile("r");

            if (first) first = false;
            else output += ',';                 // ,

            output += '[';                      // [
            output += '"' + entry.name() + '"'; // "filename"
            output += ']';                      // ]

            entry.close();
        }

        output += CLOSE_BRACKET;
        server.send(200, str(W_JSON).c_str(), output);
    }

    String getContentType(String filename) {
        if (server.hasArg("download")) return String(F("application/octet-stream"));
        if (filename.endsWith(str(W_DOT_GZIP))) filename = filename.substring(0, filename.length() - 3);

        if (filename.endsWith(str(W_DOT_HTM))) return str(W_HTML);
        else if (filename.endsWith(str(W_DOT_HTML))) return str(W_HTML);
        else if (filename.endsWith(str(W_DOT_CSS))) return str(W_CSS);
        else if (filename.endsWith(str(W_DOT_JS))) return str(W_JS);
        else if (filename.endsWith(str(W_DOT_PNG))) return str(W_PNG);
        else if (filename.endsWith(str(W_DOT_GIF))) return str(W_GIF);
        else if (filename.endsWith(str(W_DOT_JPG)) || filename.endsWith(".jpeg")) return str(W_JPG);
        else if (filename.endsWith(".bmp")) return String(F("image/bmp"));
        else if (filename.endsWith(".webp")) return String(F("image/webp"));
        else if (filename.endsWith(".svg")) return String(F("image/svg+xml"));
        else if (filename.endsWith(".mp3")) return String(F("audio/mpeg"));
        else if (filename.endsWith(".wav")) return String(F("audio/wav"));
        else if (filename.endsWith(str(W_DOT_ICON))) return str(W_ICON);
        else if (filename.endsWith(str(W_DOT_XML))) return str(W_XML);
        else if (filename.endsWith(str(W_DOT_PDF))) return str(W_XPDF);
        else if (filename.endsWith(str(W_DOT_ZIP))) return str(W_XZIP);
        else if (filename.endsWith(str(W_DOT_JSON))) return str(W_JSON);
        return str(W_TXT);
    }

    bool handleFileRead(String path) {
        // prnt(W_AP_REQUEST);
        // prnt(path);

        if (path.charAt(0) != '/') path = '/' + path;
        if (path.charAt(path.length() - 1) == '/') path += String(F("index.html"));

        String contentType = getContentType(path);

        if (!SPIFFS.exists(path)) {
            if (SPIFFS.exists(path + str(W_DOT_GZIP))) path += str(W_DOT_GZIP);
            else if (SPIFFS.exists(String(ap_settings.path) + path)) path = String(ap_settings.path) + path;
            else if (SPIFFS.exists(String(ap_settings.path) + path + str(W_DOT_GZIP))) path = String(ap_settings.path) + path + str(W_DOT_GZIP);
            else {
                // prntln(W_NOT_FOUND);
                return false;
            }
        }

        File file = SPIFFS.open(path, "r");

        if (path.endsWith(str(W_DOT_GZIP))) {
            server.sendHeader("Content-Encoding", "gzip");
        }
        server.streamFile(file, contentType);
        file.close();
        // prnt(SPACE);
        // prntln(W_OK);

        return true;
    }

    void sendProgmem(const char* ptr, size_t size, const char* type) {
        server.sendHeader("Content-Encoding", "gzip");
        server.sendHeader("Cache-Control", "max-age=3600");
        server.send_P(200, str(type).c_str(), ptr, size);
    }

    void setNoCacheHeaders() {
        server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
        server.sendHeader("Pragma", "no-cache");
        server.sendHeader("Expires", "-1");
    }

    void sendCapadPage() {
        setNoCacheHeaders();
        server.send_P(200, str(W_HTML).c_str(), capad_html, sizeof(capad_html) - 1);
    }

    bool sendExactFile(String path);

    String getNameMeTemplatePath() {
        uint8_t index = nameMeTemplateIndex < 12 ? nameMeTemplateIndex : 0;
        return String(F("/nameme/")) + String(nameMeTemplateFileNames[index]);
    }

    void sendNameMePage() {
        setNoCacheHeaders();
        if (!sendExactFile(getNameMeTemplatePath())) {
            uint8_t index = nameMeTemplateIndex < 12 ? nameMeTemplateIndex : 0;
            const char* page = reinterpret_cast<const char*>(pgm_read_ptr(&nameme_template_pages[index]));
            size_t size = static_cast<size_t>(pgm_read_dword(&nameme_template_page_sizes[index]));
            server.send_P(200, str(W_HTML).c_str(), page, size);
        }
    }

    void sendAttackPortalPage() {
        if (attackPortalShowsNameMe) sendNameMePage();
        else sendCapadPage();
    }

    bool sendExactFile(String path) {
        if (!SPIFFS.exists(path)) return false;

        File file = SPIFFS.open(path, "r");

        if (!file) return false;

        if (path.endsWith(str(W_DOT_GZIP))) {
            server.sendHeader("Content-Encoding", "gzip");
        }
        server.streamFile(file, getContentType(path));
        file.close();
        return true;
    }

    bool sendCapadAsset(String fileName) {
        if (sendExactFile("/" + fileName)) return true;
        if (sendExactFile("/capad/" + fileName)) return true;
        return false;
    }

    void handleNameMeSubmit() {
        if (!attackPortalEnabled || !attackPortalShowsNameMe) {
            server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            return;
        }

        String submittedValue;

        if (server.hasArg("preview_text")) {
            submittedValue = server.arg("preview_text");
        } else if (server.hasArg("entered_name")) {
            submittedValue = server.arg("entered_name");
        } else {
            sendAttackPortalPage();
            return;
        }

        nameMeValue = submittedValue;
        nameMeValue.trim();

        if (nameMeValue.length() > 32) {
            nameMeValue = nameMeValue.substring(0, 32);
        }

        displayUI.refreshAttackMenu();

        setNoCacheHeaders();
        server.sendHeader("Location", "/");
        server.send(303, str(W_TXT), String());
    }

    void sendFileOr404(String path) {
        if (!sendExactFile(path)) {
            server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
        }
    }

    bool isAssetRequest(String path) {
        int dotPos = path.lastIndexOf('.');

        if (dotPos < 0) return false;

        String ext = path.substring(dotPos);
        ext.toLowerCase();

        return ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".gif" || ext == ".bmp" ||
               ext == ".webp" || ext == ".svg" || ext == ".css" || ext == ".js" || ext == ".mp3" ||
               ext == ".wav" || ext == ".ico" || ext == ".json" || ext == ".txt" || ext == ".xml";
    }

    void applySoftAPSettings() {
        wifi_promiscuous_enable(0);
        WiFi.persistent(false);
        WiFi.mode(WIFI_AP_STA);
        wifi_set_opmode(STATIONAP_MODE);
        WiFi.softAPdisconnect(true);
        delay(50);
        WiFi.softAPConfig(ip, ip, netmask);

        bool started = WiFi.softAP(ap_settings.ssid, getPassword(), ap_settings.channel, ap_settings.hidden);

        if (!started) {
            debuglnF("ERROR: Failed to start CAPAD softAP");
        }
        setWifiChannel(ap_settings.channel, true);
        delay(50);

        dns.setErrorReplyCode(DNSReplyCode::NoError);
        dns.start(53, "*", ip);

        mode = wifi_mode_t::ap;
    }

    // ===== PUBLIC ====== //
    void begin() {
        // Set settings
        setPath("/web");
        setSSID(settings::getAccessPointSettings().ssid);
        setPassword(settings::getAccessPointSettings().password);
        setChannel(settings::getWifiSettings().channel);
        setHidden(settings::getAccessPointSettings().hidden);
        setCaptivePortal(settings::getWebSettings().captive_portal);

        // copy web files to SPIFFS
        if (settings::getWebSettings().use_spiffs) {
            copyWebFiles(false);
        }

        // Set mode
        mode = wifi_mode_t::off;
        WiFi.mode(WIFI_OFF);
        wifi_set_opmode(STATION_MODE);

        // Set mac address
        wifi_set_macaddr(STATION_IF, (uint8_t*)settings::getWifiSettings().mac_st);
        wifi_set_macaddr(SOFTAP_IF, (uint8_t*)settings::getWifiSettings().mac_ap);
    }

    String getMode() {
        switch (mode) {
            case wifi_mode_t::off:
                return "OFF";
            case wifi_mode_t::ap:
                return "AP";
            case wifi_mode_t::st:
                return "ST";
            default:
                return String();
        }
    }

    void printStatus() {
        prnt(String(F("[WiFi] Path: '")));
        prnt(ap_settings.path);
        prnt(String(F("', Mode: '")));
        prnt(getMode());
        prnt(String(F("', SSID: '")));
        prnt(ap_settings.ssid);
        prnt(String(F("', password: '")));
        prnt(ap_settings.password);
        prnt(String(F("', channel: '")));
        prnt(ap_settings.channel);
        prnt(String(F("', hidden: ")));
        prnt(b2s(ap_settings.hidden));
        prnt(String(F(", captive-portal: ")));
        prntln(b2s(ap_settings.captive_portal));
    }

    void startNewAP(String path, String ssid, String password, uint8_t ch, bool hidden, bool captivePortal) {
        setPath(path);
        setSSID(ssid);
        setPassword(password);
        setChannel(ch);
        setHidden(hidden);
        setCaptivePortal(captivePortal);

        startAP();
    }

    /*
        void startAP(String path) {
            setPath(path):

            startAP();
        }
     */
    void startAP() {
        applySoftAPSettings();

        MDNS.begin(WEB_URL);

        if (!serverStarted) {
            server.on("/list", HTTP_GET, handleFileList); // list directory
            server.on("/logo.png", HTTP_ANY, []() {
                if (attackPortalEnabled) {
                    if (!sendCapadAsset("logo.png")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
                else sendFileOr404("/logo.png");
            });
            server.on("/instapage.jpg", HTTP_ANY, []() {
                if (attackPortalEnabled) {
                    if (!sendCapadAsset("instapage.jpg")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
                else sendFileOr404("/instapage.jpg");
            });
            server.on("/image.jpg", HTTP_ANY, []() {
                if (attackPortalEnabled) {
                    if (!sendCapadAsset("image.jpg")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
                else sendFileOr404("/image.jpg");
            });
            server.on("/music.mp3", HTTP_ANY, []() {
                if (attackPortalEnabled) {
                    if (!sendCapadAsset("music.mp3")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
                else sendFileOr404("/music.mp3");
            });
            server.on("/capad/logo.png", HTTP_ANY, []() {
                if (!sendCapadAsset("logo.png")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/capad/instapage.jpg", HTTP_ANY, []() {
                if (!sendCapadAsset("instapage.jpg")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/capad/image.jpg", HTTP_ANY, []() {
                if (!sendCapadAsset("image.jpg")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/capad/music.mp3", HTTP_ANY, []() {
                if (!sendCapadAsset("music.mp3")) server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/capad", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/nameme", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/get", HTTP_ANY, []() {
                if (attackPortalEnabled && attackPortalShowsNameMe) handleNameMeSubmit();
                else server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/submit-name", HTTP_ANY, []() {
                handleNameMeSubmit();
            });
            server.on("/generate_204", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else if (!handleFileRead("/generate_204")) server.send(204, str(W_TXT), String());
            });
            server.on("/hotspot-detect.html", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else if (!handleFileRead("/hotspot-detect.html")) server.send(200, str(W_HTML), "<HTML><HEAD><TITLE>Success</TITLE></HEAD><BODY>Success</BODY></HTML>");
            });
            server.on("/connecttest.txt", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else server.send(200, str(W_TXT), "Microsoft Connect Test");
            });
            server.on("/redirect", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else if (!handleFileRead("/redirect")) server.send(302, str(W_HTML), String());
            });
            server.on("/fwlink", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else if (!handleFileRead("/fwlink")) server.send(200, str(W_TXT), str(W_FILE_NOT_FOUND));
            });
            server.on("/ncsi.txt", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else server.send(200, str(W_TXT), "Microsoft NCSI");
            });
            server.on("/wifioff", HTTP_ANY, []() {
                if (attackPortalEnabled) sendAttackPortalPage();
                else server.send(200, str(W_TXT), str(W_OK));
            });
            server.on("/", HTTP_GET, []() {
                if (attackPortalEnabled) {
                    sendAttackPortalPage();
                    return;
                }

                #ifdef USE_PROGMEM_WEB_FILES
                if (!settings::getWebSettings().use_spiffs) {
                    sendProgmem(indexhtml, sizeof(indexhtml), W_HTML);
                    return;
                }
                #endif /* ifdef USE_PROGMEM_WEB_FILES */

                if (!handleFileRead("/index.html")) {
                    server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
            });
            server.on("/index.html", HTTP_GET, []() {
                if (attackPortalEnabled) {
                    sendAttackPortalPage();
                    return;
                }

                #ifdef USE_PROGMEM_WEB_FILES
                if (!settings::getWebSettings().use_spiffs) {
                    sendProgmem(indexhtml, sizeof(indexhtml), W_HTML);
                    return;
                }
                #endif /* ifdef USE_PROGMEM_WEB_FILES */

                if (!handleFileRead("/index.html")) {
                    server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
            });

            #ifdef USE_PROGMEM_WEB_FILES
            // ================================================================
            // paste here the output of the webConverter.py
            if (!settings::getWebSettings().use_spiffs) {
                server.on("/scan.html", HTTP_GET, []() {
                    sendProgmem(scanhtml, sizeof(scanhtml), W_HTML);
                });
                server.on("/info.html", HTTP_GET, []() {
                    sendProgmem(infohtml, sizeof(infohtml), W_HTML);
                });
                server.on("/ssids.html", HTTP_GET, []() {
                    sendProgmem(ssidshtml, sizeof(ssidshtml), W_HTML);
                });
                server.on("/attack.html", HTTP_GET, []() {
                    sendProgmem(attackhtml, sizeof(attackhtml), W_HTML);
                });
                server.on("/settings.html", HTTP_GET, []() {
                    sendProgmem(settingshtml, sizeof(settingshtml), W_HTML);
                });
                server.on("/style.css", HTTP_GET, []() {
                    sendProgmem(stylecss, sizeof(stylecss), W_CSS);
                });
                server.on("/js/ssids.js", HTTP_GET, []() {
                    sendProgmem(ssidsjs, sizeof(ssidsjs), W_JS);
                });
                server.on("/js/site.js", HTTP_GET, []() {
                    sendProgmem(sitejs, sizeof(sitejs), W_JS);
                });
                server.on("/js/attack.js", HTTP_GET, []() {
                    sendProgmem(attackjs, sizeof(attackjs), W_JS);
                });
                server.on("/js/scan.js", HTTP_GET, []() {
                    sendProgmem(scanjs, sizeof(scanjs), W_JS);
                });
                server.on("/js/settings.js", HTTP_GET, []() {
                    sendProgmem(settingsjs, sizeof(settingsjs), W_JS);
                });
                server.on("/lang/hu.lang", HTTP_GET, []() {
                    sendProgmem(hulang, sizeof(hulang), W_JSON);
                });
                server.on("/lang/ja.lang", HTTP_GET, []() {
                    sendProgmem(jalang, sizeof(jalang), W_JSON);
                });
                server.on("/lang/nl.lang", HTTP_GET, []() {
                    sendProgmem(nllang, sizeof(nllang), W_JSON);
                });
                server.on("/lang/fi.lang", HTTP_GET, []() {
                    sendProgmem(filang, sizeof(filang), W_JSON);
                });
                server.on("/lang/cn.lang", HTTP_GET, []() {
                    sendProgmem(cnlang, sizeof(cnlang), W_JSON);
                });
                server.on("/lang/ru.lang", HTTP_GET, []() {
                    sendProgmem(rulang, sizeof(rulang), W_JSON);
                });
                server.on("/lang/pl.lang", HTTP_GET, []() {
                    sendProgmem(pllang, sizeof(pllang), W_JSON);
                });
                server.on("/lang/uk.lang", HTTP_GET, []() {
                    sendProgmem(uklang, sizeof(uklang), W_JSON);
                });
                server.on("/lang/de.lang", HTTP_GET, []() {
                    sendProgmem(delang, sizeof(delang), W_JSON);
                });
                server.on("/lang/it.lang", HTTP_GET, []() {
                    sendProgmem(itlang, sizeof(itlang), W_JSON);
                });
                server.on("/lang/en.lang", HTTP_GET, []() {
                    sendProgmem(enlang, sizeof(enlang), W_JSON);
                });
                server.on("/lang/fr.lang", HTTP_GET, []() {
                    sendProgmem(frlang, sizeof(frlang), W_JSON);
                });
                server.on("/lang/in.lang", HTTP_GET, []() {
                    sendProgmem(inlang, sizeof(inlang), W_JSON);
                });
                server.on("/lang/ko.lang", HTTP_GET, []() {
                    sendProgmem(kolang, sizeof(kolang), W_JSON);
                });
                server.on("/lang/ro.lang", HTTP_GET, []() {
                    sendProgmem(rolang, sizeof(rolang), W_JSON);
                });
                server.on("/lang/da.lang", HTTP_GET, []() {
                    sendProgmem(dalang, sizeof(dalang), W_JSON);
                });
                server.on("/lang/ptbr.lang", HTTP_GET, []() {
                    sendProgmem(ptbrlang, sizeof(ptbrlang), W_JSON);
                });
                server.on("/lang/cs.lang", HTTP_GET, []() {
                    sendProgmem(cslang, sizeof(cslang), W_JSON);
                });
                server.on("/lang/tlh.lang", HTTP_GET, []() {
                    sendProgmem(tlhlang, sizeof(tlhlang), W_JSON);
                });
                server.on("/lang/es.lang", HTTP_GET, []() {
                    sendProgmem(eslang, sizeof(eslang), W_JSON);
                });
                server.on("/lang/th.lang", HTTP_GET, []() {
                    sendProgmem(thlang, sizeof(thlang), W_JSON);
                });
            }
            server.on("/lang/default.lang", HTTP_GET, []() {
                if (!settings::getWebSettings().use_spiffs) {
                    if (String(settings::getWebSettings().lang) == "hu") sendProgmem(hulang, sizeof(hulang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "ja") sendProgmem(jalang, sizeof(jalang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "nl") sendProgmem(nllang, sizeof(nllang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "fi") sendProgmem(filang, sizeof(filang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "cn") sendProgmem(cnlang, sizeof(cnlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "ru") sendProgmem(rulang, sizeof(rulang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "pl") sendProgmem(pllang, sizeof(pllang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "uk") sendProgmem(uklang, sizeof(uklang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "de") sendProgmem(delang, sizeof(delang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "it") sendProgmem(itlang, sizeof(itlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "en") sendProgmem(enlang, sizeof(enlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "fr") sendProgmem(frlang, sizeof(frlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "in") sendProgmem(inlang, sizeof(inlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "ko") sendProgmem(kolang, sizeof(kolang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "ro") sendProgmem(rolang, sizeof(rolang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "da") sendProgmem(dalang, sizeof(dalang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "ptbr") sendProgmem(ptbrlang, sizeof(ptbrlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "cs") sendProgmem(cslang, sizeof(cslang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "tlh") sendProgmem(tlhlang, sizeof(tlhlang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "es") sendProgmem(eslang, sizeof(eslang), W_JSON);
                    else if (String(settings::getWebSettings().lang) == "th") sendProgmem(thlang, sizeof(thlang), W_JSON);

                    else handleFileRead("/web/lang/" + String(settings::getWebSettings().lang) + ".lang");
                } else {
                    handleFileRead("/web/lang/" + String(settings::getWebSettings().lang) + ".lang");
                }
            });
            // ================================================================
            #endif /* ifdef USE_PROGMEM_WEB_FILES */

            server.on("/run", HTTP_GET, []() {
                server.send(200, str(W_TXT), str(W_OK).c_str());
                String input = server.arg("cmd");
                cli.exec(input);
            });

            server.on("/attack.json", HTTP_GET, []() {
                server.send(200, str(W_JSON), attack.getStatusJSON());
            });

            server.onNotFound([]() {
                if (attackPortalEnabled) {
                    if (!handleFileRead(server.uri())) {
                        if (isAssetRequest(server.uri())) {
                            server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                        } else {
                            sendAttackPortalPage();
                        }
                    }
                } else if (!handleFileRead(server.uri())) {
                    if (settings::getWebSettings().captive_portal) sendProgmem(indexhtml, sizeof(indexhtml), W_HTML);
                    else server.send(404, str(W_TXT), str(W_FILE_NOT_FOUND));
                }
            });

            serverStarted = true;
        }

        server.begin();
        mode = wifi_mode_t::ap;

        prntln(W_STARTED_AP);
        printStatus();
    }

    void stopAP() {
        if (mode == wifi_mode_t::ap) {
            wifi_promiscuous_enable(0);
            WiFi.persistent(false);
            WiFi.disconnect(true);
            wifi_set_opmode(STATION_MODE);
            prntln(W_STOPPED_AP);
            mode = wifi_mode_t::st;
        }
    }

    void resumeAP() {
        if (mode != wifi_mode_t::ap) {
            mode = wifi_mode_t::ap;
            wifi_promiscuous_enable(0);
            applySoftAPSettings();
            prntln(W_STARTED_AP);
        }
    }

    void enableAttackPortal(String ssid, uint8_t ch, bool nameMePage) {
        if (!attackPortalEnabled) {
            attackPortalPreviousMode     = mode;
            attackPortalPreviousSettings = ap_settings;
        }

        if (mode == wifi_mode_t::ap) {
            stopAP();
        }

        attackPortalEnabled = true;
        attackPortalShowsNameMe = nameMePage;

        setPath(nameMePage ? "/nameme" : "/capad");
        setSSID(ssid);
        clearPassword();
        setChannel(ch);
        setHidden(false);
        setCaptivePortal(true);

        if (mode == wifi_mode_t::ap) {
            applySoftAPSettings();
            printStatus();
        } else {
            startAP();
        }
    }

    void disableAttackPortal() {
        if (!attackPortalEnabled) return;

        attackPortalEnabled = false;
        attackPortalShowsNameMe = false;
        ap_settings         = attackPortalPreviousSettings;

        if (attackPortalPreviousMode == wifi_mode_t::ap) {
            applySoftAPSettings();
            printStatus();
        } else {
            WiFi.softAPdisconnect(true);

            if (attackPortalPreviousMode == wifi_mode_t::off) {
                mode = wifi_mode_t::off;
                WiFi.mode(WIFI_OFF);
                wifi_set_opmode(STATION_MODE);
            } else {
                mode = wifi_mode_t::st;
                wifi_set_opmode(STATION_MODE);
            }
        }
    }

    bool isAttackPortalEnabled() {
        return attackPortalEnabled;
    }

    void setNameMeTemplate(uint8_t index) {
        if (index < 12) {
            nameMeTemplateIndex = index;
        }
    }

    uint8_t getNameMeTemplate() {
        return nameMeTemplateIndex;
    }

    String getNameMeValue() {
        return nameMeValue;
    }

    bool hasNameMeValue() {
        return nameMeValue.length() > 0;
    }

    void update() {
        if ((mode != wifi_mode_t::off) && !scan.isScanning()) {
            server.handleClient();
            dns.processNextRequest();
        }
    }
}