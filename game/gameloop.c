#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glib.h>
#include <safetychecking.h>

// 20 times a second = 50 milliseconds
// 1 second is 20*50 = 1000 milliseconds

#define TICK_TIME 50
#define MAX_LOOPS 4
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


struct GameWorldData {
	int x;
	int y;
	int w;
	int h;
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	gboolean bGameDone;
	gboolean bNetworkGame;
	gboolean bCanRender;
} *gameworld_data;
typedef struct GameWorldData GameWorldData;

int frameTicks;
int numLoops;
long tickCountAtLastCall,newTime;
SDL_Texture* texture = NULL;

SDL_Rect renderRectangle(const int x, const int y, const int w, const int h, struct GameWorldData *gameWorldData);
void renderLine(SDL_Renderer* toRenderer);

/***
 * Check for interactoon requests from controllers
 */
void sense_player_input(struct GameWorldData *gameWorldData)
{
	//Map controller actions to meanings for the game:
	// left button was pushed and button A was pressed MEANS -> request to move character left
	// while shooting active weapon.

	//Event handler
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0)
	{

		if(e.type == SDL_QUIT)
		{
			gameWorldData->bGameDone = 1;
		} else if( e.type == SDL_KEYDOWN ) {
			switch( e.key.keysym.sym )
			{
				case SDLK_UP:
					puts("up!");
					gameWorldData->y -= 20;
				break;

				case SDLK_DOWN:
					puts("down!");
					gameWorldData->y += 20;
				break;

				case SDLK_LEFT:
					puts("left!");
					gameWorldData->x -= 20;
				break;

				case SDLK_RIGHT:
					puts("right!");
					gameWorldData->x += 20;
				break;

				default:
					puts("something else!");
				break;
			}
		}
	}
}

/***
 * Collision detection, no key for door etc...
 */
void determine_restrictions(struct GameWorldData* data)
{
	// check for geometric restrictions via the gameworld data to determine whats around the character physically
	// ie. collision detection

	// check for logical restrictions ie the state the player must be in to perform certain interactions
	// ie do i have a door key to even though i'm trying to open the door in fron of me?

	// use the gameworld data to understand where the player is (level) and what he has around him

	// easy restrictions for tetris: 
	// 1) bricks cannot move outside the screen, 
	// 2) cannot fall beyond ground level
	// 3) cannot continue falling if current brick is directly above any other previously fallen brick
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

	// Tetris: move/rotate the brick according to players input

	// then: AddDefaultBehavior() for idle

}

/***
 * Keeps and updated snapshot of the player state
 */
void player_update(struct GameWorldData *gameWorldData)
{
	// read from game controller
	sense_player_input(gameWorldData);
	// First see if we can perform what the payer wants us to do (we might be unable to, next to wall ie. cant move forward)
	determine_restrictions(gameworld_data);
	// Do what we can to update the players state based on the above and what the player tied to do
	// so move the player's position if he asked to move and there was no obstacle etc.
	update_player_state();

	// If networked game:
	// broadcast players state(position eg) to other players on the network
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
	pre_select_active_zones(); // only select elments that will affect gameplay
}



void logic_sort_according_to_relevance(){}
void execute_control_mechanism(){}
void update_state(){}

/***
 * Update simple logical elements such as doors, elevators or moving platforms
 */
void update_logic_based_elements()
{
	logic_sort_according_to_relevance(); // only select elements that are important to the gameplay
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
	sense_internal_state_and_goals(); // goal: shoot down the player. internal state of element: position and heading, state of weapons systems and sustained damage
	sense_restrictions(); // avoid collisions with wall if im an enemy ai element
	// we know about our state and the players state now...
	
	// determine what the ai elements will do next (ai decisions may span several seconds or minutes of gameplay, probably refining
	// the strategy/decision on each subsequent cycle here)
	decision_engine();

	// store that the enemy moved, or it ws shot so remove it from world data structure
	update_world_data_structure();
}

/***
 * Update active elements such as decorative flying birds or doors that open and close
 */
void update_active_elements()
{
	update_logic_based_elements(); // doors, elevators, movng platforms, real enemies with a distinctive behavior (simple)
	update_ai_based_elements(); // real enemies with artificial intelligence behavior (more complex)
}

/***
 * Updates, monitors what the world is doing around the player. This is usually what the player reacts to
 */
void world_update()
{
	update_passive_elements(); //walls and most scenario items - have no attached behavior but play a key role in player restrictions
	update_active_elements(); // flying birds, doors that open and close - must be checked to keep consistent, meaningful experiance

}

