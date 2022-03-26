#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "DuyPham";
const char* password =  "28112000";

unsigned long myChannelNumber = 1641656;                         //Thingspeak channel number
const char * myWriteAPIKey = "RAIVHGA8UYVI2I1M";                  //Thingspeak API write key
WiFiClient client;

volatile byte index_uart = 0;
char buff[20];
byte data_rx;
int flag_rx = 0;
int gas_value;
int temp;
int cnt_update = 0;

void print_cli(const char* str, ...)
{
  char stringArray[128];
  
  va_list args;
  va_start(args, str);
  uint8_t len_str = vsprintf(stringArray, str, args);
  va_end(args);
  
  Serial2.write(stringArray);
}


void setup() 
{
  Serial2.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial2.println("Connecting to WiFi..");
  }
  Serial2.println("Connected to the WiFi network");
  ThingSpeak.begin(client); 
}
  
void loop()
{
  data_handle();
  Time_Update();
}


void data_handle()
{
  while(Serial2.available())
      {
          data_rx = Serial2.read();
          buff[index_uart++] = data_rx ;
          if(data_rx =='\n')
          {
            flag_rx = 1;
          }
      }
      
      if(flag_rx == 1)
      {                                 
        char *argv[10];
        uint8_t num_arg =0;
        char *token = strtok(buff," ");
        
        while(token != NULL)
        {
          argv[num_arg++] = token;    
          token = strtok(NULL," ");
        }
          temp = atoi(argv[0]);
          gas_value = atoi(argv[1]);
          //print_cli("%s\n",buff);
          print_cli("Temp: %d\n",temp);
          print_cli("Gas value: %d\n",gas_value);
        
          cnt_update ++;
          memset(buff,0,index_uart);
          index_uart = 0;
          flag_rx = 0;
      } 
}


void Time_Update()
{
  if(cnt_update >10)  // 30s
  {
    updateThingSpeak();
    cnt_update = 0;
  }
}
void updateThingSpeak ()                                             //Function to post data to Thingspeak
{
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, gas_value);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200)
  {
    //    Serial2.println(buff);
    Serial2.println("Channel update successful");
  }
  else
  {
    Serial2.println("Problem updating channel. HTTP error code " + String(x));
  }
}
  
