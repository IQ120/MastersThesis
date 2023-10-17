#include "ParticleGun.hh"

ParticleGun::ParticleGun()
{
	fParticleGun = new G4ParticleGun(1);
}

ParticleGun::~ParticleGun()
{
	delete fParticleGun;
}

void ParticleGun::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e-";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
	
	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(220.);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
