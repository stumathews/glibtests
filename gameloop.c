#include <stdio.h>
#include <windows.h>
#include <glib.h>

// 20 times a second = 50 milliseconds
// 1 second is 20*50 = 1000 milliseconds

#define TICK_TIME 50
#define MAX_LOOPS 4

struct GameWorldData {} *gameworld_data;
int frameTicks;
int numLoops;
long tickCountAtLastCall,newTime;

/***
 * Check for interactoon requests from controllers
 */
void sense_player_input()
{
	//Map controller actions to meanings for the game:
	// left button was pushed and button A was pressed MEANS -> request to move character left
	// while shooting active weapon.
}

/***
 * Collision detection, no key for door etc...
 */
void determine_restrictions(struct GameWorldData* data)
{
	// check the gameworld data to determine whats around the character physically (geometric restrictions)
	// ie. collision detection

	// check for logical restrictions such as the state the player must be in to perform certain interactions
}

/***
 * show player result of their interaction.
 * Map the restrictions to the interactions and generate the right world-level responses
 */
void update_player_state()
{
	// Trigger the moving animation, if :
	// 1. the controller is used in such a way that it MEANS move character left
	// 2. There is no restriction to move left.

	// Update the player's resultant state.

}

/***
 * Keeps and updated snapshot of the player state
 */
void player_update()
{
	sense_player_input();
	determine_restrictions(gameworld_data);
	update_player_state();
}

/***
 * Select passive elements
 */
void pre_select_active_zones()
{

}

/***
 * Update elements such as walls, and scenario items. These belong to the game world but dont have any
 * attached behavior
 */
void update_passive_elements()
{
	pre_select_active_zones();
}



void logic_sort_according_to_relevance(){}
void execute_control_mechanism(){}
void update_state(){}

/***
 * Update simple logical elements such as doors, elevators or moving platforms
 */
void update_logic_based_elements()
{
	logic_sort_according_to_relevance();
	execute_control_mechanism();
	update_state();
}



/***
 * update the word state based on all the above having been done/happened/occured
 * If shot, mark enemy as hit
 */
void update_world_data_structure()
{

}

/***
 * Generate behavior rules. The plane will turn, then try to shoot
 */
void decision_engine()
{

}


/***
 * the overall restrictions that apply
 */
void sense_restrictions()
{

}

/***
 * goals and current state must be analysed
 *	goals: shoot down aircraft.
 *	state: amount of ammo, direction of aircraft, state of weaponry
 */
void sense_internal_state_and_goals()
{

}

/***
 * An enemy 10 miles away is not important, nor is a door on another level - filter it out.
 */
void ai_sort_according_to_gamplay_relevance()
{

}

/**
 * Update elements that have intelligence like enemies with distinctive behavior
 */
void update_ai_based_elements()
{
	ai_sort_according_to_gamplay_relevance();
	sense_internal_state_and_goals();
	sense_restrictions();
	decision_engine();
	update_world_data_structure();
}

/***
 * Update active elements such as decorative flying birds or doors that open and close
 */
void update_active_elements()
{
	update_logic_based_elements();
	update_ai_based_elements();
}

/***
 * Updates, monitors what the world is doing around the player. This is usually what the player reacts to
 */
void world_update()
{
	update_passive_elements();
	update_active_elements();

}

void GameTickRun()
{
	puts("GameTick ran.");

	// This game logic keeps the world simulator running:
	player_update();
	world_update();
}

// Gets time in milliseconds now
long ticks()
{
	return timeGetTime();
}

void IndependantTickRun(long frameTime)
{
	printf("IndependantTickRun() run. FrameTime=%f\n",frameTime);
}






/***
 * Main graphics pipe line for NPC rendering.
 * Send packed NPC geometry to hardware.
 */
void npc_render_data()
{

}

/***
 * Pack generated NPC geometry data (from the animation step) for this frame into an efficient format
 */
void npc_pack_data()
{

}

/***
 * Produce static geometry data that represents the current snapshot of how the character must look
 * for a given frame.
 *
 * The main animation routines are computed.
 * keyframed to skeletal animations *
 */
