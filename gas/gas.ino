#include <stdio.h>
char buff[5];
int adc_value;
int gas_value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  adc_value=analogRead(A5);
  gas_value = adc_value*(float)(10000/1023)+200;
  sprintf(buff,"%d\n",gas_value);
  Serial.write(buff);
//  Serial.println(gas_value);
  delay(2000);
}
