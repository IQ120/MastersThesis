#include "DetConstruction.hh"

DetConstruction::DetConstruction()
{}

DetConstruction::~DetConstruction()
{}

G4VPhysicalVolume *DetConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4Box *solidWorld = new G4Box("solidWorld", 1.*m, 1.*m, 1.*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	return physWorld;
}
