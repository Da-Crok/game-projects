/// @func updateGame
/// @description handle game updates: room switching, scoring, etc.
function updateGame() {

	if(keyboard_check_pressed(vk_enter)) {
		switch(room) {
			case rmStart:
				room_goto(rmSpace);
				break;
		}
	}

	if(keyboard_check_pressed(vk_escape) && (room == rmSpace)) {
		if (pause == 0) {
			pause = 1;
			instance_deactivate_all(true);
		} else if (pause == 1) {
			pause = 0;
			instance_activate_all();
		}
	}

	if(keyboard_check_pressed(ord("E")) && (pause == 1)) {
		global.p1Score = 0;
		global.p2Score = 0;
		pause = 0;
		instance_activate_all();
		room_goto(rmStart);
	}

	if(keyboard_check_pressed(ord("R")) && (pause == 1)) {
		pause = 0;
		instance_activate_all();
		room_restart();
	}


}
