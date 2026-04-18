/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#pragma once

#include <Arduino.h>

namespace wifi {
    void begin();

    String getMode();
    void printStatus();

    void startNewAP(String path, String ssid, String password, uint8_t ch, bool hidden, bool captivePortal);
    // void startAP(String path);
    void startAP();

    void stopAP();
    void resumeAP();
    void enableAttackPortal(String ssid, uint8_t ch, bool nameMePage = false);
    void disableAttackPortal();
    bool isAttackPortalEnabled();
    void setNameMeTemplate(uint8_t index);
    uint8_t getNameMeTemplate();
    String getNameMeValue();
    bool hasNameMeValue();

    void update();
}