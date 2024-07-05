volatile unsigned long pulseCount1 = 0;
volatile unsigned long pulseCount2 = 0;
#define led1 11      // bánh
#define led2 12      // tời
const int on = 9; 
volatile bool resetFlag = false;

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(on, INPUT_PULLUP);
  
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);

  attachInterrupt(digitalPinToInterrupt(2), incrementPulseCount1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), incrementPulseCount2, RISING);
}

void loop() {

  static unsigned long lastPrintTime = 0;
  unsigned long currentTime = millis();

  // if (currentTime - lastPrintTime >= 1000) {
  //   noInterrupts();  
  //   unsigned long count1 = pulseCount1;
  //   unsigned long count2 = pulseCount2;
  //   interrupts(); 

  //   Serial.print("Pulse count 1: ");
  //   Serial.print(count1);
  //   Serial.print("\tPulse count 2: ");
  //   Serial.println(count2);

  //   lastPrintTime = currentTime;
  // }

  if (digitalRead(on)==1) {
    noInterrupts(); 
    pulseCount1 = 0;
    pulseCount2 = 0;
    interrupts(); 
    digitalWrite(led1, 0);
    digitalWrite(led2, 0);
    // Serial.println("Counts reset");
  }


}

void incrementPulseCount1() {            // bánh
  pulseCount1++;
    if(pulseCount1==23){                  // sân đỏ (24), sân xanh 22 ( xanh 23)
    digitalWrite(led1, 1);
  }
}
   
void incrementPulseCount2() {             // tời
  pulseCount2++;
      if(pulseCount2==40){                    // ( sân xanh )
    digitalWrite(led2, 1);
  }
}
