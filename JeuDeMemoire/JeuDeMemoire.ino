#include <LiquidCrystal.h>

#define BUTTON1 11
#define BUTTON2 12
#define BUTTON3 13
#define BUZZERPIN A3
#define LONG 4
#define TPS 700

int button1;
int button2;
int button3;
int longueur = LONG;
int del = TPS;
int score = 0;
int niveau = 1;

int led_pins[4] = {8,9,10};

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup()
{
   pinMode(BUZZERPIN, OUTPUT);
  lcd.begin(16, 2);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Score: "+ String(score)+ " Nv: "+ String(niveau));

  delay(1000);
 
  int s[longueur];
  
  // Genere une suite de nombre entre 0 et 2 et allume les led correspondantes.
  for (int i = 0; i < longueur; i++) {
  	s[i] = rand() %3;
    
    digitalWrite(led_pins[s[i]], HIGH);
  	delay(del);
  	digitalWrite(led_pins[s[i]], LOW);
    delay(200);
  }
  
  int resultat  = reponse(s, longueur);
  
  // Affiche message d'erreur ou succes en fonction du retour de la fonction reponse.
  
  // Reset du score et du niveau en cas d'erreur
  if (resultat == 0) {
    score = 0;
    niveau = 1;
    del = TPS;
    longueur = LONG;
  	lcd.setCursor(0, 1);
  	lcd.print("Incorrect        ");
  }
  else {
    score++;
    longueur++;
  	lcd.setCursor(0, 1);
  	lcd.print("Correct        ");

    // Passe au niveau suivant tout les 5 pts et augmente la vitesse de la sequence. 
    if (score%5 == 0) {
      niveau++;
      if (delai > 100) {
        delai = delai - 100;
      }
    }
  }
  
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("              ");
}

int reponse(int *sol, int l) 
{
  lcd.setCursor(0, 1);
  lcd.print("Reponse        ");
  
  // Liste qui va recevoir la reponse du joueur et index marquant la position dans la sequence.
  int rep[l];
  int index = 0;
  
  // Recupere les inputs et les ajoutent a la reponse tant que l'index n'est pas a la fin de la sequence.
  while (index < l) {
    
    button1 = digitalRead(BUTTON1);
  	button2 = digitalRead(BUTTON2);
  	button3 = digitalRead(BUTTON3);
    
    if (button1 == HIGH) {
      digitalWrite(led_pins[0], HIGH);
      delay(200);
      
      digitalWrite(led_pins[0], LOW);
      rep[index] = 0;
      index++;
    }

    if (button2 == HIGH) {
      digitalWrite(led_pins[1], HIGH);
      delay(200);
      
      digitalWrite(led_pins[1], LOW);
      rep[index] = 1;
      index++;
    }

    if (button3 == HIGH) {
      digitalWrite(led_pins[2], HIGH);
      delay(200);
      
      digitalWrite(led_pins[2], LOW);
      rep[index] = 2;
      index++;
    }
    
    // Active le buzzer et retourne 0 si le bouton appuyé ne correspond pas a la sequence.
    if (index >= 1) {
      if (rep[index-1] != sol[index-1]) {
        tone(BUZZERPIN, 500);
        delay(100);
        noTone(BUZZERPIN);
      	return 0;
      }
    }
    
    delay(100);
  }
  // Retourne 1 si la sequence est entrée sans erreur.
  return 1;
}