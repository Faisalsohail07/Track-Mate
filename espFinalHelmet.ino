#include <SoftwareSerial.h>
#include<TinyGPS++.h>
float lt;
float lo;
String number = "8340440537";
SoftwareSerial sim(14, 12);// RX(D5), TX(D6)
TinyGPSPlus Tgps;

void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);
  sim.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  String str = "";
  str = sim.readString();
  Serial.println(str);
  delay(100);
  sim.println("AT+CNMI=2,2,0,0,0"); // Enable SMS notification
  delay(100);
  str = sim.readString();
  Serial.println(str);
  sim.println("AT+CMGS=\"+91" + number + "\"\r");
  delay(1000);
  sim.print("Setup completed.");
  delay(1000);
  sim.write(26); // End SMS
  delay(1000);
  Serial.println("Ready...");
}

void loop()
{
  track();
  if (sim.available())
  {
    String str = "";
    str = sim.readString();
    Serial.println(str);
    delay(100);
    int i = 51;
    String cmd;
    while (i < str.length() - 2)
    {
      char c = str.charAt(i);
      cmd += c;
      i++;
    }
    cmd.toLowerCase();
    Serial.println("Command = " + cmd);
    delay(100);
    if (cmd == "track")
    {
      Serial.println("OK");
      sendMsg();
      Serial.println("Done");
    }
    if (cmd == "update number")
    {
      Serial.println("Enter Admin Password/B for back");
      delay(1000);
      sim.println("AT+CMGS=\"+91" + number + "\"\r");
      delay(1000);
      sim.print("Enter Admin Password/B for back");
      delay(1000);
      sim.write(26); // End SMS
      delay(1000);
      while (1) {
        if (sim.available())
        {
          int i = 51;
          String str, cmd;
          str = sim.readString();
          Serial.println(str);
          delay(100);
          while (i < str.length() - 2)
          {
            char c = str.charAt(i);
            cmd += c;
            i++;
          }
          Serial.println("Command = " + cmd);
          delay(100);
          if (cmd == "B")
          {
            sim.println("AT+CMGS=\"+91" + number + "\"\r");
            delay(1000);
            sim.println("Back home");
            delay(1000);
            sim.write(26); // End SMS
            delay(1000);
            break;
          }
          else if (cmd == "aryaold")
          {

            Serial.println("Enter Number/B for back");
            delay(1000);
            sim.println("AT+CMGS=\"+91" + number + "\"\r");
            delay(1000);
            sim.print("Enter Number/B for back");
            delay(1000);
            sim.write(26); // End SMS
            delay(1000);
            while (1) {
              if (sim.available())
              {
                int i = 51;
                String str, cmd;
                str = sim.readString();
                Serial.println(str);
                delay(100);
                while (i < str.length() - 2)
                {
                  char c = str.charAt(i);
                  cmd += c;
                  i++;
                }
                Serial.println("Command = " + cmd);
                delay(100);
                Serial.println("Command = " + String(cmd.length()));
                delay(100);
                if (cmd == "B")
                {
                  sim.println("AT+CMGS=\"" + number + "\"\r");
                  delay(1000);
                  sim.println("Back");
                  delay(1000);
                  sim.write(26); // End SMS
                  delay(1000);
                  break;
                }
                else if (cmd.length() >= 10)
                {
                  Serial.println("Updated number = " + number);
                  delay(100);
                  sim.println("AT+CMGS=\"+91" + number + "\"\r");
                  delay(1000);
                  sim.print("Enter Number/B for back");
                  delay(1000);
                  sim.write(26); // End SMS
                  delay(1000);
                  number = cmd;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }
}
void track() {
  if (Serial.available()) {
    if (Tgps.encode(Serial.read())) {
      if (Tgps.location.isValid()) {
        lt = Tgps.location.lat();
        lo = Tgps.location.lng();
        Serial.println("Latitude: " + String(lt));
        Serial.println("Longitude: " + String(lo));
        Serial.println("You are good to go");
      }
    }
  }
}
void sendMsg()
{
  sim.println("AT+CMGS=\"+91" + number + "\"\r");
  delay(1000);
  sim.print("Current location: ");
  sim.print("https://maps.google.com/?q=");
  sim.print(Tgps.location.lat(), 6);
  sim.print(",");
  sim.print(Tgps.location.lng(), 6);
  sim.write(26); // End SMS
  delay(1000);
}
