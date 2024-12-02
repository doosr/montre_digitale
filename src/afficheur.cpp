#include "afficheur.h"
#include <LiquidCrystal.h>

 void Afficheur::Init() {
    lcd.begin(16, 2); // Initialize the display with 16 columns and 2 rows
    lcd.backlight();  // Enable the backlight (if supported by your hardware)
    lcd.setCursor(0, 0);
    lcd.print(" Digital clock ");
    isClignotement = false;
}

  void Afficheur::Afficher(std::string heure){
    lcd.setCursor(4, 1);
    lcd.print(heure.c_str());
  }

void Afficheur::AfficherChrono(const std::string& chrono) {
    lcd.setCursor(0, 0);
    lcd.print("   Chronometer   ");
    lcd.setCursor(4, 1);
    lcd.print(chrono.c_str());
}


  void Afficheur::AfficherSansClignoter(std::string heure){
    lcd.setCursor(0, 0);
    lcd.print(" Digital clock ");
    isClignotement =false;
    Afficher(heure);
  }

  void Afficheur::AfficherClignoterHeure(std::string heure){
    lcd.setCursor(0, 0);
    lcd.print("   Set Hour    ");
    isClignotement =true;
    affichageSansClignotement = heure;
    affichageAvecClignotement = "";
    affichageAvecClignotement.append("  ").
                              append(heure.substr(2,heure.length() - 2));
  }

  void Afficheur::AfficherClignoterMinute(std::string heure){
    lcd.setCursor(0, 0);
    lcd.print("  Set Minute   ");
    isClignotement =true;
    affichageSansClignotement = heure;
    affichageAvecClignotement = "";
    affichageAvecClignotement.append(heure.substr(0,3)).
                              append("  ").
                              append(heure.substr(5,3));
  }

  void Afficheur::AfficherClignoterSeconde(std::string heure){
    lcd.setCursor(0, 0);
    lcd.print("  Set Second   ");
    isClignotement =true;
    affichageSansClignotement = heure;
    affichageAvecClignotement = "";
    affichageAvecClignotement.append(heure.substr(0,6)).
                              append("  ");
  }

  void Afficheur::FsmAfficheur(){
    switch (afficheurState)
    {
    case AfficheurStates::Stable:
        if(isClignotement){
            Afficher(affichageAvecClignotement);
            StartTimerClignotement();
            afficheurState = AfficheurStates::ClignoteOn;
        }
        break;
    case AfficheurStates::ClignoteOn:
        if(!isClignotement){
            StopTimerClignotement();
            Afficher(affichageSansClignotement);
            afficheurState = AfficheurStates::Stable;
            break;
        }
        if(IsEndTimerClignotement()){
            Afficher(affichageAvecClignotement);
            afficheurState = AfficheurStates::ClignoteOff;
            flagTimerAfficheur =false;
        }
        break;
    case AfficheurStates::ClignoteOff:
        if(!isClignotement){
            StopTimerClignotement();
            Afficher(affichageSansClignotement);
            afficheurState = AfficheurStates::Stable;
            break;
        }
        if(IsEndTimerClignotement()){
            Afficher(affichageSansClignotement);
            afficheurState = AfficheurStates::ClignoteOn;
            flagTimerAfficheur =false;
        }
        break;
    default:
        break;
    }
  }
void Afficheur::StartTimerClignotement(){
    isTimerAfficheurActive=true;
}

void Afficheur::StopTimerClignotement(){
    isTimerAfficheurActive=false;
}

bool Afficheur::IsTimerClignotementActive(){
    return isTimerAfficheurActive;
}

bool Afficheur::IsEndTimerClignotement(){
    return flagTimerAfficheur;
}
