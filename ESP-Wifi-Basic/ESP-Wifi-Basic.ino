#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Hello Alok");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.println("AT+RST");
  //delay(3000);
  callWifiBoardWithCommand("AT", 1000);

  callWifiBoardWithCommand("AT+CWJAP=\"meTestWifi\",\"11223344\"", 5000);

  callWifiBoardWithCommand("AT+CIPSTATUS", 1000);
  callWifiBoardWithCommand("AT+CIPSTART=\"TCP\",\"www.adafruit.com\",80", 4000);
  String cmd = "GET /testwifi/index.html HTTP/1.1 Host: www.adafruit.com";
  
  callWifiBoardWithCommand("AT+CIPSEND=" + String(cmd.length()), 0);
 
  callWifiBoardWithCommand(cmd, 0);
  
  while(mySerial.available()){
    if(mySerial.find('O')){
      mySerial.println("+IPD");
    }
  }
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void callWifiBoardWithCommand(String command, int waitFor)
{
  delay(1000);
  mySerial.println(command);
  delay(waitFor);
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }  
}

