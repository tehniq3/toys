
/*
 * electronic control for toy lights
 * original sw by niq_ro (Nicu FLORICA)
 * https://nicuflorica.blogspot.com/
 * http://arduinotehniq.blogspot.com/
 * https://www.arduinotehniq.com/
 * ver.0.b - brake & one flash on turn left +right
 * 
 */

#define inS1 2
#define inS2 3
#define inFL 4
#define inFS 5
#define inFR 6

#define S1 7
#define S2 8
#define FL 9
#define FS 10
#define FR 11

byte nivel1 = 5;  // intensitate lumina pozitie, din maxim 255
byte nivel2 = 250;  // intensitate lumina frana, din maxim 255
byte semnal = 0;   // stare intermitenta functie de timp
byte semnal1 = 0;  // stare buton semnalizare 1
byte semnal2 = 0;  // stare buton semnalizare 2
byte lumina = 0;   // stare lumini
byte frana = 0;    // stare frana

unsigned long tpfrana = 0;
unsigned long  tpsemnale = 400;
byte eliberareFS = 0;

void setup() {
Serial.begin(9600);

pinMode(inS1, INPUT_PULLUP);
pinMode(inS2, INPUT_PULLUP);
pinMode(inFL, INPUT_PULLUP);
pinMode(inFS, INPUT_PULLUP);
pinMode(inFR, INPUT_PULLUP);

pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(FL, OUTPUT);
pinMode(FS, OUTPUT);
pinMode(FR, OUTPUT);

digitalWrite(S1, LOW);
digitalWrite(S2, LOW);
digitalWrite(FL, LOW);
digitalWrite(FS, LOW);
analogWrite(FR, 0);

// test
digitalWrite(S1, HIGH);
digitalWrite(S2, HIGH);
delay(300);
digitalWrite(S1, LOW);
digitalWrite(S2, LOW);
delay(300);
digitalWrite(S1, HIGH);
digitalWrite(S2, HIGH);
delay(300);
digitalWrite(S1, LOW);
digitalWrite(S2, LOW);
digitalWrite(FS, HIGH);
delay(1000);
digitalWrite(FS, LOW);
digitalWrite(FL, HIGH);
delay(1000);
digitalWrite(FL, LOW);

analogWrite(FR, nivel1);

}  // sfarsit setup

void loop() {
semnal = (millis()/300)%2;

if (digitalRead(inS1) == LOW)
{
  semnal1 = 1;
  digitalWrite(S1, semnal);
}
if ((digitalRead(inS1) == HIGH) and (semnal1 == 1))
{
  semnal1 = 0;
  delay(50);
  digitalWrite(S1, LOW);
}
if (digitalRead(inS2) == LOW)
{
  semnal2 = 1;
  digitalWrite(S2, semnal);
}
if ((digitalRead(inS2) == HIGH) and (semnal2 == 1))
{
  semnal2 = 0;
  delay(50);
  digitalWrite(S2, LOW);
}

if ((digitalRead(inFS) == LOW) and (lumina == 0))
{
  if (eliberareFS == 1)
  {
  Serial.println("Faza scurta");
  lumina = 1;
  digitalWrite(FS, HIGH);
  digitalWrite(FL, LOW);
  delay(50);
  eliberareFS = 0;
  }
}

if (digitalRead(inFS) == HIGH)
{
  eliberareFS = 1;
  delay(100);
}

if ((digitalRead(inFS) == LOW) and (lumina == 1))
{
  if (eliberareFS == 1)
  {
  Serial.println("Lumini intalnire stinse");
  lumina = 0;
  digitalWrite(FS, LOW);
  digitalWrite(FL, LOW);
  eliberareFS = 0;
  delay(50);
  }
}

if ((digitalRead(inFS) == LOW) and (lumina == 2))
{
  if (eliberareFS == 1)
  {
  Serial.println("Faza scurta");
  lumina = 1;
  digitalWrite(FS, HIGH);
  digitalWrite(FL, LOW);
  eliberareFS = 0;
  delay(50);
  }
}

if ((digitalRead(inFL) == LOW) and (lumina == 1))
{
  Serial.println("Faza lunga");
  lumina = 2;
  digitalWrite(FS, LOW);
  digitalWrite(FL, HIGH); 
  delay(50);
}


if ((digitalRead(inFR) == LOW) and (frana == 0))
{
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  analogWrite(FR, nivel2);
  frana = 1;
  tpfrana = millis();
  Serial.println("Frana - 1");
}


if ((digitalRead(inFR) == LOW) and (frana == 1))
{
  if (millis() - tpfrana > tpsemnale)
  {
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  frana = 2;
  Serial.println("Frana - 2");
  }
}

if ((digitalRead(inFR) == HIGH) and (frana > 0))
{
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  analogWrite(FR, nivel1);
  frana = 0;
}



/*
if ((digitalRead(inFR) == LOW))
{
  analogWrite(FR, nivel2);
  delay(50);
}
else
{
    analogWrite(FR, nivel1);
}
*/

}  // sfarsit de program
