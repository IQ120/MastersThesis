#include "ParticleGun.hh"

ParticleGun::ParticleGun()
{
	fParticleGun = new G4ParticleGun(1);		//particle gun creation
}

ParticleGun::~ParticleGun()
{
	delete fParticleGun;				//particle gun destruction
}

void ParticleGun::GeneratePrimaries(G4Event *anEvent)		//PG function
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();	//reference na G4 fatabázi s částicemi
	G4String particleName = "e-";							
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);	//generovaná částice PG - elektron
	
	G4double worldZHalfLength = 0.;
	auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");	//z LogicalVolumeStore vytahujeme parametry světa vytvořeného v DetConstruction.cc
	G4Box* worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());			//vytáhli jsme box volume - nefunguje pokud jiný tvar?
	worldZHalfLength = worldBox->GetZHalfLength();  				//nastavení poloviny velikosti světa
	
	G4ThreeVector pos(0., 0., -worldZHalfLength);					//definice vektoru pozice particle gun
	G4ThreeVector mom(0., 0., 1.);						//definice vektoru směru částic
	
	fParticleGun->SetParticlePosition(pos);					//nastavení pozice PG
	fParticleGun->SetParticleMomentumDirection(mom);				//nastavení směru částic
	fParticleGun->SetParticleEnergy(220.*MeV);					//nastavení energie původní částice
	fParticleGun->SetParticleDefinition(particle);				//nastavení, jakou částici PG vystřeluje
	
	fParticleGun->GeneratePrimaryVertex(anEvent);	
}
