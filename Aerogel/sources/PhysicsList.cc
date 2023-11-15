#include "PhysicsList.hh"

PhysicsList::PhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());		//registruje list standartních elmag. operací
	RegisterPhysics (new G4OpticalPhysics());		//zahrne různé optickofyzikální efekty - Čerenkovo záření!!!!
}

PhysicsList::~PhysicsList()
{}
