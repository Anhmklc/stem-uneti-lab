#include <PS2X_lib.h>
#include <Servo.h>

#define PS2_DAT_PIN 11
#define PS2_CMD_PIN 12
#define PS2_SEL_PIN 10
#define PS2_CLK_PIN 13

PS2X ps2x;
Servo continuousServo;

struct Motor {
  int enablePin;
  int in1Pin;
  int in2Pin;
};

Motor motors[] = {
  {4, 23, 25},  // Motor A
  {5, 27, 29},  // Motor B
  {6, 31, 33},  // Motor C
  {7, 35, 37},  // Motor D
  {8, 39, 41},  // Motor E
  {9, 43, 45}   // Motor F
};

void setup() {
  Serial.begin(9600);
  ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN, true, true);
  continuousServo.attach(3); // Kết nối servo quay liên tục vào chân 9
  continuousServo.write(90); // Đặt servo ở vị trí trung tâm ban đầu

  for (int i = 0; i < sizeof(motors) / sizeof(motors[0]); i++) {
    pinMode(motors[i].enablePin, OUTPUT);
    pinMode(motors[i].in1Pin, OUTPUT);
    pinMode(motors[i].in2Pin, OUTPUT);
  }
}

void loop() {
  ps2x.read_gamepad();
  
  int joyLX = ps2x.Analog(PSS_LX);

  if (joyLX > 127) {
    int speed = map(joyLX, 135, 255, 0, -180);
    continuousServo.write(speed); // Quay theo chiều kim đồng hồ
  } else if (joyLX < 127) {
    int speed = map(joyLX, 0, 120, 180, 0);
    continuousServo.write(speed); // Quay ngược chiều kim đồng hồ
  } else {
    continuousServo.write(0); // Dừng lại
  }
// động cơ 550
  int joyLY = ps2x.Analog(PSS_LY);
  int joyRY = ps2x.Analog(PSS_RY);
// 2 động cơ đen bên phải
  boolean buttonUp = ps2x.Button(PSB_PAD_UP);
  boolean buttonDown = ps2x.Button(PSB_PAD_DOWN);
  boolean buttonLeft = ps2x.Button(PSB_PAD_LEFT);
  boolean buttonRight = ps2x.Button(PSB_PAD_RIGHT);
// 2 động cơ đen bên trái
  boolean buttonTriangle = ps2x.Button(PSB_TRIANGLE);
  boolean buttonCross = ps2x.Button(PSB_CROSS);
  boolean buttonSquare = ps2x.Button(PSB_SQUARE);
  boolean buttonCircle = ps2x.Button(PSB_CIRCLE); 
// 4 dộng cơ đồng thời
  boolean buttonL1 = ps2x.Button(PSB_L1);
  boolean buttonL2 = ps2x.Button(PSB_L2);
  boolean buttonR1 = ps2x.Button(PSB_R1);
  boolean buttonR2 = ps2x.Button(PSB_R2);

  int speedA = map(joyLY, 0, 255, -255, 255);
  int speedB = map(joyRY, 0, 255, -255, 255);

  int speedC = (buttonUp || buttonL1) ? 255 : ((buttonDown || buttonL2) ? -255 : 0);
  int speedE = (buttonLeft || buttonR1) ? 255 : ((buttonRight || buttonR2) ? -255 : 0);

  int speedD = (buttonTriangle || buttonL1) ? 255 : ((buttonCross || buttonL2) ? -255 : 0);
  int speedF = (buttonSquare || buttonR1) ? 255 : ((buttonCircle || buttonR2) ? -255 : 0);

  motorControl(speedA, speedB, speedC, speedD, speedE, speedF);

  delay(100);

}

void motorControl(int speedA, int speedB, int speedC, int speedD, int speedE, int speedF) {
  analogWrite(motors[0].enablePin, abs(speedA));
  digitalWrite(motors[0].in1Pin, (speedA > 0) ? HIGH : LOW);
  digitalWrite(motors[0].in2Pin, (speedA < 0) ? HIGH : LOW);

  analogWrite(motors[1].enablePin, abs(speedB));
  digitalWrite(motors[1].in1Pin, (speedB > 0) ? HIGH : LOW);
  digitalWrite(motors[1].in2Pin, (speedB < 0) ? HIGH : LOW);

  analogWrite(motors[2].enablePin, abs(speedC));
  digitalWrite(motors[2].in1Pin, (speedC > 0) ? HIGH : LOW);
  digitalWrite(motors[2].in2Pin, (speedC < 0) ? HIGH : LOW);

  analogWrite(motors[3].enablePin, abs(speedD));
  digitalWrite(motors[3].in1Pin, (speedD > 0) ? HIGH : LOW);
  digitalWrite(motors[3].in2Pin, (speedD < 0) ? HIGH : LOW);

  analogWrite(motors[4].enablePin, abs(speedE));
  digitalWrite(motors[4].in1Pin, (speedE > 0) ? HIGH : LOW);
  digitalWrite(motors[4].in2Pin, (speedE < 0) ? HIGH : LOW);

  analogWrite(motors[5].enablePin, abs(speedF));
  digitalWrite(motors[5].in1Pin, (speedF > 0) ? HIGH : LOW);
  digitalWrite(motors[5].in2Pin, (speedF < 0) ? HIGH : LOW);
}
