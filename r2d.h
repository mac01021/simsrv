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
r2dError(int error, const char *description) {
	fputs(description, stderr);
	glfwTerminate();
	exit(EXIT_FAILURE);
}
////////////////////////////////////////////////////////////////////////////


 /////////////////////// THE GAME/TASK IS IMPLEMENTED IN 4 FUNCTIONS ///////
///////////////////////   (ALL PROVIDED TO THE INIT METHOD ////////////////
typedef void *(*r2dStateFactory)();
typedef void (*r2dDrawFunc)(void *state);
typedef void (*r2dSensorFunc)(void *state, float *sensors);
typedef bool (*r2dStateUpdateFunc)(void *state, double timeElapsed, char *motor);
typedef void (*r2dStateDestructor)(void *);
/////////////////////////////////////////////////////////////////////////
typedef void (*r2dAgentFunc)(void *agent, char *pixels, float *sensors, char *motor);
////////////////////////////////////////////////////////////////////////

static bool r2dINITTED = false;
static r2dStateFactory r2dINITIAL_STATE_CALLBACK;
static r2dDrawFunc r2dDRAW_CALLBACK;
static r2dSensorFunc r2dSENSOR_CALLBACK;
static r2dStateUpdateFunc r2dEVOLVE_CALLBACK;
static r2dStateDestructor r2dDESTROY_STATE_CALLBACK;
static int32_t r2dSCREEN_WIDTH;
static int32_t r2dSCREEN_HEIGHT;
static int32_t r2dNONVISUAL_SENSOR_SIZE;
static int32_t r2dMOTOR_SIZE;


////////////INIT INITIALIZES GLFW AND STORES THE CALLBACKS THAT CONSTITUTE //
///////////                 THE TASK     ///////////////////////////////////
void
r2dInit(r2dStateFactory stateFactory,
	r2dDrawFunc drawFunc, int32_t screenWidth, int32_t screenHeight,
	r2dSensorFunc sensorFunc, int32_t nvSize,
	r2dStateUpdateFunc updateFunc, int32_t motorSize,
	r2dStateDestructor stateDestructor) {
	if (!r2dINITTED) {
		r2dINITTED = true;
		r2dINITIAL_STATE_CALLBACK = stateFactory;
		r2dDRAW_CALLBACK = drawFunc;
		r2dSENSOR_CALLBACK = sensorFunc;
		r2dEVOLVE_CALLBACK = updateFunc;
		r2dDESTROY_STATE_CALLBACK = stateDestructor;
		r2dSCREEN_HEIGHT = screenHeight;
		r2dSCREEN_WIDTH = screenWidth;
		r2dNONVISUAL_SENSOR_SIZE = nvSize;
		r2dMOTOR_SIZE = motorSize;
		if (!glfwInit()) {
			r2dError(0, "Could not initialize GLFW");
			exit(EXIT_FAILURE);
		}
	}
}

void
r2dTerminate() {
	if (r2dINITTED) {
		glfwTerminate();
		r2dINITTED = false;
	}
}

///////////////////////////////////////////////////////////////////////////


GLFWwindow *
r2dCreateWindow() {
	GLFWwindow *win = glfwCreateWindow(r2dSCREEN_WIDTH,
					   r2dSCREEN_HEIGHT,
					   "r2dSimulation",
					   NULL,
					   NULL);
	if (!win) {
		r2dError(0, "Could not create window");
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	return win;
}





//////////////////////////////////////////////////////////////////////////


void
r2dSendSessionPreludeOnSocket(int sockfd) {
	int32_t inNetworkOrder[4] = { htonl(r2dSCREEN_WIDTH),
				      htonl(r2dSCREEN_HEIGHT),
				      htonl(r2dNONVISUAL_SENSOR_SIZE),
				      htonl(r2dMOTOR_SIZE) };
	int nbBytes = 4 * sizeof(int32_t);
	if (send(sockfd, &inNetworkOrder, nbBytes, 0) != nbBytes) {
		r2dError(0, "Trouble sending session prelude on socket");
	}
}


void
r2dSendSensoryDataOnSocket(int sockfd, void *state) {
	char buf[3 * r2dSCREEN_WIDTH * r2dSCREEN_HEIGHT];
	buf[3] = 4;
	//TODO
}

void
r2dReadMotorFromSocket(int sockfd, char *motor) {
	//TODO
}

void
r2dRunServedSimulation(int sockfd) {
	r2dSendSessionPreludeOnSocket(sockfd);
	GLFWwindow *win = r2dCreateWindow();
	void *s = r2dINITIAL_STATE_CALLBACK();
	double t = glfwGetTime();
	double now, deltaT;
	char motor[r2dMOTOR_SIZE];
	do {
		r2dDRAW_CALLBACK(s);
		glfwSwapBuffers(win);
		r2dSendSensoryDataOnSocket(sockfd, s);
		r2dReadMotorFromSocket(sockfd, motor);
		now = glfwGetTime();
		deltaT = now - t;
		t = now;
	} while (r2dEVOLVE_CALLBACK(s, deltaT, motor));
	glfwDestroyWindow(win);
	close(sockfd);
	r2dDESTROY_STATE_CALLBACK(s);
}



void *
r2dHandleSocket(void *sockptr) {
	int sockfd = *((int *)sockptr);
	free(sockptr);
	r2dRunServedSimulation(sockfd);
	return NULL;
}


void
r2dListenAndServe(int port) {
	struct sockaddr_in srvAddr;
	int srvSock = socket(AF_INET, SOCK_STREAM, 0);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port = htons(port);
	if (bind(srvSock, (struct sockaddr*) &srvAddr, sizeof(srvAddr)) < 0) {
		r2dError(0, "Binding error");
	}
	listen(srvSock, 5);
	while (1) {
		int *sockptr = malloc(sizeof(int));
		*sockptr = accept(srvSock, (struct sockaddr *)NULL, NULL);
		if (!sockptr) {
			r2dError(0, "Could not allocate fd on heap!");
		}
		pthread_t newthread;
		if (pthread_create(&newthread, NULL,
				   r2dHandleSocket, sockptr)) {
			r2dError(0, "Failed to spawn thread for new world");
		}
	}
}







////////////////////////////////////////////////////////////////////////////////



void
r2dRunSimulationForAgent(void *agent, r2dAgentFunc agentFunc) {
	GLFWwindow *win = r2dCreateWindow();
	void *s = r2dINITIAL_STATE_CALLBACK();
	double t = glfwGetTime();
	double now, deltaT;
	char pixels[3 * r2dSCREEN_WIDTH * r2dSCREEN_HEIGHT];
	float sensors[r2dNONVISUAL_SENSOR_SIZE];
	char motor[r2dMOTOR_SIZE];
	do {
		r2dDRAW_CALLBACK(s);
		glfwSwapBuffers(win);
		glReadPixels(0, 0, r2dSCREEN_WIDTH, r2dSCREEN_HEIGHT,
			     GL_RGB, GL_UNSIGNED_BYTE, pixels);
		r2dSENSOR_CALLBACK(s, sensors);
		agentFunc(agent, pixels, sensors, motor);
		now = glfwGetTime();
		deltaT = now - t;
		t = now;
	} while (r2dEVOLVE_CALLBACK(s, deltaT, motor));
	glfwDestroyWindow(win);
	r2dDESTROY_STATE_CALLBACK(s);
}



