#include "Run.hh"
#include "G4HCofThisEvent.hh"
Run::Run(): G4Run() ,
  kinetic_energy_total(0), HCID(-1)
 { } 

void Run::RecordEvent(const G4Event* evt)
 { 
  if(HCID==-1)
 { 
   pSDMan = G4SDManager :: GetSDMpointer();

   HCID = pSDMan -> GetCollectionID("CsISD/CsICollect");

 }

  G4HCofThisEvent* hce = evt->GetHCofThisEvent();
  if (!hce) {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found.\n";
    G4Exception("Run::RecordEvent()","Code001", JustWarning, msg);
    return;
  }  

CsIHitsCollection* hHC1 = static_cast<CsIHitsCollection*>(hce->GetHC(HCID));

if (!hHC1)
  {
    G4ExceptionDescription msg;
     msg << "Some of hits collections of this event not found.\n";
    G4Exception("Run::RecordEvent()","Code001", JustWarning, msg);
     return;
  } 
G4double kineticEnergy = 0;
G4double edep=0;
G4cout<<"HELLO FROM RUN.CC"<<G4endl;
  for (size_t i=0;i<hHC1->GetSize();i++)
  {
    CsIHit* hit = (*hHC1)[i];
    kineticEnergy+= hit->GetKineticEnergy();
    edep+=hit->GetEdep();
  } 
 kinetic_energy_total+=kineticEnergy; 
 edep_total+=edep;
 }
void Run::Merge(const G4Run* aRun)
{
    const Run* localRun = static_cast<const Run*>(aRun);
    //em_ene += localRun->GetEmEnergy();
     kinetic_energy_total += localRun->GetTotalKineticEnergy();
     edep_total+=localRun->GetTotalEdep();
    //shower_shape += localRun->GetShowerShape();
    //Forward call to base-class
    G4Run::Merge(localRun);
}

