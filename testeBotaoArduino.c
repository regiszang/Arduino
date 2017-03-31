
// This constant won't change:
const int knapp = 8;

// Variables will change:
int ButtonState = 0;         // current state of the button
int oldButtonState = 0;     // previous state of the button


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(knapp, INPUT);
    digitalWrite(knapp, LOW);   

  
lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear(); 
  lcd.setCursor(0, 0);
  delay (11);
  lcd.print("");
  delay (11);
  lcd.setCursor(0, 1);
  delay (11);
  lcd.print("");
  delay (11);
    lcd.clear();
}

void loop() {


ButtonState = digitalRead(knapp);



//### The Button
  if (ButtonState != oldButtonState) {
    if (ButtonState == HIGH) {

   lcd.setCursor(0,1);
     delay (11);
     lcd.print("Knapp er Tryckt   ");}
    } 
    else {
   lcd.setCursor(0,1);
     delay (11);
     lcd.print("Tryck pa knappen   ");}         
}
