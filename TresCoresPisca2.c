void setup() {
  // put your setup code here, to run once:
//Projeto arduino Andrew e Regis
pinMode(10, OUTPUT);
//Verde
pinMode(5, OUTPUT);
//Azul
pinMode(1, OUTPUT);
//Vermelho
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(10,HIGH);
 delay(10);
 digitalWrite(10,LOW);
 delay(20);
 digitalWrite(5,HIGH);
 delay(40);
 digitalWrite(5,LOW);
 delay(80);
 digitalWrite(1,HIGH);
 delay(160);
 digitalWrite(1,LOW);
 delay(320);
}