// This is basically the update functions which is run x FPS to maintain a timed series on constant updates 
// that simulates constant movement for example or time intervals in a non-time related game (turn based game eg)
void GameTickRun(struct GameWorldData *gameWorldData)
{
	// This game logic keeps the world simulator running:
	player_update(gameWorldData);
	
	// make the game do something now...show game activity that the user will then respond to
	// this generates gameplay
	world_update();
}

// Gets time in milliseconds now
long ticks()
{
	return g_get_real_time() / 1000;
}

void IndependantTickRun(long frameTime)
{
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
 * Render characters (Non player Characters)
 * These are animated active elements, usually characters such as enemies
 */
void NPC_Presentation()
{
	npc_select_visible_subset(); //only thoe close to the player or affecting him are to be processed. Visibility check is usually used
	npc_animate(); // keyframed to skeletal animations represent a current snapshot of how the character must look for a given frame
	
				   // some animation methods will require specific rendering algorithms to characters will need to be rendered seperately from passive world geometry
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

// chop off items outside of the players view
void world_elements_clip()
{

}

// remove hidden objects - such as backward facing surfaces
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
 * Send audio to sound card
 */
void send_audio_to_hardware()
{

	world_select_audible_sound_sources(); // distance vs volume metric + attenuation calcs to determine whats is audible to player
	world_pack_audio_data();
	world_send_audio_data_to_audio_hardware();
}

/***
 * Send graphics to graphics card
 */
void send_geometry_to_hardware()
{
	world_pack_geometry(); // vertexes are packed into memory
	world_render_geometry(); //  send to card via OpenGL or DirectX
}

/***
 * Render the game work visually and sonically
 */
void World_Presentation()
{
	// show just the visible part of the gameworld from the player's perspective
	world_select_visible_graphic_elements(); // This will contain the 3d Rendering pipeline!
	world_select_resolution(); // Choose suitable level of detail

	send_geometry_to_hardware();  //paint it onto the screen
	send_audio_to_hardware(); 
}

void drawVerticalLineOfDots(const int SCREEN_HEIGHT, const int SCREEN_WIDTH,struct GameWorldData *gameWorldData)
{
	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(gameWorldData->windowRenderer, 0x00, 0x00, 0xFF, 0x00);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
		SDL_RenderDrawPoint(gameWorldData->windowRenderer, SCREEN_WIDTH / 2, i);
	}
}

void drawtexttureTopLeft(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, struct GameWorldData* gameWorldData, SDL_Texture* texture)
{
	//Top left corner viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 2;
	topLeftViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gameWorldData->windowRenderer, &topLeftViewport);
	//Render texture to screen

	SDL_RenderCopy(gameWorldData->windowRenderer, texture, NULL, NULL);
}

void ResetViewport(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, struct GameWorldData* gameWorldData)
{
	SDL_Rect whole_screen;
	whole_screen.x = 0;
	whole_screen.y = 0;
	whole_screen.w = SCREEN_WIDTH;
	whole_screen.h = SCREEN_HEIGHT;
	SDL_RenderSetViewport(gameWorldData->windowRenderer, &whole_screen);
}

/***
 * Render the game world (Presentation)
 * @param percentWithinTick
 */
void GameDrawWithInterpolation(float percentWithinTick, struct GameWorldData *gameWorldData)
{
	//Custom SDL drawing...

	// renderTextture(windowRenderer, texture);

	SDL_Rect fillRect = renderRectangle(gameWorldData->x, gameWorldData->y, 100,100, gameWorldData);
	renderLine(gameWorldData->windowRenderer);
	drawVerticalLineOfDots(SCREEN_HEIGHT, SCREEN_WIDTH, gameWorldData);

	drawtexttureTopLeft(SCREEN_WIDTH, SCREEN_HEIGHT, gameWorldData, texture);
	ResetViewport(SCREEN_WIDTH, SCREEN_HEIGHT, gameWorldData);
	SDL_RenderPresent(gameWorldData->windowRenderer);

	// Render the game work visually and sonically
	World_Presentation();
	
	// Render non player characters next
	NPC_Presentation();

	// Render the player
	Player_Presentation();
}

