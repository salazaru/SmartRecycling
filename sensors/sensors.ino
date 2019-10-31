// include ESP8266 libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define LED 2

int button = D1;    // D2(gpio4)
int buttonState = 0;

// for PIR Sensor
int LEDstatus = 12; // chosing pin for PIR sensor led
int PIRsensor = 13; // chhoosing pin for PIR sensor

// for IR sensor
int ledIR = 12; // choosing PIN for IR led
int inputIR = 13; // choosing input pin for IR sensor
int pinIR = 0; // variable for reading PIN status of IR sensor
int chipID = ESP.getChipId();

//ultrasonic sensors
const int TRIGPIN = 5; // D4 or 2  or  5 and D1
const int ECHOPIN = 4; // D3 or 0  or  4 and D2

void setup() 
{
    // serial and WiFi connection
    Serial.begin(115200); 
    WiFi.begin("Samsung Galaxy J3 Prime 6909", "prime6909");
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(5000); // wait for the WiFI connection completion
        Serial.println("Waiting for connection");
    }
    if (WiFi.status() == WL_CONNECTED) 
    {
        Serial.println("Connected"); 
    }

    // defining standalone blue LED as output
    pinMode(LED, OUTPUT);

    // PIRsensor declaration
    pinMode (PIRsensor, INPUT); // declaring PIR sensor as input
    pinMode (LEDstatus, OUTPUT); // declaring LED as output

    // IR sensor declaration
    pinMode (ledIR, OUTPUT); // declaring LED on IR sensor as output
    pinMode (inputIR, INPUT); // declaring IR sensor as input

    // ultrasonic sensor
    pinMode (TRIGPIN, OUTPUT); // setting trigger pin as an Output
    pinMode (ECHOPIN, INPUT); // setting echo pin as an Input
}

void loop() 
{
    if (WiFi.status()== WL_CONNECTED) // check WiFi connection status     
    {   
        StaticJsonDocument<300> doc;   // declaring static JSON buffer
        JsonObject JSONencoder = doc.createNestedObject(); 

        // photoresistor sensor
        int sensorValue = analogRead(A0);  // read the input on analog pin 0
        Serial.println(sensorValue); 

        /* Alternative serial monitor printing */
        if (sensorValue >200) 
        {
            Serial.println ("Low light conditions" + sensorValue);
        } 
        else if (sensorValue < 200) 
        {
            // print out the value you read
            Serial.println ("Ambient/Bright light conditions"
                            + sensorValue);
        }

        if (sensorValue >200) 
        {
            JSONencoder["lights"] = "off";
        }
        else if (sensorValue < 200) 
        {
            JSONencoder["lights"] = "on";
        }

        // led blinking
        digitalWrite(LED, LOW);

        // turn the LED on (Note that LOW is the voltage level)
        Serial.println("LED on");
        delay(1000); // wait for a second
        digitalWrite(LED, HIGH);

        // turn the LED off by making the voltage HIGH
        Serial.println("LED off");
        delay(1000); // wait for two seconds

        // PIR sensor motion detection 
        long state = digitalRead(PIRsensor);
        if (state == HIGH)
        {
            digitalWrite (LEDstatus, HIGH);
            Serial.println("Motion Detected!");

            // declare object of class HTTPClient
            HTTPClient http;

            // specify request destination
            http.begin("http://23.92.26.42/api/motion?id=" + chipID );

            // specify content-type header
            http.addHeader("Content-Type", "application/json");
            int httpCode = http.GET(); // send the request

            String payload = http.getString(); // get the response payload

            Serial.println("Code:");
            Serial.println(httpCode);   // print HTTP return code
            Serial.println("Payload:");
            Serial.println(payload);    // print request response payload

            http.end();  // close connection
            delay (1000); 
        }

        else if (state == LOW)
        {
            digitalWrite (LEDstatus, LOW);
            Serial.println("Motion absent!");
            delay (1000);
        }

        // IR sensor
        // digital output High = Detected; Low = not detected
        pinIR = digitalRead(inputIR);
        if (pinIR == HIGH)
        {
            // check if input is HIGH
            digitalWrite(ledIR, LOW); // turn off LED
        }
        else
        {
            digitalWrite(ledIR, LOW); // turn on LED
        }

        // ultrasonic sensor
        // clears the TRIGPIN
        digitalWrite(TRIGPIN, LOW);
        delayMicroseconds(2);

        // sets TRIGPIN HIGH for 10 micro seconds
        digitalWrite (TRIGPIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGPIN, LOW);

        // reads the ECHOPIN, 
        // returns the sound travel time in microseconds
        long duration = pulseIn(ECHOPIN, HIGH);

        // calculating distance
        int distance = duration*0.034/2;

        // print distance in serial monitor
        Serial.print("Distance:");
        Serial.println(distance);
        Serial.println( "cm");
    }
    else if (WiFi.status()!= WL_CONNECTED)
    {        
        Serial.println("Error in WiFi connection");   
    }
}
