
//info SD Card
/******************************************
  PURPOSE:  Tutorial on using the Catalex MicroSD card adapter with the Arduino Uno
  Created by      Rudy Schlaf for www.makecourse.com
        Inspired by:    "SD card datalogger" by Tom Igoe which is suppied as 'Example' with the Arduino IDE
  DATE:   5/2014
*******************************************/
/*
 This sketch shows how to use a Catalex MicroSD card adapter for datalogging
 using the Arduino standard SD.h library.   
 The circuit:
 * 1k (or higher) potentiometer as 'data input device': swiper connected to analog pin 0, other two pins: connect to 5V and GND
 * Catalex MicroSD card adapter attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** SCK - pin 13
 ** CS - pin 10
 ** GND - GND
 ** Vcc - 5V
 
*/
//fim info sd card
   
   /*
   Pinos do LCD
    
   GND => (-)
   VCC => 5V
   SDA => A4
   SCL => A5
   
   Pinos do RTC DS 3231

   pino VCC => 5V
   pino GND => GND
   pino SDA => A4
   pino SCL => A5
   pino SQW => 2
   pino 32K => desconectado
   */
  // include Library Sd Card
  #include <SD.h>      //this includes the SD card libary that comes with the Arduino
  #include <TimerOne.h>//this is a library that uses the (16 bit) timer 1 of the arduino to trigger interrupts in certain time intervals.
                     //here we use it to read sensor values precisely every 500ms. 

   
  //include Library Clock
   #include <DS3231.h>
   #include <Wire.h>
   #include <LiquidCrystal_I2C.h>


//config LCD
   LiquidCrystal_I2C lcd(0x27,20,2);  // 0x27 ou 39

//Dados Globais Clock
   DS3231 Clock;
   bool Century=false;
   bool h12;
   bool PM;
   byte ADay, AHour, AMinute, ASecond, ABits;
   bool ADy, A12h, Apm;

   byte year, month, date, DoW, hour, minute, second;


//fim Dados Globais Clock

//Dados Globais SD Card
#define chipSelect 10//we are using pin#10 as chip select pin for the SD card
//#define potentiometerSwiperPin 0//use A0 as sensor input

