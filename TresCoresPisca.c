void setup() {
  // put your setup code here, to run once:
//Projeto arduino Andrew e Regis
pinMode(10, OUTPUT);
  //andrew
//Verde
pinMode(5, OUTPUT);
//Azul
pinMode(1, OUTPUT);
//Vermelho
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(10,HIGH);
 delay(5000);
 digitalWrite(10,LOW);
 delay(300);
 digitalWrite(5,HIGH);
 delay(900);
 digitalWrite(5,LOW);
 delay(600);
 digitalWrite(1,HIGH);
 delay(100);
 digitalWrite(1,LOW);
 delay(300);
}
