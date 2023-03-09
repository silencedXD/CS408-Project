#pragma once
enum MenuCode { mainMenu, options, rLevelSelect, mLevelSelect, quit, videoOptions, audioOptions, controlsOptions, game, win, lose,
	rLevel1, rLevel2, rLevel3, mLevel1, mLevel2, mLevel3};
	//Everything past enum 6 is a level code which means we can calculate the level by subtracting 7 from any menuCode
	//This allows the MenuCode enum to be used in more places and encodes whether the game is actively on a level