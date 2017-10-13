#include <Keypad.h>
#define password_length 5
#define LED 11
#define MAGNEET_PIN 12



const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS]{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

char pass[password_length] = "****";
char passdata[password_length];
byte data_index = 0, pass_index = 0;

Keypad keypad = Keypad(makeKeymap(keys), colPins, rowPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(MAGNEET_PIN, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if(key){
    Serial.println(key);
    if(key != '#'){
      if(data_index < password_length){
        passdata[data_index] = key;
        data_index++;
        Serial.println(passdata);
      } else {
        Serial.println("Er is een te lang wachtwoord ingevuld");
      }
    }
    else if (key == '#'){
      if(!strcmp(passdata, pass)){
        Serial.println("Goed WachtWoord!");
        openLock(3);
        clearData();
      } else {
        Serial.println("Geen match");
        clearData();
    }
    } else {
      Serial.println("Fout");
  }
  }
}


void clearData(){
  while (data_index != 0){
    passdata[data_index--] = 0;
  }
  return;
}

void openLock(int tijdsduur){
  digitalWrite(LED, HIGH);
  digitalWrite(MAGNEET_PIN, HIGH);
  delay(tijdsduur * 1000);
  digitalWrite(LED, LOW);
  digitalWrite(MAGNEET_PIN, LOW);
}


