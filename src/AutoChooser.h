#include "WPILib.h"

#ifndef FRC2015TEAM4159_AUTOCHOOSER_H_
#define FRC2015TEAM4159_AUTOCHOOSER_H_

class AutoChooser {
private:
	static SendableChooser *autoChooser;
	AutoChooser(void);
public:
	enum Choices {
		NO_MOVE, MOVE_ONLY, PICK_ONE_TOTE, PICK_TWO_TOTE_SKIP, PICK_TWO_TOTE_NOSKIP, PICK_THREE_TOTE, NO_CONTAINER_TOTE
	};
	static void setup(void);
	static int getChoice(void);
};

#endif
