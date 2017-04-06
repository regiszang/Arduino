/******************************************
	PURPOSE:	Tutorial on using the Catalex MicroSD card adapter with the Arduino Uno
	Created by      Rudy Schlaf for www.makecourse.com
        Inspired by:    "SD card datalogger" by Tom Igoe which is suppied as 'Example' with the Arduino IDE
	DATE:		5/2014
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

#include <SD.h>      //this includes the SD card libary that comes with the Arduino
#include <TimerOne.h>//this is a library that uses the (16 bit) timer 1 of the arduino to trigger interrupts in certain time intervals.
                     //here we use it to read sensor values precisely every 500ms. 

#define chipSelect 10//we are using pin#10 as chip select pin for the SD card
#define potentiometerSwiperPin 0//use A0 as sensor input

volatile int sensorValue;//this is the variable used in the Interrupt Service Routine (ISR) for 'reporting' the potentiometer value to the main loop.
volatile unsigned long sensorTime;//this is the variable use in the ISR to record the time when the sensor was readout.
volatile unsigned long clockTime;//dados do Projeto Relogio:
volatile unsigned long sensorTemp;//dados do Sensor de Temperatura
volatile unsigned long sensorFlow;//dados do Sensor de Vasao

volatile byte sensorFlag;//this flag is used to communicate to the main loop that a new value was read.

void setup()
{
  Serial.begin(9600);//start setial port at 9600 baud
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
  
  Timer1.initialize(500000); // initialize timer1, and set a 500 ms second period for the interrupt interval (i.e. the ISR will be called
  //every 500000 us to read out the potentiometer that simulates a sensor in this tutorial.
  Timer1.attachInterrupt(readoutPotentiometer);  // attaches the readoutPotentiometer() function as 'Interrupt Service Routine' (ISR) to the timer1 interrupt
  //this means that every time 500000 us have passed, the readoutPotentiometer() routine will be called.

}

void loop()
{
  
  String dataString = "";//instantiate (make) an object of the string class for assembling a text line of the datalog
 
  if (sensorFlag ==1)    //if there is a sensor reading...
  {
    
    dataString = String(sensorTime) + String(", Potenciometro : , ") + String(sensorValue) ; //concatenate (add together) a string consisting of the time and the sensor reading at that time
    //ideia de leitura e escrita no SD:
      //dataString = String(clockTime) + String(";") + String(sensorTemp) + String(";") + String(sensorFlow)
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
}

void readoutPotentiometer()//this is the ISR routine that is executed everytime the timer1 interrupt is called.
{
  sensorValue = analogRead(potentiometerSwiperPin);//read out the potentiometer swiper
  sensorTime = millis();  //note the time
  sensorFlag = 1;         //set the flag that tells the loop() that there is a new sensor value to be printed.
}






