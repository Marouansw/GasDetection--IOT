
int Input = A0;
int R_LED = 2;
int G_LED = 3;
int Buzzer = 4;
int Fan = 8; // New pin for the fan
// VAL INTEGER
int val;
int MAX = 200;

void setup() {
  Serial.begin(9600);
  pinMode(Input, INPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Fan, OUTPUT); // Set the fan pin as output
}

void loop() {
  val = analogRead(A0);
  Serial.print("Gas value: ");
  Serial.println(val);
  val = analogRead(A0);
  if (val >= MAX) {
    digitalWrite(R_LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(G_LED, LOW);
    digitalWrite(Fan, HIGH); // Turn the fan on
    Serial.println("GAS LEAKING");
  }
  else {
    digitalWrite(R_LED, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(G_LED, HIGH);
    digitalWrite(Fan, LOW); // Turn the fan off
    Serial.println("NORMAL");
  }
}
