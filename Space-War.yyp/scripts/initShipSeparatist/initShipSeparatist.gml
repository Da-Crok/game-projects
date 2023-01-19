function initShipSeparatist() {
	initShip();

	// @func initShipSeparatist
	keyLeft   = ord("J");
	keyRight  = ord("L");
	keyThrust = ord("K");
	keyFire   = ord("I");

	_MISSILE = oMissileSeparatist;

	// separatist ship will start facing left
	image_angle = 180;

	// begin ship in orbit around star
	vX = 1.8 *  cos(degtorad(image_angle));
	vY = 1.8 * -sin(degtorad(image_angle));


}
