
#include "CsIConstruction.hh"





// Constructor
//
CsIConstruction::CsIConstruction()
:   G4VUserDetectorConstruction(),
     fTargetMaterial(nullptr)
{
    // set default target material to be Silicon
    SetTargetMaterial();
   

    // set default thickness
    fTargetThickness = 1.0*cm;
    // gun position will be set properly automaticaly
    fGunXPosition    = 0.0;
}

// Destructor
//
CsIConstruction::~CsIConstruction()
{

}

void CsIConstruction::SetTargetMaterial()
{
    // try to find the material in the NIST DB
   G4double z, a, density;
   G4String name, symbol;
   G4int ncomponents, natoms;
    
   a = 132.90545*g/mole;
  G4Element* elCs  = new G4Element(name="Caesium",symbol="Cs" , z= 55., a);

   a = 129.9*g/mole;
   G4Element* elI  = new G4Element(name="Iodide"  ,symbol="I" , z= 53., a);

   density = 1.000*g/cm3;
   G4Material* TargetMaterial = new G4Material(name="CsI",density,ncomponents=2);
  TargetMaterial ->AddElement(elCs, natoms=1);
  TargetMaterial ->AddElement(elI, natoms=1);
  fTargetMaterial= TargetMaterial;

  /*
G4NistManager* man = G4NistManager::Instance();
  
  G4bool isotopes = false;
  
  G4Element*  Cs = man->FindOrBuildElement("Cs" , isotopes); 
  G4Element* I = man->FindOrBuildElement("I", isotopes);
  
  
  G4Material* CsI = new G4Material("CsI", 4.51*g/cm3, 2);
  CsI->AddElement(Cs, 1);
  CsI->AddElement(I, 1);
 fTargetMaterial= CsI;
*/
}

// The detector is a simple slab with a thickness along the x-direction.

G4VPhysicalVolume* CsIConstruction::Construct()
{
    // I. CREATE MATERIALS:

    
    // 2. Material for the target: material pointer stored in fTargetMaterial
  
    // II. CREATE GEOMETRY:
    G4Material* materialWorld = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    
    G4Material* materialTarget = fTargetMaterial;
    G4Material* materialCase = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"); 

    G4cout << "\n === YOUR TARGET MATERIAL AT DETECTOR CONSTRUCTION:        " << G4endl;
    G4cout << materialTarget;
    G4cout << " =========================================================== " << G4endl;

    // 1. Define target and world sizes
    G4double targetXSize  = 14*mm;//change dimensions maybe? 14mm 
    G4double targetYSize = 14*mm; //14mm
    G4double targetZSize = 25*mm;//25mm


    G4double worldXSize   = 11.5*m;
    G4double worldYSize  = 8.5*m;
    G4double worldZSize = 4.5*m;

    G4double caseXSize=5.6*cm; //5.6 cm
    G4double caseYSize=2.3*cm;//2.3 cm
    G4double caseZSize=9.3*cm; //9.3 cm


    fGunXPosition         = -0.25*( worldXSize + targetXSize );
    // 2. Create the world and the target (both will be box):
    // a. world
    G4Box*              worldSolid   = new G4Box("solid-World",  // name
    	                                       worldXSize,   // half x-size
    	                                       worldYSize,  // half y-size
    	                                       worldZSize); // half z-size
    G4LogicalVolume*    worldLogical = new G4LogicalVolume(worldSolid,     // solid
                                                           materialWorld,  // material
                                                           "logic-World"); // name
    G4VPhysicalVolume*  worldPhysical = new G4PVPlacement(nullptr,                 // (no) rotation
                                                         G4ThreeVector(0.,0.,0.), // translation
                                                         worldLogical,            // its logical volume
                                                         "World",                 // its name
                                                         nullptr,                 // its mother volume
                                                         false,                   // not used
                                                         0);                      // copy number
    // b. target

     G4Box*              caseSolid   = new G4Box("solid-Case",  // name
    	                                       caseXSize,   // half x-size
    	                                       caseYSize,  // half y-size
    	                                       caseZSize); // half z-size 

   G4LogicalVolume*    caseLogical = new G4LogicalVolume(caseSolid,     // solid
                                                           materialCase,  // material
                                                           "logic-Case"); // name   
   G4VPhysicalVolume*  casePhysical = new G4PVPlacement(nullptr,                 // (no) rotation
                                                         G4ThreeVector(0.,0.,0.), // translation
                                                         caseLogical,            // its logical volume
                                                         "Case",                 // its name
                                                         worldLogical,             // its mother volume
                                                         false,                   // not used
                                                         1,                       // copy number
                                                         true);                      // copy number


    G4Box*      targetSolid   = new G4Box("solid-Target",
                                                     targetXSize ,
                                                     targetYSize ,
                                                     targetZSize);

    G4LogicalVolume*    targetLogical = new G4LogicalVolume(targetSolid,    // solid
                                                           materialTarget,  // material
                                                           "logic-Target"); // name
   G4VPhysicalVolume*  targetPhysical =new G4PVPlacement(nullptr,                 // (no) rotation
                                                          G4ThreeVector(0.,0.,0.), // translation
                                                          targetLogical,           // its logical volume
                                                          "Target",                // its name
                                                          caseLogical,            // its mother volume
                                                          false,                   // not used
                                                          2,                       // copy number
                                                          true);                   // enable overlap check
    // III. RETURN WITH THE World PHYSICAL-VOLUME POINTER:
logicDetector=targetLogical; 
    return worldPhysical;
}
void CsIConstruction :: ConstructSDandField()
{


    // This creates the class for my Sensitive detector crystal
     pCsISD = new CsISD("/CsISD"); //of the G4VSenstitiveDetectorClass 

    // Gets a pointer to the singleton SD class
    pSDMan = G4SDManager :: GetSDMpointer();

    // Adds the sensitive CsI class to the singleton
    pSDMan -> AddNewDetector(pCsISD);

    // Identifies which geometry region is sensitive
    logicDetector ->  SetSensitiveDetector(pCsISD);

     G4double BxValue= 1.0 * tesla;

    G4MagneticField* magField =new G4UniformMagField(G4ThreeVector(BxValue,0.,0.) );
    // If the magnetic field is a 'big' object, all threads should share it (if it is 
    // thread-safe) or else use a proxy object or some different way to share it's data.

    // 1. Find the transportation manager first
    auto transportationManager = G4TransportationManager::GetTransportationManager();
    // Code added HERE

    // 2. Get the existing field manager (more than adequate) - else create a new one
    G4FieldManager* fieldMgr= transportationManager-> GetFieldManager();

    // 2b.  Keep the world Physical volume and then use it to configure this field manager
    // G4FieldManager* 
    //     fieldMgr= fWorldPhysical->GetLogicalVolume()->GetFieldManager();


    // 3. Register the field with this field manager 
    fieldMgr->SetDetectorField(magField);
    //  Code added HERE

    // 4. Create the equation of motion, and default RK integration classes
    fieldMgr->CreateChordFinder(magField); // Default parameters




}
