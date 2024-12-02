#include <string>
#include <LiquidCrystal.h>

class Afficheur{
    private:
        LiquidCrystal lcd=LiquidCrystal(19, 23, 18, 21, 5, 15);; 
        enum AfficheurStates{
            Stable,
            ClignoteOn,
            ClignoteOff
        };
        
        bool isClignotement =false;
        std::string affichageAvecClignotement;
        std::string affichageSansClignotement;
        bool isTimerAfficheurActive=false;
        void Afficher(std::string heure);
    public:
    AfficheurStates afficheurState = AfficheurStates::Stable;
        volatile bool flagTimerAfficheur =false;

        void Init();
        void AfficherSansClignoter(std::string heure);
        void AfficherClignoterHeure(std::string heure);
        void AfficherClignoterMinute(std::string heure);
        void AfficherClignoterSeconde(std::string heure);
        void FsmAfficheur();
        void AfficherChrono(const std::string& chrono);

        void StartTimerClignotement();
        void StopTimerClignotement();
        bool IsEndTimerClignotement();
        bool IsTimerClignotementActive();
};