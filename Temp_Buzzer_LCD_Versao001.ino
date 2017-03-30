#include "pitches.h"  //add note library
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Essa é a bliblioteca do LCD + I2C pode ser comentada
//Deixarei o texto "(Pode comentar LCD + I2C)" caso não esteja usando LCD e I2C
//#include <LiquidCrystal_I2C.h>
//Biblioteca do Cristal Liquido

//---->notes in the melody
//Alerta Vermelho
int melody1[]={NOTE_CS3, NOTE_DS1, NOTE_E5, NOTE_D6,NOTE_DS1, NOTE_AS4, NOTE_DS1, NOTE_D6}; 
//---->note durations. 4=quarter note / 8=eighth note
//int noteDurations1[]={4, 4, 4, 4, 8, 8, 8, 8};
int noteDurations1[]={2, 2, 2, 2, 2, 2, 2, 2};


//Alerta Azul
//int melody2[]={NOTE_CS3, NOTE_AS4, NOTE_E5, NOTE_D6,NOTE_CS3, NOTE_AS4, NOTE_E5, NOTE_D6};
int melody2[]={NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4,NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4};
//---->note durations. 4=quarter note / 8=eighth note
int noteDurations2[]={1, 1, 1, 1, 1, 1, 1, 1};

//---->digital pin 12 has a button attached to it. Give it an name
///int buttonPin= 12;
/////tem que fazer

 
//variavel do pino que esta plugado o Sensor
//Neste caso é o pino 2, mais pode usar qualquer pino digital
#define ONE_WIRE_BUS 2
 
 
//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature sensor(&oneWire);
//(Pode comentar)
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
 
void setup(void)
{
    
  ////----->make the button's pin input
  ////pinMode(buttonPin, INPUT);
  
  //Inicia a Serial
  Serial.begin(9600);
  Serial.println("Sensor de temperatura Dallas DS18b20");
  Serial.println("Regis e Andrew");
  //Inicia o objeto da biblioteca do Dallas
  sensor.begin();

//inicia Portas de Luz de alerta
pinMode(6, OUTPUT);
//Vermelho
pinMode(4, OUTPUT);
//Verde
pinMode(10, OUTPUT);
//Azul

  //"(Pode comentar LCD + I2C)"
  //lcd.begin(16,2);
  //"(Pode comentar LCD + I2C)"
 // lcd.backlight();
  //"(Pode comentar LCD + I2C)"
 // lcd.clear();
  //"(Pode comentar LCD + I2C)"
 // lcd.setCursor(0,0);
  //"(Pode comentar LCD + I2C)"
  ///lcd.print("Sensor Dallas");
   //"(Pode comentar LCD + I2C)"
  //lcd.setCursor(0,1);
  //"(Pode comentar LCD + I2C)"
  //lcd.print("DS18b20");
  delay(300);
  //"(Pode comentar LCD + I2C)"
  //lcd.clear();
 
}
 
void loop(void)
{ 
  //Envia o comando para obter temperaturas
  sensor.requestTemperatures();
   //inicia Parametro Min Temperatura
 float vtemp_min;
 vtemp_min = 15;
 float vtemp_max;
 vtemp_max = 22;
 // A temperatura em Celsius para o dispositivo 1 no índice 0 (é possivel ligar varios sensores usando a mesma porta do arduino)
  float leitura=sensor.getTempCByIndex(0);
   //Imprime na serial a varivel que recebe os dados do Sensor
   Serial.println(leitura); 
      ////
  if (leitura < vtemp_min) 
  {
//xx Musica Azul
    //------->iterate over the notes of the melody
    for (int thisNote=0; thisNote <8; thisNote++){

      //------>to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations1 [thisNote];
      tone(8, melody1 [thisNote], noteDuration);

      //----->to distinguish the notes, set a minimum time between them
      //----->the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      //----->stop the tone playing
      noTone(8);
    }
//xx    
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tmp:");
  lcd.print(leitura);
  lcd.setCursor(0,1);
  lcd.print("Frio!");
   //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");
    
    //Acende Azul
  Serial.println("Menor de 15");
   digitalWrite(10,HIGH);
   digitalWrite(6,LOW);
   digitalWrite(4,LOW);
   delay(100);
  }
  else if (leitura > vtemp_max)
  {
//xx Musica Vermelha
    //------->iterate over the notes of the melody
    for (int thisNote=0; thisNote <8; thisNote++){

      //------>to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations2 [thisNote];
      tone(8, melody2 [thisNote], noteDuration);

      //----->to distinguish the notes, set a minimum time between them
      //----->the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      //----->stop the tone playing
      noTone(8);
    }
//xx     
   ////mensagem vermelho
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tmp:");
  lcd.print(leitura);
  lcd.setCursor(0,1);
  lcd.print("Quente!");
  
   //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");

    //Acende o Vermelho
  Serial.println("Maior de 22");
   digitalWrite(6,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(10,LOW);
   delay(100);
  }

   else
  {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tmp:");
  lcd.print(leitura);
  lcd.setCursor(0,1);
  lcd.print("Excelente!");
   //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");
    
    
    
    //Acende o verde
  Serial.println("entre 15 e 22");
   digitalWrite(4,HIGH);
   digitalWrite(6,LOW);
   digitalWrite(10,LOW);
   delay(100);
  }

   ////

   //"(Pode comentar LCD + I2C)"
  // lcd.setCursor(0,0);
   //"(Pode comentar LCD + I2C)"
  // lcd.print("Temperatura : ");
   //"(Pode comentar LCD + I2C)"
  // lcd.setCursor(0,1);
    //"(Pode comentar LCD + I2C)"
  // lcd.print("          ");
   //"(Pode comentar LCD + I2C)"
 //  lcd.setCursor(0,1);
    //"(Pode comentar LCD + I2C)"
  // lcd.print(leitura);
    //"(Pode comentar LCD + I2C)"
   //lcd.print(" Celsius ");
 
  /// delay(100);
   
 
 
}
