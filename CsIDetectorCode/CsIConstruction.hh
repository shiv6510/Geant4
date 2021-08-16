// This class is mandatory: description of the detector
#ifndef CsIConstruction_h
#define CsIConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "CsISD.hh"

// managers
#include "G4SDManager.hh"

// packages for units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

// To make a volume sensitive to hits
#include "G4VSensitiveDetector.hh"

// packages for solids
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
// geometry attributes
#include "G4VisAttributes.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"


#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"

#include <vector> 
 
class G4Material;
class G4String;
class G4LogicalVolume;

class MagneticField;

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;



class CsIConstruction : public G4VUserDetectorConstruction
{
  // Method declaration:
  public:

    // CTR & DTR
    CsIConstruction();
    virtual ~CsIConstruction();

    // The base class has the (only one) pure virtual method Construct() which
    // is invoked by the G4RunManager when it's Initialize() method is invoked.
    // The Construct() method must return the G4VPhysicalVolume pointer which
    // represents the world volume.
    // Your detector description must be implemented here in this method.
    virtual G4VPhysicalVolume* Construct();
     virtual void ConstructSDandField();
    //
    // Further (custom) methods implemnted by the user for this application:

    // Public methods to set/get the target material: G4 NIST materials
    void              SetTargetMaterial();
    const G4Material* GetTargetMaterial() const  { return fTargetMaterial; }

    // Public method to obtain the proper gun-position depending on the detector
    G4double GetGunXPosition() { return fGunXPosition; }


  // Data member declaration
  private:
     // managers
        G4SDManager * pSDMan;
        G4VSensitiveDetector * pCsISD;
    // Target material
    G4Material*            fTargetMaterial;

    // The target thickness i.e. its (full) x-size (YZ size will be set 10x this)
    G4double               fTargetThickness;

    // The midpoint between the target and the world on the negative x-side
    G4double               fGunXPosition;
    G4LogicalVolume* logicDetector; 

    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;
    

};

#endif
