#include <AccelStepper.h>
#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;



// Khai báo chân động cơ
AccelStepper LeftBackWheel(1, A0, A1);   // Động cơ 1   (Type:driver, STEP, DIR) (X)
AccelStepper LeftFrontWheel(1, 46, 48);  // Động cơ 2                            (Y)
AccelStepper RightBackWheel(1, 26, 28);  // Động cơ 3                            (E0)
AccelStepper RightFrontWheel(1, 36, 34); // Động cơ 4                            (E1)

//Khai báo chân đèn led và quạt

#define fan 10
#define led 47

int wheelSpeed = 1700;

int lbw[50], lfw[50], rbw[50], rfw[50]; // Bộ nhớ dùng để lưu trữ vị trí/ bước của động cơ/ bánh xe
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // vị trí hiện tại của động cơ Servo
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; //  vị trí trước đó của động cơ Servo
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50]; // Bộ nhớ để lưu trữ vị trí/bước của động cơ Servo
int speedDelay = 20;
int index = 0;
int dataIn;
int m = 0;

void setup() {
  // Cài đặt giá trị ban đầu cho các bước của động cơ/ bánh xe
  LeftFrontWheel.setMaxSpeed(5000);
  LeftBackWheel.setMaxSpeed(5000);
  RightFrontWheel.setMaxSpeed(5000);
  RightBackWheel.setMaxSpeed(5000);

  pinMode(led, OUTPUT);
  pinMode(fan,OUTPUT);

  //Khai báo chân cho động cơ Servo
  servo01.attach(3);
  servo02.attach(2);
  servo03.attach(14);
  servo04.attach(15);
  servo05.attach(18);
  servo06.attach(19);

  //Khai báo braud rate cho module Bluetooth
  Serial.begin(9600);

  // Cài đặt gốc ban đầu và đưa cánh tay về vị trí ban đầu khi được cấp nguồn điện
  
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 100;
  servo02.write(servo2PPos);
  servo3PPos = 120;
  servo03.write(servo3PPos);
  servo4PPos = 95;
  servo04.write(servo4PPos);
  servo5PPos = 60;
  servo05.write(servo5PPos);
  servo6PPos = 110;
  servo06.write(servo6PPos);
}

