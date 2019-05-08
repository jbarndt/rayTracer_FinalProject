#include "ofApp.h"
#include "ofxGui.h"

#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Rectangle.h"
#include "GeometricObjects/Triangle.h"
#include "GeometricObjects/Checkerboard.h"
#include "GeometricObjects/Camera.h"
#include "GeometricObjects/Pinhole.h"
#include "Utilities/Vector3D.h"
#include "ViewPlane.h"

ofxGuiGroup sphereGroup;
ofxFloatSlider sphereSliderX, sphereSliderY, sphereSliderZ;
ofxGuiGroup trigGroup;
ofxFloatSlider trigSliderX, trigSliderY, trigSliderZ;
ofxGuiGroup cameraPosGroup;
ofxFloatSlider cameraPosSliderX, cameraPosSliderY, cameraPosSliderZ;

ofxGuiGroup cameraRotGroup;
ofxFloatSlider cameraRotSliderXZ;
ofxFloatSlider cameraRotSliderYZ;

ofxGuiGroup renderGroup;
//ofxIntSlider sampleSize;
//int currSampleSize;
ofxToggle unit_disk;
ofxFloatSlider vp_dist;
ofxToggle pointLight;
ofxFloatSlider lightPosSliderX, lightPosSliderY, lightPosSliderZ;

ofxPanel gui;
ofImage img;
ofColor BLACK = ofColor(0, 0, 0);
ofColor WHITE = ofColor(255, 255, 255);
ofColor RED = ofColor(255, 0, 0);
ofColor GREEN = ofColor(0, 255, 0);
ofColor OLIVE = ofColor(80, 80, 0);
ofColor ORANGE = ofColor(255, 165, 0);
ofColor TEAL = ofColor(0, 128, 128);

ViewPlane viewPlane;

Sphere sphereOlive, sphereLight, sphereReflect;
Rectangle_rt orangeRect, orangeRectTop, orangeRectBottom, orangeRectSideFace1, orangeRectSideFace2, orangeRectBack;
Triangle trig;

std::vector<Rectangle_rt> rects_vert;
std::vector<Rectangle_rt> rects_horz;

Checkerboard checkerboard;

Point3D start;
Point3D lookat;
Vector3D dir;
Point2D pp;
Point2D lp;
Pinhole pinhole;
double hitTime;
double minHitTime;
ShadeRec hitReturnData;
ofColor pixelColor;
float height;
float lens_radius;
float sample_x;
float sample_y;
double light;
Vector3D normal;
Vector3D lightSourceDir;
Vector3D lightPt;

const int screenSize = 800;

float rand_sampling_x[screenSize][screenSize];
float rand_sampling_y[screenSize][screenSize];

Point2D map_samples_to_unit_disk(Point2D sp);
void setPixelColor(Ray ray_);

