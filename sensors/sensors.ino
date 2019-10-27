#include <Arduino_JSON.h>

//include ESP8266 library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


int button = D1; //D2(gpio4)
int buttonState=0;
#define LED 2
//For PIR Sensor
int LEDstatus = 12;//chosing pin for PIR sensor led
int PIRsensor = 13; //chhoosing pin for PIR sensor

//For IR sensor
int ledIR = 10; //choosing PIN for IR led
int inputIR = 11; //choosing input pin for IR sensor
int pinIR = 0; //variable for reading PIN status of IR sensor
float chipID = ESP.getChipId();

void setup() 
{
      // put your setup code here, to run once:
      Serial.begin(115200);                 //Serial connection
      WiFi.begin("Samsung Galaxy J3 Prime 6909", "prime6909");   //WiFi connection
          while (WiFi.status() != WL_CONNECTED) 
            {  //Wait for the WiFI connection completion
            delay(5000);
            Serial.println("Waiting for connection");
            }
          if (WiFi.status() == WL_CONNECTED) 
            {
            Serial.println("Connected"); 
            }

           //pinMode(LED, OUTPUT); // defining standalone blue LED as output

           //PIRsensor declaration
           pinMode (PIRsensor, INPUT); //declaring PIR sensor as input
           pinMode (LEDstatus, OUTPUT); //declaring LED as output

           //IR sensor declaration
           pinMode (ledIR, OUTPUT); //declaring LED on IR sensor as output
           pinMode (inputIR, INPUT); //declaring IR sensor as input
  
}

void loop() 
{

  buttonState=digitalRead(button); // put your main code here, to run repeatedly:
  if (buttonState == 1) 
      {
            // put your main code here, to run repeatedly:
            if (WiFi.status()== WL_CONNECTED) //Check WiFi connection status     
              {   
                StaticJsonDocument<300> doc;   //Declaring static JSON buffer
                JsonObject JSONencoder = doc.createNestedObject(); 

                //photoresistor sensor
                int sensorValue = analogRead(A0);   // read the input on analog pin 0
                Serial.println(sensorValue); 
                  /*Alternative serial monitor printing */
                        if (sensorValue >200) 
                          {
                              Serial.println ("Low light conditions" + sensorValue);
                            } 
                      else if (sensorValue < 200) 
                        {
                              Serial.println ("Ambient/Bright light conditions" + sensorValue);
                        }// print out the value you read

                   /* if (sensorValue >200) 
                        {
                          JSONencoder["lights"] = "off";
                        }

                    else if (sensorValue < 200) 
                        {
                            JSONencoder["lights"] = "on";
                        } */

                //led blinking
                /*digitalWrite(LED, LOW);
                Serial.println("LED on"); // Turn the LED on (Note that LOW is the voltage level)
                delay(1000); // Wait for a second
                 digitalWrite(LED, HIGH);
                Serial.println("LED off");// Turn the LED off by making the voltage HIGH
                delay(1000); // Wait for two seconds*/

          //PIR sensor motion detection 
          long state = digitalRead(PIRsensor);
          if (state == HIGH)
          {
            digitalWrite (LEDstatus, HIGH);
            Serial.println("Motion Detected!");

            /*HTTPClient http;    //Declare object of class HTTPClient

            http.begin("http://23.92.26.42/api/motion?id=" + chipID);      //Specify request destination
            http.addHeader("Content-Type", "application/json");  //Specify content-type header

            int httpCode = http.GET();//Send the request

            String payload = http.getString();                  //Get the response payload

            Serial.println("Code:");
            Serial.println(httpCode);   //Print HTTP return code
            Serial.println("Payload:");
            Serial.println(payload);    //Print request response payload

            http.end();  //Close connection

            delay (1000); */
        }
        else if (state == LOW)
        {
          digitalWrite (LEDstatus, LOW);
          Serial.println("Motion absent!");
          delay (1000);
        }
            /*HTTPClient http;    //Declare object of class HTTPClient

            http.begin("http://23.92.26.42/api/motion?id=" );      //Specify request destination
            http.addHeader("Content-Type", "application/json");  //Specify content-type header

            int httpCode = http.GET();//Send the request

            String payload = http.getString();                  //Get the response payload

            Serial.println("Code:");
            Serial.println(httpCode);   //Print HTTP return code
            Serial.println("Payload:");
            Serial.println(payload);    //Print request response payload

            http.end();  //Close connection */
     //IR sensor
     //Digital output High = Detected; Low = not detected
     pinIR = digitalRead(inputIR);
     if (pinIR == HIGH)
     {
      //check if input is HIGH
      digitalWrite(ledIR, LOW); //turn off LED
     }
     else
     {
      digitalWrite(ledIR, LOW); //turn on LED
      }
               
      
    delay(1000);  //Send a request every 30 seconds
  }
      }
  else if (WiFi.status()!= WL_CONNECTED)
              {        
                  Serial.println("Error in WiFi connection");   
              }
else if (buttonState == 0) 
   {
       delay(200);
   }
 }
