// include ESP8266 library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int button = D1; //D2(gpio4)
int buttonState=0;

void setup()
{
  Serial.begin(115200); // serial connection
  WiFi.begin("Samsung Galaxy J3 Prime 6909", "prime6909");  //WiFi connection

  // wait for the WiFI connection completion
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(5000);
    Serial.println("Waiting for connection");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connected"); 
  }
}

void loop()
{
  buttonState=digitalRead(button);
  if (buttonState == 1)
  {
    // check WiFi connection status
    if (WiFi.status()== WL_CONNECTED)
    {
      StaticJsonBuffer<300> JSONbuffer;   // declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject();

      // photoresistor sensor
      int sensorValue = analogRead(A0);   // read the input on analog pin 0
  
      Serial.println(sensorValue);   // print out the value you read

      if (sensorValue > 1000)
      {
        JSONencoder["lights"] = "on";
      }
      else if (sensorValue < 1000)
      {
        JSONencoder["lights"] = "off";
      }
      
      char JSONmessageBuffer[300];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);
 
      HTTPClient http;    // declare object of class HTTPClient
 
      http.begin("http://enjiela.pythonanywhere.com/api/add");      // specify request destination
      http.addHeader("Content-Type", "application/json");  // specify content-type header
 
      int httpCode = http.POST(JSONmessageBuffer);  // send the request
    
      String payload = http.getString();  // get the response payload

      Serial.println("Code:");
      Serial.println(httpCode);   // print HTTP return code
      Serial.println("Payload:");
      Serial.println(payload);    // print request response payload
      http.end();  // close connection
    }
    else
    {
      Serial.println("Error in WiFi connection");   
    }
    delay(2000);  //Send a request every 30 seconds
  }
  else if (buttonState == 0)
  {
    delay(200);
  }
}
