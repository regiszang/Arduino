#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já
//Essa é a bliblioteca do LCD + I2C pode ser comentada
//Deixarei o texto "(Pode comentar LCD + I2C)" caso não esteja usando LCD e I2C
//#include <LiquidCrystal_I2C.h>
//Biblioteca do Cristal Liquido
 
 
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
    //Acende Azul
  Serial.println("Menor de 15");
   digitalWrite(10,HIGH);
   digitalWrite(6,LOW);
   digitalWrite(4,LOW);
   delay(600);
  }
  else if (leitura > vtemp_max)
  {
    //Acende o Vermelho
  Serial.println("Maior de 22");
   digitalWrite(6,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(10,LOW);
   delay(600);
  }

   else
  {
    //Acende o verde
  Serial.println("entre 15 e 22");
   digitalWrite(4,HIGH);
   digitalWrite(6,LOW);
   digitalWrite(10,LOW);
   delay(600);
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
 
   delay(100);
   
 
 
}
