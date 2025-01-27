#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 센서 핀 번호
#define ONE_WIRE_BUS 2

// 릴레이 핀 번호
#define RELAY_PIN 3

// OneWire 및 DallasTemperature 객체 생성
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // 릴레이 핀 설정
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // 릴레이 초기 상태: OFF

  // 시리얼 통신 시작
  Serial.begin(9600);
  
  // DS18B20 초기화
  sensors.begin();
}

void loop() {
  // 온도 센서 데이터 요청
  sensors.requestTemperatures();

  // 온도 값 읽기 (섭씨)
  float temperature = sensors.getTempCByIndex(0);

  // 온도 출력
  Serial.print("Current Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // 온도가 정상적으로 읽혔는지 확인
  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Failed to read temperature from DS18B20 sensor.");
  } else {
    // 온도가 정상적으로 읽힌 경우에만 릴레이 제어
    if (temperature >= 5) {
      digitalWrite(RELAY_PIN, LOW); // 릴레이 OFF (30°C 이상)
      Serial.println("Relay OFF: Temperature is 5°C or higher.");
    } else if (temperature <= 1) {
      digitalWrite(RELAY_PIN, HIGH); // 릴레이 ON (28°C 이하)
      Serial.println("Relay ON: Temperature is 1°C or lower.");
    }
  }

  // 딜레이 (5초)
  delay(5000);
}