/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#include "DisplayUI.h"

#include "settings.h"
#include "wifi.h"

static const char* const kNameMeTemplateLabels[12] = {
    "HACK1",
    "HACK2",
    "HACKERFR",
    "Airtel",
    "ZTE",
    "JIO",
    "Huawei",
    "D-Link",
    "TP-Link",
    "Netgear",
    "BSNL",
    "WiFi"
};

// ===== adjustable ===== //
void DisplayUI::configInit() {
    // initialize display
    display.init();

    /*
       In case of a compiler (conversion char/uint8_t) error,
       make sure to have version 4 of the display library installed
       https://github.com/ThingPulse/esp8266-oled-ssd1306/releases/tag/4.0.0
     */
    display.setFont(DejaVu_Sans_Mono_12);

    display.setContrast(255);

    if (FLIP_DIPLAY) display.flipScreenVertically();

    display.clear();
    display.display();
}

void DisplayUI::configOn() {
    display.displayOn();
}

void DisplayUI::configOff() {
    display.displayOff();
}

void DisplayUI::updatePrefix() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(DejaVu_Sans_Mono_12);
}

void DisplayUI::updateSuffix() {
    display.display();
}

void DisplayUI::drawString(int x, int y, String str) {
    display.drawString(x, y, replaceUtf8(str, String(QUESTIONMARK)));
}

void DisplayUI::drawString(int row, String str) {
    drawString(0, row * lineHeight, str);
}

void DisplayUI::drawLine(int x1, int y1, int x2, int y2) {
    display.drawLine(x1, y1, x2, y2);
}

// ====================== //


DisplayUI::DisplayUI() {}

DisplayUI::~DisplayUI() {}


