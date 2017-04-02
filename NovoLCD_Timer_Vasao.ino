#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int milisegundos = 0;
int i = 0; //Variável para segundos
int Sec = 0;
int Min = 00; //Variável para minutos

volatile int contaPulso; //measuring the rising edges of the signal
float media = 0; //Variável para fazer a média
int vasao;
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão
int hallsensor = 2;    //The pin location of the sensor

void rpm ()     //This is the function that the interupt calls
{
  contaPulso++;  //This function measures the rising and falling edge of the hall effect sensors signal
  //incpulso
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  lcd.init();
  lcd.backlight();
 
}

void loop() {
  // put your main code here, to run repeatedly:

  Sec++;
  contaPulso = 0;    //Set NbTops to 0 ready for calculations
  sei();        //Enables interrupts
  //delay (1000);    //Wait 1 second
  cli();        //Disable interrupts

   vasao = (contaPulso  / 5.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/min 

 // entra a media
   
 if (Sec <= 60)
    {
//    lcd.init();  //    lcd.setCursor(0,0);  //    lcd.print (Sec);  //    lcd.print ("Secs");     
    }
    else if (Sec > 60)
    {
    Sec = 0;
    Min++;
//    lcd.init();  //    lcd.setCursor(0,0);  //    lcd.print (Min);  //    lcd.print ("Maior");   
    }
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,1);


  lcd.print (Min); 
  lcd.print ("M : ");  

  lcd.print (Sec); 
  lcd.print ("S "); 


  lcd.setCursor(0,0);
  lcd.print (vasao, DEC); //Prints the number calculated above
  lcd.print (" L/seg"); //Prints "L/hour" and returns a  new line
 
 // 

  Serial.print ("Tst "); 
  Serial.print ("Dados : ");
  Serial.print(Sec); //Prints the number calculated above
  Serial.print("Sec\n");
 }
   