volatile int sensorValue;//this is the variable used in the Interrupt Service Routine (ISR) for 'reporting' the potentiometer value to the main loop.
volatile unsigned long sensorTime;//this is the variable use in the ISR to record the time when the sensor was readout.
volatile byte sensorFlag;//this flag is used to communicate to the main loop that a new value was read.
String varHoraCerta;
String varDataCerta;
//Fim Dados Globais SD Card

   void setup() {
	// Start the I2C interface
        // Setup Clock
	      Wire.begin();
        Serial.begin(9600);//start setial port at 9600 baud
        lcd.init();           // initializa o lcd 
        lcd.backlight();      // acende a luz de fundo no lcd
        
        /* As linhas abaixo servem para acertar o modulo DS3231
        Para acertar, retire as barras e carregue o programa
        depois recoloque as barras novamente. */

       //Clock.setSecond(00);  // Insira os Segundos 
       //Clock.setMinute(51); // Insira os Minutos 
       //Clock.setHour(12);     // Insira a Hora 
       //Clock.setDoW(5);      // Insira o Dia da da semana dom=1
       //Clock.setDate(6);  // Insira o Dia do Mês
       //Clock.setMonth(4); // Insira o Mês
       //Clock.setYear(17);    // Insira somente os dois ultimos digitos do Ano

       // Final Setup Clock

       // Setup SD Card
        ///Serial.begin(9600);//start setial port at 9600 baud
        Serial.print("Initializing SD card...");

         pinMode(chipSelect, OUTPUT);//set chip select PIN as output. If you use another pin, apparently #10 needs to be an output anyway to be able to use the SD.h library.
   
        if (!SD.begin(chipSelect)) { // see if the card is present and can be initialized:
        Serial.println("Card failed, or not present");
        return;//exit the setup function. This quits the setup() and the program counter jumps to the loop().
                                  }
        Serial.println("card initialized.");//otherwise, tell us that the card was successfully initialized.
  
        if (SD.exists("datalog.txt"))//if the datalog.txt file is already on the disk
                                {
        SD.remove("datalog.txt");//delete it. This prevents that the data is appended to an already existing file.
                                }
  
        ///////
        Timer1.initialize(500000); // initialize timer1, and set a 500 ms second period for the interrupt interval (i.e. the ISR will be called
        //every 500000 us to read out the potentiometer that simulates a sensor in this tutorial.
        Timer1.attachInterrupt(readoutPotentiometer);  // attaches the troquei este codigo readoutPotentiometer() function as 'Interrupt Service Routine' (ISR) to the timer1 interrupt
        //this means that every time 500000 us have passed, the readoutPotentiometer() routine will be called.

       //Final Setup SD Card
   }
   
   void ReadDS3231() {
   //inseri um valor coringa para teste
  // sensorValue =1975;
   int second,minute,hour,date,month,year,temperature; 
   second=Clock.getSecond();
   minute=Clock.getMinute();
   hour=Clock.getHour(h12, PM);
   date=Clock.getDate();
   month=Clock.getMonth(Century);
   year=Clock.getYear(); 

  varDataCerta = String(date) + "/" + String(month) + "/" + String(year) ;
  
  varHoraCerta = String(hour) + ":" + String(minute) + ":" + String(second) ;
 // temperature=Clock.getTemperature();
  
  if(date<10)
  { Serial.print("0"); }
  Serial.print(date,DEC);
  Serial.print(" de ");
  if(month==1)
  { Serial.print("Janeiro"); }
  if(month==2)
  { Serial.print("Fevereiro"); }
  if(month==3)
  { Serial.print("Marco"); }
  if(month==4)
  { Serial.print("Abril"); }
  if(month==5)
  { Serial.print("Maio"); }
  if(month==6)
  { Serial.print("Junho"); }
  if(month==7)
  { Serial.print("Julho"); }
  if(month==8)
  { Serial.print("Agosto"); }
  if(month==9)
  { Serial.print("Setembro"); }
  if(month==10)
  { Serial.print("Outubro"); }
  if(month==11)
  { Serial.print("Novembro"); }
  if(month==12)
  { Serial.print("Dezembro"); }
  Serial.print(" de ");
  Serial.print("20");
  Serial.print(year,DEC);
    
  Serial.print(' ');
  Serial.print('\n');
  if(hour<10)
  { Serial.print("0"); }
  Serial.print(hour,DEC);
  Serial.print(':');
  if(minute<10)
  { Serial.print("0"); }
  Serial.print(minute,DEC);
  Serial.print(':');
  if(second<10)
  { Serial.print("0"); }
  Serial.print(second,DEC);
  Serial.print('\n');
  
  if(Clock.getDoW()==1)
  { Serial.print("Dom"); }
  if(Clock.getDoW()==2)
  { Serial.print("Seg"); }
  if(Clock.getDoW()==3)
  { Serial.print("Ter"); }
  if(Clock.getDoW()==4)
  { Serial.print("Qua"); }
  if(Clock.getDoW()==5)
  { Serial.print("Qui"); }
  if(Clock.getDoW()==6)
  { Serial.print("Sex"); }
  if(Clock.getDoW()==7)
  { Serial.print("Sab"); }
  
  //Serial.print("Temperature=");
  //Serial.print(temperature);
  //Serial.print(Clock.getDoW());
  Serial.print('\n');
  Serial.print('\n');
   }
   
  void Lcd() {
  
   int second,minute,hour,date,month,year,temperature; 
   second=Clock.getSecond();
   minute=Clock.getMinute();
   hour=Clock.getHour(h12, PM);
   date=Clock.getDate();
   month=Clock.getMonth(Century);
   year=Clock.getYear();   
    
  lcd.setCursor(1,1);
  if(date<10)
  { lcd.print("0"); }
  lcd.print(date,DEC);
  lcd.print('/');
  if(month<10)
  { lcd.print("0"); }
  lcd.print(month,DEC);
  lcd.print('/');
  lcd.print("20");
  lcd.print(year,DEC);
  
  lcd.print(" ");
  
  if(Clock.getDoW()==1)
  { lcd.print("Dom"); }
  if(Clock.getDoW()==2)
  { lcd.print("Seg"); }
  if(Clock.getDoW()==3)
  { lcd.print("Ter"); }
  if(Clock.getDoW()==4)
  { lcd.print("Qua"); }
  if(Clock.getDoW()==5)
  { lcd.print("Qui"); }
  if(Clock.getDoW()==6)
  { lcd.print("Sex"); }
  if(Clock.getDoW()==7)
  { lcd.print("Sab"); }
    
  lcd.setCursor(4,0);
  if(hour<10)
  { lcd.print("0"); }
  lcd.print(hour,DEC);
  lcd.print(':');
  if(minute<10)
  { lcd.print("0"); }
  lcd.print(minute,DEC);
  lcd.print(':');
  if(second<10)
  { lcd.print("0"); }
  lcd.print(second,DEC);
  }
  
  
  void loop() {
  ReadDS3231();
  Lcd();
  delay(1000);
  ///Serial.print(ReadDS3231());
    ////inicio loop SD Card
                            String dataString = "";//instantiate (make) an object of the string class for assembling a text line of the datalog
 
                            if (sensorFlag ==1)    //if there is a sensor reading...
                          {
    
                            dataString = String(varDataCerta) +  ","  + String(varHoraCerta) + " T1" + String(sensorTime) + String(",") + " V2" + String(sensorValue); //concatenate (add together) a string consisting of the time and the sensor reading at that time
                            //the time and the reading are separated by a 'comma', which acts as the delimiter enabling to read the datalog.txt file as two columns into
                            //a spread sheet program like excel.             
    
                            File dataFile = SD.open("datalog.txt", FILE_WRITE);//open a file named datalog.txt. FILE_WRITE mode specifies to append the string at the end of the file
                             //file names must adhere to the "8.3 format"(max 8 char in the name, and a 3 char extension)
                             //if there is no file of that name on the SD card, this .open method will create a new file.
                             //This line actually instantiates an File object named "datafile"
                            sensorFlag = 0;      //reset the sensor reading flag. This prevents the loop from running until a new sensor reading comes from the ISR.    
   
                          if (dataFile) {       // if the file is available, write to it ('datafile' is returned 1 if SD.open was successful.
                          dataFile.println(dataString);//print the concatenated data string and finish the line with a carriage return (println adds the CR automatically after printing the string)
                          dataFile.close();   //close the file. IT is a good idea to always open/close a file before and after writing to it. That way, if someone removes the card the file is most
                          //likely o.k. and can be read with the computer.
      
                          Serial.println(dataString);// print the string also to the serial port, so we can see what is going on.
                                        }  
                          // if SD.open is not successful it returns a 0, i.e. the else{} is executed if the file could not be opened/created successfully.
                          else {
                          Serial.println("error opening datalog.txt");//in that case print an error message
                              } 
                        }
    ////Fim loop SD Card

  
  }

void readoutPotentiometer()//this is the ISR routine that is executed everytime the timer1 interrupt is called.
{
  sensorValue = (1954);//read out the potentiometer swiper
  //varHoraCerta = String(ReadDS3231());
  sensorTime = millis();  //note the time
  sensorFlag = 1;         //set the flag that tells the loop() that there is a new sensor value to be printed.
}