void DisplayUI::setup() {
    configInit();
    setupButtons();
    buttonTime = currentTime;

#ifdef RTC_DS3231
    bool h12;
    bool PM_time;
    clock.setClockMode(false);
    clockHour   = clock.getHour(h12, PM_time);
    clockMinute = clock.getMinute();
#else // ifdef RTC_DS3231
    clockHour   = random(12);
    clockMinute = random(60);
#endif // ifdef RTC_DS3231

    // ===== MENUS ===== //

    // MAIN MENU
    createMenu(&mainMenu, NULL, [this]() {
        addMenuNode(&mainMenu, D_SCAN, &scanMenu);          /// SCAN
        addMenuNode(&mainMenu, D_SHOW, &showMenu);          // SHOW
        addMenuNode(&mainMenu, D_ATTACK, &attackMenu);      // ATTACK
        addMenuNode(&mainMenu, D_PACKET_MONITOR, [this]() { // PACKET MONITOR
            scan.start(SCAN_MODE_SNIFFER, 0, SCAN_MODE_OFF, 0, false, wifi_channel);
            mode = DISPLAY_MODE::PACKETMONITOR;
        });
        addMenuNode(&mainMenu, D_APST_MONITOR, [this]() {   // APST MONITOR
            startAPSTMonitor();
        });
        addMenuNode(&mainMenu, [this]() {
            return getMainClockLabel();
        }, &clockMenu);

#ifdef HIGHLIGHT_LED
        addMenuNode(&mainMenu, D_LED, [this]() {     // LED
            highlightLED = !highlightLED;
            digitalWrite(HIGHLIGHT_LED, highlightLED);
        });
#endif // ifdef HIGHLIGHT_LED
    });

    // SCAN MENU
    createMenu(&scanMenu, &mainMenu, [this]() {
        addMenuNode(&scanMenu, D_SCAN_APST, [this]() { // SCAN AP + ST
            scan.start(SCAN_MODE_ALL, 15000, SCAN_MODE_OFF, 0, true, wifi_channel);
            mode = DISPLAY_MODE::LOADSCAN;
        });
        addMenuNode(&scanMenu, D_SCAN_AP, [this]() { // SCAN AP
            scan.start(SCAN_MODE_APS, 0, SCAN_MODE_OFF, 0, true, wifi_channel);
            mode = DISPLAY_MODE::LOADSCAN;
        });
        addMenuNode(&scanMenu, D_SCAN_ST, [this]() { // SCAN ST
            scan.start(SCAN_MODE_STATIONS, 30000, SCAN_MODE_OFF, 0, true, wifi_channel);
            mode = DISPLAY_MODE::LOADSCAN;
        });
        addMenuNode(&scanMenu, [this]() {
            return scan.isAutoScanActive() ? str(D_SCANNING) : str(D_AUTOSCAN);
        }, [this]() {
            handleAutoScanMenuClick();
        });
        addMenuNode(&scanMenu, D_AP_TRACKER, [this]() {
            startAPTracker();
        });
    });

    // SHOW MENU
    createMenu(&showMenu, &mainMenu, [this]() {
        addMenuNode(&showMenu, []() {
            return String(F("APSs"));
        }, &apListMenu);
        addMenuNode(&showMenu, []() {
            return String(F("Stations"));
        }, &stationListMenu);
        addMenuNode(&showMenu, []() {
            return String(F("Names"));
        }, &nameListMenu);
        addMenuNode(&showMenu, []() {
            return String(F("SSIDs"));
        }, &ssidListMenu);
        addMenuNode(&showMenu, D_NAMEME, &namemeListMenu);
    });

    // FISH PREVIEW MENU
    createMenu(&namemeListMenu, &showMenu, [this]() {
        for (uint8_t i = 0; i < 12; i++) {
            addMenuNode(&namemeListMenu, [i]() {
                return b2a(wifi::getNameMeTemplate() == i) + String(kNameMeTemplateLabels[i]);
            }, [this, i]() {
                wifi::setNameMeTemplate(i);
                changeMenu(&namemeListMenu);
            });
        }
    });

    // AP LIST MENU
    createMenu(&apListMenu, &showMenu, [this]() {
        // add APs to list
        int c = accesspoints.count();

        for (int i = 0; i < c; i++) {
            uint16_t apID = accesspoints.getID(i);

            addMenuNode(&apListMenu, [apID]() -> String {
                int apIndex = accesspoints.find(apID);

                if (apIndex < 0) return String(F("REMOVED"));
                return String(b2a(accesspoints.getSelected(apIndex))) + accesspoints.getSSID(apIndex);
            }, [this, apID]() {
                int apIndex = accesspoints.find(apID);

                if (apIndex < 0) {
                    changeMenu(&apListMenu);
                    return;
                }

                accesspoints.getSelected(apIndex) ? accesspoints.deselect(apIndex) : accesspoints.select(apIndex);
            }, [this, apID]() {
                int apIndex = accesspoints.find(apID);

                if (apIndex < 0) {
                    changeMenu(&apListMenu);
                    return;
                }

                selectedID = apIndex;
                changeMenu(&apMenu);
            });
        }
        addMenuNode(&apListMenu, D_SELECT_ALL, [this]() { // SELECT ALL
            accesspoints.selectAll();
            changeMenu(&apListMenu);
        });
        addMenuNode(&apListMenu, D_DESELECT_ALL, [this]() { // DESELECT ALL
            accesspoints.deselectAll();
            changeMenu(&apListMenu);
        });
        addMenuNode(&apListMenu, D_REMOVE_ALL, [this]() { // REMOVE ALL
            accesspoints.removeAll();
            goBack();
        });
    });

    // STATION LIST MENU
    createMenu(&stationListMenu, &showMenu, [this]() {
        // add stations to list
        int c = stations.count();

        for (int i = 0; i < c; i++) {
            addMenuNode(&stationListMenu, [i]() {
                return b2a(stations.getSelected(i)) +
                (stations.hasName(i) ? stations.getNameStr(i) : stations.getMacVendorStr(i));
            }, [this, i]() {
                stations.getSelected(i) ? stations.deselect(i) : stations.select(i);
            }, [this, i]() {
                selectedID = i;
                changeMenu(&stationMenu);
            });
        }

        addMenuNode(&stationListMenu, D_SELECT_ALL, [this]() { // SELECT ALL
            stations.selectAll();
            changeMenu(&stationListMenu);
        });
        addMenuNode(&stationListMenu, D_DESELECT_ALL, [this]() { // DESELECT ALL
            stations.deselectAll();
            changeMenu(&stationListMenu);
        });
        addMenuNode(&stationListMenu, D_REMOVE_ALL, [this]() { // REMOVE ALL
            stations.removeAll();
            goBack();
        });
    });

    // NAME LIST MENU
    createMenu(&nameListMenu, &showMenu, [this]() {
        // add device names to list
        int c = names.count();

        for (int i = 0; i < c; i++) {
            addMenuNode(&nameListMenu, [i]() {
                return names.getSelectedStr(i) + names.getName(i);
            }, [this, i]() {
                names.getSelected(i) ? names.deselect(i) : names.select(i);
            }, [this, i]() {
                selectedID = i;
                changeMenu(&nameMenu);
            });
        }
        addMenuNode(&nameListMenu, D_SELECT_ALL, [this]() { // SELECT ALL
            names.selectAll();
            changeMenu(&nameListMenu);
        });
        addMenuNode(&nameListMenu, D_DESELECT_ALL, [this]() { // DESELECT ALL
            names.deselectAll();
            changeMenu(&nameListMenu);
        });
        addMenuNode(&nameListMenu, D_REMOVE_ALL, [this]() { // REMOVE ALL
            names.removeAll();
            goBack();
        });
    });

    // SSID LIST MENU
    createMenu(&ssidListMenu, &showMenu, [this]() {
        addMenuNode(&ssidListMenu, D_CLONE_APS, [this]() { // CLONE APs
            ssids.cloneSelected(true);
            changeMenu(&ssidListMenu);
            ssids.save(false);
        });
        addMenuNode(&ssidListMenu, [this]() {
            return b2a(ssids.getRandom()) + str(D_RANDOM_MODE); // *RANDOM MODE
        }, [this]() {
            if (ssids.getRandom()) ssids.disableRandom();
            else ssids.enableRandom(10);
            changeMenu(&ssidListMenu);
        });

        // add ssids to list
        int c = ssids.count();

        for (int i = 0; i < c; i++) {
            addMenuNode(&ssidListMenu, [i]() {
                return ssids.getName(i).substring(0, ssids.getLen(i));
            }, [this, i]() {
                selectedID = i;
                changeMenu(&ssidMenu);
            }, [this, i]() {
                ssids.remove(i);
                changeMenu(&ssidListMenu);
                ssidListMenu.selected = i;
            });
        }

        addMenuNode(&ssidListMenu, D_REMOVE_ALL, [this]() { // REMOVE ALL
            ssids.removeAll();
            goBack();
        });
    });

    // AP MENU
    createMenu(&apMenu, &apListMenu, [this]() {
        addMenuNode(&apMenu, [this]() {
            return accesspoints.getSelectedStr(selectedID)  + accesspoints.getSSID(selectedID); // *<ssid>
        }, [this]() {
            accesspoints.getSelected(selectedID) ? accesspoints.deselect(selectedID) : accesspoints.select(selectedID);
        });
        addMenuNode(&apMenu, [this]() {
            return str(D_ENCRYPTION) + accesspoints.getEncStr(selectedID);
        }, NULL);                                                                          // Encryption: -/WPA2
        addMenuNode(&apMenu, [this]() {
            return str(D_RSSI) + (String)accesspoints.getRSSI(selectedID);
        }, NULL);                                                                          // RSSI: -90
        addMenuNode(&apMenu, [this]() {
            return str(D_CHANNEL) + (String)accesspoints.getCh(selectedID);
        }, NULL);                                                                          // Channel: 11
        addMenuNode(&apMenu, [this]() {
            return accesspoints.getMacStr(selectedID);
        }, NULL);                                                                          // 00:11:22:00:11:22
        addMenuNode(&apMenu, [this]() {
            return str(D_VENDOR) + accesspoints.getVendorStr(selectedID);
        }, NULL);                                                                          // Vendor: INTEL
        addMenuNode(&apMenu, [this]() {
            return accesspoints.getSelected(selectedID) ? str(D_DESELECT) : str(D_SELECT); // SELECT/DESELECT
        }, [this]() {
            accesspoints.getSelected(selectedID) ? accesspoints.deselect(selectedID) : accesspoints.select(selectedID);
        });
        addMenuNode(&apMenu, D_CLONE, [this]() { // CLONE
            ssids.add(accesspoints.getSSID(selectedID), accesspoints.getEnc(selectedID) != ENC_TYPE_NONE, 60, true);
            changeMenu(&showMenu);
            ssids.save(false);
        });
        addMenuNode(&apMenu, D_REMOVE, [this]() { // REMOVE
            accesspoints.remove(selectedID);
            apListMenu.list->remove(apListMenu.selected);
            goBack();
        });
    });

    // STATION MENU
    createMenu(&stationMenu, &stationListMenu, [this]() {
        addMenuNode(&stationMenu, [this]() {
            return stations.getSelectedStr(selectedID) +
            (stations.hasName(selectedID) ? stations.getNameStr(selectedID) : stations.getMacVendorStr(selectedID)); // <station
            // name>
        }, [this]() {
            stations.getSelected(selectedID) ? stations.deselect(selectedID) : stations.select(selectedID);
        });
        addMenuNode(&stationMenu, [this]() {
            return stations.getMacStr(selectedID);
        }, NULL);                                             // 00:11:22:00:11:22
        addMenuNode(&stationMenu, [this]() {
            return str(D_VENDOR) + stations.getVendorStr(selectedID);
        }, NULL);                                             // Vendor: INTEL
        addMenuNode(&stationMenu, [this]() {
            return str(D_AP) + stations.getAPStr(selectedID); // AP: someAP
        }, [this]() {
            int apID = stations.getAP(selectedID);

            if (apID >= 0) {
                selectedID = apID;
                changeMenu(&apMenu);
            }
        });
        addMenuNode(&stationMenu, [this]() {
            return str(D_PKTS) + String(*stations.getPkts(selectedID));
        }, NULL);                                                                      // Pkts: 12
        addMenuNode(&stationMenu, [this]() {
            return str(D_CHANNEL) + String(stations.getCh(selectedID));
        }, NULL);                                                                      // Channel: 11
        addMenuNode(&stationMenu, [this]() {
            return str(D_SEEN) + stations.getTimeStr(selectedID);
        }, NULL);                                                                      // Seen: <1min

        addMenuNode(&stationMenu, [this]() {
            return stations.getSelected(selectedID) ? str(D_DESELECT) : str(D_SELECT); // SELECT/DESELECT
        }, [this]() {
            stations.getSelected(selectedID) ? stations.deselect(selectedID) : stations.select(selectedID);
        });
        addMenuNode(&stationMenu, D_REMOVE, [this]() { // REMOVE
            stations.remove(selectedID);
            stationListMenu.list->remove(stationListMenu.selected);
            goBack();
        });
    });

    // NAME MENU
    createMenu(&nameMenu, &nameListMenu, [this]() {
        addMenuNode(&nameMenu, [this]() {
            return names.getSelectedStr(selectedID) + names.getName(selectedID); // <station name>
        }, [this]() {
            names.getSelected(selectedID) ? names.deselect(selectedID) : names.select(selectedID);
        });
        addMenuNode(&nameMenu, [this]() {
            return names.getMacStr(selectedID);
        }, NULL);                                                                   // 00:11:22:00:11:22
        addMenuNode(&nameMenu, [this]() {
            return str(D_VENDOR) + names.getVendorStr(selectedID);
        }, NULL);                                                                   // Vendor: INTEL
        addMenuNode(&nameMenu, [this]() {
            return str(D_AP) + names.getBssidStr(selectedID);
        }, NULL);                                                                   // AP: 00:11:22:00:11:22
        addMenuNode(&nameMenu, [this]() {
            return str(D_CHANNEL) + (String)names.getCh(selectedID);
        }, NULL);                                                                   // Channel: 11

        addMenuNode(&nameMenu, [this]() {
            return names.getSelected(selectedID) ? str(D_DESELECT) : str(D_SELECT); // SELECT/DESELECT
        }, [this]() {
            names.getSelected(selectedID) ? names.deselect(selectedID) : names.select(selectedID);
        });
        addMenuNode(&nameMenu, D_REMOVE, [this]() { // REMOVE
            names.remove(selectedID);
            nameListMenu.list->remove(nameListMenu.selected);
            goBack();
        });
    });

    // SSID MENU
    createMenu(&ssidMenu, &ssidListMenu, [this]() {
        addMenuNode(&ssidMenu, [this]() {
            return ssids.getName(selectedID).substring(0, ssids.getLen(selectedID));
        }, NULL);                                                   // SSID
        addMenuNode(&ssidMenu, [this]() {
            return str(D_ENCRYPTION) + ssids.getEncStr(selectedID); // WPA2
        }, [this]() {
            ssids.setWPA2(selectedID, !ssids.getWPA2(selectedID));
        });
        addMenuNode(&ssidMenu, D_REMOVE, [this]() { // REMOVE
            ssids.remove(selectedID);
            ssidListMenu.list->remove(ssidListMenu.selected);
            goBack();
        });
    });

    // ATTACK MENU
    createMenu(&attackMenu, &mainMenu, [this]() {
        auto restartAttack = [this]() {
            attack.start(beaconSelected, deauthSelected, false, probeSelected, capadSelected, namemeSelected, true,
                         settings::getAttackSettings().timeout * 1000);
        };
        auto usesPortalTargets = [this]() {
            return (capadSelected || namemeSelected) && (accesspoints.selected() > 0);
        };

        if (wifi::hasNameMeValue()) {
            addMenuNode(&attackMenu, [this]() {
                return left(wifi::getNameMeValue(), maxLen - 1);
            }, []() {});
        }

        addMenuNode(&attackMenu, [this]() { // *DEAUTH 0/0
            if (attack.isRunning()) return leftRight(b2a(deauthSelected) + str(D_DEAUTH),
                                                     (String)attack.getDeauthPkts() + SLASH +
                                                     (String)attack.getDeauthMaxPkts(), maxLen - 1);
            else return leftRight(b2a(deauthSelected) + str(D_DEAUTH), (String)scan.countSelected(), maxLen - 1);
        }, [this, restartAttack]() { // deauth
            deauthSelected = !deauthSelected;

            if (attack.isRunning()) restartAttack();
        });
        addMenuNode(&attackMenu, [this, usesPortalTargets]() { // *BEACON 0/0
            if (attack.isRunning()) return leftRight(b2a(beaconSelected) + str(D_BEACON),
                                                     (String)attack.getBeaconPkts() + SLASH +
                                                     (String)attack.getBeaconMaxPkts(), maxLen - 1);
            else return leftRight(b2a(beaconSelected) + str(D_BEACON),
                                  (String)(usesPortalTargets() ? accesspoints.selected() : ssids.count()),
                                  maxLen - 1);
        }, [this, restartAttack]() { // beacon
            beaconSelected = !beaconSelected;

            if (attack.isRunning()) restartAttack();
        });
        addMenuNode(&attackMenu, [this, usesPortalTargets]() { // *PROBE 0/0
            if (attack.isRunning()) return leftRight(b2a(probeSelected) + str(D_PROBE),
                                                     (String)attack.getProbePkts() + SLASH +
                                                     (String)attack.getProbeMaxPkts(), maxLen - 1);
            else return leftRight(b2a(probeSelected) + str(D_PROBE),
                                  (String)(usesPortalTargets() ? accesspoints.selected() : ssids.count()),
                                  maxLen - 1);
        }, [this, restartAttack]() { // probe
            probeSelected = !probeSelected;

            if (attack.isRunning()) restartAttack();
        });
        addMenuNode(&attackMenu, [this]() { // AUTOSCAN
            return leftRight(scan.isAutoScanActive() ? str(D_SCANNING) : str(D_AUTOSCAN),
                             String(accesspoints.count()), maxLen - 1);
        }, [this]() {
            handleAutoScanMenuClick();
        });
        addMenuNode(&attackMenu, [this]() { // *NAMEME
            return leftRight(b2a(namemeSelected) + str(D_NAMEME), (String)accesspoints.selected(), maxLen - 1);
        }, [this, restartAttack]() { // nameme
            namemeSelected = !namemeSelected;

            if (namemeSelected) capadSelected = false;
            if (attack.isRunning()) restartAttack();
        });
        addMenuNode(&attackMenu, [this]() { // *CAPAD
            return leftRight(b2a(capadSelected) + str(D_CAPAD), (String)accesspoints.selected(), maxLen - 1);
        }, [this, restartAttack]() { // capad
            capadSelected = !capadSelected;

            if (capadSelected) namemeSelected = false;
            if (attack.isRunning()) restartAttack();
        });
        addMenuNode(&attackMenu, [this]() { // START
            return leftRight(str(attack.isRunning() ? D_STOP_ATTACK : D_START_ATTACK),
                             attack.getPacketRate() > 0 ? (String)attack.getPacketRate() : String(), maxLen - 1);
        }, [this, restartAttack]() {
            if (attack.isRunning()) attack.stop();
            else restartAttack();
        });
    });

    // CLOCK MENU
    createMenu(&clockMenu, &mainMenu, [this]() {
        addMenuNode(&clockMenu, D_TIME, &timeMenu);
        addMenuNode(&clockMenu, D_STOPWATCH, &stopwatchMenu);
        addMenuNode(&clockMenu, D_TIMER, &timerMenu);
    });

    createMenu(&timeMenu, &clockMenu, [this]() {
        addMenuNode(&timeMenu, D_DISPLAY, [this]() {
            openClockDisplay(CLOCK_ITEM::TIME);
        });
        addMenuNode(&timeMenu, D_VALUE, [this]() {
            openClockValueEditor(CLOCK_ITEM::TIME);
        });
        addMenuNode(&timeMenu, D_SET, [this]() {
            setMainClockItem(CLOCK_ITEM::TIME);
        });
    });

    createMenu(&stopwatchMenu, &clockMenu, [this]() {
        addMenuNode(&stopwatchMenu, D_DISPLAY, [this]() {
            openClockDisplay(CLOCK_ITEM::STOPWATCH);
        });
        addMenuNode(&stopwatchMenu, D_VALUE, [this]() {
            openClockValueEditor(CLOCK_ITEM::STOPWATCH);
        });
        addMenuNode(&stopwatchMenu, D_SET, [this]() {
            setMainClockItem(CLOCK_ITEM::STOPWATCH);
        });
    });

    createMenu(&timerMenu, &clockMenu, [this]() {
        addMenuNode(&timerMenu, D_DISPLAY, [this]() {
            openClockDisplay(CLOCK_ITEM::TIMER);
        });
        addMenuNode(&timerMenu, D_VALUE, [this]() {
            openClockValueEditor(CLOCK_ITEM::TIMER);
        });
        addMenuNode(&timerMenu, D_SET, [this]() {
            setMainClockItem(CLOCK_ITEM::TIMER);
        });
    });

    // ===================== //

    // set current menu to main menu
    changeMenu(&mainMenu);
    clockTime           = currentTime;
    stopwatchLastUpdate = currentTime;
    timerLastUpdate     = currentTime;
    enabled   = true;
    startTime = currentTime;
}

