#include <stdio.h>
#include <windows.h>
#include <glib.h>

// 20 times a second = 50 milliseconds
// 1 second is 20*50 = 1000 milliseconds

#define TICK_TIME 50
#define MAX_LOOPS 4

void GameTickRun()
{
	puts("GameTick ran.");

	// This game logic keeps the world simulator running:
	player_update();
	world_update();
}

/***
 * Updates, monitors what the world is doing around the player. This is usually what the player reacts to
 */
void world_update()
{
	update_passive_elements();
	update_active_elements();

}

/***
 * Update elements such as walls, and scenario items. These belong to the game world but dont have any
 * attached behavior
 */
void update_passive_elements()
{
	pre_select_active_zones();
}

void pre_select_active_zones()
{

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
 * Update simple logical elements such as doors, elevators or moving platforms
 */
void update_logic_based_elements()
{
	logic_sort_according_to_relevance();
	execute_control_mechanism();
	update_state();
}

void logic_sort_according_to_relevance(){}
void execute_control_mechanism(){}
void update_state(){}

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

/***
 * Keeps and updated snapshot of the player state
 */
void player_update()
{
	sense_player_input();
	determine_restrictions();
	update_player_state();
}

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

// Gets time in milliseconds now
long ticks()
{
	return timeGetTime();
}

void IndependantTickRun(long frameTime)
{
	printf("IndependantTickRun() run. FrameTime=%f\n",frameTime);
}

void GameDrawWithInterpolation(float percentWithinTick)
{
	printf("GameDrawWithInterpolation() run. percentWithinTick=%f\n",percentWithinTick);
}

int frameTicks;
int numLoops;
long tickCountAtLastCall,newTime;
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
