#define LED 2
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//For PIR Sensor
int LEDstatus = 12;//chosing pin for PIR sensor led
int PIRsensor = 13; //chhoosing pin for PIR sensor

//For IR sensor
int ledIR = 12; //choosing PIN for IR led
int inputIR = 13; //choosing input pin for IR sensor
int pinIR = 0; //variable for reading PIN status of IR sensor

//ultrasonic sensors

#define TRIGPIN 5 //D4 or 2  or  5& D1
#define ECHOPIN 4 //D3 or 0 or  4 & D2

void setup() 
{
          // put your setup code here, to run once:

          
          
         
         /* pinMode(LED, OUTPUT); */ // defining standalone blue LED as output

          
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
                  delay (2000);
                  }

                  //PIRsensor declaration
           pinMode (PIRsensor, INPUT); //declaring PIR sensor as input
           pinMode (LEDstatus, OUTPUT); //declaring LED as output


               //IR sensor declaration
               pinMode (ledIR, OUTPUT); //declaring LED on IR sensor as output
               pinMode (inputIR, INPUT); //declaring IR sensor as input


                  //ultrasonic sensor
             pinMode (TRIGPIN, OUTPUT); //setting trigger pin as an Output
             pinMode (ECHOPIN, INPUT); //setting echo pin as an Input 


              
}

void loop() 
{
                  // put your main code here, to run repeatedly:
                  //led blinking
                /*digitalWrite(LED, LOW);
                Serial.println("LED on"); // Turn the LED on (Note that LOW is the voltage level)
                delay(1000); // Wait for a second
                 digitalWrite(LED, HIGH);
                Serial.println("LED off");// Turn the LED off by making the voltage HIGH
                delay(1000); // Wait for two seconds */
                
                if (WiFi.status() == WL_CONNECTED) //perform operations once connected to WiFi
                {
                                  delay (1000);
                                 /* Photoresistor */
                                  int photo_res_value = analogRead (A0);
                                  Serial.println(photo_res_value);
                                      if (photo_res_value > 200)
                                      {
                                       Serial.println("Low light"); 
                                      }
                                      else if (photo_res_value < 200)
                                      {
                                        Serial.println ("Ambient/Bright light");                                      
                                      }


                               //PIR sensor motion detection 
                              long state = digitalRead(PIRsensor);
                              if (state == HIGH)
                              {
                                      digitalWrite (LEDstatus, HIGH);
                                      Serial.println("Motion Detected!");
                                      delay (200);
                              }
                              else if (state == LOW)
                              {
                                      digitalWrite (LEDstatus, LOW);
                                      Serial.println("Motion absent!");
                                      delay (200);
                              }


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


                              //ultrasonic sensor

                              //clears the trigPin
                              digitalWrite(TRIGPIN, LOW);
                              delayMicroseconds(2);

                              //sets trigPin HIGH for 10 micro seconds
                              digitalWrite (TRIGPIN, HIGH);
                              delayMicroseconds(10);

                              
                              digitalWrite(TRIGPIN, LOW);
                              //Reads the echoPin
                              //returns the sound travel time in microseconds
                              long duration = pulseIn(ECHOPIN, HIGH);

                              //calculating distance
                              long distance = duration*0.034/2;

                              //print distance in serial monitor
                              Serial.print("Distance:");
                              Serial.print(distance);
                              Serial.println(" cm");
                              //delay(200); 
                              
                }

                else if (WiFi.status()!= WL_CONNECTED) //when unable to connect to WiFi
                {
                  Serial.println("Error in WiFI connection");
                }

}
