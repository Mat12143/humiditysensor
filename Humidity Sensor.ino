// Humidity Sensor with LCD Display
// Track the Humidty in the room and it displays the value on the LCD Display with a water drop animation and a warning if the limit is reached

// By Mat12143
// Thanks to https://maxpromer.github.io/LCD-Character-Creator/ for the LCD Display custom char generator

// Libraries
#include <DHT.h>
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// The length of the array containing the water drop animation
const int ARRAY_LENGTH = 9;

// Sensor Vars
const int DHTPIN = 8;
const DHTTYPE = DHT11;

DHT dht = DHT(DHTPIN, DHTTYPE);


byte dropAnimation[ARRAY_LENGTH][8] = {
  // Part 1
  {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
  },
  {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
  },
  // Part  2
  {
  B00000,
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001
  },
  // Part  3
  {
  B00000,
  B00000,
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001
  },
  // Part  4
  {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01010,
  B01010,
  B10001
  },
  // Part  5
  {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01010,
  B01010
  },
  // Part  6
  {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01010
  },
  // Part  7
  {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100
  },
  // Part  8
  {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100
  }
};


void setup() {
  lcd.begin(16, 2);
  
  // Creating the custom chars for the LCD to display the animation
  for(int i = 0; i < ARRAY_LENGTH; i++) {
    lcd.createChar(i, dropAnimation[i]);
  }

  lcd.clear();

}
void loop() {

  lcd.clear();

  dht.begin();
  float humidity = dht.readHumidity();

  lcd.setCursor(0, 0);

  // Sensor Error check
  if (isnan(humidity)) {
    lcd.print("ERRORE SENSORE");

  } else {

    // Humidity limit
    if (humidity <= 55) lcd.print("SITUAZIONE BUONA");
    else lcd.print("APRIRE FINESTRE!");

  }

  // Water Drop Animation
  lcd.setCursor(6, 1);
  lcd.print(String(humidity) + "%");

  for(int i = 0; i < ARRAY_LENGTH; i++) {
    lcd.setCursor(4, 1);
    lcd.write((char) i);

    delay(200);
  }
}