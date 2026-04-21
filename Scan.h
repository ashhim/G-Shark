/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#pragma once

#include "Arduino.h"
#include "Accesspoints.h"
#include "Stations.h"
#include "Names.h"
#include "SSIDs.h"
#include "language.h"
#include "SimpleList.h"

#define SCAN_MODE_OFF 0
#define SCAN_MODE_APS 1
#define SCAN_MODE_STATIONS 2
#define SCAN_MODE_ALL 3
#define SCAN_MODE_SNIFFER 4
#define SCAN_MODE_AUTOSCAN 5
#define SCAN_MODE_APST_MONITOR 6
#define SCAN_MODE_AP_TRACKER 7
#define SCAN_DEFAULT_TIME 15000
#define SCAN_DEFAULT_CONTINUE_TIME 10000
#define SCAN_PACKET_LIST_SIZE 64
#define AUTOSCAN_AP_TIMEOUT 60000
#define APST_MONITOR_AP_TIMEOUT 15000
#define APST_MONITOR_STATION_TIMEOUT 15000
#define APST_MONITOR_STATION_TIME 5000
#define APST_MONITOR_AP_LIST_SIZE 128
#define APST_MONITOR_STATION_LIST_SIZE 128
#define AP_TRACKER_TIMEOUT 5000
#define AP_TRACKER_LIST_SIZE 64

extern Accesspoints accesspoints;
extern Stations     stations;
extern Names names;
extern SSIDs ssids;

extern uint8_t wifiMode;

extern void setWifiChannel(uint8_t ch, bool force);
extern bool appendFile(String path, String& buf);
extern bool writeFile(String path, String& buf);
extern void readFileToSerial(const String path);
extern String escape(String str);
extern String fixUtf8(String str);

class Scan {
    public:
        Scan();

        void sniffer(uint8_t* buf, uint16_t len);
        void start(uint8_t mode, uint32_t time, uint8_t nextmode, uint32_t continueTime, bool channelHop, uint8_t channel);
        void start(uint8_t mode);

        void setup();
        void update();
        void stop();
        void save(bool force);
        void save(bool force, String filePath);

        void selectAll();
        void deselectAll();
        void printAll();
        void printSelected();

        uint8_t getPercentage();
        uint32_t getPackets(int i);
        uint32_t countAll();
        uint32_t countSelected();
        bool isScanning();
        bool isSniffing();
        bool isContinuous();
        bool isAutoScanActive();
        bool isAPSTMonitorActive();
        bool isAPTrackerActive();

        void nextChannel();
        void setChannel(uint8_t newChannel);

        String getMode();
        double getScaleFactor(uint8_t height);
        uint32_t getMaxPacket();
        uint32_t getPacketRate();
        uint16_t getMonitorAccesspointCount();
        uint16_t getMonitorStationCount();
        uint16_t getTrackerAccesspointCount();
        uint16_t getTrackerPacketCount();
        String getTrackerSSID(int num);
        int getTrackerRSSI(int num);
        int8_t getTrackerTrend(int num);

        uint16_t deauths = 0;
        uint16_t packets = 0;

    private:
        SimpleList<uint16_t>* list;                      // packet list

        struct MonitorDevice {
            uint8_t  mac[6];
            uint8_t  ch;
            uint32_t lastSeen;
        };

        struct TrackerAccesspoint {
            uint8_t  mac[6];
            String   ssid;
            int      rssi;
            int8_t   trend;
            uint32_t lastSeen;
        };

        SimpleList<MonitorDevice>* monitorAccesspoints;
        SimpleList<MonitorDevice>* monitorStations;
        SimpleList<TrackerAccesspoint>* trackerAccesspoints;

        uint32_t sniffTime          = SCAN_DEFAULT_TIME; // how long the scan runs
        uint32_t snifferStartTime   = 0;                 // when the scan started
        uint32_t snifferOutputTime  = 0;                 // last info output (every 3s)
        uint32_t snifferChannelTime = 0;                 // last time the channel was changed
        uint32_t snifferPacketTime  = 0;                 // last time the packet rate was reseted (every 1s)

        uint8_t scanMode = 0;

        uint8_t scan_continue_mode = 0;                          // restart mode after scan stopped
        uint32_t continueTime      = SCAN_DEFAULT_CONTINUE_TIME; // time in ms to wait until scan restarts
        uint32_t continueStartTime = 0;                          // when scan restarted

        bool channelHop     = true;
        uint16_t tmpDeauths = 0;
        uint16_t trackerPackets = 0;

        bool apWithChannel(uint8_t ch);
        int findAccesspoint(uint8_t* mac);
        bool isAPSTMonitorStationScan();
        int findMonitorDevice(SimpleList<MonitorDevice>* deviceList, uint8_t* mac);
        void resetAPSTMonitor();
        void updateMonitorAccesspoint(uint8_t* mac, uint8_t ch);
        void updateMonitorStation(uint8_t* mac);
        void updateMonitorDevice(SimpleList<MonitorDevice>* deviceList, uint8_t* mac, uint8_t ch, uint16_t maxSize);
        void pruneMonitorDevices(SimpleList<MonitorDevice>* deviceList, uint32_t timeout);
        int findOldestMonitorDevice(SimpleList<MonitorDevice>* deviceList);
        int findTrackerAccesspoint(uint8_t* mac);
        void resetAPTracker();
        void updateTrackerAccesspoint(uint8_t id);
        void pruneTrackerAccesspoints(uint32_t timeout);
        void sortTrackerAccesspoints();

        String FILE_PATH = "/scan.json";
};
