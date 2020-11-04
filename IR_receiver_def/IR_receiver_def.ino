#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}
 
void loop() 
{
  decode_results results;

  if (irrecv.decode(&results)){
    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
      Serial.println(results.value, HEX);
      //Serial.print((char)results.value);
      irrecv.resume();
  }
}
