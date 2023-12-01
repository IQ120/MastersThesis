#ifndef PARTICLES_HH
#define PARTICLES_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"

#include "G4RunManager.hh"

class ParticleGun : public G4VUserPrimaryGeneratorAction
{
public:
	ParticleGun();
	~ParticleGun();
	
	virtual void GeneratePrimaries(G4Event*);
	
private:
	G4ParticleGun *fParticleGun;

};

#endif
