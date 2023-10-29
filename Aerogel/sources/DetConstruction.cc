#include "DetConstruction.hh"

DetConstruction::DetConstruction()
{}

DetConstruction::~DetConstruction()
{}

G4VPhysicalVolume *DetConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
	
	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	G4Element *C = nist->FindOrBuildElement("C");
	
	G4Material *Aerogel = new G4Material("Aerogel", 0.0286*g/cm3, 3);
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);
	
	
		
	G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
	G4double rindexAerogel[2] = {1.006, 1.006};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	
	Aerogel->SetMaterialPropertiesTable(mptAerogel);

	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	
	
	G4Box *solidWorld = new G4Box("solidWorld", 1.*m, 1.*m, 1.*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Box *AerogelBox = new G4Box("AerogelBox", 5.*cm, 5.*cm, 2.*cm);
	G4LogicalVolume *logicGel = new G4LogicalVolume(AerogelBox, Aerogel, "logicGel");
	G4VPhysicalVolume *physGel = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicGel, "physGel", logicWorld, false, 0, true);
	
	return physWorld;
}
