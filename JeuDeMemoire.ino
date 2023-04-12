#include <LiquidCrystal.h>
#include "DHT.h"

#define BUTTON1 11
#define BUTTON2 12
#define BUTTON3 13

int button1;
int button2;
int button3;

int led_pins[4] = {8,9,10};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{

  lcd.setCursor(0, 0);
  lcd.print("Jeu de Memoire");
  
  suite();
  reponse();
  
  delay(10);
}

void suite()
{
  int a = rand() %3;
  int b = rand() %3;
  int c = rand() %3;
  

  digitalWrite(led_pins[a], HIGH);
  delay(2000);
  digitalWrite(led_pins[a], LOW);
  
  digitalWrite(led_pins[b], HIGH);
  delay(2000);
  digitalWrite(led_pins[b], LOW);
  
  digitalWrite(led_pins[c], HIGH);
  delay(2000);
  digitalWrite(led_pins[c], LOW);
}

void reponse() 
{
  lcd.setCursor(0, 0);
  lcd.print("Reponse        ");
  
  int index = 0;
  
  while (index < 3) {
    
    button1 = digitalRead(BUTTON1);
  	button2 = digitalRead(BUTTON2);
  	button3 = digitalRead(BUTTON3);
    
    if (button1 == HIGH) {
      digitalWrite(led_pins[0], HIGH);
      delay(1000);
      digitalWrite(led_pins[0], LOW);
      index++;
    }

    if (button2 == HIGH) {
      digitalWrite(led_pins[1], HIGH);
      delay(1000);
      index++;
      digitalWrite(led_pins[1], LOW);
    }

    if (button3 == HIGH) {
      digitalWrite(led_pins[2], HIGH);
      delay(1000);
      index++;
      digitalWrite(led_pins[2], LOW);
    }
    
    lcd.setCursor(0, 1);
  	lcd.print(index);
  } 
}