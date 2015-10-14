//
//
// STUFF HERE.
//
// OK
//
//


#include <arpa/inet.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "GLFW/glfw3.h"





typedef void *(*r2dStateFactory)();
typedef void (*r2dDrawFunc)(void*);
typedef void (*r2dStateUpdateFunc)(void* state, double timeElapsed);
typedef void (*r2dStateDestructor)(void*);

static bool INITTED = false;
static int SOCKET_FD = 0;
static pthread_t LISTENER_THREAD;
static r2dStateFactory INITIAL_STATE_CALLBACK;
static r2dDrawFunc DRAW_CALLBACK;
static r2dStateUpdateFunc EVOLVE_CALLBACK;
static r2dStateDestructor DESTROY_STATE_CALLBACK;
static int32_t SCREEN_WIDTH;
static int32_t SCREEN_HEIGHT;
static int32_t MOTOR_SIZE;


typedef struct {
	GLFWwindow *window;
	void *state;
	double timeElapsed;
	int sockfd;
	bool freeOnTermination;
} r2dWorld;

void
r2dError(int error, const char *description) {
	fputs(description, stderr);
	glfwTerminate();
	exit(EXIT_FAILURE);
}

r2dWorld
r2dCreateWorldWithSocket(int sockfd, bool freeOnTermination) {
	GLFWwindow *win = glfwCreateWindow(SCREEN_WIDTH,
					   SCREEN_HEIGHT,
					   "r2dSimulation",
					   NULL,
					   NULL);
	if (!win) {
		r2dError(0, "Could not create window");
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	//TODO: SET CALLBACKS OR SOMETHING
	r2dWorld world = (r2dWorld) { win,
				      INITIAL_STATE_CALLBACK(),
				      glfwGetTime(),
				      sockfd,
				      freeOnTermination};
	return world;
}

r2dWorld
r2dCreateWorld(bool freeOnTermination) {
	return r2dCreateWorldWithSocket(0, freeOnTermination);
}

void
r2dDestroyWorld(r2dWorld *world) {
	glfwDestroyWindow(world->window);
	if (world->sockfd > 0) {
		close(world->sockfd);
	}
	DESTROY_STATE_CALLBACK(world->state);
	if (world->freeOnTermination) {
		free(world);
	}
}


void
r2dRunWorld(r2dWorld *world) {
	while(!glfwWindowShouldClose(world->window) && true) {
		DRAW_CALLBACK(world->state);
		glfwSwapBuffers(world->window);
		//socketSendPixels();

		glfwPollEvents();
		//socketReadMotor();
		double now = glfwGetTime();
		double deltaT = now - world->timeElapsed;
		world->timeElapsed = now;
		EVOLVE_CALLBACK(world->state, deltaT);
	}
	r2dDestroyWorld(world);
}

void *
r2dRunWorldVoid(void *world) {
	r2dRunWorld((r2dWorld *) world);
	return NULL;
}

void
r2dBeginSocketSession(int sockfd) {
	int32_t inNetworkOrder[3] = { htonl(SCREEN_WIDTH),
				      htonl(SCREEN_HEIGHT),
				      htonl(MOTOR_SIZE) };
	if (send(sockfd, &inNetworkOrder, 3 * sizeof(int32_t), 0) != 3*sizeof(int32_t)) {
		r2dError(0, "Trouble sending session prelude on socket");
	}
}


void*
r2dAcceptConnections(void *nothing) {
	while (1) {
		int connfd = accept(SOCKET_FD, (struct sockaddr *)NULL, NULL);
		r2dBeginSocketSession(connfd);
		r2dWorld *world = malloc(sizeof(r2dWorld));
		if (!world) {
			r2dError(0, "Could not allocate world on heap!");
		}
		*world = r2dCreateWorldWithSocket(connfd, true);
		pthread_t newthread;
		if (pthread_create(&newthread, NULL, r2dRunWorldVoid, world)) {
			r2dError(0, "Failed to spawn thread for new world");
		}
	}
	return NULL;
}

void
r2dInit(r2dStateFactory stateFactory,
	r2dDrawFunc drawFunc,
	r2dStateUpdateFunc updateFunc,
	r2dStateDestructor stateDestructor,
	int32_t screenWidth,
	int32_t screenHeight,
	int32_t motorSize,
	int portno) {
	if (!INITTED) {
		INITTED = true;
		INITIAL_STATE_CALLBACK = stateFactory;
		DRAW_CALLBACK = drawFunc;
		EVOLVE_CALLBACK = updateFunc;
		DESTROY_STATE_CALLBACK = stateDestructor;
		SCREEN_HEIGHT = screenHeight;
		SCREEN_WIDTH = screenWidth;
		MOTOR_SIZE = motorSize;
		if (!glfwInit()) {
			r2dError(0, "Could not initialize GLFW");
			exit(EXIT_FAILURE);
		}
		if (portno) {
			struct sockaddr_in srvAddr;
			SOCKET_FD = socket(AF_INET, SOCK_STREAM, 0);
			if (SOCKET_FD > 0) {
				srvAddr.sin_family = AF_INET;
				srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
				srvAddr.sin_port = htons(portno);
				if (bind(SOCKET_FD, (struct sockaddr*) &srvAddr, sizeof(srvAddr)) < 0) {
					r2dError(0, "Binding error");
				}
				listen(SOCKET_FD, 5);
			}
		}
		pthread_create(&LISTENER_THREAD, NULL, r2dAcceptConnections, NULL);
	}
}

void
r2dWaitForever() {
	pthread_join(LISTENER_THREAD, NULL);
}

void
r2dTerminate() {
	if (INITTED) {
		glfwTerminate();
		INITTED = false;
	}
}

