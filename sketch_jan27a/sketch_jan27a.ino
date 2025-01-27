#include <DHT.h>

// DHT 센서 설정
#define DHTPIN 2       // AM2302의 데이터 핀을 D2에 연결
#define DHTTYPE DHT22  // 센서 타입: DHT22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// 내부 LED 핀 설정
#define LED_BUILTIN 13

void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);
  Serial.println("DHT22 온습도 측정 시작");

  // DHT 센서 초기화
  dht.begin();

  // LED 핀을 출력 모드로 설정
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // 온도와 습도 읽기
  float temperature = dht.readTemperature(); // 섭씨 온도 읽기
  float humidity = dht.readHumidity();       // 습도 읽기

  // 데이터 유효성 확인
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("온습도 데이터를 읽을 수 없습니다!");
  } else {
    Serial.print("현재 온도: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("현재 습도: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // LED 블링킹
  digitalWrite(LED_BUILTIN, HIGH); // LED 켜기
  delay(1000);                     // 1초 대기
  digitalWrite(LED_BUILTIN, LOW);  // LED 끄기
  delay(1000);                     // 1초 대기
}
