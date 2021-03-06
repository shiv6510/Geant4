
#ifndef YOURPRIMARYGENERATORACTION_HH
#define YOURPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "G4UImanager.hh"

// forward declarations
class G4ParticleGun;
class G4Event;
class G4String;

class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:  // Method declarations
    
    // Constructor & Destructor
    YourPrimaryGeneratorAction();
    virtual ~YourPrimaryGeneratorAction();

    // (Pure) virtual method to generata primary events
    virtual void GeneratePrimaries(G4Event*);

  private:  // Data member declarations

     G4GeneralParticleSource* fParticleGun = nullptr; // this will be your photon source
     
};

#endif
