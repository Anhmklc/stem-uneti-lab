#include <PS2X_lib.h>
#include <AFMotor.h>



PS2X ps2x;

int error = 0;
byte vibrate = 0; 
AF_DCMotor M1(1);
AF_DCMotor M4(4);
AF_DCMotor M2(2);
AF_DCMotor M3(3);

void setup()
{

  Serial.begin(9600);

  error = ps2x.config_gamepad(A0, A1, A2, A3, true, true); //(clock, command, attention, data)

  if (error == 0)
  {
    Serial.println("Controlador encontrado y configurado");
  }
  else
  {
    Serial.println("Error, mando no encontrado");
  }

  M2.run(RELEASE);
  M3.run(RELEASE);
  M1.run(RELEASE);
  M4.run(RELEASE);

}

void loop()
{

  int temp;
  ps2x.read_gamepad(false, vibrate);

  vibrate = ps2x.Analog(PSAB_BLUE);

  if (ps2x.Button(PSB_PAD_UP))
  {

    Serial.print("LEN ");
    M3.setSpeed(255);
    M3.run(BACKWARD);
    M4.setSpeed(255);
    M4.run(BACKWARD);

  }


  else if (ps2x.Button(PSB_PAD_DOWN))
  {

    Serial.print("XUONG ");
    M4.setSpeed(255);
    M4.run(FORWARD);
    M3.setSpeed(255);
    M3.run(FORWARD);

  }

  else if (ps2x.Button(PSB_PAD_LEFT))
  {

    Serial.println("TRAI ");
    M4.setSpeed(255);
    M4.run(BACKWARD);
    M3.setSpeed(255);
    M3.run(FORWARD);

  }

  else if (ps2x.Button(PSB_PAD_RIGHT))
  {

    Serial.println("PHAI ");
    M4.setSpeed(255);
    M4.run(FORWARD);
    M3.setSpeed(255);
    M3.run(BACKWARD);

  }

  if (ps2x.ButtonPressed(PSB_CIRCLE))
  {
    Serial.println("Circle just pressed");
    M1.run(FORWARD);
    M1.setSpeed(255);
  }

  if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
  {
    Serial.println("Square just released");
    M1.run(BACKWARD);
    M1.setSpeed(255);
  }


  else if (ps2x.Button(PSB_SELECT))
  {
    Serial.println("Presionaste seleccionar: ");

  }
  else if (ps2x.Button(PSB_START))
  {
    Serial.println("Presionaste entrar: ");
  }
  if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)

    if (ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if (ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if (ps2x.Button(PSB_L2))
    {
      Serial.println("L2 pressed");
      M1.run(RELEASE);

    }
    if (ps2x.Button(PSB_R1) )
    {
      Serial.print("R1 pressed");

    }
    if (ps2x.Button(PSB_R2))
    {
      Serial.println("R2 pressed");

    }
    if (ps2x.Button(PSB_TRIANGLE))
    {
      Serial.println("Triangle pressed");
      M2.run(FORWARD);
      M2.setSpeed(255);
    }
    if (ps2x.Button(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
    {
      Serial.println("X just changed");
      M2.run(BACKWARD);
      M2.setSpeed(255);
    }
  }
  if (ps2x.Button(PSB_L1) ) { //print stick values if either is TRUE

  }

  if ((ps2x.ButtonReleased(PSB_PAD_UP)) || (ps2x.ButtonReleased(PSB_PAD_DOWN)) || (ps2x.ButtonReleased(PSB_PAD_LEFT)) || (ps2x.ButtonReleased(PSB_PAD_RIGHT)) || (ps2x.ButtonReleased(PSB_TRIANGLE)) || (ps2x.ButtonReleased(PSB_CROSS)) || (ps2x.ButtonReleased(PSB_CIRCLE)) || (ps2x.ButtonReleased(PSB_SQUARE)))
  {
    M2.run(RELEASE);
    M3.run(RELEASE);

    M4.run(RELEASE);

  }

  delay(50);

}
