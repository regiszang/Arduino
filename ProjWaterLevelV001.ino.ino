int pinAgua = 11;
//int pinBuzzer = 12;
int pinLedVerm = 12;
int pinLedVerd = 6;

void setup(){
  //pinAgua
  pinMode(pinAgua,INPUT);
//  pinMode(pinBuzzer,OUTPUT);

//  pinBuzzer
//  pinMode(12,OUTPUT);

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
