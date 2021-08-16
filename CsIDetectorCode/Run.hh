#ifndef Run_h
#define Run_h 1

#include "G4VHit.hh"
#include "CsIHit.hh"
#include "G4Threading.hh"
#include "G4Allocator.hh"
#include "G4Event.hh"
#include "G4Run.hh"
// a template class for defining a collection of hits
#include "G4THitsCollection.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
 class Run : public G4Run {
 public:
  Run();
  virtual ~Run() {};
  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);
  G4double GetTotalKineticEnergy() const { return kinetic_energy_total; }
  G4double GetTotalEdep() const {return edep_total;}
  //G4double GetHadEnergy() const { return had_ene; }
  //G4double GetShowerShape() const { return shower_shape; }
 private:
 // G4double em_ene; //accumulated energy in EM calo
  //G4double had_ene;//accumulated energy in HAD calo
  //G4double shower_shape;//accumulated shower shape ( f=EM/(EM+HAD) )
  //G4int ECHCID; //ID for EM hits collection
  G4int HCID; 
  G4double kinetic_energy_total; 
  G4double edep_total;
  G4SDManager * pSDMan;
  CsIHitsCollection * HC;
  
 }; 
#endif 
