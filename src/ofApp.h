#pragma once

#include "ofMain.h"
#include "Utilities/Point2D.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		//Point2D map_samples_to_unit_disk(Point2D sp);
		//Vector3D ofApp::get_direction(const Point2D& p) const;
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
