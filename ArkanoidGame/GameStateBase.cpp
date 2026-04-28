#include "GameStateBase.h"

Arcanoid::GameStateBase::GameStateBase()
{
	assert(font.loadFromFile(FONTS_PATH + "Font.otf"));
}
