#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
	ParticleGun *gun = new ParticleGun();
	SetUserAction(gun);
}
