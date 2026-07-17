# G-Shark

G-Shark is a custom **ESP8266 wearable Wi-Fi tool** built around the ESP8266 Deauther codebase and extended with a compact OLED-driven UI, hardware buttons, live scan views, a serial CLI, a local web interface, SPIFFS-backed assets, persistent settings, and multiple monitoring / scanning modes.

> This repository is a reverse-engineered firmware project.  
> The documentation below describes the code that exists in the firmware, the hardware it expects, and the runtime workflow exposed by the source.

---

## Contents

- [Overview](#overview)
- [Project Goals](#project-goals)
- [Hardware Architecture](#hardware-architecture)
- [GPIO / Pinout](#gpio--pinout)
- [Hardware BOM](#hardware-bom)
- [Power Architecture](#power-architecture)
- [Flash, EEPROM, and SPIFFS](#flash-eeprom-and-spiffs)
- [Module Dependency Graph](#module-dependency-graph)
- [Feature Inventory](#feature-inventory)
- [Display / Screen Output](#display--screen-output)
- [Menu Hierarchy](#menu-hierarchy)
- [Web Interface](#web-interface)
- [CLI Reference](#cli-reference)
- [Scan Architecture](#scan-architecture)
- [Attack Architecture](#attack-architecture)
- [Workflow Summary](#workflow-summary)
- [Build / Flash Notes](#build--flash-notes)
- [Files Included](#files-included)

---

## Overview

G-Shark is centered on the **ESP8266** and the project code confirms ESP8266-specific APIs, Wi-Fi promiscuous sniffing, raw frame transmission, and flash-backed configuration. It is **not** an ESP32 firmware and it does **not** implement Bluetooth/BLE.

The firmware combines:

- OLED UI (`DisplayUI`)
- Button navigation
- AP / station scanning
- Live monitoring modes
- Packet monitor
- Clock / stopwatch / timer screens
- Serial CLI
- Local web UI from SPIFFS
- Persistent settings in EEPROM emulation
- Optional RTC support (`DS3231`)
- RGB LED status support
- Captive-portal style local web presentation

---

## Project Goals

The codebase is designed to run as a compact standalone device that can:

- scan nearby Wi-Fi access points and stations
- present live network data on the OLED
- expose controls over serial and browser interfaces
- store settings persistently
- drive a wearable display and a small button set
- provide multiple monitoring views for signal analysis

The repository also contains later UI extensions referenced in the attached change logs, including:

- `AP TRACKER`
- `APST TRACKER`
- `AUTOSCAN`
- `APST MONITOR`
- `CLOCK`
- live AP/station list views
- continuous scan behavior updates

---

## Hardware Architecture

The active firmware profile is a compact watch-style ESP8266 build with:

- ESP8266 module
- I²C OLED display
- four navigation buttons
- one WS2812 / NeoPixel status LED
- optional DS3231 RTC
- flash-backed settings and files

The code supports several board profiles, but the active watch configuration uses the following GPIO map.

---

## GPIO / Pinout

### Active watch profile

| Function | GPIO | NodeMCU label | Notes |
|---|---:|---|---|
| OLED SDA | GPIO4 | D2 | I²C data |
| OLED SCL | GPIO5 | D1 | I²C clock |
| Button UP | GPIO14 | D5 | menu up / scroll up |
| Button DOWN | GPIO12 | D6 | menu down / scroll down |
| Button A | GPIO2 | D4 | select / confirm |
| Button B | GPIO0 | D3 | back / cancel |
| NeoPixel DIN | GPIO15 | D8 | status LED |

### Bus notes

- OLED uses I²C.
- DS3231, if enabled, shares the same I²C bus.
- The current profile is configured for an SH1106-style OLED at address `0x3C`.

### Boot-sensitive pins

| GPIO | Role |
|---|---|
| GPIO0 | boot mode-sensitive |
| GPIO2 | boot mode-sensitive |
| GPIO15 | boot mode-sensitive |

These pins matter during power-up because the ESP8266 bootloader samples them.

---

## Hardware BOM

### Confirmed by firmware

- ESP8266 module
- SH1106 OLED or compatible SSD1306/OLED variant, depending on compile-time profile
- 4 tactile buttons
- 1 WS2812 / NeoPixel RGB LED
- optional DS3231 RTC
- onboard SPI flash

### Required but not defined in firmware

The firmware does not define the exact electrical implementation of these items, but a functional build normally also requires:

- 3.3 V regulator
- battery or regulated supply
- charging circuit if battery powered
- power switch
- pull-ups / pull-downs for ESP8266 boot pins
- decoupling capacitors
- programming header or USB-UART bridge
- antenna matched to the chosen ESP8266 module

### Not confirmed by source

The repository does not provide a schematic, PCB layout, or Gerbers, so the following are not verifiable from the firmware alone:

- exact ESP8266 module variant
- battery capacity
- charge IC
- protection IC
- regulator model
- connector selection
- enclosure mechanics
- antenna routing

---

## Power Architecture

The firmware assumes a **3.3 V logic rail**.

### Likely power path

```text
USB 5V / battery input
    -> charger or regulator
    -> 3.3V rail
    -> ESP8266 + OLED + buttons + LED + RTC
```

### Firmware-side power behavior

Confirmed behaviors:

- OLED can be turned on/off
- display contrast is configured
- Wi-Fi is actively used in scan / monitor / AP modes
- NeoPixel status output is supported
- the firmware does not implement deep sleep as a primary operating mode

### Power characteristics

Relative load order:

1. Wi-Fi transmit / injection
2. Wi-Fi receive / scan
3. OLED rendering
4. NeoPixel activity
5. RTC standby
6. buttons

The firmware does not implement battery percentage calculation or fuel-gauge logic.

---

## Flash, EEPROM, and SPIFFS

### Flash layout

The ESP8266 internal flash is used for:

- firmware code
- EEPROM emulation
- SPIFFS filesystem

### EEPROM

The firmware uses EEPROM emulation for persistent settings.

Key points:

- settings are stored in a structured config block
- a magic number is used for validation
- settings are loaded on boot and saved on demand

### SPIFFS

SPIFFS stores the local web UI and assets such as:

- HTML pages
- JavaScript
- CSS
- images
- audio assets
- named page templates
- generated or exported content

### Notable content in the repository

- `data/web/`
- `data/nameme/`
- `data/logo.png`
- `data/instapage.jpg`
- `data/music.mp3`

---

## Module Dependency Graph

```text
esp8266_deauther.ino
├── settings
├── wifi
├── DisplayUI
├── Scan
├── Attack
├── CLI
├── Accesspoints
├── Stations
├── SSIDs
├── Names
├── LED
└── SPIFFS assets / web UI
```

### Dependency highlights

- `DisplayUI` depends on `Scan`, `Attack`, `Accesspoints`, `Stations`, `SSIDs`, `Names`, and settings.
- `Scan` depends on Wi-Fi hardware APIs plus the AP/station databases.
- `Attack` depends on selected APs, stations, SSIDs, and Wi-Fi raw transmit support.
- `CLI` and the web UI expose the same internal state from different frontends.
- `Settings` is the central persistence layer.

---

## Feature Inventory

### Core

- ESP8266 firmware
- modular class design
- serial console
- OLED front panel
- local web interface
- SPIFFS-backed assets
- EEPROM-backed settings
- optional RTC integration
- RGB LED status output

### Wi-Fi

- AP scanning
- station scanning
- combined scan modes
- hidden AP detection
- channel management
- vendor lookup from OUI table
- promiscuous sniffing
- raw 802.11 frame transmission
- live packet statistics

### UI / UX

- splash / intro screen
- main menu
- scan menu
- select menu
- attack menu
- packet monitor
- AP monitor / station monitor variants
- AP tracker
- APST tracker
- APST monitor
- clock
- stopwatch
- timer
- loading screens
- button test
- scrolling lists
- fixed-value right-aligned metrics
- trend arrows on live data

### Storage / persistence

- settings save / load
- AP / station / SSID / name lists
- SPIFFS file operations from CLI
- web assets stored locally
- generated JSON responses for the browser UI

### Web interface

- offline browser-based control surface
- dynamic status pages
- scan data pages
- attack status pages
- settings pages
- local portal behavior for compatible clients

### CLI

- scan commands
- select/deselect commands
- save/load commands
- file commands
- LED commands
- screen commands
- settings commands
- script execution commands
- packet send commands
- attack commands

---

## Display / Screen Output

The OLED output is organized into screens and menus. Exact wording comes from `language.h` and the display logic in `DisplayUI.cpp`.

### Boot / intro

```text
CRABOX
#iM
G-Shark 2.6
```

### Main menu

```text
SCAN
SELECT
ATTACK
PACKET MONITOR
APST MONITOR
CLOCK
```

### Scan menu

```text
[BACK]
SCAN AP + ST
SCAN APs
SCAN Stations
AUTOSCAN
AP TRACKER
APST TRACKER
```

### Select menu

```text
APs
Stations
SSIDs
Names
```

### Attack menu

```text
[BACK]
DEAUTH
BEACON
PROBE
FISH
CAPAD
START
STOP
```

### Clock menu

```text
CLOCK DISPLAY
SET CLOCK
STOPWATCH
TIMER
```

### Live monitor examples

The attached change logs show extended live display behavior such as:

- AP tracker list with RSSI trend arrows
- APST tracker list with AP and station counts
- autoscan live AP list
- packet monitor graph
- APST monitor graph

Typical live formats used by the firmware include:

```text
APs [15]       PKTs [642]
>Home WiFi      -37 ↑
 Office         -45 ↑
 TP-Link        -61 ↓
```

```text
APs [15]       ST [5]
>Home WiFi      -37 ↑ ST [5]
 Office         -45 ↑ ST [2]
 TP-Link        -61 ↓ ST [7]
```

```text
AP [0] ST [0]
/_____
---------^--
```

### Common on-screen labels

The firmware includes screen labels such as:

- `SELECT`
- `PACKET MONITOR`
- `APST MONITOR`
- `CLOCK`
- `CLOCK DISPLAY`
- `SET CLOCK`
- `STOPWATCH`
- `TIMER`
- `SCAN AP + ST`
- `SCAN APs`
- `SCAN Stations`
- `AUTOSCAN`
- `AP TRACKER`
- `APST TRACKER`
- `DEAUTH`
- `BEACON`
- `PROBE`
- `FISH`
- `CAPAD`
- `START`
- `STOP`

---

## Menu Hierarchy

### Main menu

- SCAN
- SELECT
- ATTACK
- PACKET MONITOR
- APST MONITOR
- CLOCK

### Scan

- SCAN AP + ST
- SCAN APs
- SCAN Stations
- AUTOSCAN
- AP TRACKER
- APST TRACKER

### Select

- APs
- Stations
- SSIDs
- Names

### Attack

- DEAUTH
- BEACON
- PROBE
- FISH
- CAPAD
- START
- STOP

### Clock

- CLOCK DISPLAY
- SET CLOCK
- STOPWATCH
- TIMER

---

## Web Interface

The firmware serves a local browser interface from SPIFFS. It is intended for offline use and exposes the same internal data used by the OLED and CLI.

### Likely web assets

- page HTML
- JS controllers
- CSS
- image assets

### Web UI responsibilities

- show scan results
- show selected AP/station lists
- show settings
- show runtime status
- control available firmware functions via HTTP

### Captive portal behavior

The firmware includes a captive portal page system. In a legitimate deployment, this means connected clients can be redirected to a local landing page served from the device.

> This README intentionally documents the portal as a local management interface and does not describe credential-harvesting or phishing workflows.

---

## CLI Reference

The serial CLI supports:

- help and info commands
- scanning
- selection management
- saving/loading lists and settings
- file management in SPIFFS
- LED control
- screen control
- scripted command execution
- packet transmission commands
- attack commands

### Representative syntax from `language.h`

```text
scan [<all/aps/stations>] [-t <time>] [-c <continue-time>] [-ch <channel>]
show [selected] [<all/aps/stations/names/ssids>]
select [<all/aps/stations/names>] [<id>]
deselect [<all/aps/stations/names>] [<id>]
add ssid <ssid> [-wpa2] [-cl <clones>]
add name <name> [-ap <id>] [-s]
attack [beacon] [deauth] [deauthall] [probe] [nooutput] [-t <timeout>]
stop <all/scan/attack/script>
led <r> <g> <b>
led <#rrggbb>
screen <on/off>
screen mode <menu/packetmonitor/buttontest/loading>
```

---

## Scan Architecture

The scan engine is split into multiple runtime modes:

- AP scan
- station scan
- combined AP + station scan
- autoscan
- AP tracker
- APST tracker
- APST monitor

### Shared data structures

- Access point database
- Station database
- SSID list
- Name list

### Runtime behavior

- scan modes update the shared databases
- the display reads from those databases
- the CLI and web UI can inspect or modify the same state
- the attack engine consumes selected targets from those lists

### Tracker / monitor extensions

The attached change logs show later additions such as:

- persistent autoscan history
- per-AP expiry
- auto-selection of scanned APs
- live AP tracker
- APST tracker with station counts
- APST monitor graph mode
- background scan continuation behavior

These are documented in the change history but should be validated against the final source tree before flashing a release build.

---

## Attack Architecture

The attack subsystem uses raw Wi-Fi frame generation through ESP8266 Wi-Fi APIs.

### Supported methods exposed by the firmware

- deauthentication
- beacon frame generation
- probe frame generation
- CAPAD / captive-portal related feature entry
- start / stop control

### High-level flow

1. user selects targets
2. the attack engine reads the selected APs / stations / SSIDs
3. the firmware builds management frames
4. the ESP8266 transmits raw packets
5. counters and status update on the OLED / CLI / web UI

### Important note

The repository contains attack-oriented functionality. This README documents the code that exists in the project, but it does not provide operational instructions for misuse.

---

## Workflow Summary

### Boot flow

```text
Power on
-> bootloader
-> setup()
-> SPIFFS / EEPROM / UI init
-> intro screen
-> main menu
```

### Scan flow

```text
Open SCAN
-> choose scan mode
-> update AP/station databases
-> render live list / monitor
```

### Select flow

```text
Open SELECT
-> view APs / Stations / SSIDs / Names
-> choose targets
-> selected items are used by other modules
```

### Attack flow

```text
Open ATTACK
-> choose method
-> start
-> packet generation
-> packet transmit
-> status / counters
```

### Web flow

```text
Connect browser
-> local HTTP page
-> load from SPIFFS
-> request JSON status
-> update controls
```

### CLI flow

```text
Open serial terminal
-> enter command
-> parser dispatches command
-> state updates
-> output printed to serial
```

---

## Build / Flash Notes

### Platform

- Arduino IDE / ESP8266 core
- ESP8266 board profile

### Libraries expected by the source

- OLED driver library
- DS3231 library
- SimpleButton
- SPI / Wire / FS
- ESP8266 Wi-Fi / Arduino core

### Practical notes

- compile-time board macros in `A_config.h` determine the pinout and screen variant
- the OLED library version matters for `String` / `char` conversions
- many runtime features depend on the active profile in `A_config.h`

---

## Files Included

### Core source

- `esp8266_deauther.ino`
- `DisplayUI.cpp/.h`
- `Scan.cpp/.h`
- `Attack.cpp/.h`
- `CLI.cpp/.h`
- `Accesspoints.cpp/.h`
- `Stations.cpp/.h`
- `SSIDs.cpp/.h`
- `Names.cpp/.h`
- `settings.cpp/.h`
- `led.cpp/.h`
- `wifi.cpp/.h`
- `language.h`
- `A_config.h`

### Assets

- `data/web/`
- `data/nameme/`
- `data/logo.png`
- `data/instapage.jpg`
- `data/music.mp3`

### Reference / bundled libraries

- OLED driver sources
- DS3231 driver
- SimpleButton
- other bundled support headers

---

## Project Notes

This repository contains substantial UI evolution in the attached change logs, including:

- new live scan modes
- autoscan persistence behavior
- AP/ST tracker views
- APST monitor screen
- clock / stopwatch / timer screens
- intro / splash handling fixes
- menu restructuring
- select-menu cleanup
- scan performance refinements

Those logs are useful as design history, but the README above documents the verified firmware structure and the operational modules in the repository.

---

## License

The source headers indicate MIT licensing for the upstream codebase. Check the repository license file for the exact terms before redistribution.
