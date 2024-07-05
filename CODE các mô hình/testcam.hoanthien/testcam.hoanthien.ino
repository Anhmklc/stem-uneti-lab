#include <PS2X_lib.h> // Thư viện PS2X

#define PS2_DAT_PIN 51
#define PS2_CMD_PIN 50
#define PS2_SEL_PIN 53
#define PS2_CLK_PIN 52 

#define dir1 22 
#define dir2 24 
#define dir3 26  
#define dir4 28    

#define dayluara 8                     // động cơ đẩy lúa ra
#define in1 23
#define in11 25
#define xuc 7                          // động cơ xúc
#define in2 27
#define in22 29
#define keoloxo 6                        // planet kéo lò xo
#define in3 31
#define in33 33
#define xilanh 5                           // xilanh điện
#define in4 35
#define in44 37

#define chot 45                // role van chốt bắn
#define kepbong 47           // role van kẹp bóng 

#define homeban 40           // công tắc home bắn bóng

PS2X ps2x; 
byte max = 170 ; 
byte a=8,b=15,c=255,d=0;        //a: gt up , b:gt down , c:ham/k ham         d:muc giam toc  
int error = 0;
byte type = 0;
byte vibrate = 0;
byte  batdc3 = 0,batdc2 = 0,batdc1 = 0,ban=0,tocdodc3=101,batxl13=0,batxl24=0 ,batxl5=0,batxl6=0,chedokep=0,batxl79=0,batxl810=0,batxl11=0;
unsigned long oldtime=0;
int time;


void setup() {
  Serial.begin(9600);

  ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN, true, true);                     //   // Khởi tạo module PS2X
  int error = ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN);                    // Kiểm tra kết nối nút tay cầm PS2

  if (error == 0) {
    Serial.println("Nút tay cầm PS2 đã được kết nối");
  } else {
    Serial.println("Không tìm thấy nút tay cầm PS2");
  }

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);

  pinMode(dayluara, OUTPUT);            // động cơ đẩy lúa ra
  pinMode(in1, OUTPUT);
  pinMode(in11, OUTPUT);
  pinMode(xuc, OUTPUT);              // động cơ xúc
  pinMode(in2, OUTPUT);
  pinMode(in22, OUTPUT);
  pinMode(keoloxo, OUTPUT);          // planet kéo lò xo
  pinMode(in3, OUTPUT);
  pinMode(in33, OUTPUT);
  pinMode(xilanh, OUTPUT);           // xilanh điện
  pinMode(in4, OUTPUT);
  pinMode(in44, OUTPUT);

pinMode(chot, OUTPUT);                  // role van chốt bắn
pinMode(kepbong, OUTPUT);               // role van kẹp bóng 
pinMode(homeban, INPUT_PULLUP);                // công tắc home bắn bóng

analogWrite(dayluara, 0);
  digitalWrite(in1, HIGH);
  digitalWrite(in11, LOW);
analogWrite(xuc, 0);
  digitalWrite(in2, HIGH);
  digitalWrite(in22, LOW);
analogWrite(keoloxo, 0);
  digitalWrite(in3, HIGH);
  digitalWrite(in33, LOW);
analogWrite(xilanh, 0);
  digitalWrite(in4, HIGH);
  digitalWrite(in44, LOW);

digitalWrite(chot, LOW);
digitalWrite(kepbong, LOW);

 //xung 1 2 
    TCCR1A=0; TCCR1B=0;TIMSK1 = 0;
    DDRB |= (1 << PB6);
    DDRB |= (1 << PB5);
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12)|(1 << WGM13);
    TCCR1A |= (1 << COM1B1);
    TCCR1A |= (1 << COM1A1);
    ICR1 = 255;
    OCR1B = 255;
    OCR1A = 255;
    TCCR1B |= (1 << CS10)|(1 << CS11);
    //xung 3 4
    TCCR2A=0; TCCR2B=0;TIMSK2 = 0;
    DDRB |= (1 << PB4);
    DDRH |= (1 << PH6);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2B1);
    TCCR2A |= (1 << COM2A1);
    OCR2B = 255;
    OCR2A = 255;
    TCCR2B |= (1 << CS22);
  delay(300); 

}






