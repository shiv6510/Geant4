#ifndef CsIHit_h
#define CsIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
class G4AttDef;
class G4AttValue;
class CsIHit : public G4VHit
 {
 public:
  CsIHit(G4int i,G4double t,G4double ke,G4double edep);
  CsIHit(const CsIHit &right);
  virtual ~CsIHit() {}
  const CsIHit& operator=(const CsIHit &right);
  G4bool operator==(const CsIHit &right) const;
  inline void *operator new(size_t);
  inline void operator delete(void*aHit);
 
  void Print();
 
  G4int GetID() const { return fId; }
 
  void SetTime(G4double val) { fTime = val; }
  void SetCopyNo(G4int val) {fId=val;}
  void SetKineticEnergy(G4double val) {fkineticEnergy=val;}
  void SetEdep(G4double val) {fEdep=val;}
  G4double GetTime() const { return fTime; }
  G4double GetKineticEnergy() const {return fkineticEnergy;}
  G4double GetEdep() const {return fEdep;}
 private:
  G4int fId;
  G4double fTime;
  G4double fkineticEnergy; 
  G4double fEdep;
};
 
 typedef G4THitsCollection<CsIHit> CsIHitsCollection;
 
 extern G4ThreadLocal G4Allocator<CsIHit>* CsIHitAllocator;
 
 inline void* CsIHit::operator new(size_t)
 {
    if (!CsIHitAllocator)
      CsIHitAllocator = new G4Allocator<CsIHit>;
    return (void*)CsIHitAllocator->MallocSingle();
 }
 
 inline void CsIHit::operator delete(void*aHit)
 {
    CsIHitAllocator->FreeSingle((CsIHit*) aHit);
 } 

#endif