//-------------------------------------------------------------
void ofApp::setup() {


  //Create a ViewPlane that is 500x500. The actuall window will be larger.
  viewPlane = ViewPlane(screenSize, screenSize);

  ofSetWindowShape(viewPlane.hres, viewPlane.vres);
  ofSetWindowPosition(30, 30);
  ofBackground(BLACK);

  //This allocates space for an offscreen buffer. 
  //The image will be rendered in this buffer pixel by pixel. Then, when all updates are done for the frame, the 
  //   buffer is sent to the display.
  //Notice that this large buffer is only created once. Each frame, it is reused.
  img.allocate(viewPlane.hres, viewPlane.vres, OF_IMAGE_COLOR);
  img.setColor(BLACK);

  gui.setup();
  // add a slider with <label>, <initial value>, <min>, <max>
  sphereGroup.setup("Move Sphere");
  sphereGroup.add(sphereSliderX.setup("x", 0, -25, 25));
  sphereGroup.add(sphereSliderY.setup("y", 0, -25, 25));
  sphereGroup.add(sphereSliderZ.setup("z", 0, -25, 25));
  gui.add(&sphereGroup);

  trigGroup.setup("Move Triangle");
  trigGroup.add(trigSliderX.setup("x", 0, -25, 25));
  trigGroup.add(trigSliderY.setup("y", 0, -25, 25));
  trigGroup.add(trigSliderZ.setup("z", 0, -25, 25));
  gui.add(&trigGroup);

  cameraPosGroup.setup("Camera position");
  cameraPosGroup.add(cameraPosSliderX.setup("x", 0, -25, 25));
  cameraPosGroup.add(cameraPosSliderY.setup("y", 0, -25, 25));
  cameraPosGroup.add(cameraPosSliderZ.setup("z", 0, -25, 25));
  gui.add(&cameraPosGroup);

  cameraRotGroup.setup("Camera rotation");
  cameraRotGroup.add(cameraRotSliderXZ.setup("left/right", 3.14, 0, 6.28));
  cameraRotGroup.add(cameraRotSliderYZ.setup("up/down", 3.14, 0, 6.28));
  gui.add(&cameraRotGroup);

  gui.add(vp_dist.setup("ViewPlane distance", 500, 0, 500));

  renderGroup.setup("Rendering");
  //sampleGroup.add(sampleSize.setup("# of samples", 1, 1, 25));
  renderGroup.add(unit_disk.setup("Use unit disk", false));
  renderGroup.add(pointLight.setup("Point Light", false));
  renderGroup.add(lightPosSliderX.setup("Pt Light x", 0, -25, 25));
  renderGroup.add(lightPosSliderY.setup("Pt Light y", 0, -25, 25));
  renderGroup.add(lightPosSliderZ.setup("Pt Light z", 0, -25, 25));
  gui.add(&renderGroup);

  sphereOlive = Sphere(100, 50, 100, 5);
  sphereLight = Sphere(0, 0, 0, 0.1);
  sphereReflect = Sphere(0, 20, -20, 5);

  Point3D rect_position = Point3D(6, 0,-20);
  orangeRect = Rectangle_rt(rect_position, Vector3D(4.0, 0, 0), Vector3D(0, 4.0, 0));
  orangeRectBottom = Rectangle_rt(rect_position, Vector3D(4.0, 0, 0), Vector3D(0,0,-4.0));
  orangeRectSideFace1 = Rectangle_rt(rect_position, Vector3D(0, 4.0, 0), Vector3D(0, 0, -4.0));

  rect_position = Point3D(10, 4, -24);
  orangeRectBack = Rectangle_rt(rect_position, Vector3D(-4.0, 0, 0), Vector3D(0, -4.0, 0));
  orangeRectTop = Rectangle_rt(rect_position, Vector3D(-4.0, 0, 0), Vector3D(0, 0, 4.0));
  orangeRectSideFace2 = Rectangle_rt(rect_position, Vector3D(0, -4.0, 0), Vector3D(0, 0, 4.0));

  checkerboard = Checkerboard();

  for (int i = 0; i < viewPlane.hres; i++) {
	  for (int j = 0; j < viewPlane.vres; j++) {

		  rand_sampling_x[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		  rand_sampling_y[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	  }
  }
}

//--------------------------------------------------------------
void ofApp::update() {

	/*if (currSampleSize != sampleSize) {
		currSampleSize = sampleSize;
	}*/
	int sampleSize = 1;

	height = 5.0;

		img.setColor(BLACK);

		if (vp_dist != pinhole.dist) {
			pinhole.set_view_distance(vp_dist);
		}

		//Point3D pt = convert_rad_xyz(1.0f, cameraRotSliderTh, cameraRotSliderPhi);

		//pinhole.set_lookat(pt.x, height + pt.y, pt.z);

		pinhole.set_eye(cameraPosSliderX, cameraPosSliderY + height, cameraPosSliderZ);

		start = pinhole.get_eye();//Point3D(0.0, height, 0.0);

		lookat = Point3D(start.x + sin(-cameraRotSliderXZ), start.y + sin(cameraRotSliderYZ), start.z + cos(-cameraRotSliderXZ) + cos(cameraRotSliderYZ));
		pinhole.set_lookat(lookat);
		pinhole.compute_uvw();

		dir = Vector3D(0.0, 0.0, 1.0);
		Ray ray_ = Ray(start, dir);

		hitTime = 0;
		lens_radius = 2.0;
		sample_x = 0.0;
		sample_y = 0.0;

		//		int sqrtSampleSize = (int)(sqrt((float)sampleSize));

		sphereOlive.set_center(sphereSliderX - 5, sphereSliderY + 5, sphereSliderZ - 20);
		sphereLight.set_center(lightPosSliderX, lightPosSliderY, lightPosSliderZ);
		trig.set_origin(trigSliderX, trigSliderY, trigSliderZ - 15);

		//Directional light
		lightSourceDir = Vector3D(4, 4, 4);//cos(PI / 4.0);
		lightSourceDir.normalize();

		//Point light
		lightPt = Vector3D(lightPosSliderX, lightPosSliderY, lightPosSliderZ);


		for (int col = 0; col < viewPlane.hres; col++) {
			for (int row = 0; row < viewPlane.vres; row++) {

				/*hitCount = 0;
				colorAvg = 0;
				r = 0;
				g = 0;
				b = 0;*/
				pixelColor = NULL;
				minHitTime = std::numeric_limits<double>::max();
				hitReturnData = ShadeRec();

				for (int n = 0; n < sampleSize; n++) {

					sample_x = rand_sampling_x[row][col];
					sample_y = rand_sampling_y[row][col];

					pp.x = (sample_x - 0.5) + viewPlane.pixelSize * (col - 0.5*(viewPlane.hres - 1));
					pp.y = (sample_y - 0.5) + height + (viewPlane.pixelSize * ((viewPlane.vres - row) - 0.5*(viewPlane.vres - 1)));
					
					if (unit_disk) pp = map_samples_to_unit_disk(pp);
					//lp = pp * lens_radius;
					//ray_.start = pinhole.get_lens_origin(lp.x, lp.y);
					ray_.dir = pinhole.get_direction(pp); 

					setPixelColor(ray_);
				}

				if (pixelColor != NULL) img.setColor(col, row, pixelColor);

			}
		}
		img.update();
}

void setPixelColor(Ray ray_) {

	hitTime = 0;
	minHitTime = std::numeric_limits<double>::max();

	if (sphereReflect.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);
			float ndotwo = normal * ray_.dir;
			Vector3D wi = ray_.dir - 2.0 * normal * ndotwo;
			Ray bouncedRay = Ray(hitReturnData.local_hit_point, wi);
			setPixelColor(bouncedRay);
		}
	}

	if (sphereLight.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			pixelColor = WHITE;
		}
	}

	if (sphereOlive.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 80, light * 80, 0);
			}
		}
	}

	//cout << r << ", " << g << ", " << b << "\n";

	if (trig.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;

			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(0, light * 128, light * 128);
			}
		}
	}

	if (orangeRect.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;

			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
			//cout << "hit" << "\n";
		}
	}
	if (orangeRectBottom.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
			//cout << "hit" << "\n"

		}
	}
	if (orangeRectSideFace1.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
			//cout << "hit" << "\n";
		}
	}
	if (orangeRectTop.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
		}
	}
	if (orangeRectSideFace2.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
		}
	}
	if (orangeRectBack.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			if (light < 0) {
				pixelColor = BLACK;
			}
			else {
				pixelColor = ofColor(light * 255, light * 165, 0);
			}
		}
	}

	if (checkerboard.hit(ray_, hitTime, hitReturnData)) {
		if (hitTime < minHitTime) {
			minHitTime = hitTime;
			normal = Vector3D(hitReturnData.normal.x, hitReturnData.normal.y, hitReturnData.normal.z);

			if (pointLight) {
				Point3D hitPt = hitReturnData.local_hit_point;
				Vector3D lightPtDir = lightPt - hitPt;
				lightPtDir.normalize();

				light = normal * lightPtDir;
			}
			else {
				//Directional light
				light = normal * lightSourceDir;
			}

			// return true if white, return false if black 
			if (checkerboard.getColor(hitReturnData.local_hit_point.x, hitReturnData.local_hit_point.y, hitReturnData.local_hit_point.z)) {
				if (light < 0) {
					pixelColor = BLACK;
				}
				else {
					pixelColor = ofColor(light * 255, light * 255, light * 255);
				}

			}
			// if black, add 0, aka: do nothing

			//cout << "hit at: " << hitReturnData.local_hit_point.x << ", " << hitReturnData.local_hit_point.y << ", " << hitReturnData.local_hit_point.z << "
			//cout << checkerboard.getColor(hitReturnData.hit_point.x, hitReturnData.hit_point.y, hitReturnData.hit_point.z) << "\n";
		}
	}
}


 Point3D convert_rad_xyz(float radius, float Th, float Phi) {
	 float xCor = radius * sin((double)Phi) * cos((double)Th);
	 float yCor = radius * sin((double)Phi) * sin((double)Th);
	 float zCor = radius * cos((double)Phi);
	 return(Point3D(xCor, yCor, zCor));
}

 Point2D map_samples_to_unit_disk(Point2D sp) {

	 int size = 5;
	 float r, phi;                                    // polar coordinates

		 // map sample point to [-1, 1]  [-1,1]

		 sp.x = 2.0 * sp.x - 1.0;
		 sp.y = 2.0 * sp.y - 1.0;

		 if (sp.x > -sp.y) {                        // sectors 1 and 2
			 if (sp.x > sp.y) {                   // sector 1 
				 r = sp.x;
				 phi = sp.y / sp.x;
			 }
			 else {                               // sector 2
				 r = sp.y;
				 phi = 2.0 - sp.x / sp.y;
			 }
		 }
		 else {                                     // sectors 3 and 4
			 if (sp.x < sp.y) {                   // sector 3
				 r = -sp.x;
				 phi = 4.0 + sp.y / sp.x;
			 }
			 else {                               // sector 4
				 r = -sp.y;
				 //at origin
				 if (sp.y != 0.0)               // avoid division by zero 
					 phi = 6.0 - sp.x / sp.y;
				 else
					 phi = 0.0;
			 }
		 }
		 phi *= PI / 4.0;

		 sp.x = r * cos(phi);
		 sp.y = r * sin(phi);

		 return sp;
 }


//--------------------------------------------------------------
void ofApp::draw() {
  img.draw(0, 0);
  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}