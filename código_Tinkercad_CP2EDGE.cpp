#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

byte grau[8]={B11100,B10100,B11100,B00000,B00000,B00000,B00000,B00000};

const int analogIn = A2;
int humiditysensorOutput = 0;

#define led_vermelho 9
#define lde_amarelo 8

// Defining Variables
int humidade = 0;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;


int ldr = A0 ; 
int vldr = 0; 
int buzzer = 13;
int ver = 12;
int amarelo = 11;
int verde = 10;


void setup()
{
  
  pinMode(ldr, INPUT);
  pinMode(ver, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.createChar(1,grau); // criar um character para o LCD
  pinMode(A1, INPUT);

  
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  

 digitalWrite(13, LOW);
  vldr = analogRead (ldr);
  Serial.println(vldr);
 
    
  //---------------- DHT11-------------//
  RawValue = analogRead(analogIn);
  tempC = (((RawValue / 1023.0) * 5000)- 500) * 0.1; // 500 is the offset
  Serial.print("\t Temperature in C = ");
  Serial.print(tempC,1);
  humiditysensorOutput = analogRead(A1);
  humidade = map(humiditysensorOutput, 0, 1023, 0, 100);
  Serial.print("Humidity: "); 
// Printing out Humidity Percentage
  Serial.print(humidade);
  Serial.println("%");
  Serial.println("");
  Serial.println("");
//LDR 
if(vldr <= 103)// BAIXO LDR
  {
 		digitalWrite(verde, HIGH);
    	lcd.setCursor(4, 0);
  		lcd.print("Ambiente");
    	lcd.setCursor(7, 1);
  		lcd.print("OK");
//------------desligar os outros leds-----------//
    	digitalWrite(amarelo, LOW);
    	digitalWrite(ver, LOW);
//---------- leitura do sensor novamente -------//  	
    	vldr = analogRead (ldr);
  		Serial.println(vldr);
  		delay(5000);
        digitalWrite(verde, LOW);
  }
 lcd.clear();
 
 // MEIO TERMO 
    if ((vldr >= 104) && (vldr <= 206))// logica para o LED amarelo ligar 
  {
   		
  		digitalWrite(amarelo, HIGH);
   		lcd.setCursor(4,0);
  		lcd.print("Ambiente");
   		lcd.setCursor(3,1);
  		lcd.print("a meia luz");
   // deligar leds
    	digitalWrite(verde, LOW);
    	digitalWrite(ver, LOW);
    	
   		vldr = analogRead (ldr);
  		Serial.println(vldr);
        delay(5000);
        digitalWrite(amarelo, LOW);
  }	

 lcd.clear();

// TEMP OK 
      if ((tempC >= 10) && (tempC <= 15 ) )
    {
    lcd.setCursor(0, 0);
    lcd.print("Temp. OK"); 

    lcd.setCursor(0, 1);
    lcd.print("Temp. = "); 
    lcd.print(tempC);
    lcd.write(1);
 
   RawValue = analogRead(analogIn);
   tempC = (((RawValue / 1023.0) * 5000)- 500) * 0.1; // 500 is the offset
	  delay(5000);
  
    }
lcd.clear();

//UMIDADE OK 
   if ((humidade >= 60) && (humidade <= 80 ) )
  {
  lcd.setCursor(0, 0);
  lcd.print("umidade OK"); 

  lcd.setCursor(0, 1);
  lcd.print("Umidade: "); 
  lcd.print(humidade); 
  lcd.write(37); 
	
  humiditysensorOutput = analogRead(A1);
  humidade = map(humiditysensorOutput, 0, 1023, 0, 100); 
  delay(5000);
  }

lcd.clear();

while (vldr >= 207){// LDR ALTO

        digitalWrite(verde, LOW);
    	digitalWrite(amarelo, LOW);
   		
   		lcd.setCursor(4,0);
  		lcd.print("Ambiente");
   		lcd.setCursor(2,1);
  		lcd.print("muito claro ");
  		
   		digitalWrite(13, HIGH);
    	digitalWrite(ver, HIGH);
    	digitalWrite(led_vermelho, HIGH);
        
   //---------- leitura do sensor novamente -------//  	
  		vldr = analogRead (ldr); 
  		Serial.println(vldr);
   		delay(5000);
}

lcd.clear();

//------------------ TEMP ------------//
// ------------- BAIXA
while (tempC <= 9){
    lcd.setCursor(0, 0);
    lcd.print("Temp. Baixa"); 

    lcd.setCursor(0, 1);
    lcd.print("Temp. = "); 
    lcd.print(tempC);
    lcd.write(1);
    digitalWrite(lde_amarelo, HIGH);
    digitalWrite(13, HIGH);
   RawValue = analogRead(analogIn);
   tempC = (((RawValue / 1023.0) * 5000)- 500) * 0.1; // 500 is the offset
	delay(5000); 
}
 digitalWrite(lde_amarelo, LOW);
lcd.clear();

// --------------- ALTO
while(tempC >= 16) {
    lcd.setCursor(0, 0);
    lcd.print("Temp. Alta"); 

    lcd.setCursor(0, 1);
    lcd.print("Temp. = "); 
    lcd.print(tempC);
    lcd.write(1);
    digitalWrite(lde_amarelo, HIGH);
    digitalWrite(13, HIGH);
    RawValue = analogRead(analogIn);
    tempC = (((RawValue / 1023.0) * 5000)- 500) * 0.1; // 500 is the offset
    }
 digitalWrite(lde_amarelo, LOW);
lcd.clear();

//------------------ UMIDADE ------------//
// ---------- BAIXO
while (humidade <= 60)
  {
  lcd.setCursor(0, 0);
  lcd.print("umidade BAIXA"); 

  lcd.setCursor(0, 1);
  lcd.print("Umidade: "); 
  lcd.print(humidade); 
  lcd.write(37); 
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(13, HIGH);
  humiditysensorOutput = analogRead(A1);
  humidade = map(humiditysensorOutput, 0, 1023, 0, 100); 
  delay(5000);
  }
  digitalWrite(led_vermelho, LOW);
lcd.clear();

// -------------- ALTO
while(humidade >= 80 )
  {
  lcd.setCursor(0, 0);
  lcd.print("umidade ALTA"); 

  lcd.setCursor(0, 1);
  lcd.print("Umidade: "); 
  lcd.print(humidade); 
  lcd.write(37); 
    digitalWrite(led_vermelho, HIGH);
	digitalWrite(13, HIGH);
  humiditysensorOutput = analogRead(A1);
  humidade = map(humiditysensorOutput, 0, 1023, 0, 100); 
  delay(5000);
  }
  digitalWrite(led_vermelho, LOW);
lcd.clear();
}