#ifdef HIGHLIGHT_LED
void DisplayUI::setupLED() {
    pinMode(HIGHLIGHT_LED, OUTPUT);
    digitalWrite(HIGHLIGHT_LED, HIGH);
    highlightLED = true;
}

#endif // ifdef HIGHLIGHT_LED

void DisplayUI::update(bool force) {
    if (!enabled) return;
    if (!currentMenu) changeMenu(&mainMenu);

    up->update();
    down->update();
    a->update();
    b->update();
    updateAutoScanMenuAction();
    updateAPTrackerStopAction();

    if (mode == DISPLAY_MODE::INTRO) {
        if (currentTime - startTime >= screenIntroTime) mode = DISPLAY_MODE::MENU;
    } else {
        updateClockRuntime();
    }

    draw(force);

    uint32_t timeout = settings::getDisplaySettings().timeout * 1000;

    if (currentTime > timeout) {
        if (!tempOff) {
            if (buttonTime < currentTime - timeout) off();
        } else {
            if (buttonTime > currentTime - timeout) on();
        }
    }
}

void DisplayUI::on() {
    if (enabled) {
        configOn();
        tempOff    = false;
        buttonTime = currentTime; // update a button time to keep display on
        prntln(D_MSG_DISPLAY_ON);
    } else {
        prntln(D_ERROR_NOT_ENABLED);
    }
}

