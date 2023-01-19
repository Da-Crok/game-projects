/// @func initShip
/// @description initialize generic ship
function initShip() {
	_MASS = 100;
	_THRUST = 2;
	_TURN_SPEED = 3;


	_MISSILE		  = oMissileRepublic;	// type of missile fired
	_MAX_MISSILES     = 5;		// max number of missiles
	_DV_MISSILE		  = 8;		// delta V when a missile is fired
	_MISSILE_RELOAD   = 80;		// time to reload a missile
	_MISSILE_ARM      = 8;		// time for fired missile to arm
	_MISSILE_LIFE     = 110;	// time for fired missile to be destroyed
	_MISSILE_FIRERATE = 7;		// minimum time between each missile fired
	_MAX_FUEL		  = 150;	// max fuel

	canFire = true;			// allows the ship to fire a missile when true


	vX = 0;
	vY = 0;

	image_angle = 0;
	image_speed = 0;
	image_index = 0;

	ammo = _MAX_MISSILES;
	fuel = _MAX_FUEL;


}
