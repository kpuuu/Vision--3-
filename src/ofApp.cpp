#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 320;
    height = 240;
    
    frame = 0;// init frame value to zero
    bSaveSequence = false;// this one will allow you to save just when you want to and not all the time that the app is running.

    angle = 0;
    
    kinect.init(true);
    kinect.open();
    kinect.setCameraTiltAngle(angle);
    
   // colorImg.allocate(kinect.width,kinect.height); NO necesitamos color :o!
    grayImage.allocate(kinect.width,kinect.height);
    

}


//--------------------------------------------------------------
void ofApp::update()
{
    kinect.update();
    
    if (kinect.isFrameNew())
    {
       // colorImg.setFromPixels(kinect.getPixels(), 640, 480);
        grayImage.setFromPixels(kinect.getDepthPixels(), 640, 480);
    }
   
    
    if(bSaveSequence){
        
        ofImage img;
        ofxCvColorImage tmp;
        tmp = grayImage;
        img.setFromPixels(tmp.getPixelsRef());
        bSaveSequence=false;
        img.saveImage(ofToString(frame)+".png"); // change the ".jpg" for ".png" if you want a png sequence.
        frame++;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
  //  colorImg.draw(20, 20, width, height);
    grayImage.draw(20, 20, width, height);
    
    //record.newFrame(kinect.getPixels(), kinect.getRawDepthPixels()); // ???
    //record.init("images/depth.mov"); /// ???
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
    switch (key)
    {
        case OF_KEY_UP:
            angle++;
            if (angle > 30)
                angle = 30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if (angle < -30)
                angle = -30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case 'f':
            ofToggleFullscreen();
            
        case 's': // this is the space bar. you can change it to any key you want to.
            bSaveSequence =true;
    }  
}

//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
}

