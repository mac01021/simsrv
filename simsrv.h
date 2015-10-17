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


///////////////////////// DIE ON ERROR /////////////////////////////////////
void
simsrvError(int error, const char *description) {
	fputs(description, stderr);
	glfwTerminate();
	exit(EXIT_FAILURE);
}
////////////////////////////////////////////////////////////////////////////


 /////////////////////// THE GAME/TASK IS IMPLEMENTED IN 4 FUNCTIONS ///////
///////////////////////   (ALL PROVIDED TO THE INIT METHOD ////////////////
typedef void *(*simsrvStateFactory)();
typedef void (*simsrvDrawFunc)(void *state);
typedef void (*simsrvSensorFunc)(void *state, float *sensors);
typedef bool (*simsrvStateUpdateFunc)(void *state, double timeElapsed, char *motor);
typedef void (*simsrvStateDestructor)(void *);
/////////////////////////////////////////////////////////////////////////
typedef void (*simsrvAgentFunc)(void *agent, char *pixels, float *sensors, char *motor);
////////////////////////////////////////////////////////////////////////

static bool simsrvINITTED = false;
static simsrvStateFactory simsrvINITIAL_STATE_CALLBACK;
static simsrvDrawFunc simsrvDRAW_CALLBACK;
static simsrvSensorFunc simsrvSENSOR_CALLBACK;
static simsrvStateUpdateFunc simsrvEVOLVE_CALLBACK;
static simsrvStateDestructor simsrvDESTROY_STATE_CALLBACK;
static int32_t simsrvSCREEN_WIDTH;
static int32_t simsrvSCREEN_HEIGHT;
static int32_t simsrvNONVISUAL_SENSOR_SIZE;
static int32_t simsrvMOTOR_SIZE;


////////////INIT INITIALIZES GLFW AND STORES THE CALLBACKS THAT CONSTITUTE //
///////////                 THE TASK     ///////////////////////////////////
void
simsrvInit(simsrvStateFactory stateFactory,
	simsrvDrawFunc drawFunc, int32_t screenWidth, int32_t screenHeight,
	simsrvSensorFunc sensorFunc, int32_t nvSize,
	simsrvStateUpdateFunc updateFunc, int32_t motorSize,
	simsrvStateDestructor stateDestructor) {
	if (!simsrvINITTED) {
		simsrvINITTED = true;
		simsrvINITIAL_STATE_CALLBACK = stateFactory;
		simsrvDRAW_CALLBACK = drawFunc;
		simsrvSENSOR_CALLBACK = sensorFunc;
		simsrvEVOLVE_CALLBACK = updateFunc;
		simsrvDESTROY_STATE_CALLBACK = stateDestructor;
		simsrvSCREEN_HEIGHT = screenHeight;
		simsrvSCREEN_WIDTH = screenWidth;
		simsrvNONVISUAL_SENSOR_SIZE = nvSize;
		simsrvMOTOR_SIZE = motorSize;
		if (!glfwInit()) {
			simsrvError(0, "Could not initialize GLFW");
			exit(EXIT_FAILURE);
		}
	}
}

void
simsrvTerminate() {
	if (simsrvINITTED) {
		glfwTerminate();
		simsrvINITTED = false;
	}
}

///////////////////////////////////////////////////////////////////////////


