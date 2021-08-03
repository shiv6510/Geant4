#include "YourDetectorConstruction.hh"

// for geometry definitions
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

// Constructor
//
YourDetectorConstruction::YourDetectorConstruction() : G4VUserDetectorConstruction()
{
}

// Destructor
//
YourDetectorConstruction::~YourDetectorConstruction()
{
}
// The detector is a simple slab with a thickness along the x-direction.
//
G4VPhysicalVolume* YourDetectorConstruction::Construct()
{
    // Materials
    G4Material* case_material
        = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    G4Material* crystal_material
        = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ge");
    G4Material* world_material
        = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    G4Material* window_material
        = G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");

    // II. CREATE GEOMETRY:

    // a. Create the world (a box), defining first its size:
    G4double worldXSize   = 11.5824*m;
    G4double worldYSize   = 4.572*m;
    G4double worldZSize   = 8.5344*m;
    G4Box* worldSolid
           = new G4Box("solid-World",    // name
    	               0.5*worldXSize,  // x-size
    	               0.5*worldYSize,  // y-size
    	               0.5*worldZSize); // z-size
    G4LogicalVolume* worldLogical
           = new G4LogicalVolume(worldSolid,     // solid
                                 world_material,  // material
                                 "logic-World"); // name
    G4VPhysicalVolume* worldPhysical
           = new G4PVPlacement(nullptr,                 // (no) rotation
                               G4ThreeVector(0.,0.,0.), // translation
                               worldLogical,            // its logical volume
                               "World",                 // its name
                               nullptr,                 // its mother volume
                               false,                   // not used
                               0);                      // copy number

    //Casing Geometry
    G4double case_radius = 6.30*cm;
    G4double case_height = 8.33*cm;
    G4double crystal_radius = 0.79*case_radius;
    G4double crystal_height = 0.74*case_height;
    G4double stand_trans = (1.0-0.7)*case_height;
    G4ThreeVector z_trans(0,0,stand_trans/6.);

    G4Tubs* case_0
        = new G4Tubs("case_0", 0*cm, case_radius, case_height/2., 0*deg, 360*deg);
    G4Tubs* case_1
        = new G4Tubs("case_1", 0.1*crystal_radius, crystal_radius,
                     (case_height-(stand_trans/3.))/2., 0*deg, 360*deg);
    G4Tubs* case_2
        = new G4Tubs("case_2", 0, 0.101*crystal_radius, 2.*stand_trans/3./2., 0*deg, 360*deg);


    G4SubtractionSolid* case_01
        = new G4SubtractionSolid("case_01", case_0, case_1, nullptr, z_trans);

    G4SubtractionSolid* case_012
        = new G4SubtractionSolid("case_012", case_01, case_2, nullptr,
                                 G4ThreeVector(0,0,((case_height-(2*stand_trans/3.))+0.001)/2.));


    G4LogicalVolume* case_logical
        = new G4LogicalVolume(case_012, case_material, "case_012");

    G4VPhysicalVolume* case_physical
        = new G4PVPlacement(nullptr,  G4ThreeVector(0,0,0), case_logical,
                            "case", worldLogical, true, 0, true);

    //Crystal Geometry
    G4ThreeVector cryst_1_z_trans(0,0,(.7*case_height-crystal_height)/2.);

    G4Tubs* crystal_0
        = new G4Tubs("crystal_0", 0, crystal_radius-1.*micrometer, crystal_height/2., 0*deg, // took off 1 cm from crystal radius to get rid of overlap
                     360*deg);
    G4Tubs* crystal_1
        = new G4Tubs("crystal_1", 0, 0.2*crystal_radius,
                     (case_height-stand_trans)/2, 0*deg, 360*deg);

    G4SubtractionSolid* crystal_01
         = new G4SubtractionSolid("crystal_01", crystal_0, crystal_1, nullptr, cryst_1_z_trans);

    G4LogicalVolume* crystal_logical
         = new G4LogicalVolume(crystal_01, crystal_material, "crystal_01");

	logicDetector = crystal_logical;

    G4double insertion_parameter  = (case_height/2. - stand_trans/3.) - (crystal_height/2.);
    G4VPhysicalVolume* crystal_physical
        = new G4PVPlacement(nullptr,  G4ThreeVector(0,0,0-insertion_parameter+1.*micrometer) // raised the placement of the crystal in case to get rid of overlap
                           , logicDetector, "crystal", worldLogical, true, 0, true);

    // Beryllium Window
    G4double window_height = 0.02*case_height;
    G4double window_trans = (case_height-window_height)/2.;

    G4Tubs* window
        = new G4Tubs("window", 0, crystal_radius, window_height/2, 0*deg, 360*deg);

    G4LogicalVolume* window_logical
        = new G4LogicalVolume(window, window_material, "window");
    G4VPhysicalVolume* window_physical
        = new G4PVPlacement(nullptr, G4ThreeVector(0,0,window_trans), window_logical,
               "window", worldLogical, true, 0, true);
    // ++++++++++++++++++++++++++ YOUR CODE FROM HERE ++++++++++++++++++++++++
	//fTargetPhysical = new G4PVPlacement (nullptr,  G4ThreeVector(0,1000,0-insertion_parameter)
    //                        , crystal_logical, "crystal", worldLogical, true, 0);
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	G4VSensitiveDetector* HPGe = new MySensitiveDetector("HPGe");
	G4SDManager* SDMan = G4SDManager::GetSDMpointer();
	SDMan->AddNewDetector(HPGe);
	logicDetector->SetSensitiveDetector(HPGe);

    // III. RETURN THE World PHYSICAL-VOLUME POINTER:
    return worldPhysical;
}


/*
void YourDetectorConstruction::ConstructSDandField(){

	MySensitiveDetector *HPGe = new MySensitiveDetector("HPGe");
	logicDetector->SetSensitiveDetector(HPGe);
}
*/
