#ifndef CsIPhysicsList_h
#define CsIPhysicsList_h 1

// handles units, constants and Geant4 CLHEP typing (i.e, G4int, G4String etc)
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "G4VUserPhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"

// include all the particles of interest
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

// include all processes of interest
#include "G4Transportation.hh"
#include "G4ProcessManager.hh"

// Import physics for optical photon physics
#include "G4VModularPhysicsList.hh"
#include "G4VUserPhysicsList.hh"


// include process library
#include "G4RadioactiveDecayBase.hh"
#include "G4Decay.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4Geantino.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics.hh"

class CsIPhysicsList
{

    public: 
        CsIPhysicsList();
        virtual ~CsIPhysicsList();
    
   // protected:

       // virtual void SetCuts();

        // define the particles or nuclides
       // void ConstructParticle();
     //   void ConstructProcess();

        // define the process handles
       // void ConstructEM();
        //void ConstructGeneral();

    private:
        // define particle types
       // G4BosonConstructor* pBosonConstructor;
       // G4LeptonConstructor* pLeptonConstructor;
        //G4MesonConstructor* pMesonConstructor;
        //G4BaryonConstructor* pBaryonConstructor;
        //G4IonConstructor* pIonConstructor;
        //G4ShortLivedConstructor* pShortLivedConstructor;
        //G4ParticleDefinition* particle;

        //G4ProcessManager* pProcessManager;

        // declare the process
        //G4RadioactiveDecayBase* raddecay;
        

};

#endif

