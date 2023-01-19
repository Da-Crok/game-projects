/// @func updateShip
/// @description updates Ship
function updateShip() {

	var aX, aY;

	aX = 0;
	aY = 0;

	if (fuel < 0)         fuel = 0;
	if (fuel > _MAX_FUEL) fuel = _MAX_FUEL;

	// turning
	if (keyboard_check(keyLeft))  image_angle += _TURN_SPEED;
	if (keyboard_check(keyRight)) image_angle -= _TURN_SPEED;

	// thrusting
	if (keyboard_check(keyThrust) && (fuel > 0)) {
		fuel--;
	
		aX = (_THRUST / _MASS) *  cos(degtorad(image_angle));
		aY = (_THRUST / _MASS) * -sin(degtorad(image_angle));
	
		image_index = 1 - image_index; // thrust animation
	} else {
		image_index = 0;
	}

	if (!keyboard_check(keyThrust)) fuel++;

#region fire missile
	if (keyboard_check(keyFire) && (ammo > 0) && canFire) {
		var inst;
		inst = instance_create_layer(x,y,"Instances",_MISSILE);
		with (inst) {
			x = other.x;
			y = other.y;
			vX = other.vX + other._DV_MISSILE *  cos(degtorad(other.image_angle));
	        vY = other.vY + other._DV_MISSILE * -sin(degtorad(other.image_angle));
			armTime  = other._MISSILE_ARM;
			life = other._MISSILE_LIFE;
		}
	
		canFire = false;
		alarm[1] = _MISSILE_FIRERATE;
	
		// ammo management
		ammo--;
		if (alarm[0] <= 0) alarm[0] = _MISSILE_RELOAD;
	}
#endregion

	updateVehicle(aX, aY);


}
