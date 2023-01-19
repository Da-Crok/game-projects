/// @func updateVehicle
/// @description handle ship movement
/// @param aX - acceleration from vehicle in x direction
/// @param aY - acceleration from vehicle in y direction
function updateVehicle(argument0, argument1) {

	// acceleration from the vehicle
	var aX = argument0;
	var aY = argument1;

	// add acceleration from gravity wells
	for(i = 0; i < instance_number(oGravityWell); i++) {
		var inst = instance_find(oGravityWell,i);
		with (inst) {
			var rX = x - other.x;
			var rY = y - other.y;
			var rmag = sqrt(rX*rX + rY*rY);
			aX += (g * _MASS) * rX / (rmag*rmag*rmag);
			aY += (g * _MASS) * rY / (rmag*rmag*rmag);
		}
	}

	// velocity
	vX += aX;
	vY += aY;

	if		(vX > MAX_V)  vX = MAX_V;
	else if (vX < -MAX_V) vX = -MAX_V;

	if		(vY > MAX_V)  vY = MAX_V;
	else if (vY < -MAX_V) vY = -MAX_V;

	// position
	x += vX;
	y += vY;

	// room wrap
	if		(x < 0)			  x += room_width;
	else if (x > room_width)  x -= room_width;

	if		(y < 0)			  y += room_height;
	else if (y > room_height) y -= room_height;


}
