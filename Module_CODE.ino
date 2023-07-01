#include <SoftwareSerial.h>

SoftwareSerial SIM900A(2, 3);

void setup()
{
  SIM900A.begin(9600); // GSM Module Baud rate – communication speed
  Serial.begin(9600); // Baud rate of Serial Monitor in the IDE app
  Serial.println("Text Message Module Ready & Verified");
  delay(100);
  Serial.println("Type 's' to send a message or 'r' to receive a message");
}

void loop()
{
  if (Serial.available() > 0)
  {
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        ReceiveMessage();
        break;
      case 'i':
        Serial.println("You entered 'i'");
        break;
    }
  }

  if (SIM900A.available() > 0)
  {
    Serial.write(SIM900A.read());
  }
}

void SendMessage()
{
  Serial.println("Sending Message, please wait...");
  SIM900A.println("AT+CMGF=1"); // Text Mode initialization
  delay(1000);
  Serial.println("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Receiver's Mobile Number
  delay(1000);
  Serial.println("Set SMS Content");
  SIM900A.println("Bhai kya haal hain? (Brother, how are you?) This message has been sent through Arduino Uno, not a mobile phone. Wink, wink!"); // Message content
  delay(100);
  Serial.println("Done");
  SIM900A.println((char)26);
  delay(1000);
  Serial.println("Message sent successfully");
}

void ReceiveMessage()
{
  Serial.println("Receiving Messages");
  delay(1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // Receiving Mode Enabled
  delay(1000);
  Serial.println("Message Received Successfully");
}
