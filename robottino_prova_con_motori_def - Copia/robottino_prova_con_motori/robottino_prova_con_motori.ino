#include <Matrix.h>
#include <IRremote.h>

long ir_rec;

Matrix myMatrix(A4, A5);
IRrecv irrecv(A1);
decode_results results;

uint8_t smile[8] = {0x00, 0x18, 0x24, 0x00, 0x00, 0xa5, 0xa5, 0x42};
uint8_t front2[8] = {0x00, 0x81, 0x42, 0x24, 0x99, 0x42, 0x24, 0x18};
uint8_t back2[8] = {0x18, 0x24, 0x42, 0x99, 0x24, 0x42, 0x81, 0x00};
uint8_t left2[8] = {0x48, 0x24, 0x12, 0x09, 0x09, 0x12, 0x24, 0x48};
uint8_t right2[8] = {0x12, 0x24, 0x48, 0x90, 0x90, 0x48, 0x24, 0x12};
uint8_t stop2[8] = {0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18};
uint8_t  LEDArray[8];

void setup() {
  Serial.begin(9600);
  myMatrix.begin(112);

  myMatrix.clear();
  irrecv.enableIRIn();

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {

  myMatrix.writeDisplay();
  for (int i = 0; i < 8; i++)
  {
    LEDArray[i] = smile[i];
    for (int j = 7; j >= 0; j--)
    {
      if ((LEDArray[i] & 0x01) > 0)
        myMatrix.drawPixel(j, i, 1);
      LEDArray[i] = LEDArray[i] >> 1;
    }
  }
  myMatrix.writeDisplay();

  if (irrecv.decode(&results)) {
    ir_rec = results.value;
    String type = "UNKNOWN";
    String typelist[14] = {"UNKNOWN", "NEC", "SONY", "RC5", "RC6", "DISH", "SHARP", "PANASONIC", "JVC", "SANYO", "MITSUBISHI", "SAMSUNG", "LG", "WHYNTER"};
    if (results.decode_type >= 1 && results.decode_type <= 13) {
      type = typelist[results.decode_type];
    }
    Serial.print("IR TYPE:" + type + "  ");
    Serial.println(ir_rec, HEX);
    irrecv.resume();
  } else {

  }
  // va avanti
  if (ir_rec == 0xFF629D) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = front2[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();

    digitalWrite(4, LOW);
    analogWrite(5, 100);
    digitalWrite(2, LOW);
    analogWrite(9, 100);
    delay(2000);

    ir_rec = 0xFF02FD;
  }
  // stop
  if (ir_rec == 0xFF02FD) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = stop2[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();

    digitalWrite(4, LOW);
    analogWrite(5, 0);
    digitalWrite(2, LOW);
    analogWrite(9, 0);
    delay(2000);
  }
  // gira a sinistra
  if (ir_rec == 0xFF22DD) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = left2[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();

    digitalWrite(4, LOW);
    analogWrite(5, 100);
    digitalWrite(2, HIGH);
    analogWrite(9, 0);
    delay(2000);

    ir_rec = 0xFF02FD;
  }
  // va indietro
  if (ir_rec == 0xFFA857) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = back2[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();

    digitalWrite(4, HIGH);
    analogWrite(5, 100);
    digitalWrite(2, HIGH);
    analogWrite(9, 100);
    delay(2000);

    ir_rec = 0xFF02FD;
  }
  // gira a destra
  if (ir_rec == 0xFFC23D) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = right2[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();

    digitalWrite(4, HIGH);
    analogWrite(5, 0);
    digitalWrite(2, LOW);
    analogWrite(9, 100);
    delay(2000);
    
    ir_rec = 0xFF02FD;
  }
  // smile
  if (ir_rec == 0xFF42BD) {
    myMatrix.clear();
    myMatrix.writeDisplay();
    for (int i = 0; i < 8; i++)
    {
      LEDArray[i] = smile[i];
      for (int j = 7; j >= 0; j--)
      {
        if ((LEDArray[i] & 0x01) > 0)
          myMatrix.drawPixel(j, i, 1);
        LEDArray[i] = LEDArray[i] >> 1;
      }
    }
    myMatrix.writeDisplay();
  }
}
