/* Auto-generated from data/nameme/*.html */
#pragma once

#include <Arduino.h>

const char Astra_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Astra</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: linear-gradient(145deg, #102242, #2d66b7);
      color: #eef5ff;
      font-family: "Segoe UI", Arial, sans-serif;
    }
    .card {
      width: min(88vw, 420px);
      padding: 28px;
      border-radius: 24px;
      background: rgba(255, 255, 255, 0.12);
      border: 1px solid rgba(255, 255, 255, 0.28);
      backdrop-filter: blur(10px);
      box-shadow: 0 18px 40px rgba(0, 0, 0, 0.25);
    }
    h1 { margin: 0 0 8px; text-align: center; letter-spacing: 0.08em; }
    p { margin: 0 0 18px; text-align: center; color: #b9ddff; }
    label { display: block; margin-bottom: 10px; font-size: 14px; text-transform: uppercase; }
    input, button {
      width: 100%;
      box-sizing: border-box;
      border-radius: 14px;
      font-size: 16px;
    }
    input {
      padding: 14px 16px;
      border: 1px solid rgba(255, 255, 255, 0.28);
      background: rgba(10, 19, 38, 0.35);
      color: #eef5ff;
    }
    button {
      margin-top: 16px;
      padding: 14px 16px;
      border: none;
      background: #8ed6ff;
      color: #0b2344;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="card" action="/get">
    <h1>Astra</h1>
    <p>Glass panel preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Send To Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Breach_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Breach</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: #050805;
      color: #8cff72;
      font-family: "Courier New", monospace;
    }
    .terminal {
      width: min(90vw, 460px);
      padding: 24px;
      border: 1px solid #1d5f1a;
      background: #081108;
      box-shadow: 0 0 30px rgba(35, 255, 35, 0.12);
    }
    .bar { margin-bottom: 20px; color: #4cff4c; }
    h1 { margin: 0 0 8px; font-size: 22px; }
    p { margin: 0 0 18px; color: #79d978; }
    label, input, button { display: block; width: 100%; box-sizing: border-box; }
    input {
      padding: 12px 14px;
      border: 1px solid #2f8f2b;
      background: #000;
      color: #8cff72;
      font-family: inherit;
    }
    button {
      margin-top: 14px;
      padding: 12px 14px;
      border: 1px solid #2f8f2b;
      background: #0e2a0e;
      color: #8cff72;
      font-family: inherit;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="terminal" action="/get">
    <div class="bar">preview://ui2/terminal</div>
    <h1>Breach</h1>
    <p>Retro terminal preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Preview text" required>
    <button type="submit">EXECUTE</button>
  </form>
</body>
</html>
)rawliteral";

const char Brimstone_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Brimstone</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: grid;
      place-items: center;
      background: linear-gradient(160deg, #fff8ef, #ffe6cf);
      font-family: Georgia, "Times New Roman", serif;
      color: #39251a;
    }
    .sheet {
      width: min(88vw, 420px);
      padding: 30px;
      background: #fffdf8;
      border-radius: 18px;
      box-shadow: 0 18px 45px rgba(102, 66, 35, 0.14);
      border-top: 8px solid #c78a53;
    }
    h1 { margin: 0 0 10px; font-size: 30px; }
    p { margin: 0 0 18px; color: #6d4d35; }
    label { display: block; margin-bottom: 8px; font-size: 14px; letter-spacing: 0.08em; text-transform: uppercase; }
    input, button {
      width: 100%;
      box-sizing: border-box;
      border-radius: 12px;
      font-size: 16px;
    }
    input {
      padding: 14px 15px;
      border: 1px solid #d6b190;
      background: #fff;
      color: #39251a;
    }
    button {
      margin-top: 14px;
      padding: 14px 15px;
      border: none;
      background: #39251a;
      color: #fff8ef;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="sheet" action="/get">
    <h1>Brimstone</h1>
    <p>Editorial card preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Update Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Chamber_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Chamber</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: repeating-linear-gradient(180deg, #f7f0de 0, #f7f0de 34px, #e8ddc4 35px);
      font-family: "Trebuchet MS", sans-serif;
      color: #473a1f;
    }
    .note {
      width: min(88vw, 420px);
      padding: 26px;
      border-radius: 8px;
      background: rgba(255, 251, 240, 0.96);
      box-shadow: 0 20px 40px rgba(80, 62, 24, 0.18);
      border-left: 8px solid #d77c32;
    }
    h1 { margin: 0 0 8px; }
    p { margin: 0 0 18px; }
    label { display: block; margin-bottom: 8px; font-weight: 700; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 13px 14px;
      border: 1px solid #c6b48d;
      border-radius: 8px;
      background: #fffdf7;
      color: #473a1f;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 13px 14px;
      border: none;
      border-radius: 8px;
      background: #d77c32;
      color: #fff;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="note" action="/get">
    <h1>Chamber</h1>
    <p>Notebook preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Write a short message" required>
    <button type="submit">Pin To Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Clove_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Clove</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: linear-gradient(135deg, #0c111d 0%, #161f34 100%);
      font-family: "Segoe UI", sans-serif;
    }
    .shell {
      width: min(90vw, 520px);
      display: grid;
      grid-template-columns: 1fr 1.3fr;
      overflow: hidden;
      border-radius: 24px;
      background: #f5f7fb;
      box-shadow: 0 22px 48px rgba(0, 0, 0, 0.28);
    }
    .side {
      padding: 28px 22px;
      background: linear-gradient(180deg, #4f87ff, #6b49ff);
      color: #fff;
    }
    .side h1 { margin: 0 0 12px; font-size: 30px; }
    .side p { margin: 0; line-height: 1.5; }
    .main { padding: 28px 24px; color: #1a2238; }
    label { display: block; margin-bottom: 8px; font-size: 13px; text-transform: uppercase; letter-spacing: 0.08em; }
    input, button { width: 100%; box-sizing: border-box; border-radius: 14px; font-size: 16px; }
    input { padding: 14px 16px; border: 1px solid #cfd6ea; }
    button {
      margin-top: 16px;
      padding: 14px 16px;
      border: none;
      background: #1a2238;
      color: #fff;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="shell" action="/get">
    <div class="side">
      <h1>Clove</h1>
      <p>Split-screen preview with a bold sidebar and clean form area.</p>
    </div>
    <div class="main">
      <label for="preview_text">Enter preview text</label>
      <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
      <button type="submit">Submit Preview</button>
    </div>
  </form>
</body>
</html>
)rawliteral";

const char Cypher_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Cypher</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: grid;
      place-items: center;
      background:
        radial-gradient(circle at 20% 20%, #ffd7ea 0, transparent 24%),
        radial-gradient(circle at 80% 30%, #d7f5ff 0, transparent 28%),
        linear-gradient(180deg, #fff6fb, #eef8ff);
      color: #294055;
      font-family: "Segoe UI", sans-serif;
    }
    .bubble {
      width: min(88vw, 420px);
      padding: 28px;
      border-radius: 28px;
      background: rgba(255, 255, 255, 0.78);
      box-shadow: 0 18px 40px rgba(89, 124, 150, 0.18);
    }
    h1 { margin: 0 0 10px; text-align: center; }
    p { margin: 0 0 18px; text-align: center; color: #557489; }
    label { display: block; margin-bottom: 8px; font-weight: 600; }
    input, button {
      width: 100%;
      box-sizing: border-box;
      border-radius: 999px;
      font-size: 16px;
    }
    input {
      padding: 14px 18px;
      border: 1px solid #d5e6f0;
      background: #fff;
      color: #294055;
    }
    button {
      margin-top: 14px;
      padding: 14px 18px;
      border: none;
      background: linear-gradient(90deg, #ff8dc6, #79d5ff);
      color: #1c3146;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="bubble" action="/get">
    <h1>Cypher</h1>
    <p>Soft pastel preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Send Preview</button>
  </form>
</body>
</html>
)rawliteral";

const char Deadlock_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Deadlock</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: #0d1017;
      color: #f3f6ff;
      font-family: "Segoe UI", sans-serif;
    }
    .panel {
      width: min(88vw, 430px);
      padding: 28px;
      border-radius: 18px;
      background: #171c29;
      border: 1px solid #293147;
      box-shadow: 0 18px 45px rgba(0, 0, 0, 0.3);
    }
    .tag {
      display: inline-block;
      padding: 6px 10px;
      border-radius: 999px;
      background: #25304b;
      color: #9ebcff;
      font-size: 12px;
      letter-spacing: 0.08em;
      text-transform: uppercase;
    }
    h1 { margin: 14px 0 8px; }
    p { margin: 0 0 18px; color: #aab6d7; }
    label { display: block; margin-bottom: 8px; font-size: 13px; text-transform: uppercase; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px 15px;
      border-radius: 12px;
      border: 1px solid #344160;
      background: #0f1420;
      color: #f3f6ff;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 14px 15px;
      border: none;
      border-radius: 12px;
      background: #8aa7ff;
      color: #15203a;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="panel" action="/get">
    <span class="tag">Dashboard</span>
    <h1>Deadlock</h1>
    <p>Dark dashboard preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Save Preview</button>
  </form>
</body>
</html>
)rawliteral";

const char Fade_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Fade</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: grid;
      place-items: center;
      background:
        linear-gradient(90deg, rgba(0, 0, 0, 0.05) 1px, transparent 1px),
        linear-gradient(rgba(0, 0, 0, 0.05) 1px, transparent 1px),
        #f9f4ee;
      background-size: 20px 20px;
      font-family: Arial, sans-serif;
      color: #302820;
    }
    .card {
      width: min(88vw, 420px);
      padding: 26px;
      border-radius: 20px;
      background: #fff;
      box-shadow: 0 18px 45px rgba(67, 45, 20, 0.14);
      border-top: 10px solid #ff8c42;
    }
    h1 { margin: 0 0 8px; font-size: 32px; }
    p { margin: 0 0 18px; color: #6b5a49; }
    label { display: block; margin-bottom: 8px; font-size: 13px; letter-spacing: 0.08em; text-transform: uppercase; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px 15px;
      border-radius: 10px;
      border: 1px solid #dfd3c8;
      background: #fffdf9;
      color: #302820;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 14px 15px;
      border: none;
      border-radius: 10px;
      background: #302820;
      color: #fff;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="card" action="/get">
    <h1>Fade</h1>
    <p>Grid card preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Push To Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Gekko_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Gekko</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: #1a1510;
      color: #ffd595;
      font-family: "Courier New", monospace;
    }
    .console {
      width: min(90vw, 460px);
      padding: 24px;
      border-radius: 18px;
      background: #241d16;
      border: 1px solid #5f4a2f;
      box-shadow: 0 0 30px rgba(255, 189, 92, 0.12);
    }
    h1 { margin: 0 0 8px; font-size: 26px; }
    p { margin: 0 0 18px; color: #f0c279; }
    label { display: block; margin-bottom: 8px; }
    input, button {
      width: 100%;
      box-sizing: border-box;
      font-family: inherit;
      font-size: 16px;
      border-radius: 10px;
    }
    input {
      padding: 12px 14px;
      border: 1px solid #806543;
      background: #130f0b;
      color: #ffd595;
    }
    button {
      margin-top: 14px;
      padding: 12px 14px;
      border: 1px solid #806543;
      background: #ffd595;
      color: #1a1510;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="console" action="/get">
    <h1>Gekko</h1>
    <p>Amber console preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Preview text" required>
    <button type="submit">TRANSMIT</button>
  </form>
</body>
</html>
)rawliteral";

const char Harbor_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Harbor</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: grid;
      place-items: center;
      background: #fbfbfc;
      color: #111827;
      font-family: "Segoe UI", sans-serif;
    }
    .frame {
      width: min(88vw, 420px);
      padding: 30px;
      background: #fff;
      border: 4px solid #111827;
      box-shadow: 14px 14px 0 #ffcf33;
    }
    h1 { margin: 0 0 8px; font-size: 34px; }
    p { margin: 0 0 18px; color: #4b5563; }
    label { display: block; margin-bottom: 8px; font-size: 13px; font-weight: 700; letter-spacing: 0.06em; text-transform: uppercase; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px;
      border: 2px solid #111827;
      background: #fff;
      color: #111827;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 14px;
      border: 2px solid #111827;
      background: #111827;
      color: #fff;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="frame" action="/get">
    <h1>Harbor</h1>
    <p>High-contrast poster preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Post To Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Iso_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Iso</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background: linear-gradient(180deg, #ffb074 0%, #ff7f6d 52%, #743d7b 100%);
      font-family: "Segoe UI", sans-serif;
      color: #fff6f2;
    }
    .sunrise {
      width: min(88vw, 420px);
      padding: 28px;
      border-radius: 24px;
      background: rgba(75, 27, 67, 0.32);
      border: 1px solid rgba(255, 255, 255, 0.28);
      box-shadow: 0 20px 50px rgba(71, 19, 60, 0.3);
    }
    h1 { margin: 0 0 8px; text-align: center; }
    p { margin: 0 0 18px; text-align: center; color: #ffe3d9; }
    label { display: block; margin-bottom: 8px; font-size: 14px; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px 16px;
      border-radius: 14px;
      border: 1px solid rgba(255, 255, 255, 0.35);
      background: rgba(255, 255, 255, 0.16);
      color: #fff6f2;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 14px 16px;
      border: none;
      border-radius: 14px;
      background: #fff6f2;
      color: #743d7b;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="sunrise" action="/get">
    <h1>Iso</h1>
    <p>Sunrise gradient preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Glow To Display</button>
  </form>
</body>
</html>
)rawliteral";

const char Jett_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Jett</title>
  <style>
    body {
      margin: 0;
      min-height: 100vh;
      display: grid;
      place-items: center;
      background:
        linear-gradient(rgba(120, 180, 255, 0.15) 1px, transparent 1px),
        linear-gradient(90deg, rgba(120, 180, 255, 0.15) 1px, transparent 1px),
        #081728;
      background-size: 26px 26px;
      color: #dcefff;
      font-family: "Segoe UI", sans-serif;
    }
    .blueprint {
      width: min(88vw, 430px);
      padding: 28px;
      border-radius: 18px;
      background: rgba(7, 18, 31, 0.78);
      border: 1px solid rgba(120, 180, 255, 0.32);
      box-shadow: 0 20px 48px rgba(0, 0, 0, 0.28);
    }
    h1 { margin: 0 0 8px; letter-spacing: 0.08em; }
    p { margin: 0 0 18px; color: #9cc7ef; }
    label { display: block; margin-bottom: 8px; font-size: 13px; text-transform: uppercase; letter-spacing: 0.08em; }
    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px 15px;
      border-radius: 12px;
      border: 1px solid rgba(120, 180, 255, 0.4);
      background: rgba(9, 26, 46, 0.9);
      color: #dcefff;
      font-size: 16px;
    }
    button {
      width: 100%;
      margin-top: 14px;
      padding: 14px 15px;
      border: none;
      border-radius: 12px;
      background: #7cc1ff;
      color: #0a1c30;
      font-size: 16px;
      font-weight: 700;
    }
  </style>
</head>
<body>
  <form class="blueprint" action="/get">
    <h1>Jett</h1>
    <p>Blueprint preview</p>
    <label for="preview_text">Enter preview text</label>
    <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
    <button type="submit">Send Blueprint</button>
  </form>
</body>
</html>
)rawliteral";

const char* const nameme_template_pages[] PROGMEM = {
    Astra_html,
    Breach_html,
    Brimstone_html,
    Chamber_html,
    Clove_html,
    Cypher_html,
    Deadlock_html,
    Fade_html,
    Gekko_html,
    Harbor_html,
    Iso_html,
    Jett_html
};

const size_t nameme_template_page_sizes[] PROGMEM = {
    sizeof(Astra_html) - 1,
    sizeof(Breach_html) - 1,
    sizeof(Brimstone_html) - 1,
    sizeof(Chamber_html) - 1,
    sizeof(Clove_html) - 1,
    sizeof(Cypher_html) - 1,
    sizeof(Deadlock_html) - 1,
    sizeof(Fade_html) - 1,
    sizeof(Gekko_html) - 1,
    sizeof(Harbor_html) - 1,
    sizeof(Iso_html) - 1,
    sizeof(Jett_html) - 1
};
