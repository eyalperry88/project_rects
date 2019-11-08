#pragma once

#include "ofMain.h"

#define PROJECTION_SCREEN_OFFSET 1920

#define PROJECTION_SCREEN_WIDTH 1280
#define PROJECTION_SCREEN_HEIGHT 800

#define MAX_RECTS 4

typedef struct {

	float 	x;
	float 	y;
	bool 	bBeingDragged;
	bool 	bOver;
	float 	radius;

} draggableVertex;

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    draggableVertex vertices[MAX_RECTS * 4];
    int numVertices;
    int lastVertex[MAX_RECTS];

    float hue[MAX_RECTS];
    float saturation[MAX_RECTS];
    float brightness[MAX_RECTS];

    int activeRect;
    int activeMode;
};
