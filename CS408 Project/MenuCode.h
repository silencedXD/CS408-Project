#pragma once
enum MenuCode { mainMenu, options, levelSelect, tutorial, instructions, quit, videoOptions, audioOptions, controlsOptions, game, win, lose,
	level1, level2, level3, practiseLevel1, practiseLevel2, practiseLevel3};
	//Everything past enum 6 is a level code which means we can calculate the level by subtracting 7 from any menuCode
	//This allows the MenuCode enum to be used in more places and encodes whether the game is actively on a level