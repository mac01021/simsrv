
#include "r2d.h"

double *
makestate() {
	double *d = malloc(sizeof(double));
	*d = 0;
	return d;
}

void
teardown(double *d) {
	free(d);
}

void
render(double *S) {
	printf("%f\n", *S);
}

void
evolve(double *S, double timeElapsed) {
	(*S) += timeElapsed;
}

int
main() {
	double S = 0;
	r2dInit(makestate, render, evolve, teardown, 640, 480, 8, 30303);
	r2dWaitForever();
	//r2dWorld world = r2dCreateWorld(false);
	//r2dRunWorld(&world);
	//r2dTerminate();
}