GLFWwindow *
simsrvCreateWindow() {
	GLFWwindow *win = glfwCreateWindow(simsrvSCREEN_WIDTH,
					   simsrvSCREEN_HEIGHT,
					   "simsrvSimulation",
					   NULL,
					   NULL);
	if (!win) {
		simsrvError(0, "Could not create window");
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	return win;
}





//////////////////////////////////////////////////////////////////////////


void
simsrvSendSessionPreludeOnSocket(int sockfd) {
	int32_t inNetworkOrder[4] = { htonl(simsrvSCREEN_WIDTH),
				      htonl(simsrvSCREEN_HEIGHT),
				      htonl(simsrvNONVISUAL_SENSOR_SIZE),
				      htonl(simsrvMOTOR_SIZE) };
	int nbBytes = 4 * sizeof(int32_t);
	if (send(sockfd, &inNetworkOrder, nbBytes, 0) != nbBytes) {
		simsrvError(0, "Trouble sending session prelude on socket");
	}
}


void
simsrvSendSensoryDataOnSocket(int sockfd, void *state) {
	char buf[3 * simsrvSCREEN_WIDTH * simsrvSCREEN_HEIGHT];
	buf[3] = 4;
	//TODO
}

void
simsrvReadMotorFromSocket(int sockfd, char *motor) {
	//TODO
}

void
simsrvRunServedSimulation(int sockfd) {
	simsrvSendSessionPreludeOnSocket(sockfd);
	GLFWwindow *win = simsrvCreateWindow();
	void *s = simsrvINITIAL_STATE_CALLBACK();
	double t = glfwGetTime();
	double now, deltaT;
	char motor[simsrvMOTOR_SIZE];
	do {
		simsrvDRAW_CALLBACK(s);
		glfwSwapBuffers(win);
		simsrvSendSensoryDataOnSocket(sockfd, s);
		simsrvReadMotorFromSocket(sockfd, motor);
		now = glfwGetTime();
		deltaT = now - t;
		t = now;
	} while (simsrvEVOLVE_CALLBACK(s, deltaT, motor));
	glfwDestroyWindow(win);
	close(sockfd);
	simsrvDESTROY_STATE_CALLBACK(s);
}



void *
simsrvHandleSocket(void *sockptr) {
	int sockfd = *((int *)sockptr);
	free(sockptr);
	simsrvRunServedSimulation(sockfd);
	return NULL;
}


void
simsrvListenAndServe(int port) {
	struct sockaddr_in srvAddr;
	int srvSock = socket(AF_INET, SOCK_STREAM, 0);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port = htons(port);
	if (bind(srvSock, (struct sockaddr*) &srvAddr, sizeof(srvAddr)) < 0) {
		simsrvError(0, "Binding error");
	}
	listen(srvSock, 5);
	while (1) {
		int *sockptr = malloc(sizeof(int));
		*sockptr = accept(srvSock, (struct sockaddr *)NULL, NULL);
		if (!sockptr) {
			simsrvError(0, "Could not allocate fd on heap!");
		}
		pthread_t newthread;
		if (pthread_create(&newthread, NULL,
				   simsrvHandleSocket, sockptr)) {
			simsrvError(0, "Failed to spawn thread for new world");
		}
	}
}







////////////////////////////////////////////////////////////////////////////////



void
simsrvRunSimulationForAgent(void *agent, simsrvAgentFunc agentFunc) {
	GLFWwindow *win = simsrvCreateWindow();
	void *s = simsrvINITIAL_STATE_CALLBACK();
	double t = glfwGetTime();
	double now, deltaT;
	char pixels[3 * simsrvSCREEN_WIDTH * simsrvSCREEN_HEIGHT];
	float sensors[simsrvNONVISUAL_SENSOR_SIZE];
	char motor[simsrvMOTOR_SIZE];
	do {
		simsrvDRAW_CALLBACK(s);
		glfwSwapBuffers(win);
		glReadPixels(0, 0, simsrvSCREEN_WIDTH, simsrvSCREEN_HEIGHT,
			     GL_RGB, GL_UNSIGNED_BYTE, pixels);
		simsrvSENSOR_CALLBACK(s, sensors);
		agentFunc(agent, pixels, sensors, motor);
		now = glfwGetTime();
		deltaT = now - t;
		t = now;
	} while (simsrvEVOLVE_CALLBACK(s, deltaT, motor));
	glfwDestroyWindow(win);
	simsrvDESTROY_STATE_CALLBACK(s);
}



