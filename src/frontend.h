#pragma once

const char INDEX_HTML[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang="ru">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Управление машиной</title>

    <style>
      body {
        margin: 0;
        background: #222;
        color: white;
        font-family: Arial;
        text-align: center;
        user-select: none;
        touch-action: none;
      }

      h2 {
        margin-top: 20px;
      }

      .joystick {
        width: 250px;
        height: 250px;
        background: #444;
        border-radius: 50%;
        margin: 40px auto;
        position: relative;
        border: 4px solid #666;
      }

      .stick {
        width: 90px;
        height: 90px;
        background: #2196F3;
        border-radius: 50%;
        position: absolute;

        left: 80px;
        top: 80px;

        box-shadow: 0 4px 10px #000;
      }

      .status {
        font-size: 24px;
        margin-top: 20px;
        color: #00ff88;
      }

      .dpad {
        display: grid;
        grid-template-columns: repeat(3, 70px);
        grid-template-rows: repeat(3, 70px);
        gap: 6px;
        width: max-content;   /* ← сжать до размера кнопок */
        margin: 20px auto;    /* ← центрировать по горизонтали */
      }

      .dpad button {
        width: 70px;
        height: 70px;
        font-size: 22px;
        font-weight: bold;
        border: none;
        border-radius: 10px;
        background: #2196F3;
        color: white;
        cursor: pointer;
        user-select: none;
      }

      .dpad button:active { background: #1565C0; }

      /* расстановка по сетке */
      .up    { grid-column: 2; grid-row: 1; }
      .left  { grid-column: 1; grid-row: 2; }
      .right { grid-column: 3; grid-row: 2; }
      .down  { grid-column: 2; grid-row: 3; }

      .dpad2x2 {
        display: grid;
        grid-template-columns: repeat(2, 70px);
        grid-template-rows: repeat(2, 70px);
        gap: 6px;

        width: max-content;
        margin: 30px auto;
      }

      .dpad2x2 button {
        width: 70px;
        height: 70px;
        font-size: 22px;
        font-weight: bold;
        border: none;
        border-radius: 10px;
        background: #2196F3;
        color: white;
        cursor: pointer;
        user-select: none;
      }

      .dpad2x2 button:active { background: #1565C0; }

      .control-panel {
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 40px;
        width: 100%;
      }

      .camera-container {
        display: flex;
        flex-direction: column;
        gap: 10px;
      }

      .camera-settings {
        display: flex;
        gap: 5px;
      }

      #cameraPage {
        width: 700px;
        height: 500px;
        border: 1px solid #ccc;
      }

      .joystick-container {
        display: flex;
        align-items: center;
        justify-content: center;
      }
    </style>
  </head>

  <body>

    <h2>Управление</h2>
    <div class="control-panel">
      <div class="camera-container">
        <div class="camera-settings">
          <input type="text" id="cameraUrl" placeholder="https://example.com">
          <button id="updateCameraUrl">Изменить iframe</button>
        </div>

        <iframe id="cameraPage" src="" width="700" height="500"></iframe>
      </div>

      <div class="joystick-container">
        <div id="joystick-move" class="joystick">
          <div id="stick-move" class="stick"></div>
        </div>
      </div>
    </div>

    <div id="status-move" class="status">СТОП</div>

    <div id="cameraController" class="dpad">
      <button class="up" onclick="sendCommandCamera('camera_up')">Вверх</button>
      <button class="down" onclick="sendCommandCamera('camera_down')">Вниз</button>
      <button class="right" onclick="sendCommandCamera('camera_left')">Вправо</button>
      <button class="left" onclick="sendCommandCamera('camera_right')">Влево</button>
    </div>
    <div class="dpad2x2">
      <button class="d" onclick="sendCommand('run_d')">D</button>
      <button class="b" onclick="sendCommand('run_b')">B</button>
      <button class="c" onclick="sendCommand('run_c')">C</button>
      <button class="a" onclick="sendCommand('run_a')">A</button>
      <button class="stop" onclick="sendCommand('stop')">stop</button>
    </div>

  <script>

  const joystick = document.getElementById("joystick-move");
  const stick = document.getElementById("stick-move");
  const statusText = document.getElementById("status-move");

  let active_move = false;
  let lastCommand_move = "";

  function sendCommand(command) {

    if (command === lastCommand_move)
      return;

    lastCommand_move = command;

    fetch("/" + command)
      .catch(() => {});

    statusText.innerText = command.toUpperCase();
  }

  function sendCommandCamera(command) {
    fetch("/" + command)
      .catch(() => {});

    statusText.innerText = command.toUpperCase();
  }

  function stop() {
    lastCommand_move = "";
    fetch("/stop").catch(() => {});
    statusText.innerText = "СТОП";
  }

  function moveJoystick(x, y) {

    const rect = joystick.getBoundingClientRect();

    const centerX = rect.width / 2;
    const centerY = rect.height / 2;

    let dx = x - rect.left - centerX;
    let dy = y - rect.top - centerY;

    const maxDistance = 80;

    const distance = Math.sqrt(dx * dx + dy * dy);

    if (distance > maxDistance) {
      dx = dx / distance * maxDistance;
      dy = dy / distance * maxDistance;
    }

    stick.style.left = (centerX - 45 + dx) + "px";
    stick.style.top  = (centerY - 45 + dy) + "px";


    // Определяем направление

    if (Math.abs(dx) < 20 && Math.abs(dy) < 20) {
      return;
    }

    if (Math.abs(dx) > Math.abs(dy)) {

      if (dx > 0) {
        sendCommand("right");
      } else {
        sendCommand("left");
      }

    } else {

      if (dy < 0) {
        sendCommand("forward");
      } else {
        // Назад пока не реализован в Arduino
        sendCommand("back");
      }
    }
  }


  // МЫШЬ

  joystick.addEventListener("mousedown", function(e) {
    active_move = true;
    moveJoystick(e.clientX, e.clientY);
  });

  document.addEventListener("mousemove", function(e) {
    if (active_move) {
      moveJoystick(e.clientX, e.clientY);
    }
  });

  document.addEventListener("mouseup", function() {
    if (active_move) {
      active_move = false;

      stick.style.left = "80px";
      stick.style.top = "80px";

      stop();
    }
  });


  // СЕНСОРНЫЙ ЭКРАН

  joystick.addEventListener("touchstart", function(e) {
    active_move = true;

    const touch = e.touches[0];

    moveJoystick(touch.clientX, touch.clientY);

    e.preventDefault();
  });

  joystick.addEventListener("touchmove", function(e) {
    if (active_move) {

      const touch = e.touches[0];

      moveJoystick(touch.clientX, touch.clientY);

      e.preventDefault();
    }
  });

  joystick.addEventListener("touchend", function() {

    active_move = false;

    stick.style.left = "80px";
    stick.style.top = "80px";

    stop();
  });

  const pressedKeys = new Set();

  // Маппинг клавиш на команды
  const keyMap = {
    "ArrowUp":    "forward",
    "ArrowDown":  "back",
    "ArrowLeft":  "left",
    "ArrowRight": "right",
    "KeyW":       "forward",
    "KeyS":       "back",
    "KeyA":       "left",
    "KeyD":       "right",
  };

  // Функция, которая определяет, какую команду слать,
  // исходя из всех зажатых клавиш (диагонали и приоритеты)
  function updateFromKeyboard() {

    let dx = 0;
    let dy = 0;

    if (pressedKeys.has("ArrowRight") || pressedKeys.has("KeyD")) dx += 1;
    if (pressedKeys.has("ArrowLeft")  || pressedKeys.has("KeyA")) dx -= 1;
    if (pressedKeys.has("ArrowUp")    || pressedKeys.has("KeyW")) dy -= 1;
    if (pressedKeys.has("ArrowDown")  || pressedKeys.has("KeyS")) dy += 1;

    // Ничего не нажато — стоп
    if (dx === 0 && dy === 0) {
      stop();
      resetStickVisual();
      return;
    }

    // Двигаем «виртуальный стик» для визуальной обратной связи
    const maxDistance = 80;
    let vx = dx;
    let vy = dy;
    const len = Math.sqrt(vx * vx + vy * vy);
    if (len > 1) { vx /= len; vy /= len; } // нормализуем диагональ

    const centerX = joystick.clientWidth / 2;
    const centerY = joystick.clientHeight / 2;

    stick.style.left = (centerX - 45 + vx * maxDistance) + "px";
    stick.style.top  = (centerY - 45 + vy * maxDistance) + "px";

    // Определяем команду (та же логика, что и в moveJoystick)
    if (Math.abs(dx) > Math.abs(dy)) {
      sendCommand(dx > 0 ? "right" : "left");
    } else if (Math.abs(dy) > Math.abs(dx)) {
      sendCommand(dy < 0 ? "forward" : "back");
    } else {
      // Диагональ — можно выбрать приоритет.
      // Например, вперёд-вправо → "forward" (как у вас в джойстике приоритет вертикали)
      sendCommand(dy < 0 ? "forward" : "back");
    }
  }

  function resetStickVisual() {
    stick.style.left = "80px";
    stick.style.top  = "80px";
  }

  // Нажатие клавиши
  document.addEventListener("keydown", function(e) {

    // Игнорируем, если фокус в поле ввода (на всякий случай)
    if (e.target.tagName === "INPUT" || e.target.tagName === "TEXTAREA") return;

    // Стоп по пробелу или Escape
    if (e.code === "Space" || e.code === "Escape") {
      e.preventDefault();
      pressedKeys.clear();
      stop();
      resetStickVisual();
      return;
    }

    if (keyMap[e.code]) {
      e.preventDefault(); // чтобы страница не скроллилась стрелками
      pressedKeys.add(e.code);
      updateFromKeyboard();
    }
  });

  // Отпускание клавиши
  document.addEventListener("keyup", function(e) {
    if (keyMap[e.code]) {
      pressedKeys.delete(e.code);
      updateFromKeyboard();
    }
  });

  // Если окно потеряло фокус — сбрасываем всё (иначе клавиша «залипнет»)
  window.addEventListener("blur", function() {
    pressedKeys.clear();
    stop();
    resetStickVisual();
  });


  const input = document.getElementById('cameraUrl');
  const iframe = document.getElementById('cameraPage');
  const button = document.getElementById('updateCameraUrl');

  button.addEventListener('click', () => {
    const newUrl = input.value; 

    iframe.src = newUrl;
  });

  </script>

  </body>
  </html>
)rawliteral";