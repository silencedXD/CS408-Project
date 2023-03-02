#include "Rock.h"

Rock::Rock(int x_, int y_, int z_, int type_, sf::SoundBuffer* buffer) {
	x = x_;
	y = y_;
	z = z_;
	type = type_;
	range = 10;

	deleteFlag = false;
	sound = sf::Sound();
	sound.setBuffer(*buffer);
	sound.setPosition(x, y, z);
}

bool Rock::checkCollision(int player_x, int player_y, int player_z) {
	if (x == player_x && y == player_y && z == player_z) {	//Return true if there is a direct collision
		return true;
	}
	else {//If the player is one move away then a sound is played to tell them they are near
		int xDif = calcDistance(x, player_x);
		int yDif = calcDistance(y, player_y);
		
		if (xDif < range && yDif < range) {			
			if (sound.getStatus() != sf::SoundSource::Playing) {
				int volume = 100 - range * xDif;
				sound.setVolume(volume);
				float rangeFactor = 1 / float(range);
				float pitchFactor = rangeFactor * yDif;
				float pitch = 1.0 - pitchFactor;
				sound.setPitch(pitch);
				sound.play();
			}
		}
		return false;
	}
}

int Rock::calcDistance(int x, int player_x) {
	return abs(x - player_x);
}

bool Rock::isNearPlayer(int player_x, int player_y, int player_z) {
	if (abs(x - player_x) < range) {
		return true;			
	}
	else {
		return false;
	}
}
