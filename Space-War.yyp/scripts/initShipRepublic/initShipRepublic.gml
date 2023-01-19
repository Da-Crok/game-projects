function initShipRepublic() {
	initShip();

	// @func initShipRepublic
	keyLeft   = ord("A");
	keyRight  = ord("D");
	keyThrust = ord("S");
	keyFire   = ord("W");

	_MISSILE = oMissileRepublic;

	// begin ship in orbit around star
	vX = 1.8 *  cos(degtorad(image_angle));
	vY = 1.8 * -sin(degtorad(image_angle));


}