void DisplayUI::off() {
    if (enabled) {
        configOff();
        tempOff = true;
        prntln(D_MSG_DISPLAY_OFF);
    } else {
        prntln(D_ERROR_NOT_ENABLED);
    }
}

void DisplayUI::showIntro() {
    cancelAutoScanMenuAction();
    cancelAPTrackerStopAction();
    startTime  = currentTime;
    drawTime   = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;
    mode       = DISPLAY_MODE::INTRO;
}

void DisplayUI::setupButtons() {
    up   = new ButtonPullup(BUTTON_UP);
    down = new ButtonPullup(BUTTON_DOWN);
    a    = new ButtonPullup(BUTTON_A);
    b    = new ButtonPullup(BUTTON_B);

    // === BUTTON UP === //
    up->setOnClicked([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        cancelAutoScanMenuAction();
        cancelAPTrackerStopAction();

        if (!tempOff) {
            if (mode == DISPLAY_MODE::MENU) {                 // when in menu, go up or down with cursor
                if (currentMenu->selected > 0) currentMenu->selected--;
                else currentMenu->selected = currentMenu->list->size() - 1;
            } else if (mode == DISPLAY_MODE::AUTOSCAN_VIEW) {
                if (accesspoints.count() > 0) {
                    if (autoScanRow > 0) autoScanRow--;
                    else autoScanRow = accesspoints.count() - 1;
                }
            } else if (mode == DISPLAY_MODE::APTRACKER) {
                if (scan.getTrackerAccesspointCount() > 0) {
                    if (trackerRow > 0) trackerRow--;
                    else trackerRow = scan.getTrackerAccesspointCount() - 1;
                }
            } else if (mode == DISPLAY_MODE::PACKETMONITOR) { // when in packet monitor, change channel
                scan.setChannel(wifi_channel + 1);
            } else if (mode == DISPLAY_MODE::CLOCK) {         // when in clock, change value
                adjustClockValue(1);
            }
        }
    });

    up->setOnHolding([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        cancelAutoScanMenuAction();
        cancelAPTrackerStopAction();
        if (!tempOff) {
            if (mode == DISPLAY_MODE::MENU) {                 // when in menu, go up or down with cursor
                if (currentMenu->selected > 0) currentMenu->selected--;
                else currentMenu->selected = currentMenu->list->size() - 1;
            } else if (mode == DISPLAY_MODE::AUTOSCAN_VIEW) {
                if (accesspoints.count() > 0) {
                    if (autoScanRow > 0) autoScanRow--;
                    else autoScanRow = accesspoints.count() - 1;
                }
            } else if (mode == DISPLAY_MODE::APTRACKER) {
                if (scan.getTrackerAccesspointCount() > 0) {
                    if (trackerRow > 0) trackerRow--;
                    else trackerRow = scan.getTrackerAccesspointCount() - 1;
                }
            } else if (mode == DISPLAY_MODE::PACKETMONITOR) { // when in packet monitor, change channel
                scan.setChannel(wifi_channel + 1);
            } else if (mode == DISPLAY_MODE::CLOCK) {         // when in clock, change value
                adjustClockValue(10);
            }
        }
    }, buttonDelay);

    // === BUTTON DOWN === //
    down->setOnClicked([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        cancelAutoScanMenuAction();
        cancelAPTrackerStopAction();
        if (!tempOff) {
            if (mode == DISPLAY_MODE::MENU) {                 // when in menu, go up or down with cursor
                if (currentMenu->selected < currentMenu->list->size() - 1) currentMenu->selected++;
                else currentMenu->selected = 0;
            } else if (mode == DISPLAY_MODE::AUTOSCAN_VIEW) {
                if (accesspoints.count() > 0) {
                    if (autoScanRow < accesspoints.count() - 1) autoScanRow++;
                    else autoScanRow = 0;
                }
            } else if (mode == DISPLAY_MODE::APTRACKER) {
                if (scan.getTrackerAccesspointCount() > 0) {
                    if (trackerRow < scan.getTrackerAccesspointCount() - 1) trackerRow++;
                    else trackerRow = 0;
                }
            } else if (mode == DISPLAY_MODE::PACKETMONITOR) { // when in packet monitor, change channel
                scan.setChannel(wifi_channel - 1);
            } else if (mode == DISPLAY_MODE::CLOCK) {         // when in clock, change value
                adjustClockValue(-1);
            }
        }
    });

    down->setOnHolding([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        cancelAutoScanMenuAction();
        cancelAPTrackerStopAction();
        if (!tempOff) {
            if (mode == DISPLAY_MODE::MENU) {                 // when in menu, go up or down with cursor
                if (currentMenu->selected < currentMenu->list->size() - 1) currentMenu->selected++;
                else currentMenu->selected = 0;
            } else if (mode == DISPLAY_MODE::AUTOSCAN_VIEW) {
                if (accesspoints.count() > 0) {
                    if (autoScanRow < accesspoints.count() - 1) autoScanRow++;
                    else autoScanRow = 0;
                }
            } else if (mode == DISPLAY_MODE::APTRACKER) {
                if (scan.getTrackerAccesspointCount() > 0) {
                    if (trackerRow < scan.getTrackerAccesspointCount() - 1) trackerRow++;
                    else trackerRow = 0;
                }
            } else if (mode == DISPLAY_MODE::PACKETMONITOR) { // when in packet monitor, change channel
                scan.setChannel(wifi_channel - 1);
            }

            else if (mode == DISPLAY_MODE::CLOCK) {           // when in clock, change value
                adjustClockValue(-10);
            }
        }
    }, buttonDelay);

    // === BUTTON A === //
    a->setOnClicked([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        if (!tempOff) {
            switch (mode) {
                case DISPLAY_MODE::MENU:

                    if (currentMenu->list->get(currentMenu->selected).click) {
                        currentMenu->list->get(currentMenu->selected).click();
                    }
                    break;

                case DISPLAY_MODE::AUTOSCAN_VIEW:
                    closeAutoScanView();
                    break;

                case DISPLAY_MODE::APTRACKER:
                    handleAPTrackerStopClick();
                    break;

                case DISPLAY_MODE::PACKETMONITOR:
                case DISPLAY_MODE::APSTMONITOR:
                case DISPLAY_MODE::LOADSCAN:
                    if ((mode == DISPLAY_MODE::PACKETMONITOR) || (mode == DISPLAY_MODE::APSTMONITOR) || !scan.isAutoScanActive()) scan.stop();
                    mode = DISPLAY_MODE::MENU;
                    break;

                case DISPLAY_MODE::CLOCK:
                    if (clockEditField < 2) {
                        clockEditField++;
                    } else {
                        clockEditField = 0;
                        mode = DISPLAY_MODE::MENU;
                    }
                    break;

                case DISPLAY_MODE::CLOCK_DISPLAY:
                    mode = DISPLAY_MODE::MENU;
                    break;
            }
        }
    });

    a->setOnHolding([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        if (!tempOff) {
            if (mode == DISPLAY_MODE::MENU) {
                if (currentMenu->list->get(currentMenu->selected).hold) {
                    currentMenu->list->get(currentMenu->selected).hold();
                }
            }
        }
    }, 800);

    // === BUTTON B === //
    b->setOnClicked([this]() {
        scrollCounter = 0;
        scrollTime    = currentTime;
        buttonTime    = currentTime;
        if (!tempOff) {
            switch (mode) {
                case DISPLAY_MODE::MENU:
                    cancelAutoScanMenuAction();
                    goBack();
                    break;

                case DISPLAY_MODE::AUTOSCAN_VIEW:
                    closeAutoScanView();
                    break;

                case DISPLAY_MODE::APTRACKER:
                    handleAPTrackerStopClick();
                    break;

                case DISPLAY_MODE::PACKETMONITOR:
                case DISPLAY_MODE::APSTMONITOR:
                case DISPLAY_MODE::LOADSCAN:
                    if ((mode == DISPLAY_MODE::PACKETMONITOR) || (mode == DISPLAY_MODE::APSTMONITOR) || !scan.isAutoScanActive()) scan.stop();
                    mode = DISPLAY_MODE::MENU;
                    break;

                case DISPLAY_MODE::CLOCK:
                case DISPLAY_MODE::CLOCK_DISPLAY:
                    clockEditField = 0;
                    mode = DISPLAY_MODE::MENU;
                    break;
            }
        }
    });
}

