#include <Arduino.h>

// Eingänge
unsigned int schalter_pin = 12;
unsigned int taster_pin = 13;

// Ausgänge
unsigned int ampel_rot_pin = 5;
unsigned int ampel_gelb_pin = 4;
unsigned int ampel_gruen_pin = 3;
unsigned int rundumleuchte_pin = 2;

// int = Integer == Ganzzahl (-5,0,1,3,4)
// unsigned == ohne Vorzeichen (nur nicht-negative Zahlen, 0,1,2, ...)

void setup() {
  // put your setup code here, to run once:

  // Eingänge (mit internem Pull-Up-Widerstand)
  pinMode(schalter_pin, INPUT_PULLUP);
  pinMode(taster_pin, INPUT_PULLUP);

  // Ausgänge
  pinMode(ampel_rot_pin, OUTPUT);
  pinMode(ampel_gelb_pin, OUTPUT);
  pinMode(ampel_gruen_pin, OUTPUT);
  pinMode(rundumleuchte_pin, OUTPUT);
}

enum state_type { grundzustand, box_frei, box_belegt, ausfahrt_vorbereiten };
state_type zustand = grundzustand;

void loop() {

  // Zustandsübergänge (Pfeile)
  if (zustand == grundzustand) {
    if (digitalRead(schalter_pin) == LOW) {
      zustand = box_frei;
    }
  } else if (zustand == box_frei) {
    if (digitalRead(taster_pin) == LOW) {
      zustand = box_belegt;
    }
  } else if (zustand == box_belegt) {
    if (true) { // Todo: nach 27 s
      zustand = ausfahrt_vorbereiten;
    } else { // noch nicht 27 s um
      zustand = box_belegt; // könnten wir uns sparen
    }
  } else if (zustand == ausfahrt_vorbereiten) {
    if (false) { // Todo: nach 3 s
      zustand = box_frei;
    } else if (digitalRead(schalter_pin) == HIGH) {
      zustand = grundzustand;
    }
  }

  // Aktionen in Zuständen
  if (zustand == grundzustand) {
    digitalWrite(ampel_rot_pin, HIGH);
    digitalWrite(ampel_gelb_pin, LOW);
    digitalWrite(ampel_gruen_pin, LOW);
    digitalWrite(rundumleuchte_pin, LOW);
  } else if (zustand == box_frei) {
    digitalWrite(ampel_rot_pin, LOW);
    digitalWrite(ampel_gelb_pin, LOW);
    digitalWrite(ampel_gruen_pin, HIGH);
    digitalWrite(rundumleuchte_pin, HIGH);
  } else if (zustand == box_belegt) {
    digitalWrite(ampel_rot_pin, HIGH);
    digitalWrite(ampel_gelb_pin, LOW);
    digitalWrite(ampel_gruen_pin, LOW);
    digitalWrite(rundumleuchte_pin, HIGH);
  } else if (zustand == ausfahrt_vorbereiten) {
    digitalWrite(ampel_rot_pin, HIGH);
    digitalWrite(ampel_gelb_pin, HIGH);
    digitalWrite(ampel_gruen_pin, LOW);
    digitalWrite(rundumleuchte_pin, HIGH);
  }

}