#include <SoftwareSerial.h>

int Input = A0;
int R_LED = 2;
int G_LED = 3;
int Buzzer = 4;
int Fan = 5; 

int val = 0;
int MAX = 200;  // Threshold value for gas leak detection

SoftwareSerial sim800l(8, 9); // RXD -> 8 , TXD -> 9 

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  Serial.println("Initializing SIM800L...");
  delay(1000);

  sim800l.println("AT");
  delay(1000);
  while (sim800l.available()) {
      Serial.write(sim800l.read());
  }

  pinMode(Input, INPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Fan, OUTPUT);
}

void loop() {
  val = analogRead(Input);

  if (val >= MAX) {
    digitalWrite(R_LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(G_LED, LOW);

    delay(4000); // Wait for stability
    Serial.println("GAS LEAKING !!, Value: " + String(val));
    Serial.println("Ready to make a call...");
    sim800l.println("ATD+212663109100;");
    delay(20000); // Ensure the call lasts at least 20 seconds
    // Hang up the call
    sim800l.println("ATH");
    delay(1000);
    Serial.println("Call ended.");
    
    digitalWrite(Fan, HIGH);
    delay(10000); 


  } else {
    digitalWrite(R_LED, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(G_LED, HIGH);
    digitalWrite(Fan, LOW);
  }

  delay(1000);
}