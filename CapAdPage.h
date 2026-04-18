/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#pragma once

#include <Arduino.h>

const char capad_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <base href="/">
  <title>Crabox - Digital Solutions</title>
  <style>
    html, body {
      margin: 0;
      padding: 0;
      background-color: #000;
      color: #fff;
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      text-align: center;
      overflow-x: hidden;
      scroll-behavior: smooth;
    }

    .logo {
      margin: 60px auto 30px;
      max-width: 220px;
      display: block;
      transition: transform 0.5s ease, box-shadow 0.5s ease;
      cursor: pointer;
      filter: drop-shadow(0 0 10px #f29f1a);
    }

    .logo:hover {
      transform: scale(1.1) rotate(-3deg);
      box-shadow: 0 12px 24px rgba(255, 255, 255, 0.25);
    }

    #info-section {
      max-width: 750px;
      margin: 0 auto;
      background: rgba(255, 255, 255, 0.05);
      border-radius: 18px;
      padding: 35px 40px;
      box-shadow: 0 15px 30px rgba(0, 0, 0, 0.6);
      text-align: left;
      margin-bottom: 50px;
    }

    #info-section h2 {
      color: #f29f1a;
      margin-bottom: 18px;
      font-size: 32px;
    }

    #info-section h3 {
      color: #f8b740;
      margin-top: 30px;
      font-size: 24px;
    }

    #info-section ul {
      padding-left: 24px;
      list-style-type: square;
    }

    #info-section li {
      margin-bottom: 10px;
      font-size: 17px;
    }

    .service-image {
      display: block;
      margin: 40px auto 30px;
      max-width: 98%;
      height: auto;
      border-radius: 15px;
      box-shadow: 0 5px 25px rgba(255, 255, 255, 0.15);
      transition: transform 0.4s ease-in-out, box-shadow 0.4s ease-in-out;
      animation: floatUpDown 3s ease-in-out infinite;
    }

    .service-image:hover {
      transform: scale(1.05);
      box-shadow: 0 10px 30px rgba(255, 255, 255, 0.4);
    }

    @keyframes floatUpDown {
      0% { transform: translateY(0); }
      50% { transform: translateY(100px); }
      100% { transform: translateY(0); }
    }

    .bottom-buttons {
      position: fixed;
      bottom: 30px;
      width: 100%;
      display: flex;
      justify-content: center;
      gap: 20px;
      z-index: 999;
    }

    .social-btn {
      font-size: 18px;
      padding: 12px 25px;
      border: none;
      border-radius: 12px;
      cursor: pointer;
      transition: all 0.3s ease;
      font-weight: bold;
      color: white;
      user-select: none;
      box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
    }

    .social-btn.instagram {
      background: linear-gradient(135deg, #e1306c, #c13584);
    }

    .social-btn.instagram:hover {
      background: linear-gradient(135deg, #c13584, #833ab4);
      transform: translateY(-3px) scale(1.05);
      box-shadow: 0 8px 20px #c13584;
    }

    .social-btn.linkedin {
      background: linear-gradient(135deg, #0077b5, #005983);
    }

    .social-btn.linkedin:hover {
      background: linear-gradient(135deg, #005983, #003f5c);
      transform: translateY(-3px) scale(1.05);
      box-shadow: 0 8px 20px #005983;
    }

    audio {
      display: none;
    }

    #bottom-anchor {
      height: 1px;
      margin-bottom: 200px;
    }
  </style>
  <script>
    function toggleMusic() {
      const music = document.getElementById('bg-music');
      if (music.paused) music.play();
      else music.pause();
    }

    function openInstagram() {
      window.location = 'instagram://user?username=crabox_';
      setTimeout(() => window.location = 'https://www.instagram.com/crabox_/#', 1500);
      setTimeout(() => window.location = '/wifioff?site=instagram', 3000);
    }

    function openLinkedIn() {
      window.location = 'linkedin://company/crabox';
      setTimeout(() => window.location = 'https://www.linkedin.com/company/crabox', 1500);
      setTimeout(() => window.location = '/wifioff?site=linkedin', 3000);
    }

    function slowScrollTo(element, duration) {
      const targetPosition = element.getBoundingClientRect().top + window.pageYOffset;
      const startPosition = window.pageYOffset;
      const distance = targetPosition - startPosition;
      let startTime = null;

      function animation(currentTime) {
        if (startTime === null) startTime = currentTime;
        const timeElapsed = currentTime - startTime;
        const run = easeInOutQuad(timeElapsed, startPosition, distance, duration);
        window.scrollTo(0, run);
        if (timeElapsed < duration) {
          requestAnimationFrame(animation);
        }
      }

      function easeInOutQuad(t, b, c, d) {
        t /= d / 2;
        if (t < 1) return c / 2 * t * t + b;
        t--;
        return -c / 2 * (t * (t - 2) - 1) + b;
      }

      requestAnimationFrame(animation);
    }

    window.addEventListener('load', () => {
      setTimeout(() => {
        const anchor = document.getElementById('bottom-anchor');
        slowScrollTo(anchor, 100);
      }, 1000);
    });

    let musicPlayed = false;
    function tryPlayMusic() {
      if (!musicPlayed) {
        const music = document.getElementById('bg-music');
        const playPromise = music.play();
        if (playPromise !== undefined) {
          playPromise.then(() => {
            musicPlayed = true;
          }).catch(() => {
          });
        }
      }
    }

    ['touchstart', 'click', 'scroll', 'keydown', 'mousemove'].forEach(eventType => {
      window.addEventListener(eventType, tryPlayMusic, { once: true });
    });
  </script>
</head>
<body>
  <img src="/logo.png" class="logo" onclick="toggleMusic()" title="Click to play/pause music" onerror="this.style.display='none'">

  <div id="info-section">
    <h2>The Right Choice for Your Digital Growth</h2>
    <h3>Our Services:</h3>
    <ul>
      <li>Mobile Applications</li>
      <li>Custom Websites</li>
      <li>Smart Invoicing Systems</li>
      <li>Custom-Built PCs & Tech</li>
      <li>Internet of Things (IoT) Solutions</li>
    </ul>

    <img src="/instapage.jpg" alt="Instagram Showcase" class="service-image" onerror="this.onerror=null;this.src='/image.jpg';" />
  </div>

  <div class="bottom-buttons">
    <button class="social-btn instagram" onclick="openInstagram()">Instagram</button>
    <button class="social-btn linkedin" onclick="openLinkedIn()">LinkedIn</button>
  </div>

  <div id="bottom-anchor"></div>
  <audio id="bg-music" src="/music.mp3" loop preload="auto"></audio>
</body>
</html>
)rawliteral";

const char nameme_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>FISH Preview</title>
  <style>
    :root {
      --bg-1: #11203b;
      --bg-2: #1f4a8a;
      --panel: rgba(255, 255, 255, 0.12);
      --line: rgba(255, 255, 255, 0.25);
      --text: #eef4ff;
      --accent: #8bd3ff;
    }

    body {
      margin: 0;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      background:
        radial-gradient(circle at top left, #3d79d8 0%, transparent 32%),
        linear-gradient(145deg, var(--bg-1), var(--bg-2));
      color: var(--text);
      font-family: "Segoe UI", Arial, sans-serif;
    }

    .panel {
      width: min(88vw, 420px);
      padding: 28px;
      border: 1px solid var(--line);
      border-radius: 22px;
      background: var(--panel);
      backdrop-filter: blur(10px);
      box-shadow: 0 20px 50px rgba(0, 0, 0, 0.28);
    }

    h1 {
      margin: 0 0 8px;
      font-size: 34px;
      text-align: center;
      letter-spacing: 0.06em;
    }

    p {
      margin: 0 0 20px;
      text-align: center;
      color: var(--accent);
    }

    label {
      display: block;
      margin-bottom: 10px;
      font-size: 14px;
      text-transform: uppercase;
      letter-spacing: 0.08em;
    }

    input {
      width: 100%;
      box-sizing: border-box;
      padding: 14px 16px;
      font-size: 16px;
      color: var(--text);
      background: rgba(8, 15, 28, 0.28);
      border: 1px solid var(--line);
      border-radius: 14px;
    }

    button {
      width: 100%;
      margin-top: 18px;
      padding: 14px 16px;
      font-size: 16px;
      font-weight: 700;
      color: #082038;
      background: #8bd3ff;
      border: none;
      border-radius: 999px;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <div class="panel">
    <form action="/get">
      <h1>FISH</h1>
      <p>Safe preview mode</p>
      <label for="preview_text">Enter preview text</label>
      <input id="preview_text" name="preview_text" type="text" maxlength="32" placeholder="Type something for the display" required>
      <button type="submit">Send To Display</button>
    </form>
  </div>
</body>
</html>
)rawliteral";