void tangtoc4(){
   if (OCR1B > max){
     if (OCR1B<11){
       OCR1B=0;
       OCR1A=0;
       OCR2A=0;
       OCR2B=0;
     }
     else{
      OCR1B = OCR1B - a;
      OCR1A = OCR1A - a;
      OCR2A = OCR2A - a;
      OCR2B = OCR2B - a;
     }
   delay(70); 
   }
}
void giamtoc4(){
  if (OCR1B <= 230)
   OCR1B = OCR1B + b;
  if (OCR1A <= 230) 
   OCR1A = OCR1A + b;
  if (OCR2A <= 230)   
   OCR2A = OCR2A + b;
  if (OCR2B <= 230) 
   OCR2B = OCR2B + b;
   delay(70); 
   if (OCR1B >=230)
         OCR1B = c;
      if (OCR1A >= 230) 
         OCR1A = c;
      if (OCR2A >= 230)   
         OCR2A = c;
     if (OCR2B >= 230) 
         OCR2B = c;
}
void tangtocxoay(){
   if (OCR1B > 230){
     if (OCR1B<11){
       OCR1B=0;
       OCR1A=0;
       OCR2A=0;
       OCR2B=0;
     }
     else{
      OCR1B = OCR1B - 3;
      OCR1A = OCR1A - 3;
      OCR2A = OCR2A - 3;
      OCR2B = OCR2B - 3;
     }
   delay(50); 
   }
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
  boolean buttonR1 = ps2x.Button(PSB_R1);
  boolean buttonR2 = ps2x.Button(PSB_R2);
  boolean buttonL1 = ps2x.Button(PSB_L1);
  boolean buttonL2 = ps2x.Button(PSB_L2);



if (joyRY > 50) {                   // nâng hạ xi lanh
  analogWrite(xilanh, 255);
  digitalWrite(in4, HIGH);
  digitalWrite(in44, LOW);
    Serial.println("len");
  } 
   if (joyRY < -50) {
  analogWrite(xilanh, 255);
  digitalWrite(in4, LOW);
  digitalWrite(in44, HIGH);
    Serial.println("xuong");
  }
 


if(ps2x.Button(PSB_R1)) {
 

  if (joyLY > 100) {
digitalWrite(dir1, 0);
digitalWrite(dir2, 0);
digitalWrite(dir3, 1);
digitalWrite(dir4, 1);
tangtoc4();
    Serial.println("tien");
  } 
  
 if (joyLY < -100) {
digitalWrite(dir1, 1);
digitalWrite(dir2, 1);
digitalWrite(dir3, 0);
digitalWrite(dir4, 0);
tangtoc4();
    Serial.println("lui");
  }

  if (joyLX > 100) {
      digitalWrite(dir1,1);
      digitalWrite(dir2,0);
      digitalWrite(dir3,1);
      digitalWrite(dir4,0);
      Serial.println("phai");
      tangtoc4();
  } 
  if (joyLX < -100) {
          digitalWrite(dir1,0);
      digitalWrite(dir2,1);
      digitalWrite(dir3,0);
      digitalWrite(dir4,1);
      Serial.println("trai");
      tangtoc4();
  }
}


if(buttonTriangle){
 digitalWrite(kepbong, HIGH);
 Serial.println("kẹp");
  if(digitalRead(homeban) == HIGH){
  analogWrite(keoloxo, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in33, LOW);
digitalWrite(chot, LOW);
  Serial.println("kéo");
return;
 }
   else if(digitalRead(homeban) == LOW){
  analogWrite(keoloxo, 0);
  digitalWrite(in3, HIGH);
  digitalWrite(in33, LOW); 
  Serial.println("dừng kéo");
  return;
 }
analogWrite(xuc, 255);
  digitalWrite(in2, HIGH);
  digitalWrite(in22, LOW);
delay(2500);
digitalWrite(kepbong, HIGH);
analogWrite(xuc, 255);
  digitalWrite(in2, HIGH);
  digitalWrite(in22, LOW);
 if(ps2x.Button(PSB_CIRCLE) && digitalRead(homeban) == LOW){
   digitalWrite(chot, HIGH);
 }
}






}




  



