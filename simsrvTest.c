
#include "simsrv.h"

void *
makestate() {
	double *d = malloc(sizeof(double));
	*d = 0;
	return (void *)d;
}

void
teardown(void *d) {
	free((double *)d);
}

void
sense(void *S, float *dst) {
	float r = (float)rand();
	*dst = r/((float)RAND_MAX);
}

void
render(void *S) {
	printf("The state is %f\n", *((double *)S));
}

bool
evolve(void *S, double timeElapsed, char *motor) {
	double *n;
	n = (double *)S;
	(*n) += timeElapsed;
	if (motor[0]) {
		*n = 0;
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
		render, 640, 480, //render at 640 by 480
		sense, 1,         // 1 floating point sensor
		evolve, 8,        // 8 bytes of motor control
		teardown);
	simsrvRunSimulationForAgent(NULL, AI);
	simsrvTerminate();
}
