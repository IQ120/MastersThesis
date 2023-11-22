#include "DetConstruction.hh"


DetConstruction::DetConstruction()
{}

DetConstruction::~DetConstruction()
{}

G4VPhysicalVolume *DetConstruction::Construct()
{

	//############################---Materiálové_definice---#########################
	
	//###---WORLDMAT---###
	G4NistManager *nist = G4NistManager::Instance();		//vytvoření NIST manažera pro hledání v databázi materiálů
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");	//nalezení vzduchu v databázi G4
	
	//###---AEROGEL_MAT---###
	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);	//vytvoření SiO2 materiálu
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);		//přidání křemíku do SiO2
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);		//přidání kyslíku do SiO2
	
	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);	//vytvoření H2O materiálu
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);		//přidání vodíku do H2O
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);		//přidání kyslíku do H2O
	
	G4Element *C = nist->FindOrBuildElement("C");			//Nalezení uhlíku v G4 databázi
	
	G4Material *Aerogel = new G4Material("Aerogel", 0.0286*g/cm3, 3);	//vytvoření aerogelu z SiO2, H2O a C
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);
	
	//###---ALUMINIUM_REFLECTOR_MAT---###
	G4Material *RefMat = nist->FindOrBuildMaterial("G4_Al");		//vyhledání materiálu reflektoru v databázi
	
	//###---LEAD_GLASS_CAL_MAT---###
	G4Material *PbGlass = nist->FindOrBuildMaterial("G4_GLASS_LEAD");	//vyhledání lead glass v G4 databázi
		
	//###########################---Material_Properties_Tables---###############################
		
	G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};	//vytvoření pole energií pro material properties table
	G4double rindexAerogel[2] = {1.006, 1.006};				//vytvoření pole odrazností pro material poperties table aerogelu
	G4double rindexWorld[2] = {1.0, 1.0};					//vytvoření pole odrazností pro material properties table vzduchu
	G4double rindexRef[2] = {1.3729, 1.3729};				//vytvoření pole odraznosti pro hliníkový reflektor
	
	//###---rindex_aerogel---###
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();	//vytvoření material properties table pro aerogel
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);			//přiřazení rindexu pro různé energie světla v aerogelu
	
	Aerogel->SetMaterialPropertiesTable(mptAerogel);				//přiřazení MPT aerogelu

	//###---rindex_world---###
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();	//vytvoření MPT pro vzduch (svět)
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);			//přiřazení rindexu pro různé energie svtla ve vzduchu
	
	worldMat->SetMaterialPropertiesTable(mptWorld);				//přiřazení MPT vzduchu
	
	//###---rindex_reflector---###
	G4MaterialPropertiesTable *mptRef = new G4MaterialPropertiesTable();		//vytvoření MPT pro reflektor
	mptRef->AddProperty("RINDEX", energy, rindexRef, 2);				//přiřazení rindexu hliníku do MPT
	
	RefMat->SetMaterialPropertiesTable(mptRef);					//přiřazení MPT reflektoru
	//#########################---Geometrie---################################
	
	//#######---WORLD---########
	G4Box *solidWorld = new G4Box("World", 50.*cm, 50.*cm, 3.*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");					//vytvoření objemu, logického objemu a vložení světa
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "World", 0, false, 0, true);	
	
	//#######---AEROGEL---#######
	
	G4Box *AerogelBox = new G4Box("AerogelBox", 5.*cm, 5.*cm, 2.*cm);
	G4LogicalVolume *logicGel = new G4LogicalVolume(AerogelBox, Aerogel, "logicGel");					//vytvoření objemu a logického objemu aerogelu
	G4VPhysicalVolume* physGel[4];											//definování pole aerogelů o 4 položkách
	
	//#######---REFLECTOR---#######
	
	G4Para* ref1 = new G4Para("ref1", 1.*um, 50.*mm, 25.*mm, 0., 45.*deg, 0.);			//určení geometrie první části reflektoru
	G4Para* ref2 = new G4Para("ref2", 1.*um, 50.*mm, 25.*mm, 0., -45.*deg, 0.);			//určení geometrie druhé části reflektoru
	
	G4LogicalVolume *logicRef1 = new G4LogicalVolume(ref1, RefMat, "logicRef1");			//přiřazení logického objemu
	G4LogicalVolume *logicRef2 = new G4LogicalVolume(ref2, RefMat, "logicRef2");

	G4VPhysicalVolume* physRef1[4];		//vytvoření polí reflektorů
	G4VPhysicalVolume* physRef2[4];
	
	for(G4int n = 0; n < 4; n++){		//for cyklus generující opakující se prvky - aerogel a reflektory - každá iterace posune prvky o 20 cm
		physGel[n] = new G4PVPlacement(0, G4ThreeVector(0., 0., n*20.*cm), logicGel, "physGel", logicWorld, false, n+100, true);
		G4VPhysicalVolume *physRef1 = new G4PVPlacement(0, G4ThreeVector(25.*mm, 0.*mm, 45.*mm + n*20.*cm), logicRef1, "physRef1", logicWorld, false, n+200, true);	
		G4VPhysicalVolume *physRef2 = new G4PVPlacement(0, G4ThreeVector(-25.*mm, 0.*mm, 45.*mm + n*20.*cm), logicRef2, "physRef2", logicWorld, false, n+300, true);
	}
	
	//#######---LEAD_GLASS_CALORIMETER---#######
	
	G4Box* PbGlassCal = new G4Box("PbGlassCal", 25.*cm, 25.*cm, 50.*cm);
	G4LogicalVolume *logicCal = new G4LogicalVolume(PbGlassCal, PbGlass, "logicCal");
	G4VPhysicalVolume *physCal = new G4PVPlacement(0, G4ThreeVector(0., 0., 150.*cm), logicCal, "physCal", logicWorld, false, 0, true);  
	
	return physWorld;
}