SDL_Rect renderRectangle(const int x, const int y, const int w, const int h, struct GameWorldData *gameWorldData)
{
	SDL_Renderer *toRenderer = gameWorldData->windowRenderer;
	SDL_SetRenderDrawColor(toRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(toRenderer);

	SDL_Rect fillRect = { x , y , w, h };
	SDL_SetRenderDrawColor(toRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(toRenderer, &fillRect);

	return fillRect;
}

SDL_Texture* loadCreateTexture(char* texturePath, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* imageSurface = IMG_Load(texturePath);
	CHK_ExitIf(imageSurface == NULL,"SDL could not load image!",(char*)IMG_GetError());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	CHK_ExitIf(newTexture == NULL,"Unable to create texture!",(char*)SDL_GetError());

	//Get rid of old loaded surface
	SDL_FreeSurface(imageSurface);
	return newTexture;
}

SDL_Window* GetSDLWindow(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	SDL_Window* outWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
	CHK_ExitIf(outWindow == NULL, "Window could not be created!",(char*)SDL_GetError());
	return outWindow;
}

SDL_Renderer* GetSDLWindowRenderer(SDL_Window* window)
{
	SDL_Renderer* outRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	CHK_ExitIf(outRenderer == NULL, "Renderer could not be created!", (char*)SDL_GetError());
	SDL_SetRenderDrawColor(outRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	return outRenderer;
}

SDL_Texture* GetSDLTexture(char* path, SDL_Renderer* windowRenderer)
{
	CHK_ExitIf(path == NULL, "textture path cant be empty!", "no path given");
	SDL_Texture* outTexture = loadCreateTexture(path, windowRenderer);
	CHK_ExitIf(outTexture == NULL, "could not load textture", "outTexture");
	return outTexture;
}

void renderLine(SDL_Renderer* toRenderer)
{
	 //Draw blue horizontal line
	SDL_SetRenderDrawColor( toRenderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderDrawLine( toRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
}

void renderTextture(SDL_Renderer* toRenderer, SDL_Texture* texture)
{
	SDL_RenderClear(toRenderer);

	//Render texture to renderer
	SDL_RenderCopy(toRenderer, texture, NULL, NULL);

	//Update rendrer
	SDL_RenderPresent(toRenderer);
}



void InitSDL()
{
	// Initialise SDL
	CHK_ExitIf(SDL_Init(SDL_INIT_VIDEO) < 0, "SDL could not initialize!", (char*)SDL_GetError());

	// Initialize SDL Image extension
	CHK_ExitIf(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG), "SDL_image could not initialize!", (char*)IMG_GetError());
}

void CleanupResources(struct GameWorldData* gameWorldData)
{
	SDL_DestroyRenderer(gameWorldData->windowRenderer);
	SDL_DestroyWindow(gameWorldData->window);

	gameWorldData->window = NULL;
	gameWorldData->windowRenderer = NULL;

	IMG_Quit();
	SDL_Quit();

	free(gameWorldData);
}

struct GameWorldData* InitGameWorldData()
{
	struct GameWorldData* gameWorldData = malloc(sizeof(struct GameWorldData));
	CHK_ExitIf(gameWorldData == NULL,"malloc failed","creatiung gameworld data");

	gameWorldData->x = 0;
	gameWorldData->y = 0;
	gameWorldData->w = 100;
	gameWorldData->h = 100;
	gameWorldData->window = NULL;
	gameWorldData->windowRenderer = NULL;
	gameWorldData->bGameDone = 0;
	gameWorldData->bNetworkGame = 0;
	gameWorldData->bCanRender = 1;
	return gameWorldData;
}

int main(int argc, char *args[])
{
	GameWorldData* gameWorldData = InitGameWorldData();



	InitSDL();

	gameWorldData->window = GetSDLWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	gameWorldData->windowRenderer = GetSDLWindowRenderer(gameWorldData->window);

	//texture = GetSDLTexture("texture.png", gameWorldData->windowRenderer);

	tickCountAtLastCall = ticks();

	while(!gameWorldData->bGameDone) {
		newTime = ticks();
		frameTicks = 0;
		numLoops = 0;
		long ticksSince = newTime - tickCountAtLastCall;

		// New frame, happens consistently every 50 milliseconds. Ie 20 times a second.
		// 20 times a second = 50 milliseconds
		// 1 second is 20*50 = 1000 milliseconds
		while((ticksSince) > TICK_TIME && numLoops < MAX_LOOPS ) {
			GameTickRun(gameWorldData); // logic/update

			// tickCountAtLastCall is now been +TICK_TIME more since the last time. update it
			tickCountAtLastCall += TICK_TIME;

			frameTicks += TICK_TIME; numLoops++;
			ticksSince = newTime - tickCountAtLastCall;
		}

		IndependantTickRun(frameTicks); // handle player input, general housekeeping

		if(!gameWorldData->bNetworkGame && (ticksSince > TICK_TIME)) {
			tickCountAtLastCall = newTime - TICK_TIME;
		} else if(gameWorldData->bCanRender) {
			float percentOutsideFrame = (ticksSince/TICK_TIME)*100;
			GameDrawWithInterpolation(percentOutsideFrame,gameWorldData);
		}
	}
	puts("Game done");
	CleanupResources(gameWorldData);
	return 0;
}
