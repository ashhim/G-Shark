/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#pragma once

#include "Arduino.h"
#include <ESP8266WiFi.h>
extern "C" {
  #include "user_interface.h"
}
#include "language.h"
#include "SimpleList.h"
#include "Names.h"

extern Names names;
extern uint32_t currentTime;

extern String searchVendor(uint8_t* mac);
extern String leftRight(String a, String b, int len);
extern String fixUtf8(String str);
extern String bytesToStr(const uint8_t* b, uint32_t size);

struct AP {
    uint16_t id;
    String  ssid;
    uint8_t ch;
    int     rssi;
    uint8_t enc;
    uint8_t mac[6];
    bool    hidden;
    bool    selected;
    bool    autoScan;
    uint32_t lastSeen;
};

class Accesspoints {
    public:
        Accesspoints();

        void sort();
        void sortAfterChannel();

        void add(uint8_t id, bool selected);
        bool addOrUpdate(uint8_t id, bool selected, bool autoScan = false);
        void prepareAutoScan();
        bool removeExpiredAutoScan(uint32_t timeout);

        void print(int num);
        void print(int num, bool header, bool footer);

        void select(int num);
        void deselect(int num);
        void remove(int num);
        void select(String ssid);
        void deselect(String ssid);
        void remove(String ssid);

        void printAll();
        void printSelected();
        void selectAll();
        void deselectAll();
        void clear();
        void removeAll();

        String getSSID(int num);
        String getNameStr(int num);
        String getEncStr(int num);
        String getMacStr(int num);
        String getVendorStr(int num);
        String getSelectedStr(int num);
        uint8_t getCh(int num);
        uint8_t getEnc(int num);
        uint16_t getID(int num);
        int getRSSI(int num);
        uint8_t* getMac(int num);
        bool getHidden(int num);
        bool getSelected(int num);

        int find(uint16_t id);
        int find(uint8_t* mac);

        int count();
        int selected();

        bool check(int num);
        bool changed = false;

    private:
        SimpleList<AP>* list;
        uint16_t nextID = 0;

        bool internal_check(int num);
        void internal_select(int num);
        void internal_deselect(int num);
        void internal_remove(int num);
        bool readScanAP(AP& ap, uint8_t id, bool selected);
};