String DisplayUI::getChannel() {
    String ch = String(wifi_channel);

    if (ch.length() < 2) ch = ' ' + ch;
    return ch;
}

void DisplayUI::draw(bool force) {
    if (force || ((currentTime - drawTime > drawInterval) && currentMenu)) {
        drawTime = currentTime;

        updatePrefix();

        switch (mode) {
            case DISPLAY_MODE::BUTTON_TEST:
                drawButtonTest();
                break;

            case DISPLAY_MODE::MENU:
                drawMenu();
                break;

            case DISPLAY_MODE::LOADSCAN:
                drawLoadingScan();
                break;

            case DISPLAY_MODE::AUTOSCAN_VIEW:
                drawAutoScanView();
                break;

            case DISPLAY_MODE::PACKETMONITOR:
                drawPacketMonitor();
                break;

            case DISPLAY_MODE::APSTMONITOR:
                drawAPSTMonitor();
                break;

            case DISPLAY_MODE::APTRACKER:
                drawAPTracker();
                break;

            case DISPLAY_MODE::INTRO:
                drawIntro();
                break;
            case DISPLAY_MODE::CLOCK:
            case DISPLAY_MODE::CLOCK_DISPLAY:
                drawClock();
                break;
            case DISPLAY_MODE::RESETTING:
                drawResetting();
                break;
        }

        updateSuffix();
    }
}

void DisplayUI::drawButtonTest() {
    drawString(0, str(D_UP) + b2s(up->read()));
    drawString(1, str(D_DOWN) + b2s(down->read()));
    drawString(2, str(D_A) + b2s(a->read()));
    drawString(3, str(D_B) + b2s(b->read()));
}

void DisplayUI::drawMenu() {
    bool compactMenu = (currentMenu == &mainMenu) || (currentMenu == &scanMenu) || (currentMenu == &showMenu) ||
                       (currentMenu == &namemeListMenu);
    int  rowsPerPage = compactMenu ? 6 : 5;
    int  rowHeight   = compactMenu ? 10 : 12;

    display.setFont(compactMenu ? ArialMT_Plain_10 : DejaVu_Sans_Mono_12);

    String tmp;
    int    tmpLen;
    int    row = (currentMenu->selected / rowsPerPage) * rowsPerPage;

    // correct selected if it's off
    if (currentMenu->selected < 0) currentMenu->selected = 0;
    else if (currentMenu->selected >= currentMenu->list->size()) currentMenu->selected = currentMenu->list->size() - 1;

    // draw menu entries
    for (int i = row; i < currentMenu->list->size() && i < row + rowsPerPage; i++) {
        tmp    = currentMenu->list->get(i).getStr();
        tmpLen = tmp.length();

        // horizontal scrolling
        if ((currentMenu->selected == i) && (tmpLen >= maxLen)) {
            tmp = tmp + tmp;
            tmp = tmp.substring(scrollCounter, scrollCounter + maxLen - 1);

            if (((scrollCounter > 0) && (scrollTime < currentTime - scrollSpeed)) || ((scrollCounter == 0) && (scrollTime < currentTime - scrollSpeed * 4))) {
                scrollTime = currentTime;
                scrollCounter++;
            }

            if (scrollCounter > tmpLen) scrollCounter = 0;
        }

        tmp = (currentMenu->selected == i ? CURSOR : SPACE) + tmp;
        drawString(0, (i - row) * rowHeight, tmp);
    }
}

void DisplayUI::drawLoadingScan() {
    String percentage;

    if (scan.isScanning()) {
        percentage = String(scan.getPercentage()) + '%';
    } else {
        percentage = str(DSP_SCAN_DONE);
    }

    drawString(0, leftRight(str(DSP_SCAN_FOR), scan.getMode(), maxLen));
    drawString(1, leftRight(str(DSP_APS), String(accesspoints.count()), maxLen));
    drawString(2, leftRight(str(DSP_STS), String(stations.count()), maxLen));
    drawString(3, leftRight(str(DSP_PKTS), String(scan.getPacketRate()) + str(DSP_S), maxLen));
    drawString(4, center(percentage, maxLen));
}