void loop() {

  digitalWrite(fan,HIGH);
  digitalWrite(led,HIGH);

  // Kiểm tra tín hiệu từ Module Bluetooh đến Arduino
  if (Serial.available() > 0) {
    dataIn = Serial.read();  // Đọc dữ liệu

    if (dataIn == 0) {
      m = 0;
    }
    if (dataIn == 1) {
      m = 1;
    }
    if (dataIn == 2) {
      m = 2;
    }
    if (dataIn == 3) {
      m = 3;
    }
    if (dataIn == 4) {
      m = 4;
    }
    if (dataIn == 5) {
      m = 5;
    }
    if (dataIn == 6) {
      m = 6;
    }
    if (dataIn == 7) {
      m = 7;
    }
    if (dataIn == 8) {
      m = 8;
    }
    if (dataIn == 9) {
      m = 9;
    }
    if (dataIn == 10) {
      m = 10;
    }
    if (dataIn == 11) {
      m = 11;
    }
    if (dataIn == 12) {
      m = 12;
    }
    if (dataIn == 14) {
      m = 14;
    }
    if (dataIn == 16) {
      m = 16;
    }
    if (dataIn == 17) {
      m = 17;
    }
    if (dataIn == 18) {
      m = 18;
    }
    if (dataIn == 19) {
      m = 19;
    }
    if (dataIn == 20) {
      m = 20;
    }
    if (dataIn == 21) {
      m = 21;
    }
    if (dataIn == 22) {
      m = 22;
    }
    if (dataIn == 23) {
      m = 23;
    }
    if (dataIn == 24) {
      m = 24;
    }
    if (dataIn == 25) {
      m = 25;
    }
    if (dataIn == 26) {
      m = 26;
    }
    if (dataIn == 27) {
      m = 27;
    }

    // Thực hiện các hướng di chuyển của xe theo giá trị được nhận về từ Module Bluetooth
    if (m == 4) {
      moveSidewaysLeft();
    }
    if (m == 5) {
      moveSidewaysRight();
    }
    if (m == 2) {
      moveForward();
    }
    if (m == 7) {
      moveBackward();
    }
    if (m == 3) {
      moveRightForward();
    }
    if (m == 1) {
      moveLeftForward();
    }
    if (m == 8) {
      moveRightBackward();
    }
    if (m == 6) {
      moveLeftBackward();
    }
    if (m == 9) {
      rotateLeft();
    }
    if (m == 10) {
      rotateRight();
    }

    if (m == 0) {
      stopMoving();
    }

    // Tốc độ bánh xe
    if (dataIn > 30 & dataIn < 100) {
      wheelSpeed = dataIn * 40;
    }

    // Di chuyển cánh tay robot
    // Di chuyển động cơ Servo 1
    while (m == 16) {        // Di chuyển hướng quay của động cơ Servo cùng chiều kim đồng hồ
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo01.write(servo1PPos);
      servo1PPos++;
      delay(speedDelay);
    }
    
    while (m == 17) {
      if (Serial.available() > 0) { // Di chuyển hướng quay của động cơ Servo ngược chiều kim đồng hồ
        m = Serial.read();
      }
      servo01.write(servo1PPos);
      servo1PPos--;
      delay(speedDelay);
    }
    // Di chuyển động cơ Servo 2
    while (m == 19) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo02.write(servo2PPos);
      servo2PPos++;
      delay(speedDelay);
    }
    while (m == 18) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo02.write(servo2PPos);
      servo2PPos--;
      delay(speedDelay);
    }
    // Di chuyển động cơ Servo 3
    while (m == 20) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo03.write(servo3PPos);
      servo3PPos++;
      delay(speedDelay);
    }
    while (m == 21) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo03.write(servo3PPos);
      servo3PPos--;
      delay(speedDelay);
    }
    // Di chuyển động cơ Servo 4
    while (m == 23) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo04.write(servo4PPos);
      servo4PPos++;
      delay(speedDelay);
    }
    while (m == 22) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo04.write(servo4PPos);
      servo4PPos--;
      delay(speedDelay);
    }
    // Di chuyển động cơ Servo 5
    while (m == 25) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo05.write(servo5PPos);
      servo5PPos++;
      delay(speedDelay);
    }
    while (m == 24) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo05.write(servo5PPos);
      servo5PPos--;
      delay(speedDelay);
    }
    // Di chuyển động cơ Servo 6
    while (m == 26) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo06.write(servo6PPos);
      servo6PPos++;
      delay(speedDelay);
    }
    while (m == 27) {
      if (Serial.available() > 0) {
        m = Serial.read();
      }
      servo06.write(servo6PPos);
      servo6PPos--;
      delay(speedDelay);
    }

    // Nếu thanh trượt tốc độ của cánh tay robot bị thay đổi
    if (dataIn > 101 & dataIn < 250) {
      speedDelay = dataIn / 10; // Thay đổi tốc độ quay của động cơ Servo (delay time)
    }

    // Nếu nút nhấn "SAVE" được nhấn
    if (m == 12) {
      // Nên đặt vị trí ban đầu là vị trí 0
      if (index == 0) {
        LeftBackWheel.setCurrentPosition(0);
        LeftFrontWheel.setCurrentPosition(0);
        RightBackWheel.setCurrentPosition(0);
        RightFrontWheel.setCurrentPosition(0);
      }
      lbw[index] = LeftBackWheel.currentPosition();  // Lưu vị trí vào bộ nhớ
      lfw[index] = LeftFrontWheel.currentPosition();
      rbw[index] = RightBackWheel.currentPosition();
      rfw[index] = RightFrontWheel.currentPosition();

      servo01SP[index] = servo1PPos;  // Lưu vị trí vào bộ nhớ
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      servo05SP[index] = servo5PPos;
      servo06SP[index] = servo6PPos;
      index++;                        // Tăng chỉ số bộ nhớ 
      m = 0;
    }

    // Nếu nút nhấn "RUN" được nhấn
    if (m == 14) {
      runSteps();

      // Nếu nút nhấn "RESET" được nhấn
      if (dataIn != 14) {
        stopMoving();
        memset(lbw, 0, sizeof(lbw)); // Xóa toàn bộ vị trí đã lưu trong bộ nhớ về 0
        memset(lfw, 0, sizeof(lfw));
        memset(rbw, 0, sizeof(rbw));
        memset(rfw, 0, sizeof(rfw));
        memset(servo01SP, 0, sizeof(servo01SP)); // Xóa toàn bộ vị trí đã lưu trong bộ nhớ về 0
        memset(servo02SP, 0, sizeof(servo02SP));
        memset(servo03SP, 0, sizeof(servo03SP));
        memset(servo04SP, 0, sizeof(servo04SP));
        memset(servo05SP, 0, sizeof(servo05SP));
        memset(servo06SP, 0, sizeof(servo06SP));
        index = 0;  // Đưa giá trị về 0
      }
    }
  }
  LeftFrontWheel.runSpeed();
  LeftBackWheel.runSpeed();
  RightFrontWheel.runSpeed();
  RightBackWheel.runSpeed();


}
void moveForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void rotateLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void rotateRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveRightForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}

