#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()		//operátor vytvoření ake
{}

ActionInitialization::~ActionInitialization()		//destruktor actioninitialization
{}

void ActionInitialization::Build() const
{
	ParticleGun *gun = new ParticleGun();		//definice fce ActionInitialization - spustí particle gun
	SetUserAction(gun);
}
