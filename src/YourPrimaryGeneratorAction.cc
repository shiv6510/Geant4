
#include "YourPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh" 

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
   // create the particle-gun object
   /*
   G4int nParticle = 1;
   fParticleGun    = new G4ParticleGun(nParticle);
	*/
	fParticleGun = new G4GeneralParticleSource();
}


YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction()
{
   delete fParticleGun;
}


void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt)
{
   /*
   G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
   G4String particleName="gamma";
   G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
   
   G4ThreeVector pos(3.*cm, 0., 100*cm);
   G4ThreeVector mom(0, 0., -1.);
   
   fParticleGun->SetParticlePosition(pos);
   fParticleGun->SetParticleMomentumDirection(mom);
   fParticleGun->SetParticleEnergy(185.7*keV);
   fParticleGun->SetParticleDefinition(particle);
	*/
	G4UImanager* UImanager = G4UImanager::GetUIpointer(); 

    UImanager->ApplyCommand("/control/execute source.mac");
    fParticleGun->GeneratePrimaryVertex(evt);
}