void npc_animate()
{

}

/***
 * Select NPCs that are visible as they should be rendered only. Ignore those behind you or on other levels
 */
void npc_select_visible_subset()
{

}

/***
 * Render characters (Non passive Characters)
 * These are animated active elements, usually characters such as enemies
 */
void NPC_Presentation()
{
	npc_select_visible_subset();
	npc_animate();
	npc_pack_data();
	npc_render_data();
}

/***
 * Send player's geometry to the hardware for processing
 */
void player_render_data()
{

}
/***
 * Pack player's geometry into efficient format
 */
void player_data_pack()
{

}
/***
 * Produce static geometry data that represents the current snapshot of how the player must look
 * for a given frame.
 *
 * The main animation routines are computed.
 * keyframed to skeletal animations
 */
void player_animate()
{

}

/***
 * Render player.
 * The player is always visible.
 * Simplier graphics pipeline to NPC and Passive elements
 * no LOD determination - hero is always drawn in High-resoluton meshes
 */
void Player_Presentation()
{
	player_animate();
	player_data_pack();
	player_render_data();
}


/***
 * Send packed audio data to sound hardware(sound card)
 */
void world_send_audio_data_to_audio_hardware()
{

}

/***
 * Pack audio data into efficient format
 */
void world_pack_audio_data()
{

}
/***
 * Select audible sources using typically distance vs volume metric
 */
void world_select_audible_sound_sources()
{

}
/**
 * Store geometry in an efficient format
 */
void world_pack_geometry()
{

}


/***
 * Send packed goemetry to hardware for processing.
 * Eg. OpenGL,Direct3D
 */
void world_render_geometry()
{

}

void world_elements_clip()
{

}
void world_elements_cull()
{

}
void world_elements_occulude()
{

}

/***
 * filter away invisible or irrelevant elements to reduce render overhead.
 * Main graphics pipeline.
 */
void world_select_visible_graphic_elements()
{
	world_elements_clip();
	world_elements_cull();
	world_elements_occulude();
}


/***
 * Determine from elements'd chacracteristics (distance etc) the LOD to be used
 */
void world_select_resolution()
{

}

/***
 * Render the game work visually and sonically
 */
void World_Presentation()
{
	world_select_visible_graphic_elements();
	world_select_resolution();

	// Send graphics to graphics card
	world_pack_geometry();
	world_render_geometry();

	// Send audio to sound card
	world_select_audible_sound_sources();
	world_pack_audio_data();
	world_send_audio_data_to_audio_hardware();
}

/***
 * Render the game world (Presentation)
 * @param percentWithinTick
 */
void GameDrawWithInterpolation(float percentWithinTick)
{
	printf("GameDrawWithInterpolation() run. percentWithinTick=%f\n",percentWithinTick);
	World_Presentation();
	NPC_Presentation();
	Player_Presentation();

}


int main(int argc, char **argv)
{
	gboolean bGameDone = FALSE;
	gboolean bNetworkGame = FALSE;
	gboolean bCanRender = TRUE;

	tickCountAtLastCall = ticks();
	while(!bGameDone) {
		newTime = ticks();
		frameTicks = 0;
		numLoops = 0;
		long ticksSince = newTime - tickCountAtLastCall;
		while((ticksSince) > TICK_TIME && numLoops < MAX_LOOPS ) {
			GameTickRun(); // logic/update
			// tickCountAtLastCall is now been +TICK_TIME more since the last time. update it
			tickCountAtLastCall += TICK_TIME;

			frameTicks += TICK_TIME; numLoops++;
			ticksSince = newTime - tickCountAtLastCall;
		}
		IndependantTickRun(frameTicks); // handle player input, general housekeeping
		if(!bNetworkGame && (ticksSince > TICK_TIME))
			tickCountAtLastCall = newTime - TICK_TIME;
		if(bCanRender) {
			float percentOutsideFrame = (ticksSince/TICK_TIME)*100;
			GameDrawWithInterpolation(percentOutsideFrame);
		}

	}
	return 0;
}
