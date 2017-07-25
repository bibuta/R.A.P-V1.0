 #include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 45, 44, 47, 46);

#include <DHT.h>


#define DHTPIN 28    
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
int chk;
float hum;  //Stores humidity value
float temp;
int led = 43;
const int buzzer = 4;     
const int ledPin = 28;   
long durationS;
int distanceS;
long durationD;
int distanceD;
int info = 0;
long durationF;
int distanceF;
int E1 = 10;  
int M1 = 12; 
int E2 = 11;                      
int M2 = 13;                        
const int trigPinS = 34;
const int echoPinS = 35;
const int trigPinD = 32;
const int echoPinD = 33;
const int trigPinF = 42;
const int echoPinF = 40;
int FlamePinF = 49;
int FlameF = HIGH;

int FlamePinD = 50;
int FlameS = HIGH; 
int FlamePinS = 52; 
int FlameD = HIGH; 
int fan = 51;  
int state = 0;
int stopat = 0;
int spd = 110;
byte smiley[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
void setup() 
  {
pinMode(FlamePinD, INPUT);
pinMode(FlamePinS, INPUT);
pinMode(FlamePinF, INPUT);
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);
    pinMode(led, OUTPUT); 
    pinMode(trigPinS, OUTPUT);
pinMode(echoPinS, INPUT);
pinMode(trigPinD, OUTPUT);
pinMode(echoPinD, INPUT);
pinMode(trigPinF, OUTPUT);
pinMode(echoPinF, INPUT);
pinMode(fan, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode(ledPin, OUTPUT); 
pinMode(buzzer, OUTPUT);
   Serial.begin(9600);
  lcd.createChar(0, smiley);
dht.begin();
lcd.begin(16, 2);
Serial.print("R.A.P. V1.0");
delay(2000);
} 

void loop() 
{ 
  
  buttonState = digitalRead(buttonPin);
  senzori();
  int sensorValue = analogRead(A8);
  float voltage = sensorValue * (5.00 / 1023.00) * 2;
  
if(voltage<7)
{
 Serial.print("             Voltaj: "); Serial.print(voltage);
      Serial.println(" V"); 
}
 hum = dht.readHumidity();
    temp= dht.readTemperature();
if(temp > 48.00)
{
 tone(buzzer, 1500); 
  delay(1000);       
  noTone(buzzer);     
  delay(1000);  
  tone(buzzer, 1400); 
  delay(1000);        
  noTone(buzzer);    
  delay(1000);  
  tone(buzzer, 1500); 
  delay(1000);       
  noTone(buzzer);     
  delay(1000);  
  tone(buzzer, 1400); 
  delay(1000);       
  noTone(buzzer);     
  delay(1000); 
}
lcd.setCursor(0,1);
 lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C"); 
  lcd.setCursor(10,1);
  printVolts();
  if(Serial.available() > 0){
    
    lcd.setCursor(0,0);
    lcd.write("Bluetooth: ON ");
    info = Serial.read();
   
    state = 0; 
  }
  else{
     
    lcd.setCursor(0,0);
    lcd.write("Bluetooth: "); 
  }
  digitalWrite(led, LOW);
  if(info == '1'){                
       if(state == 0){
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        digitalWrite(led, HIGH);
        Serial.print("     Temperatura: ");      
      Serial.print(temp);
      Serial.println("°C");
      
      
      state = 1;
       }
    
   }
  else if(info == '0'){
      if(state == 0){
      digitalWrite(led, HIGH);
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.print("             Voltaj: "); Serial.print(voltage);
      Serial.println(" V");
      
      state = 1;
     }
     }
     else if(info == '2')
     {
      digitalWrite(led, HIGH);
      Serial.print(" Distanta Fata: ");
      Serial.print(distanceF);
      Serial.println(" cm");
     }
     else if(info == '3')
     {
      digitalWrite(led, HIGH);
      Serial.print(" Distanta stanga: ");
      Serial.print(distanceS);
      Serial.println(" cm");
     }
     else if(info == '4')
     {
      digitalWrite(led, HIGH);
      Serial.print(" Distanta dreapta: ");
      Serial.print(distanceD);
      Serial.println(" cm");
     }
      else if(info == 'E')
     {
      digitalWrite(led, HIGH);
      if(spd<190)
      {
      spd=spd+10;}
      Serial.print("               Viteza: ");
      Serial.println(spd);
     }
     else if(info == 'F')
     {
      digitalWrite(led, HIGH);
       if(spd>100)
      {
      spd=spd-10;
      Serial.print("               Viteza: ");
      Serial.println(spd);
      }
     }
     else if(info == '5')
     {
      digitalWrite(led, HIGH);
      Serial.println("               R.A.P V1.0");
      
     }
     else if(info == '6')
     {
      digitalWrite(led, HIGH);
      Serial.println("                  Manual");
      stopat = 1;
     }
     else if(info == '7')
     {
      digitalWrite(led, HIGH);
      Serial.println("                 Automat");
      stopat = 0;
     }
     if(stopat == 1)
     {
       if(info == '8')
     {
      digitalWrite(led, HIGH);
      fata(spd);
     }
      else if(info == '9')
     {
      digitalWrite(led, HIGH);
      spate(spd);
     }
     else if(info == 'A')
     {
      digitalWrite(led, HIGH);
      stanga(185);
     }
     else if(info == 'B')
     {
      digitalWrite(led, HIGH);
      dreapta(185);
     }
     else if(info == 'C')
     {
      digitalWrite(led, HIGH);
      stoop();
      analogWrite(fan,0);
     }
     else if(info == 'D')
     {
      digitalWrite(led, HIGH);
      analogWrite(fan,128);
      delay(20);
      
      stoop();
     }
    
     else if(info == 'G')
     {
      digitalWrite(led, HIGH);
       tone(buzzer, 1400); 
       delay(300);       
      noTone(buzzer);
     }
     }
     else if(stopat==0)
     {
      if(FlameF == LOW ||  FlameD == LOW || FlameS == LOW)
{     
  Serial.println("Focul a fost gasit");
  
  if( FlameD == LOW)
  {
    dreapta(150);
    delay(150);
    stoop();
    delay(300);
  }
  if(FlameS == LOW)
  {
    stanga(150);
    delay(150);
    stoop();
    delay(300);
  }
   if(FlameF == LOW && FlameS== LOW && distanceF > 10 )
  {
    stanga(150);
    delay(150);
     stoop();
    delay(300);
  }
  if(FlameF == LOW && FlameD == LOW && distanceF > 10 )
  {
    dreapta(150);
    delay(150);
    stoop();
    delay(300);
  }
if(FlameF == LOW && distanceF > 12 )
  {
    fata(110);
    delay(150);
    stoop();
    delay(300);
  }
  if(FlameF == LOW && distanceF < 12 )
  {
    stoop();
    
    analogWrite(fan,180);
    
     tone(buzzer, 1500); 
  delay(50);        
  noTone(buzzer);     
  delay(50);  
  tone(buzzer, 1400); 
  delay(50);        
  noTone(buzzer);    
  delay(50);  
  tone(buzzer, 1500); 
  delay(50);      
  noTone(buzzer);    
  delay(50);  
  tone(buzzer, 1400); 
  delay(50);       
  noTone(buzzer);     
  delay(2000); 
  
  }
  if(FlameF == LOW && distanceF < 7 )
  {
    spate(150);
    
    
   
  }
}
else 

{
 analogWrite(fan,0);
 if(distanceF < 10)
{ 
  stoop();
  delay(100);
  spate();
  delay(700);
  if(distanceS>distanceD)
  {
    stanga(160);
    delay(520);
    stoop();
  }
  else
  {
    dreapta(160);
    delay(520);
    stoop();
  }  
} 
else if (distanceS < 12)
{
   dreapta(160);
   
}
else if (distanceD < 12)
{
   stanga(160);
}  

  

else
{
  fata(spd);
  delay(30);
}

}   
    
     }       
}

void fata(int vit)
{
  digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, vit);  
    analogWrite(E2, vit);
    delay(30);  
}
void spate(int vit)
{
  digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, vit);  
    analogWrite(E2, vit);
    delay(30);  
}
void stoop()
{
  digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 0);  
    analogWrite(E2, 0);
    delay(30);  
}
void spate()
{
  digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 110);  
    analogWrite(E2, 110);
    delay(30);  
}
void dreapta(int vit)
{
  digitalWrite(M1,LOW);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 0);  
    analogWrite(E2, vit);
    
}
void stanga(int vit)
{
  digitalWrite(M1,HIGH);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, vit);  
    analogWrite(E2, 0);
    
}

void senzori()
{
  FlameF = digitalRead(FlamePinF);
  
  FlameD = digitalRead(FlamePinD);
  FlameS = digitalRead(FlamePinS);
  digitalWrite(trigPinF, LOW);
delayMicroseconds(2);
digitalWrite(trigPinF, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinF, LOW);
durationF = pulseIn(echoPinF, HIGH);
distanceF= durationF*0.034/2;
  digitalWrite(trigPinS, LOW);
delayMicroseconds(2);
digitalWrite(trigPinS, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinS, LOW);
durationS = pulseIn(echoPinS, HIGH);
distanceS= durationS*0.034/2;
digitalWrite(trigPinD, LOW);
delayMicroseconds(2);
digitalWrite(trigPinD, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinD, LOW);
durationD = pulseIn(echoPinD, HIGH);
distanceD= durationD*0.034/2;
}

void printVolts()
{
  int sensorValue = analogRead(A8); 
  float voltage = sensorValue * (5.00 / 1023.00) * 2; 
  lcd.setCursor(9,1);
  
  lcd.print(voltage); 
  lcd.print(" V");
}