void DisplayUI::drawAutoScanView() {
    display.setFont(ArialMT_Plain_10);

    int count = accesspoints.count();
    int rowsPerPage = 5;
    int rowHeight = 10;

    if (count <= 0) autoScanRow = 0;
    else if (autoScanRow >= count) autoScanRow = count - 1;
    else if (autoScanRow < 0) autoScanRow = 0;

    drawString(0, leftRight(scan.isAutoScanActive() ? str(D_SCANNING) : str(D_AUTOSCAN), String(count), maxLen));

    if (count <= 0) {
        drawString(2, center(String(F("Scanning APs")), maxLen));
        return;
    }

    int row = (autoScanRow / rowsPerPage) * rowsPerPage;

    for (int i = row; i < count && i < row + rowsPerPage; i++) {
        String tmp = accesspoints.getSSID(i);
        int    tmpLen = tmp.length();

        if ((autoScanRow == i) && (tmpLen >= maxLen)) {
            tmp = tmp + tmp;
            tmp = tmp.substring(scrollCounter, scrollCounter + maxLen - 1);

            if (((scrollCounter > 0) && (scrollTime < currentTime - scrollSpeed)) ||
                ((scrollCounter == 0) && (scrollTime < currentTime - scrollSpeed * 4))) {
                scrollTime = currentTime;
                scrollCounter++;
            }

            if (scrollCounter > tmpLen) scrollCounter = 0;
        }

        tmp = (autoScanRow == i ? CURSOR : SPACE) + tmp;
        drawString(0, (i - row + 1) * rowHeight, tmp);
    }
}

void DisplayUI::drawPacketMonitor() {
    double scale = scan.getScaleFactor(sreenHeight - lineHeight - 2);

    String headline = leftRight(str(D_CH) + getChannel() + String(' ') + String('[') + String(scan.deauths) + String(']'), String(scan.getPacketRate()) + str(D_PKTS), maxLen);

    drawString(0, 0, headline);

    if (scan.getMaxPacket() > 0) {
        int i = 0;
        int x = 0;
        int y = 0;

        while (i < SCAN_PACKET_LIST_SIZE && x < screenWidth) {
            y = (sreenHeight-1) - (scan.getPackets(i) * scale);
            i++;

            // Serial.printf("%d,%d -> %d,%d\n", x, (sreenHeight-1), x, y);
            drawLine(x, (sreenHeight-1), x, y);
            x++;

            // Serial.printf("%d,%d -> %d,%d\n", x, (sreenHeight-1), x, y);
            drawLine(x, (sreenHeight-1), x, y);
            x++;
        }
        // Serial.println("---------");
    }
}

void DisplayUI::drawAPSTMonitor() {
    display.setFont(ArialMT_Plain_10);
    updateAPSTMonitorHistory();

    String headline = leftRight(String(F("AP [")) + String(scan.getMonitorAccesspointCount()) + ']',
                                String(F("ST [")) + String(scan.getMonitorStationCount()) + ']',
                                maxLen);

    drawString(0, 0, headline);

    uint16_t maxValue = 1;

    for (uint8_t i = 0; i < SCAN_PACKET_LIST_SIZE; i++) {
        if (apMonitorHistory[i] > maxValue) maxValue = apMonitorHistory[i];
        if (stMonitorHistory[i] > maxValue) maxValue = stMonitorHistory[i];
    }

    int graphTop    = lineHeight + 2;
    int graphBottom = sreenHeight - 1;

    drawGraphLine(stMonitorHistory, maxValue, graphTop, graphBottom, true);
    drawGraphLine(apMonitorHistory, maxValue, graphTop, graphBottom, false);
}

void DisplayUI::drawAPTracker() {
    display.setFont(ArialMT_Plain_10);

    int count       = scan.getTrackerAccesspointCount();
    int rowsPerPage = 5;
    int rowHeight   = 10;

    if (count <= 0) trackerRow = 0;
    else if (trackerRow >= count) trackerRow = count - 1;
    else if (trackerRow < 0) trackerRow = 0;

    drawString(0, leftRight(String(F("APs [")) + String(count) + ']',
                            String(F("PKTs [")) + String(scan.getTrackerPacketCount()) + ']',
                            maxLen));

    if (count <= 0) {
        drawString(2, center(String(F("Tracking APs")), maxLen));
        return;
    }

    int row = (trackerRow / rowsPerPage) * rowsPerPage;

    for (int i = row; i < count && i < row + rowsPerPage; i++) {
        String ssid = scan.getTrackerSSID(i);
        String line = ssid + ' ' + String(scan.getTrackerRSSI(i)) + String(F(" dBm"));
        int tmpLen  = line.length();

        if ((trackerRow == i) && (tmpLen >= maxLen - 1)) {
            line = line + line;
            line = line.substring(scrollCounter, scrollCounter + maxLen - 2);

            if (((scrollCounter > 0) && (scrollTime < currentTime - scrollSpeed)) ||
                ((scrollCounter == 0) && (scrollTime < currentTime - scrollSpeed * 4))) {
                scrollTime = currentTime;
                scrollCounter++;
            }

            if (scrollCounter > tmpLen) scrollCounter = 0;
        }
        else if (tmpLen >= maxLen - 1) {
            line = line.substring(0, maxLen - 2);
        }

        line = (trackerRow == i ? CURSOR : SPACE) + line;
        int y = (i - row + 1) * rowHeight;

        drawString(0, y, line);
        drawTrackerArrow(screenWidth - 8, y + 3, scan.getTrackerTrend(i));
    }
}

void DisplayUI::updateClockRuntime() {
    bool editingTime      = (mode == DISPLAY_MODE::CLOCK) && (selectedClockItem == CLOCK_ITEM::TIME);
    bool editingStopwatch = (mode == DISPLAY_MODE::CLOCK) && (selectedClockItem == CLOCK_ITEM::STOPWATCH);
    bool editingTimer     = (mode == DISPLAY_MODE::CLOCK) && (selectedClockItem == CLOCK_ITEM::TIMER);

#ifdef RTC_DS3231
    if (!editingTime) {
        bool h12;
        bool PM_time;
        clockHour   = clock.getHour(h12, PM_time);
        clockMinute = clock.getMinute();
        clockSecond = clock.getSecond();
    }
#else // ifdef RTC_DS3231
    if (!editingTime) {
        while (currentTime - clockTime >= 1000) {
            setTime(clockHour, clockMinute, clockSecond + 1);
            clockTime += 1000;
        }
    } else {
        clockTime = currentTime;
    }
#endif // ifdef RTC_DS3231

    if (stopwatchLastUpdate == 0) stopwatchLastUpdate = currentTime;
    if (!editingStopwatch) {
        stopwatchValue += currentTime - stopwatchLastUpdate;
    }
    stopwatchLastUpdate = currentTime;

    if (timerLastUpdate == 0) timerLastUpdate = currentTime;
    if (!editingTimer && (timerValue > 0)) {
        uint32_t delta = currentTime - timerLastUpdate;

        if (delta >= timerValue) timerValue = 0;
        else timerValue -= delta;
    }
    timerLastUpdate = currentTime;
}

void DisplayUI::drawClockItem(String title, String value, bool editing) {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    drawString(0, leftRight(title, editing ? str(D_VALUE) : str(D_DISPLAY), maxLen));

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(screenWidth / 2, 20, value);

    if (editing) {
        display.setFont(ArialMT_Plain_10);
        display.drawString(screenWidth / 2, 52, getClockEditFieldLabel());
    }
}

