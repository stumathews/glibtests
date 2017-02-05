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
