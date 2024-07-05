#include <PS2X_lib.h> // Thư viện PS2X

#define PS2_DAT_PIN 51
#define PS2_CMD_PIN 50
#define PS2_SEL_PIN 53
#define PS2_CLK_PIN 52

PS2X ps2x; // Đối tượng PS2X

// Chân kết nối driver BTS7960
int enA = 4;
int in1 = 23;
int in2 = 25;
int enB = 5;
int in3 = 27;
int in4 = 29;
int enC = 6;
int in5 = 31;
int in6 = 33;
int enD = 7;
int in7 = 35;
int in8 = 37;
int enE = 8;
int in9 = 39;
int in10 = 41;
int enF = 9;
int in11 = 43;
int in12 = 45;

void setup() {
  Serial.begin(9600);

  // Khởi tạo module PS2X
  ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN, true, true);

  // Kiểm tra kết nối nút tay cầm PS2
  int error = ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN);

  if (error == 0) {
    Serial.println("Nút tay cầm PS2 đã được kết nối");
  } else {
    Serial.println("Không tìm thấy nút tay cầm PS2");
  }

  // Thiết lập chân kết nối driver BTS7960
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(enE, OUTPUT);
  pinMode(in9, OUTPUT);
  pinMode(in10, OUTPUT);
  pinMode(enF, OUTPUT);
  pinMode(in11, OUTPUT);
  pinMode(in12, OUTPUT);
}

void loop() {
  ps2x.read_gamepad();

  // Đọc giá trị từ joystick và nút điều khiển
  int joyLX = ps2x.Analog(PSS_LX);
  int joyLY = ps2x.Analog(PSS_LY);
  int joyRX = ps2x.Analog(PSS_RX);
  int joyRY = ps2x.Analog(PSS_RY);
  boolean buttonUp = ps2x.Button(PSB_PAD_UP);
  boolean buttonDown = ps2x.Button(PSB_PAD_DOWN);
  boolean buttonLeft = ps2x.Button(PSB_PAD_LEFT);
  boolean buttonRight = ps2x.Button(PSB_PAD_RIGHT);
  boolean buttonTriangle = ps2x.Button(PSB_TRIANGLE);
  boolean buttonCross = ps2x.Button(PSB_CROSS);
  boolean buttonSquare = ps2x.Button(PSB_SQUARE);
  boolean buttonCircle = ps2x.Button(PSB_CIRCLE);

  // Điều khiển chuyển động của robot dựa trên giá trị joystick và nút điều khiển
  int motorSpeedA = map(joyLY, 0, 255, -255, 255);
  int motorSpeedB = map(joyRY, 0, 255, -255, 255);

  // Điều khiển động cơ và xuất hành động lên Serial Monitor
  motorControl(motorSpeedA, motorSpeedB, joyLX, joyRX, buttonUp, buttonDown, buttonLeft, buttonRight, buttonTriangle, buttonCross, buttonSquare, buttonCircle);

  delay(100);
}


// Hàm điều khiển động cơ robot
void motorControl(int speedA, int speedB, int joyLX, int joyRX, boolean buttonUp, boolean buttonDown, boolean buttonLeft, boolean buttonRight, boolean buttonTriangle, boolean buttonCross, boolean buttonSquare, boolean buttonCircle) {
  // Điều khiển động cơ A
  if (speedA > 50) {
    analogWrite(enA, speedA);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (speedA < -50) {
    analogWrite(enA, abs(speedA));
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enA, 0);
  }

  // Điều khiển động cơ B
  if (speedB > 50) {
    analogWrite(enB, speedB);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (speedB < -50) {
    analogWrite(enB, abs(speedB));
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enB, 0);
  }

  // Điều khiển động cơ C
  if (buttonUp) {
    analogWrite(enC, 255);
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (buttonDown) {
    analogWrite(enC, 255);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enC, 0);
  }

  // Điều khiển động cơ D
  if (buttonTriangle) {
    analogWrite(enD, 255);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (buttonCross) {
    analogWrite(enD, 255);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enD, 0);
  }

  // Điều khiển động cơ E
  if (buttonLeft) {
    analogWrite(enE, 255);
    digitalWrite(in9, HIGH);
    digitalWrite(in10, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (buttonRight) {
    analogWrite(enE, 255);
    digitalWrite(in9, LOW);
    digitalWrite(in10, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enE, 0);
  }

  // Điều khiển động cơ F
  if (buttonSquare) {
    analogWrite(enF, 255);
    digitalWrite(in11, HIGH);
    digitalWrite(in12, LOW);
    Serial.println("Robot di chuyen ve phia truoc");
  } else if (buttonCircle) {
    analogWrite(enF, 255);
    digitalWrite(in11, LOW);
    digitalWrite(in12, HIGH);
    Serial.println("Robot di chuyen ve phia sau");
  } else {
    analogWrite(enF, 0);
  }
}
