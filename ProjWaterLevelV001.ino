//Inicial Variable
//Input Variable
int pinAgua = 11;
//Output Variable
//int pinBuzzer = 10;
int pinLedVerm = 12;
int pinLedVerd = 6;

void setup(){
  //Setup input data from pinAgua to arduino
  pinMode(pinAgua,INPUT);
  // pinMode(pinBuzzer,OUTPUT);

  //Setup Output data to 
  //pinBuzzer
  //pinMode(12,OUTPUT);

  pinMode(pinLedVerd, OUTPUT);
  //Verde
  pinMode(pinLedVerm , OUTPUT);
  //Vermelho

  Serial.begin(9600);
  Serial.println("Teste Nivel Fixo");
  Serial.println("Regis e Andrew");
    
  
}
void loop(){
  if(digitalRead(pinAgua)==HIGH){
   Serial.println("Pin Agua Low"); 
   // digitalWrite(pinBuzzer,LOW);
   digitalWrite(pinLedVerm,HIGH);
   //Pino vermelho 12
   digitalWrite(pinLedVerd,LOW);
   //Pino verde 6
   delay(500);

   
  }else{
  //digitalWrite(pinBuzzer,HIGH);
  Serial.println("Pin Agua High"); 
  digitalWrite(pinLedVerm,LOW);
  digitalWrite(pinLedVerd,HIGH);
  delay(500);
  }
}
