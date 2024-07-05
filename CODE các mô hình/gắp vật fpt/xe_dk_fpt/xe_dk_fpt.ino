#include <PS2X_lib.h>  //for v1.6           xe 2                   

#define PS2_DAT        53    
#define PS2_CMD        48
#define PS2_SEL        52  
#define PS2_CLK        50  
#define pressures   false
#define rumble      false
#define dir1 28 
#define dir2 26 
#define dir3 24   
#define dir4 22  

#define pwm1 7
#define pwm2 8

#define ctup 23
#define ctdown 25
#define cbhut 37   // xe không dùng

#define gap 41
#define namcham 43

PS2X ps2x; 
byte vibrate=0, type=0, tocdo=0, up=0, down=0, kep=0, hut=0, kh=0;    
float a=2, b=5, c=251, d=2, x=20, y=-20, max=210;
int error = 0;
unsigned long oldtime=0;
int time;
bool L1Pressed = false;


void setup(){
  Serial.begin(9600);

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);

pinMode(pwm1, OUTPUT);
pinMode(pwm2, OUTPUT);
pinMode(gap, OUTPUT);
pinMode(namcham, OUTPUT);

pinMode(ctdown, INPUT_PULLUP);
pinMode(ctup, INPUT_PULLUP);
pinMode(cbhut, INPUT_PULLUP);

analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
digitalWrite(gap, 0);
digitalWrite(namcham, 0);

//------------------------------------------------------------------------------- Di chuyển     
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
delay(50); 
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
delay(30);
  if(error == 0){
    Serial.println("ok");
  }
  else if(error == 1){
    Serial.println("No ok");
  }
 type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
	case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
   }
}
  


void tangtoc(){
   if (OCR1B > max){
      OCR1B = OCR1B - a;
      OCR1A = OCR1A - a;
      OCR2A = OCR2A - a;
      OCR2B = OCR2B - a;
delay(50); 
    }
    if (OCR1B<max){
       OCR1B=max;
       OCR1A=max;
       OCR2A=max;
       OCR2B=max;
     }
}
void giamtoc(){
  if (OCR1B <= 245)
   OCR1B = OCR1B + b;
  if (OCR1A <= 245) 
   OCR1A = OCR1A + b;
  if (OCR2A <= 245)   
   OCR2A = OCR2A + b;
  if (OCR2B <= 245) 
   OCR2B = OCR2B + b;

if (OCR1B >=250)
         OCR1B = c;
if (OCR1A >= 250) 
         OCR1A = c;
if (OCR2A >= 250)   
         OCR2A = c;
if (OCR2B >= 250) 
         OCR2B = c;
}
void xoay(){
   if (OCR1B > max){
      OCR1B = OCR1B - d;
      OCR1A = OCR1A - d;
      OCR2A = OCR2A - d;
      OCR2B = OCR2B - d;
delay(50); 
    }
    if(OCR1B<max){
       OCR1B=max;
       OCR1A=max;
       OCR2A=max;
       OCR2B=max;
     }
}





