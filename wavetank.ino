#define enA 6
#define in1 9
#define in2 10
int potValue;
int pwmOutput;
const int potmotor = A6;
int y;

#include <Adafruit_NeoPixel.h>
#define PIN 8
#define NUMPIXELS 10
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int numReadings = 15;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int x;
const int colorpot = A7;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  pixels.begin();
}

void loop() {
  potValue = analogRead(potmotor);
  pwmOutput = map(potValue, 0, 1024, 0 , 255);
  analogWrite(enA, pwmOutput);

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(colorpot);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  y = map(average, 0, 1024, 0, 65536);
  pixels.clear();
  delay(10);
  uint32_t rgbcolor = pixels.ColorHSV(y);
  pixels.fill(rgbcolor);
  pixels.show();
  delay(10);
}
