/// @description reloads a missile

// reload one missile
ammo++;

// continue loading missiles until full
if (ammo < _MAX_MISSILES) alarm[0] = _MISSILE_RELOAD;