void loop() {
    ps2x.read_gamepad(false, vibrate);
if (ps2x.NewButtonState()) {        

//-----------------------------------------------------------------------------------------------------tốc độ
 if(tocdo==0){
    max=210;
    a=2, b=40, d=2;
    tocdo=1;
Serial.println("max=210");
}
 if(ps2x.Button(PSB_R2)){
   if(tocdo==1){
    max=130;
    a=7, b=40, d=4;
    tocdo=0;
Serial.println("max=150");
   }
  }
 if(ps2x.Button(PSB_R2) && ps2x.Button(PSB_TRIANGLE)){
    max=1;
    a=10, b=40, d=5;
    tocdo=0;
Serial.println("max=1");
  }



//-----------------------------------------------------------------------------------------------------------nâng hạ
 if(ps2x.Button(PSB_L1)){
  up=1;
analogWrite(pwm1, 255);

Serial.println("nâng");
}
 if(ps2x.Button(PSB_L2)){
  down=1;
analogWrite(pwm2, 255);
Serial.println("hạ");
}


//--------------------------------------------------------------------------dừng nâng
if(ps2x.Button(PSB_SQUARE)){
analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
Serial.println("stop nâng");
}


//----------------------------------------------------------------------------------------------------------kẹp 
if(ps2x.Button(PSB_R3)){
  if(kep==0){
   digitalWrite(gap, 1);
     kep=1;
Serial.println("gắp vào");
  }
  else{
    digitalWrite(gap, 0);
    kep=0;
    kh=1;
Serial.println("mở gắp");
  }
}


//----------------------------------------------------------------------------------------------------------hút 
if(ps2x.Button(PSB_L3)){
  if(hut==0){
   digitalWrite(namcham, 1);
     hut=1;
Serial.println("hút");
  }
  else{
    digitalWrite(namcham, 0);
    hut=0;
    kh=1;
Serial.println("nhả hút");
  }
}





}

//--------------------------------------------------------------------------------------công tắc hành trình
 if((digitalRead(ctup)==0) && up==1){
up=0;
analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
Serial.println("dừng trên");
 }
 if((digitalRead(ctdown)==0) && down==1){
down=0;
analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
Serial.println("dừng dưới");
 }

// //---------------------------------------------------------------------auto kẹp
// if(digitalRead(cbhut)==0 && hut==0 && kep==0 && kh==0){
//   digitalWrite(namcham, 1);
// Serial.println("hút vào");
// delay(200);
//   digitalWrite(gap, 1);
// Serial.println("gắp vào");
// kep=1, hut=1, kh=1;
// }
// if(digitalRead(cbhut)==1){
//   kh=0;
// }





            
//------------------------------------------------------------------------------joystik ps2
   if(ps2x.Button(PSB_R1)) {
      int analogLX = ps2x.Analog(PSS_LX)-128;
      int analogLY = ps2x.Analog(PSS_LY)-127;
      int analogRX = ps2x.Analog(PSS_RX)-128;
      int analogRY = ps2x.Analog(PSS_RY)-127;
if((analogRY<=x) && (analogRY>=y) && (analogRX<=x) && (analogRX>=y)){
  if (analogLY==128) {
      digitalWrite(dir1,1);
      digitalWrite(dir2,1);
      digitalWrite(dir3,0);
      digitalWrite(dir4,0);
      tangtoc();
  }
  if  (analogLY==-127) {
      digitalWrite(dir1,0);
      digitalWrite(dir2,0);
      digitalWrite(dir3,1);
      digitalWrite(dir4,1);
      tangtoc();
  }
  if  (analogLX==127) {
      digitalWrite(dir1,1);
      digitalWrite(dir2,0);
      digitalWrite(dir3,0);
      digitalWrite(dir4,1);
      tangtoc();
  }
  if  (analogLX==-128) { 
      digitalWrite(dir1,0);
      digitalWrite(dir2,1);
      digitalWrite(dir3,1);
      digitalWrite(dir4,0);
      tangtoc();
  }
}
  if  (analogRX==-128) {   
        digitalWrite(dir1,0);
        digitalWrite(dir2,0);
        digitalWrite(dir3,0);
        digitalWrite(dir4,0);
        xoay();
  }
  if  (analogRX==127) { 
        digitalWrite(dir1,1);
        digitalWrite(dir2,1);
        digitalWrite(dir3,1);
        digitalWrite(dir4,1); 
        xoay();
  }

 if ((analogLX<=x) && (analogLX>=y) && (analogLY<=x) && (analogLY>=y) && (analogRY<=x) && (analogRY>=y) && (analogRX<=x) && (analogRX>=y) && !(ps2x.Button(PSB_R3)) && !(ps2x.Button(PSB_L3))) { 
  if ((OCR1B <= 250) && (OCR1A <= 250) && (OCR2A <= 250) && (OCR2B <= 250)){
   OCR1B = OCR1B + b;
   OCR1A = OCR1A + b;
   OCR2A = OCR2A + b;
   OCR2B = OCR2B + b;
  }
    else{
         OCR1B = c;
         OCR1A = c;
         OCR2A = c;
         OCR2B = c;
    }
  }
 }
else{
       OCR1B=251;
       OCR1A=251;
       OCR2A=251;
       OCR2B=251;
 }
}

