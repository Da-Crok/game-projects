function updateMissile() {
	life--;
	armTime--;

	if (armTime < 0) {
		armed = true;
		image_index = 1;
	}

	updateVehicle(0, 0);

	if (life < 0) instance_destroy();


}
