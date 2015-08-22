#include "AutoChooser.h"

SendableChooser *AutoChooser::autoChooser;

void AutoChooser::setup(void)
{
	autoChooser = new SendableChooser();

	//c++ is a bit different, not implementing this feature.

	//autoChooser->AddDefault("Do Nothing", Choices::NO_MOVE);
	//autoChooser->AddObject("Move Only", Choices::MOVE_ONLY);
	//autoChooser->AddObject("3 Tote Pickup", Choices::PICK_THREE_TOTE);
}

int AutoChooser::getChoice(void)
{
	return -1; //autoChooser->GetSelected();
	//Returns pointer, please don't use.
}
