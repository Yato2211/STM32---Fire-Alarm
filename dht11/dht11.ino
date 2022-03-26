#include "DHT.h"  
#include <stdio.h>      
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  

char buff_uart[3];  
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin(); 

}

void loop() {
      
  int humi = dht.readHumidity();    
  int temp = dht.readTemperature(); 
  sprintf(buff_uart,"%d\n",temp);
 
//  Serial.println(buff_uart);   // ham nay tu dong gui them dau cach
  Serial.write(buff_uart);                   // ham nay phai tu them      
  delay(2000);                     
}
