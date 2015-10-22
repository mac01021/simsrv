
#include "simsrv.h"
#include "r2d.h"


typedef struct {
	double val;
	r2dTexture sprites;
} State;

void *
makestate() {
	State *s = malloc(sizeof(State));
	s->val = 0;
	s->sprites = r2dLoadTextureFromFile("spritesheet.png", GL_NEAREST);
	printf("%d: %d x %d\n\n\n", s->sprites.glid,
				    s->sprites.width,
				    s->sprites.height);
	return (void *)s;
}

void
teardown(void *s) {
	free((State *)s);
}

void
sense(void *S, float *dst) {
	float r = (float)rand();
	*dst = r/((float)RAND_MAX);
}

void
render(void *S) {
	glClear(GL_COLOR_BUFFER_BIT);
	State *state = (State *)S;
	//printf("The state is %f\n", ((State *) S)-> val);
	r2dRectangle src = r2dCreateRectangle(223, 124, 17, 12);
	r2dRectangle dst = r2dCreateRectangle(40, 40, 17, 12);
	r2dDrawFromTexture(&(state->sprites), &dst, &src, 0);
}

bool
evolve(void *S, double timeElapsed, char *motor) {
	State *state = (State *) S;
	state->val += timeElapsed;
	if (motor[0]) {
		state->val = 0;
	}
	return true;
}


void
AI(void *identity, char *pixels, float *sensors, char *motor) {
	if (sensors[0] > .99) {
		motor[0] = 1;
	} else {
		motor[0] = 0;
	}
}

int
main() {
	double S = 0;
	simsrvInit(makestate,
		render, 480, 640, 
		sense, 1,         // 1 floating point sensor
		evolve, 8,        // 8 bytes of motor control
		teardown);
	printf("Starting up...\n");
	printf("loaded sprites.\n");
	simsrvRunSimulationForAgent(NULL, AI);
	simsrvTerminate();
}


