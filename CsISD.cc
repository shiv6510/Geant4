#include "CsISD.hh"
#include "CsIHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
// constructor
CsISD::CsISD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), HCID(-1)
{
HCID=-1; 
G4String Detectorname = "CsICollect";
collectionName.insert(Detectorname);
 total_hits=0;

}
// destructor
CsISD::~CsISD(){}
void CsISD :: Initialize(G4HCofThisEvent * hce)
{
    //G4cout<<"HCID construct: "<<HCID<<G4endl;
  //  G4cout<<"Detector NAME:  "<<SensitiveDetectorName<<G4endl; //getting CsISD
    // create a new hits collection which represents all steps in an event
    //G4cout<<"Collection NAME: "<<collectionName[0]<<G4endl; // getting CsICollect which is correct 
    fHitsCollection = new CsIHitsCollection(SensitiveDetectorName, collectionName[0]);
      // G4cout<<"HCID in CSISD "<<HCID<<G4endl; //getting 0 which is good? 
//pCsISD = new CsISD("/CsISD"); This must be the reason why 

    // Get the HCID from the SD manager
  
  
    pSDMan = G4SDManager :: GetSDMpointer();
    HCID = pSDMan -> GetCollectionID(fHitsCollection);
    //HCID=GetCollectionID(0);//gets 0 as well
    // Add hits to the collection of hits for this event
    hce -> AddHitsCollection(HCID, fHitsCollection);
   //G4cout<<"HCID: for CSISD.cc file "<<HCID<<G4endl;
   
//else
//{
//  G4cout<<"NO"<<G4endl; 
//G4cout<<"HCID: "<<HCID<<G4endl;

//} 
}
 G4bool CsISD::ProcessHits(G4Step* step, G4TouchableHistory*)
 {
     auto edep = step -> GetTotalEnergyDeposit();
     if (edep==0.) return true;
     auto particleName = step -> GetTrack() -> GetParticleDefinition() -> GetParticleName();
     G4Track *track = step->GetTrack();
     G4double kineticEnergy=track->GetKineticEnergy();
  //  G4cout << "particle name: " << particleName << " | " << "energy deposited: " << edep << G4endl;
    //G4cout<<"HCID: for CSISD.cc file "<<HCID<<G4endl;//getting 0
    //G4cout<<"Hello!"<<G4endl;
  
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
 
   G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable()); //G4touchableHistory outdated but that's the second agrument? 
   auto copyNo = touchable->GetVolume(2)->GetCopyNo();
 //  G4cout<<"Copy number: "<<copyNo<<G4endl; //constantly getting copy number two? Due to the physical volume being labeled 2 
 // G4cout<<"Kinetic energy:  "<<kineticEnergy<<G4endl;//Always getting a kinetic energy of 1 MeV, 2 copynumber, and 0 hit time. 
    G4double hitTime = preStepPoint->GetGlobalTime();
  //  G4cout<<"HIT TIME:  "<<hitTime<<G4endl;
    // check if this finger already has a hit
   // G4int ix = -1;
    //id=(*fHitsCollection)[0]->GetID(); Getting a segementation fault, meaning that there is nothing in the hits collection? 
   // G4cout<<"GET ID"<<id<<G4endl; //loop isn't even running! So this code isn't running 
   /* for (G4int i=0;i<fHitsCollection->entries();i++)
    {
     // id=(*fHitsCollection)[i]->GetID(); 
      //G4cout<<"GET ID"<<id<<G4endl; //loop isn't even running! So this code isn't running 
      if ((*fHitsCollection)[i]->GetID()==copyNo)
      { ix = i;

        G4cout<<"Already hit!"<<G4endl;
       
       
        break;
      }
      
    }
 
    if (ix>=0) // if it has, then take the earlier time
    {  G4cout<<"NO HIT!"<<G4endl;
      if ((*fHitsCollection)[ix]->GetTime()>hitTime)
      { (*fHitsCollection)[ix]->SetTime(hitTime); }
    }*/
     // if not, create a new hit and set it to the collection
     
      
   
      CsIHit* hit = new CsIHit(copyNo,hitTime,kineticEnergy,edep);
      hit->SetCopyNo(copyNo);
      hit->SetTime(hitTime);
      hit->SetKineticEnergy(kineticEnergy);
      hit->SetEdep(edep);
      fHitsCollection->insert(hit);

    
      for (G4int i=0;i<fHitsCollection->entries();i++)
        {
           // G4cout<<"Hit collection entry :  "<< (*fHitsCollection)[i]<<G4endl;
            //Giving me reasons like 0x3e18500
           //Also 0x3e184e0 
           auto n_hits=fHitsCollection->entries();
         //  G4cout<<"ARRAY SIZE:  "<<n_hits<<G4endl; //confirmed, getting an array size of only 1 
           //But only once, it is not going though multiple entries. Only an array size of 1?

        }

      //G4cout<<"HIT!"<<G4endl;
      //total_hits+=1;
    // id=(*fHitsCollection)[0]->GetID(); //getting 2 
     //G4cout<<"GET ID"<<id<<G4endl; 
     //G4cout<<"TOTAL HITS: "<< total_hits<<G4endl;
    
    return true;
 } 
