#ifndef DETCONSTRUCTION_HH
#define DETCONSTRUCTION_HH

#include "globals.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Para.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolumeStore.hh"

class DetConstruction :public G4VUserDetectorConstruction
{
public:
	DetConstruction();
	~DetConstruction();
	
	G4VPhysicalVolume *Construct();
};

#endif
