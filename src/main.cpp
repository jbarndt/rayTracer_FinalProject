#include "ofMain.h"
#include "ofApp.h"

//========================================================================
// NOTES for CS491
// Joel made the following general changes from the books code:
// 1) Replaced wxwidets with OpenFrameworks.
//
// 2) Many rendering apps use floats over doubles because the difference
//   is too small to see and floats are faster. The textbook code mixes
//   floats and doubles. This is bad as you get the worst of both worlds 
//   (slow and inaccurate), confusing to the developer, and warnnings from
//   the compiler. Excepting the RGB values, Joel changed all floats to 
//   double. In the case of the RGB values, explicit casts or math functions
//   for floats (absf, not abs, powf, not pow) were used.
//
// 3) In this Bere Bones ray traser, I commented out all references to 
//    Material as it is not used.
//
// 4) changed some of the too short variable names: ie, 's' to 'pixelSize'.
//
// 5) Added constructors with arguments to set starting values.
//
// 6) Removed some of the levels of abstraction. For example, replaced the 
//    SingleSphere object (which just creates a single Sphear object) with 
//    simply making a single Sphere in ofApp.cpp.
//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
