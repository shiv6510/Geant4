# include "CsIHit.hh" 
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<CsIHit>* CsIHitAllocator=0;
 
 CsIHit::CsIHit(G4int i,G4double t,G4double ke,G4double edep)
 : G4VHit(), fId(i), fTime(t),fkineticEnergy(ke), fEdep(edep)
 {}
 CsIHit::CsIHit(const CsIHit &right):G4VHit(),

  fId(right.fId),
  fTime(right.fTime),
  fkineticEnergy(right.fkineticEnergy),
  fEdep(right.fEdep)
{}

const CsIHit& CsIHit::operator=(const CsIHit &right)
{
  fId = right.fId;
  fTime = right.fTime;
  fkineticEnergy=right.fkineticEnergy;
  fEdep=right.fEdep;
  return *this;
}
G4bool CsIHit::operator==(const CsIHit &/*right*/) const
{
  return false;
}
 void CsIHit::Print()
 {
    G4cout << " CsI[" << fId << "] " << fTime/ns << " (nsec)" << "kinetic energy: " << fkineticEnergy/keV<<"Energy deposited"<<fEdep/keV <<G4endl;
 } 
