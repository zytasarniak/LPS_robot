#pragma once

const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
  body {
    font-family: sans-serif;
    text-align: center;
    background-color: #f0f0f0;
  }

  .modes {
    margin: 20px 0;
    display: flex;
    justify-content: center;
    gap: 20px;
  }

  .mode-btn {
    width: 120px !important;
    height: 60px !important;
    font-size: 18px !important;
    background: #28a745 !important;
  }

  .pad {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 10px;
  }

  .middle {
    display: flex;
    gap: 10px;
  }

  button {
    width: 100px;
    height: 100px;
    font-size: 40px;
    border-radius: 12px;
    border: none;
    background: #333;
    color: white;
    user-select: none;
    -webkit-user-select: none;
    touch-action: manipulation;
  }
  
  .cat-btn {
  width: 100px;
  height: 100px;
  font-size: 36px;
  padding: 10px;
  margin-top: 10px;
  background: #dfca95;
  border-radius: 20%;
}


  button:active {
    background: #555;
  }

  .stop-btn {
    background: #d9534f;
  }
</style>
</head>

<body>

  <div class="modes">
    <button class="mode-btn" onclick="fetch('/manual')">MANUAL</button>
    <button class="mode-btn" style="background:#007bff !important;" onclick="fetch('/auto')">AUTO</button>
  </div>

  <div class="pad">
    <button ontouchstart="fetch('/forward')" ontouchend="fetch('/stop')" onmousedown="fetch('/forward')" onmouseup="fetch('/stop')">▲</button>

    <div class="middle">
      <button ontouchstart="fetch('/left')" ontouchend="fetch('/stop')" onmousedown="fetch('/left')" onmouseup="fetch('/stop')">◀</button>
      <button class="stop-btn" onclick="fetch('/stop')">■</button>
      <button ontouchstart="fetch('/right')" ontouchend="fetch('/stop')" onmousedown="fetch('/right')" onmouseup="fetch('/stop')">▶</button>
    </div>

    <button ontouchstart="fetch('/backward')" ontouchend="fetch('/stop')" onmousedown="fetch('/backward')" onmouseup="fetch('/stop')">▼</button>
  </div>
  
<div>
  <button class="cat-btn" ontouchstart="fetch('/miau')">🐱</button>
</div>


</body>
</html>
)rawliteral";