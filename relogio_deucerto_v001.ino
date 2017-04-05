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
  
   #include <DS3231.h>
   #include <Wire.h>
   #include <LiquidCrystal_I2C.h>

   LiquidCrystal_I2C lcd(0x27,20,2);  // 0x27 ou 39

   DS3231 Clock;
   bool Century=false;
   bool h12;
   bool PM;
   byte ADay, AHour, AMinute, ASecond, ABits;
   bool ADy, A12h, Apm;

   byte year, month, date, DoW, hour, minute, second;

   void setup() {
	// Start the I2C interface
	Wire.begin();
        Serial.begin(9600);
        lcd.init();           // initializa o lcd 
        lcd.backlight();      // acende a luz de fundo no lcd
        
        /* As linhas abaixo servem para acertar o modulo DS3231
        Para acertar, retire as barras e carregue o programa
        depois recoloque as barras novamente. */

       //Clock.setSecond(00);  // Insira os Segundos 
       //Clock.setMinute(44); // Insira os Minutos 
       //Clock.setHour(21);     // Insira a Hora 
       //Clock.setDoW(3);      // Insira o Dia da da semana dom=1
       //Clock.setDate(4);  // Insira o Dia do Mês
       //Clock.setMonth(4); // Insira o Mês
        //Clock.setYear(16);    // Insira somente os dois ultimos digitos do Ano
   }
   
   void ReadDS3231() {
   
   int second,minute,hour,date,month,year,temperature; 
   second=Clock.getSecond();
   minute=Clock.getMinute();
   hour=Clock.getHour(h12, PM);
   date=Clock.getDate();
   month=Clock.getMonth(Century);
   year=Clock.getYear(); 
  
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
  }