String DisplayUI::getClockItemLabel(CLOCK_ITEM item) {
    switch (item) {
        case CLOCK_ITEM::TIME:
            return str(D_TIME);

        case CLOCK_ITEM::STOPWATCH:
            return str(D_STOPWATCH);

        case CLOCK_ITEM::TIMER:
            return str(D_TIMER);

        default:
            return str(D_CLOCK);
    }
}

String DisplayUI::getClockDisplayValue(CLOCK_ITEM item, bool compact) {
    switch (item) {
        case CLOCK_ITEM::TIME:
            return formatTimeValue(compact);

        case CLOCK_ITEM::STOPWATCH:
            return formatDurationValue(stopwatchValue, compact);

        case CLOCK_ITEM::TIMER:
            return formatDurationValue(timerValue, compact);

        default:
            return str(D_CLOCK);
    }
}

String DisplayUI::getMainClockLabel() {
    if (mainClockItem == CLOCK_ITEM::NONE) return str(D_CLOCK);
    return getClockDisplayValue(mainClockItem, true);
}

String DisplayUI::formatTimeValue(bool compact) {
    String value = String(clockHour);

    value += ':';
    value += padTime(clockMinute);

    if (!compact) {
        value += ':';
        value += padTime(clockSecond);
    }

    return value;
}

String DisplayUI::formatDurationValue(uint32_t value, bool compact) {
    uint32_t totalSeconds = value / 1000;
    uint32_t hours        = totalSeconds / 3600;
    uint32_t minutes      = (totalSeconds / 60) % 60;
    uint32_t seconds      = totalSeconds % 60;

    if (compact && (hours == 0)) {
        return String(totalSeconds / 60) + ':' + padTime(seconds);
    }

    String output = String(hours);

    output += ':';
    output += padTime(minutes);
    output += ':';
    output += padTime(seconds);
    return output;
}

String DisplayUI::padTime(int value) {
    if (value < 10) return String('0') + String(value);
    return String(value);
}

String DisplayUI::getClockEditFieldLabel() {
    switch (clockEditField) {
        case 0:
            return String(F("HOUR"));

        case 1:
            return String(F("MINUTE"));

        default:
            return String(F("SECOND"));
    }
}

void DisplayUI::openClockDisplay(CLOCK_ITEM item) {
    selectedClockItem = item;
    clockEditField    = 0;
    mode              = DISPLAY_MODE::CLOCK_DISPLAY;
}

void DisplayUI::openClockValueEditor(CLOCK_ITEM item) {
    selectedClockItem = item;
    clockEditField    = 0;
    mode              = DISPLAY_MODE::CLOCK;
}

void DisplayUI::setMainClockItem(CLOCK_ITEM item) {
    mainClockItem = item;
}

void DisplayUI::adjustClockValue(int step) {
    int fieldStep = step;

    if ((clockEditField == 0) && (fieldStep > 1)) fieldStep = 1;
    if ((clockEditField == 0) && (fieldStep < -1)) fieldStep = -1;

    if (selectedClockItem == CLOCK_ITEM::TIME) {
        if (clockEditField == 0) setTime(clockHour + fieldStep, clockMinute, clockSecond);
        else if (clockEditField == 1) setTime(clockHour, clockMinute + fieldStep, clockSecond);
        else setTime(clockHour, clockMinute, clockSecond + fieldStep);

        clockTime = currentTime;
        return;
    }

    uint32_t amount = (clockEditField == 0) ? 3600000UL : ((clockEditField == 1) ? 60000UL : 1000UL);
    uint32_t delta  = amount * (uint32_t)abs(fieldStep);
    uint32_t* value = (selectedClockItem == CLOCK_ITEM::STOPWATCH) ? &stopwatchValue : &timerValue;

    if (fieldStep >= 0) {
        *value += delta;
    } else if (*value > delta) {
        *value -= delta;
    } else {
        *value = 0;
    }

    if (selectedClockItem == CLOCK_ITEM::STOPWATCH) stopwatchLastUpdate = currentTime;
    else timerLastUpdate = currentTime;
}

void DisplayUI::drawIntro() {
    drawString(0, center(str(D_INTRO_0), maxLen));
    drawString(1, center(str(D_INTRO_1), maxLen));
    drawString(2, center(str(D_INTRO_2), maxLen));
    drawString(3, center(DEAUTHER_VERSION, maxLen));

}

void DisplayUI::drawClock() {
    drawClockItem(getClockItemLabel(selectedClockItem), getClockDisplayValue(selectedClockItem, false), mode == DISPLAY_MODE::CLOCK);
}

void DisplayUI::drawResetting() {
    drawString(2, center(str(D_RESETTING), maxLen));
}

void DisplayUI::clearMenu(Menu* menu) {
    while (menu->list->size() > 0) {
        menu->list->remove(0);
    }
}

void DisplayUI::changeMenu(Menu* menu) {
    if (menu) {
        // only open list menu if it has nodes
        if (((menu == &apListMenu) && (accesspoints.count() == 0))) {
            return;
        }

        if (currentMenu) clearMenu(currentMenu);
        currentMenu           = menu;
        currentMenu->selected = 0;
        buttonTime            = currentTime;

        if (selectedID < 0) selectedID = 0;

        if (currentMenu->parentMenu) {
            addMenuNode(currentMenu, D_BACK, currentMenu->parentMenu); // add [BACK]
            currentMenu->selected = 1;
        }

        if (currentMenu->build) currentMenu->build();
    }
}

void DisplayUI::goBack() {
    if (currentMenu->parentMenu) changeMenu(currentMenu->parentMenu);
}

void DisplayUI::openAutoScanView() {
    scrollCounter = 0;
    scrollTime    = currentTime;
    autoScanRow   = 0;
    mode          = DISPLAY_MODE::AUTOSCAN_VIEW;
}

void DisplayUI::closeAutoScanView() {
    scrollCounter = 0;
    scrollTime    = currentTime;
    mode          = DISPLAY_MODE::MENU;
}

void DisplayUI::startAutoScan() {
    cancelAutoScanMenuAction();
    scan.start(SCAN_MODE_AUTOSCAN, 0, SCAN_MODE_AUTOSCAN, 0, true, wifi_channel);
}

void DisplayUI::startAPSTMonitor() {
    resetAPSTMonitorHistory();
    scan.start(SCAN_MODE_APST_MONITOR, 0, SCAN_MODE_APST_MONITOR, 0, true, wifi_channel);
    mode = DISPLAY_MODE::APSTMONITOR;
}

void DisplayUI::startAPTracker() {
    cancelAutoScanMenuAction();
    cancelAPTrackerStopAction();
    scrollCounter = 0;
    scrollTime    = currentTime;
    trackerRow    = 0;
    scan.start(SCAN_MODE_AP_TRACKER, 0, SCAN_MODE_OFF, 0, true, wifi_channel);
    mode = DISPLAY_MODE::APTRACKER;
}

void DisplayUI::handleAutoScanMenuClick() {
    if (!scan.isAutoScanActive()) {
        startAutoScan();
        openAutoScanView();
        return;
    }

    if (autoScanMenuActionPending && (currentTime - autoScanMenuClickTime <= 1000)) {
        cancelAutoScanMenuAction();
        scan.stop();
        mode = DISPLAY_MODE::MENU;
        return;
    }

    updateAutoScanMenuContext();
    autoScanMenuActionPending = true;
    autoScanMenuClickTime     = currentTime;
}

