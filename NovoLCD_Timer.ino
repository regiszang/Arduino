#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int milisegundos = 0;
int i = 0; //Variável para segundos
int Sec = 0;
int Min = 00; //Variável para minutos
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  lcd.init();
  lcd.backlight();
 
}

void loop() {
  // put your main code here, to run repeatedly:

  Sec++;

 if (Sec <= 60)
    {
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print (Sec);
    lcd.print ("Secs");     
    }
    else if (Sec > 60)
    {
    Sec = 0;
    Min++;
//    lcd.init();
//    lcd.setCursor(0,0);
//    lcd.print (Min); 
//    lcd.print ("Maior");   
    }
   
 // lcd.init();
 // lcd.backlight();
  lcd.setCursor(0,1);


  lcd.print (Min); 
  lcd.print ("M : ");  

  lcd.print (Sec); 
  lcd.print ("S "); 
 

  Serial.print ("Tst "); 
  Serial.print ("Dados : ");
  Serial.print(Sec); //Prints the number calculated above
  Serial.print("Sec\n");
 }
   


