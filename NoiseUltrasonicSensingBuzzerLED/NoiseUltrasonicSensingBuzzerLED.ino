int currentValue;
int maxValue;
int minValue;
unsigned long timer;
int sampleSpan = 200;  // Amount in milliseconds to sample data
int volume;            // this roughly goes from 0 to 700
int ledpin = 7;

const int buzzer = 8;

#define trigPin 13
#define echoPin 12

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  resetValues();
}

void loop() {
  // Code For Sensing Sound
  currentValue = analogRead(A0);

  if (currentValue < minValue) {
    minValue = currentValue;
  }
  if (currentValue > maxValue) {
    maxValue = currentValue;
  }

  if (millis() - timer >= sampleSpan) {
    volume = maxValue - minValue;
    Serial.print("Volume : ");
    Serial.println(volume);
    resetValues();
  }

  // I arbitrarily select 100 as the value above which the
  //microphone is picking a loud noise.
  if (volume > 50) {
    // Serial.println("Loud");
    digitalWrite(ledpin, HIGH);
    tone(buzzer, 2000);  // Send 1KHz sound signal...
    delay(1000);         // ...for 1 sec
    noTone(buzzer);      // Stop sound...
  } else {
    // Serial.println("Quiet");
    digitalWrite(ledpin, LOW);
    noTone(buzzer);  // Stop sound...
  }

  sensingDistance();
}

void resetValues() {
  maxValue = 0;
  minValue = 1024;
  timer = millis();
}

void sensingDistance() {
  // Code For Sensing Distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  // delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 15 && distance != 0) {
    digitalWrite(ledpin, HIGH);
    tone(buzzer, 2000);  // Send 1KHz sound signal...
    delay(1000);         // ...for 1 sec
    noTone(buzzer);      // Stop sound...
  } else {
    digitalWrite(ledpin, LOW);
    noTone(buzzer);  // Stop sound...
  }
  // delay(500);
  // delayMicroseconds(2);
}