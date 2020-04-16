/* This code works with ESP8266 12E NodeMcu its main function is to read data from https://www.worldometers.info/
   * Through ThingSpeak app ThingHTTP and displays on the Serial monitor 
   * also through BLYNK data is displace on BLYNK serial which can be seen on any device
   * This project was created during COVID-19 pandemic and it tracks numbers in KENYA
    */

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#include <ESP8266WiFi.h>        //Use ESP8266 functions                                              
#include <ESP8266HTTPClient.h>
// to write to blynk
#include <BlynkSimpleEsp8266.h>

char auth[]="XZis3p_CVZzT2AKVGgYghSS_vTRzRoXR"; // blynk token
                                                                       
 char ssid[] = "xxxxxxxxx";              //Your router SSID and password                             
char password[] =  "xxxxxxxx"; 

const char* host = "api.thingspeak.com";
const int httpPortRead = 80;                                           
                                                
const char* url1 = "/apps/thinghttp/send_request?api_key=G09FQCP02O91H6NI";     //Those URLs are mine but I kept them so you can replace the key only
const char* url2 = "/apps/thinghttp/send_request?api_key=DPCA7JHHB148OJVD";
const char* url3 = "/apps/thinghttp/send_request?api_key=6FAFZP7ZQ1XVY54Y"; 


int To_remove;      //There are some irrelevant data on the string and here's how I keep the index
                    //of those characters 

String Cases,Death,Recover,Data_Raw;  //Here I keep the numbers that I got

WiFiClient client;      //Create a WiFi client and http client                                                     
HTTPClient http; 
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);            //Start the serial communication 
  Blynk.begin(auth, ssid, password);// start bynk                                                          

  //WiFi.mode(WIFI_STA);// use it as station mode 
  WiFi.disconnect();             //Disconnect and reconnect to the Wifi you set                                                 
  delay(1000); 

   WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
     Serial.println(ssid);                                                
  Blynk.begin(auth, ssid, password);
  
  Serial.println("Connected to the WiFi network");   //Display feedback on the serial monitor                                        
  Serial.println(WiFi.localIP()); 

}

void loop() {
  // put your main code here, to run repeatedly:

   //Reading 1: Reading of cases
    if( http.begin(host,httpPortRead,url1))        //Connect to the host and the url                                      
      {
        Blynk.run();
        int httpCode = http.GET();                //Check feedback if there's a response                                                  
        if (httpCode > 0)                                                              
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   //Here we store the raw data string

              Serial.print("Cases (RAW value): ");  //I choosed to display it on the serial monitor to help you debug
              Serial.println(Data_Raw);
                                                    
              To_remove = Data_Raw.indexOf(">");                      //I look for the position of this symbol ">"                                 
              Data_Raw.remove(0,To_remove+1);                        //I remove it and everything that's before
              To_remove = Data_Raw.indexOf("<");                     //I look for the position of this symbol ">"                                
              Data_Raw.remove(To_remove,Data_Raw.length());          //I remove it and everything that's after
                                                                     //Example: This is the raw data received <td style="font-weight: bold; text-align:right">63,927</td>
                                                                     //First we look for ">" and we remove everything before it including it
                                                                     //We stay with this 63,927</td>
                                                                     //We look for "<" symbol and we remove it + everything after
                                                                     //We keep only this 63,927 as string
              Cases=Data_Raw;
              Serial.print("Cases: ");  //I choosed to display it on the serial monitor to help you debug
              Serial.println(Cases);   
              Blynk.virtualWrite(V0, Cases); // write deaths to blynk                                            
                                                                                        
            }
        }
        else //If we can't get data
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }



        http.end();                                                                 
      } 
    else //If we can't connect to the HTTP
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }

//Reading 2 is the same thing as reading 1

      if( http.begin(host,httpPortRead,url2))                                              
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   
              
              Serial.print("Deaths (RAW value): ");
              Serial.println(Data_Raw);
                                                    
              To_remove = Data_Raw.indexOf(">");                                   
              Data_Raw.remove(0,To_remove+1); 
              To_remove = Data_Raw.indexOf("<");                                   
              Data_Raw.remove(To_remove,Data_Raw.length());

              Death=Data_Raw;
              Serial.print("Deaths: ");
              Serial.println(Death);

               Blynk.virtualWrite(V1, Death);

                                                                
                                                                                        
            }
        }
        else 
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }



        http.end();                                                                 
      } 
    else 
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }

//Reading 3 is the same thing as reading 1

      if( http.begin(host,httpPortRead,url3))                                              
      {
        int httpCode = http.GET();                                                      
        if (httpCode > 0)                                                               
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   

              Serial.print("Recoveries (RAW value): ");
              Serial.println(Data_Raw);
                                                    
              To_remove = Data_Raw.indexOf(">");                                   
              Data_Raw.remove(0,To_remove+1); 
              To_remove = Data_Raw.indexOf("<");                                   
              Data_Raw.remove(To_remove,Data_Raw.length());

              Recover=Data_Raw;
              Serial.print("Recoveries: ");
              Serial.println(Recover);

               Blynk.virtualWrite(V2, Recover);
                                                                 
                                                                                        
            }
        }
        else 
        {
          Serial.printf("[HTTP] GET... failed, error1: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();                                                                 
      } 
    else 
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }
    
    delay(5000);

    while (WiFi.status() != WL_CONNECTED)     //In case the Wifi connexion is lost                                    
      { 
        
        WiFi.disconnect();                                                        
        delay(1000);                                                             
        
        WiFi.begin(ssid, password);                                              
        Serial.println("Reconnecting to WiFi..");       
        delay(10000);                                                             
      }


}
