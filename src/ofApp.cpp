#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

  ofSetWindowPosition(PROJECTION_SCREEN_OFFSET, 0); // second screen - projector

  ofHideCursor();

	ofBackground(0,0,0);
  ofEnableSmoothing();

  ofSetRectMode(OF_RECTMODE_CORNER);

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

  // init rects
  numVertices = 0;
  for (int i = 0; i < MAX_RECTS * 4; i++){
    vertices[i].x = 0;
    vertices[i].y = 0;
    vertices[i].bOver = false;
    vertices[i].bBeingDragged 	= false;
    vertices[i].radius = 8;
  }
  // load config, if exists
  ofBuffer buffer = ofBufferFromFile("config.txt");
  int idx = 0;
  for (auto line : buffer.getLines()){
      if (idx % 2 == 0) {
        vertices[idx / 2].x = std::stoi(line);
        ofLogNotice() << idx / 2 << " x " << std::stoi(line);
      } else {
        vertices[idx / 2].y = std::stoi(line);
        ofLogNotice() << idx / 2 << " y " << std::stoi(line);
        numVertices++;
      }
      idx++;
      if (idx >= MAX_RECTS * 8) {
        break;
      }
  }

  activeRect = 0;
  activeMode = 0;
  for (int i = 0; i < MAX_RECTS; i++) {
    hue[i] = 0;
    saturation[i] = 200;
    brightness[i] = 200;
    lastVertex[i] = i * 4;
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  for (int j = 0; j < MAX_RECTS; j++) {
    ofColor shapeColor = ofColor::fromHsb(hue[j], saturation[j], brightness[j]);
    ofSetColor( shapeColor );
    ofFill();
    ofBeginShape();
    for (int i = j*4; i < (j+1)*4; i++){
      ofVertex(vertices[i].x, vertices[i].y);
    }
    ofEndShape(true);
  }

  ofColor cursorColor(255, 0, 0);
  ofSetColor( cursorColor );
  ofFill();
  ofDrawCircle( mouseX, mouseY, 8 );

  for (int i = 0; i < numVertices; i++){
		if (vertices[i].bOver) {
      ofColor cursorHiglightColor(0, 255, 0);
      ofSetColor( cursorHiglightColor );
      ofFill();
		  ofDrawCircle(mouseX, mouseY, 12);
    }
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
  float *value;
  if (activeMode == 0) {
    value = &(hue[activeRect]);
  } else if (activeMode == 1) {
    value = &(saturation[activeRect]);
  } else if (activeMode == 2){
    value = &(brightness[activeRect]);
  } else {
    return;
  }
  if (key == OF_KEY_UP) {
    *value += 1.0;
    if (*value > 255) {
      if (activeMode == 0) {
        // for hue, loop over
        *value = 1;
      } else {
        *value = 255;
      }
    }
  } else if (key == OF_KEY_DOWN) {
    *value -= 1.0;
    if (*value < 0) {
      if (activeMode == 0) {
        // for hue, loop over
        *value = 254;
      } else {
        *value = 0;
      }
    }
  }
  ofLogNotice() << "New value: " << *value;
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
  if (key == '1') {
    activeRect = 1;
    ofLogNotice() << "Active Polygon: " << activeRect;
  } else if (key == '2') {
    activeRect = 2;
    ofLogNotice() << "Active Polygon: " << activeRect;
  } else if (key == '3') {
    activeRect = 3;
    ofLogNotice() << "Active Polygon: " << activeRect;
  } else if (key == '0') {
    activeRect = 0;
    ofLogNotice() << "Active Polygon: " << activeRect;
  } else if (key == 'h') {
    activeMode = 0;
    ofLogNotice() << "Active Mode: HUE";
  } else if (key == 's') {
    activeMode = 1;
    ofLogNotice() << "Active Mode: SATURATION";
  } else if (key == 'v' || key == 'b') {
    activeMode = 2;
    ofLogNotice() << "Active Mode: BRIGHTNESS";
  } else if (key == OF_KEY_RETURN) {
    activeMode = 3;
    ofLogNotice() << "Active Mode: ADD/CHANGE VERTEX";
  }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  for (int i = 0; i < numVertices; i++){
		float diffx = x - vertices[i].x;
		float diffy = y - vertices[i].y;
		float dist = sqrt(diffx*diffx + diffy*diffy);
		if (dist < vertices[i].radius){
			vertices[i].bOver = true;
		} else {
			vertices[i].bOver = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  for (int i = 0; i < numVertices; i++){
		if (vertices[i].bBeingDragged == true){
			vertices[i].x = x;
			vertices[i].y = y;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  for (int i = 0; i < numVertices; i++){
    vertices[i].bBeingDragged = false;
  }

  if (activeMode == 3) {
    vertices[lastVertex[activeRect]].x = x;
    vertices[lastVertex[activeRect]].y = y;

    lastVertex[activeRect]++;
    numVertices++;
    if (lastVertex[activeRect] >= (activeRect + 1) * 4) lastVertex[activeRect] = activeRect * 4;
    if (numVertices > MAX_RECTS * 4) numVertices = MAX_RECTS * 4;
  } else {
    for (int i = 0; i < numVertices; i++){
  		float diffx = x - vertices[i].x;
  		float diffy = y - vertices[i].y;
  		float dist = sqrt(diffx*diffx + diffy*diffy);
  		if (dist < vertices[i].radius){
  			vertices[i].bBeingDragged = true;
  		}
  	}
  }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  bool updateConfig = false;
  for (int i = 0; i < 4; i++){
		if (vertices[i].bBeingDragged == true){
			updateConfig = true;
		}
	}
  if (updateConfig) {
    ofFile configFile;
    configFile.open("config.txt",ofFile::WriteOnly);
    for (int i = 0; i < numVertices; i++){
  		configFile << vertices[i].x << "\n";
      configFile << vertices[i].y << "\n";
  	}
  }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