void DisplayUI::updateAutoScanMenuAction() {
    if (!autoScanMenuActionPending) return;

    if (!scan.isAutoScanActive() || (mode != DISPLAY_MODE::MENU) || !isAutoScanMenuSelected()) {
        cancelAutoScanMenuAction();
        return;
    }

    if (currentTime - autoScanMenuClickTime > 1000) {
        cancelAutoScanMenuAction();
        openAutoScanView();
    }
}

void DisplayUI::cancelAutoScanMenuAction() {
    autoScanMenuActionPending = false;
    autoScanMenuClickTime     = 0;
    autoScanMenuOwner         = NULL;
    autoScanMenuIndex         = 0;
}

bool DisplayUI::isAutoScanMenuSelected() {
    return currentMenu && autoScanMenuOwner && (currentMenu == autoScanMenuOwner) &&
           (currentMenu->selected == autoScanMenuIndex);
}

void DisplayUI::refreshAttackMenu() {
    if (!enabled || (mode != DISPLAY_MODE::MENU) || !currentMenu || (currentMenu != &attackMenu)) return;
    changeMenu(&attackMenu);
}

void DisplayUI::updateAutoScanMenuContext() {
    autoScanMenuOwner = currentMenu;
    autoScanMenuIndex = currentMenu ? currentMenu->selected : 0;
}

void DisplayUI::cancelAPTrackerStopAction() {
    apTrackerStopPending   = false;
    apTrackerStopClickTime = 0;
}

void DisplayUI::handleAPTrackerStopClick() {
    if (!scan.isAPTrackerActive()) {
        cancelAPTrackerStopAction();
        mode = DISPLAY_MODE::MENU;
        return;
    }

    if (apTrackerStopPending && (currentTime - apTrackerStopClickTime <= 1000)) {
        cancelAPTrackerStopAction();
        scan.stop();
        mode = DISPLAY_MODE::MENU;
        return;
    }

    apTrackerStopPending   = true;
    apTrackerStopClickTime = currentTime;
}

void DisplayUI::updateAPTrackerStopAction() {
    if (!apTrackerStopPending) return;

    if ((mode != DISPLAY_MODE::APTRACKER) || !scan.isAPTrackerActive() || (currentTime - apTrackerStopClickTime > 1000)) {
        cancelAPTrackerStopAction();
    }
}

void DisplayUI::resetAPSTMonitorHistory() {
    for (uint8_t i = 0; i < SCAN_PACKET_LIST_SIZE; i++) {
        apMonitorHistory[i] = 0;
        stMonitorHistory[i] = 0;
    }

    apstMonitorSampleTime = currentTime;
}

void DisplayUI::updateAPSTMonitorHistory() {
    const uint16_t sampleInterval = 500;

    if (apstMonitorSampleTime == 0) apstMonitorSampleTime = currentTime;

    while (currentTime - apstMonitorSampleTime >= sampleInterval) {
        for (uint8_t i = 0; i < SCAN_PACKET_LIST_SIZE - 1; i++) {
            apMonitorHistory[i] = apMonitorHistory[i + 1];
            stMonitorHistory[i] = stMonitorHistory[i + 1];
        }

        apMonitorHistory[SCAN_PACKET_LIST_SIZE - 1] = scan.getMonitorAccesspointCount();
        stMonitorHistory[SCAN_PACKET_LIST_SIZE - 1] = scan.getMonitorStationCount();
        apstMonitorSampleTime += sampleInterval;
    }
}

void DisplayUI::drawGraphLine(uint16_t* values, uint16_t maxValue, int graphTop, int graphBottom, bool dotted) {
    int prevX = 0;
    int prevY = getGraphY(values[0], maxValue, graphTop, graphBottom);

    for (uint8_t i = 1; i < SCAN_PACKET_LIST_SIZE; i++) {
        int x = i * 2;
        int y = getGraphY(values[i], maxValue, graphTop, graphBottom);

        if (dotted) drawDottedLine(prevX, prevY, x, y);
        else drawLine(prevX, prevY, x, y);

        prevX = x;
        prevY = y;
    }
}

void DisplayUI::drawDottedLine(int x0, int y0, int x1, int y1) {
    int dx  = abs(x1 - x0);
    int sx  = x0 < x1 ? 1 : -1;
    int dy  = -abs(y1 - y0);
    int sy  = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int i   = 0;

    while (true) {
        if ((i & 1) == 0) display.setPixel(x0, y0);
        if ((x0 == x1) && (y0 == y1)) break;

        int e2 = err * 2;

        if (e2 >= dy) {
            err += dy;
            x0  += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y0  += sy;
        }

        i++;
    }
}

void DisplayUI::drawTrackerArrow(int x, int y, int8_t trend) {
    if (trend > 0) {
        drawLine(x, y + 4, x, y);
        drawLine(x, y, x - 2, y + 2);
        drawLine(x, y, x + 2, y + 2);
    } else if (trend < 0) {
        drawLine(x, y, x, y + 4);
        drawLine(x, y + 4, x - 2, y + 2);
        drawLine(x, y + 4, x + 2, y + 2);
    }
}

int DisplayUI::getGraphY(uint16_t value, uint16_t maxValue, int graphTop, int graphBottom) {
    if (maxValue == 0) return graphBottom;

    int graphHeight = graphBottom - graphTop;

    if (graphHeight <= 0) return graphBottom;

    return graphBottom - ((int)value * graphHeight / (int)maxValue);
}

void DisplayUI::createMenu(Menu* menu, Menu* parent, std::function<void()>build) {
    menu->list       = new SimpleList<MenuNode>;
    menu->parentMenu = parent;
    menu->selected   = 0;
    menu->build      = build;
}

void DisplayUI::addMenuNode(Menu* menu, std::function<String()>getStr, std::function<void()>click,
                            std::function<void()>hold) {
    menu->list->add(MenuNode{ getStr, click, hold });
}

void DisplayUI::addMenuNode(Menu* menu, std::function<String()>getStr, std::function<void()>click) {
    addMenuNode(menu, getStr, click, NULL);
}

void DisplayUI::addMenuNode(Menu* menu, std::function<String()>getStr, Menu* next) {
    addMenuNode(menu, getStr, [this, next]() {
        changeMenu(next);
    });
}

void DisplayUI::addMenuNode(Menu* menu, const char* ptr, std::function<void()>click) {
    addMenuNode(menu, [ptr]() {
        return str(ptr);
    }, click);
}

void DisplayUI::addMenuNode(Menu* menu, const char* ptr, Menu* next) {
    addMenuNode(menu, [ptr]() {
        return str(ptr);
    }, next);
}

void DisplayUI::setTime(int h, int m, int s) {
    if (s >= 60) {
        s = 0;
        m++;
    }

    if (m >= 60) {
        m = 0;
        h++;
    }

    if (h >= 24) {
        h = 0;
    }

    if (s < 0) {
        s = 59;
        m--;
    }

    if (m < 0) {
        m = 59;
        h--;
    }

    if (h < 0) {
        h = 23;
    }

    clockHour   = h;
    clockMinute = m;
    clockSecond = s;

#ifdef RTC_DS3231
    clock.setHour(clockHour);
    clock.setMinute(clockMinute);
    clock.setSecond(clockSecond);
#endif // ifdef RTC_DS3231
}
