// https://github.com/T-vK/ESP32-BLE-Keyboard
#include <BleKeyboard.h>
#include <config.h>

BleKeyboard bleKeyboard(KEYBOARD_NAME);

void KeyInit(const uint8_t key_pin)
{
  pinMode(key_pin, INPUT_PULLUP);
}
bool isKeyDown(const uint8_t key_pin)
{
  return !digitalRead(key_pin);
}

bool KeyReader(const uint8_t pin, const char key)
{
  const bool key_tmp = isKeyDown(pin);

  if (key_tmp)
    bleKeyboard.press(key);
  else
    bleKeyboard.release(key);

  return key_tmp;
}

void setup()
{
  KeyInit(PIN_W);
  KeyInit(PIN_A);
  KeyInit(PIN_S);
  KeyInit(PIN_D);
  pinMode(PIN_LED, OUTPUT);
  bleKeyboard.begin();
}

void loop()
{
  // もしキーボードが接続されていなかったら
  if (!bleKeyboard.isConnected())
  {
    // 3s 待機
    delay(3000);
    return;
  }

  // 10ms 待機
  delay(10);

  // WASD 入力
  if (KeyReader(PIN_W, 'w') ||
      KeyReader(PIN_A, 'a') ||
      KeyReader(PIN_S, 's') ||
      KeyReader(PIN_D, 'd'))
    // LED 点灯
    digitalWrite(PIN_LED, HIGH);
  else
    // LED 消灯
    digitalWrite(PIN_LED, LOW);
}