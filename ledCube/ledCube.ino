int ledpins[] = {2,3,4,5};
int groundpins[] = {6,7};

void setup () {
  for(int i = 0; i < 4; i++) {       
    pinMode(ledpins[i],OUTPUT);
  }                         
  for (int i= 0; i<2; i++) {
    pinMode(groundpins[i],OUTPUT);
  }
}

void loop() {
  twist();
  drop();
  diagonal();
}


void twist() {
  int patterns[4][4] = {
    {0, 1, 2, 3},
    {1, 2, 3, 0},
    {2, 3, 0, 1},
    {3, 0, 1, 2}
  };
  const int delaytime = 100;

  for (int p = 0; p < 4; p++) {

    int groundIndex = p % 2;
    digitalWrite(groundpins[groundIndex], HIGH);

    for (int i = 0; i < 4; i++) {
      digitalWrite(ledpins[patterns[p][i]], HIGH);
      delay(delaytime);
    }
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledpins[patterns[p][i]], LOW);
      delay(delaytime);
    }
    digitalWrite(groundpins[groundIndex], LOW);
  }
}

void drop() {
  const int delaytime = 75;

  for (int c = 0; c < 2; c++) {
    for (int i = 0; i < 4; i++) {
      toggleLed(groundpins[0], groundpins[1], ledpins[i], delaytime);
    }
  }
}
void toggleLed(int groundPin1, int groundPin2, int ledPin, int delaytime) {
  digitalWrite(groundPin1, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(delaytime);
  digitalWrite(groundPin1, LOW);
  digitalWrite(groundPin2, HIGH);
  delay(delaytime);
  digitalWrite(groundPin2, LOW);
  digitalWrite(ledPin, LOW);
}

void diagonal() {
  const int delaytime = 100;

  for (int i = 0; i < 4; i++) {
    toggleLedDiagonal(groundpins[1], ledpins[i], delaytime);
    toggleLedDiagonal(groundpins[0], ledpins[i], delaytime);
  }
  
  for (int i = 0; i < 4; i++) {
    toggleLedDiagonal(groundpins[0], ledpins[i], delaytime);
    toggleLedDiagonal(groundpins[1], ledpins[i], delaytime);
  }
}
void toggleLedDiagonal(int groundPin, int ledPin, int delaytime) {
  digitalWrite(groundPin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(delaytime);
  digitalWrite(groundPin, LOW);
  digitalWrite(ledPin, LOW);
  delay(delaytime);
}