// Chế độ tự động - chạy các vị trí/ bước đã lưu trong bộ nhớ
void runSteps() {
  while (dataIn != 13) {   // Thực hiện lặp đi lặp lại các vị trí/ bước đã lưu trong bộ nhớ cho đến khi nhấn nút "RESET"
    for (int i = 0; i <= index - 2; i++) {  // Chạy qua tất cả các bước 
      if (Serial.available() > 0) {      // Kiểm tra dữ liệu đọc được từ Module Bluetooth đến Arduino
        dataIn = Serial.read();
        if ( dataIn == 15) {           // Nếu nút nhất "PAUSE" được nhấn
          while (dataIn != 14) {         // Chờ cho đến khi nút nhấn "RUN" được nhấn lại
            if (Serial.available() > 0) {
              dataIn = Serial.read();
              if ( dataIn == 13) {
                break;
              }
            }
          }
        }
        // Nếu thanh trượt tốc độ bị thay đổi
        if (dataIn > 100 & dataIn < 150) {
          speedDelay = dataIn / 10; // Thay đổi tốc độ động cơ Servo (delay time)
        }
        // Tốc độ bánh xe Mecanum
        if (dataIn > 30 & dataIn < 100) {
          wheelSpeed = dataIn * 10;
          dataIn = 14;
        }
      }
      LeftFrontWheel.moveTo(lfw[i]);
      LeftFrontWheel.setSpeed(wheelSpeed);
      LeftBackWheel.moveTo(lbw[i]);
      LeftBackWheel.setSpeed(wheelSpeed);
      RightFrontWheel.moveTo(rfw[i]);
      RightFrontWheel.setSpeed(wheelSpeed);
      RightBackWheel.moveTo(rbw[i]);
      RightBackWheel.setSpeed(wheelSpeed);

      while (LeftBackWheel.currentPosition() != lbw[i] & LeftFrontWheel.currentPosition() != lfw[i] & RightFrontWheel.currentPosition() != rfw[i] & RightBackWheel.currentPosition() != rbw[i]) {
        LeftFrontWheel.runSpeedToPosition();
        LeftBackWheel.runSpeedToPosition();
        RightFrontWheel.runSpeedToPosition();
        RightBackWheel.runSpeedToPosition();
      }
      // Động cơ Servo 1
      if (servo01SP[i] == servo01SP[i + 1]) {
      }
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Động cơ Servo 2
      if (servo02SP[i] == servo02SP[i + 1]) {
      }
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Động cơ Servo 3
      if (servo03SP[i] == servo03SP[i + 1]) {
      }
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Động cơ Servo 4
      if (servo04SP[i] == servo04SP[i + 1]) {
      }
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }

      // Động cơ Servo 5
      if (servo05SP[i] == servo05SP[i + 1]) {
      }
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }

      // Động cơ Servo 6
      if (servo06SP[i] == servo06SP[i + 1]) {
      }
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}
