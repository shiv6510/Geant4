
#include "YourPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh" 

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
   // create the particle-gun object (source)
	fParticleGun = new G4GeneralParticleSource();
}


YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction()
{
   delete fParticleGun;
}


void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt)
{
	G4UImanager* UImanager = G4UImanager::GetUIpointer(); 

   // source.mac includes the settings for the particleGun, including energy distrubtion, radiation direction, etc. 
   UImanager->ApplyCommand("/control/execute source.mac");
   fParticleGun->GeneratePrimaryVertex(evt); // fires a particle
}

