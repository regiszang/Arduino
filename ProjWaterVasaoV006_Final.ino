#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// set the LCD address to 0x27 for a 16 chars and 2 line display
// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com

volatile int contaPulso; //measuring the rising edges of the signal
float media = 0; //Variável para fazer a média
int vasao;
int Min = 00; //Variável para minutos
int i = 0; //Variável para segundos
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão
int hallsensor = 2;    //The pin location of the sensor

void rpm ()     //This is the function that the interupt calls
{
  contaPulso++;  //This function measures the rising and falling edge of the hall effect sensors signal
  //incpulso
}
// The setup() method runs once, when the sketch starts
void setup()
{
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  lcd.init();
  lcd.backlight();
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
}

// the loop() method runs over and over again,
// as long as the Arduino has power
void loop ()
{
  contaPulso = 0;    //Set NbTops to 0 ready for calculations
  sei();        //Enables interrupts
  //delay (1000);    //Wait 1 second
  lcd.init();
  cli();        //Disable interrupts
  
 //vasao = contaPulso / 5.5; //Converte para L/min
  vasao = (contaPulso * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 

  media = media + vasao; //Soma a vazão para o calculo da media
  i++;
  //lcd.init();
  sei();        //Enables interrupts

  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print (vasao, DEC); //Prints the number calculated above
  lcd.print (" L/hour"); //Prints "L/hour" and returns a  new line
//Tempo de contagem
  lcd.setCursor(0, 0);
  lcd.print(Min);
  lcd.print(":"); //Escreve :
  lcd.print(i); //Escreve a contagem i (segundos)
  lcd.print("Min "); //Escreve :
 
  // Neste conjunto de linhas fizemos a média das leituras obtidas a cada 1 minuto
 if (i == 60)
 {
 Min++;
 lcd.print(Min);
  
 if (Min >= 60)
 {
 Min = 0;
 }
 media = media / 60; //faz a média
  cli();

  Serial.print (vasao, DEC); //Prints the number calculated above
  Serial.print (" L/hour\r\n"); //Prints "L/hour" and returns a  new line
 media = 0; //Zera a variável media para uma nova contagem
 i = 0; //Zera a variável i para uma nova contagem
 }
}
