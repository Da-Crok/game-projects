/// @func drawGame
/// @description draw UI elements
function drawGame() {

	switch(room){
		case rmSpace:
			draw_set_halign(fa_left);
			draw_text(20,20,string("P1: "+string(global.p1Score)));
			draw_text(20,40,string("P2: "+string(global.p2Score)));
		
			draw_set_halign(fa_right);
			draw_text(room_width-20,20,string("PRESS ESCAPE FOR MENU/RESTART"));
		
			if (pause) drawPauseMenu();
		
			break;
		
		case rmStart:
			draw_set_halign(fa_center);
			var c = c_yellow;
			draw_text_transformed_color(
				room_width/2, 175, "SPACE WAR",
				3, 3, 0, c,c,c,c, 1
			);
		
			draw_text(
				room_width/2, 275,
@"Destroy your opponent's ship to score points!



>> PRESS ENTER TO START <<
"
	);
		
			draw_set_halign(fa_right);
			draw_text(
				room_width/2, 600,
@"Player 1         

A/D: Rotate          
S:   Thrust          
W:   Fire Missile    
"
	);		

			draw_set_halign(fa_left);
			draw_text(
				room_width/2, 600,
@"        Player 2

J/L: Rotate
K:   Thrust
I:   Fire Missile
"
	);
			break;
	}


}
