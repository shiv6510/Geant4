
#include "YourPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh" 


YourPrimaryGeneratorAction::YourPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
   // create the particle-gun object
  // G4int nParticle = 1;
   //fParticleGun    = new G4ParticleGun(nParticle);
   m_particleGun = new G4GeneralParticleSource();

}


YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction()
{
   //delete fParticleGun;
   delete m_particleGun;
}


void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt)
{
  // fParticleGun->GeneratePrimaryVertex(evt);
   m_particleGun->GeneratePrimaryVertex(evt);
}
/*
MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
        m_particleGun = new G4GeneralParticleSource();
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() {
        delete m_particleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
        m_particleGun->GeneratePrimaryVertex(anEvent);
}
*/
