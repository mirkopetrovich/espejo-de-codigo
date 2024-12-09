#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   //mapa.load("Halftone screens/40x30x17.charliestrip.png");
   mapa.load("Halftone screens/40x40x11.halftonestrip.png");
   // mapa.load("Halftone screens/40x40x32.mezzo1.png");
    //mapa.load("Halftone screens/40x40x32.glassgrad.png");
   // mapa.load("st3.png");
    
   
    
    mapa.setAnchorPoint(0.5,0.5);
    ofBackground(0,0,0);
    camWidth = 1920;
    camHeight = 1080;
    vidGrabber.setDeviceID(1);
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    ofTrueTypeFont::setGlobalDpi(72);
    font.load("MiradorVF.ttf", 20,true,true);
    
    set_1 =  string(" 10");
    set_2 =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
    set_3 =  string("01 ");
    set_4 =  string(" x.");
    set_5 =  string("12345678901234567890123456789012");
    set_6 =  string("12345678901234567");
    set_7 =  string("😎");
    
     
    asciiCharacters = set_5;
    
    ofEnableAlphaBlending();
    
    gui.setup();
    gui.add(paso_x.set("H", 39, 10, 300));
    gui.add(paso_y.set("V", 28, 10, 300));
    gui.add(ancho.set("ancho", camWidth, 10, camWidth));
    gui.add(alto.set("alto", camHeight, 10, camHeight));
    gui.add(ancho_.set("ancho_",0, -1080, 1080));
    gui.add(alto_.set("alto_", 0, -1920, 1920));
    gui.add(size.set("size", 20, 5, 40));
    gui.add(gap.set("gap", 0, 0, 500));
    gui.add(gapp.set("gapp", 0, 0, 500));
    gui.add(zoom.set("zoom", 2., 0., 2.));
    gui.add(curva.set("curva", 2.5, 0., 20.));
    gui.add(ss1.set("ss1", 0, 0,  1920));
    gui.add(ss2.set("ss2", 1, 1,  17));
    gui.add(ss3.set("ss3", 0, 0,  1920));
    gui.add(ss4.set("ss4", 0, 0,  1920));
    gui.add(ss5.set("ss5", 0, 0,  1920));
    gui.add(ss6.set("ss6", 0, 0,  1920));
    gui.add(ss7.set("ss7", 0, 0,  1920));
    gui.add(ss8.set("ss8", 0, 0,  1920));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // change background video alpha value based on the cursor's x-position
    //float zoom = ofMap(mouseX, 0, ofGetWidth(), 0, 5.);
    
    // set a white fill color with the alpha generated above
    //ofSetColor(255,255,255,80);

    // draw the raw video frame with the alpha value generated above
    ofPushMatrix();
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    ofSetHexColor(0xffffff);
    ofNoFill();

    
    
    
   /* for (int i = alto_; i < 1920; i+= paso_y){
        for (int j = ancho_; j < 1080; j+= paso_x){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            
            // calculate the index of the character from our asciiCharacters array
            int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            
            // draw the character at the correct location
            ofPushMatrix();
            if (acolor==1) {
                color=(pixelsRef.getColor(i,j));
                
                //ITU BT.709 : Y = 0.2126 R + 0.7152 G + 0.0722 B
                int gris = 0.2126*color.r+0.7152*color.g*0.0722*color.b;
                
                //ITU BT.601 : Y = 0.299 R + 0.587 G + 0.114 B
                //int gris = 0.299*color.r+0.587*color.g*0.114*color.b;
                if (gris>255) gris = 255;
            ofSetColor(gris);
        }
            
                if (acolor==2) {
                    ofSetColor(pixelsRef.getColor(i,j));
                }
            
            if (acolor==0) {
               // font.drawString(ofToString(asciiCharacters[character]), j, i);
                ofDrawRectangle((j-ancho_)*(gap/100.),((i-alto_)*(gap/100.)), 15, 15);
            }
            ofPopMatrix();
        }
    } */
    
    
    for (int i = 0; i < 1920; i+= paso_y){
        for (int j = 0; j <1080; j+= paso_x){
            float lightness = pixelsRef.getColor(i,j).getLightness();
            int character = powf( ofMap(lightness, 0, 255, 0, 1), curva) * asciiCharacters.size();
           // int character = powf( ofMap(lightness, 0, 255, 0, 1), curva) * ofUTF8Length(asciiCharacters);
            color=(pixelsRef.getColor(i,j));
            
            if (bn) {
                if (blanco) ofSetColor(255);
                else ofSetColor(lightness);
                    }
            else ofSetColor(color);
            //font.drawString(ofToString(asciiCharacters[character]), (1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto);
            //font.drawString(ofToString(character), (1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto);
            
            
           //mapa.drawSubsection((1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto_,ss3,ss4, ss6, character*ss5);
           // mapa.drawSubsection( (1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto_,zoom*ss3,zoom*ss3,character*ss5,ss6,ss7*2.,ss7*2.);
            mapa.drawSubsection((1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto_,paso_x*zoom,paso_y*zoom,character*40,0,40,40);
            
            
           // font.drawString( ofUTF8Substring(asciiCharacters, character, 1), (1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto);
            //font.drawString(ofToString(asciiCharacters[character]), (1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto);
            ;
            //ofDrawRectangle((1080-(j*zoom))+ancho_,(1920-(i*zoom))+alto_, gapp, gapp);
        }
    }
    
    ofPopMatrix();
    ofSetColor(255);
    
    
    //mapa.drawSubsection(ss1,ss2,ss3,ss4,ss5,ss6,ss7,ss8);
    
    if (!show_gui)  {
        gui.draw();
        vidGrabber.draw(384,0,384,216);
        mapa.draw(200,300);
    }
    // gui.setPosition(330,0);

    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    if (key == 'l'){
        bn=!bn;
    }
    
    if (key == 'k'){
        blanco=!blanco;
    }
    
    if (key == 'a'){
        acolor = 0;
    }
    
    if (key == 's'){
        acolor = 1;
    }
    
    if (key == 'd'){
        acolor = 2;
    }
    
    if (key == '1') {
        asciiCharacters = set_1;
    }
    
    if (key == '2'){
        asciiCharacters = set_2;
    }
    
    if (key == '3'){
        asciiCharacters = set_3;
    }
    
    if (key == '4'){
        asciiCharacters = set_4;
    }
    
    if (key == '5'){
        asciiCharacters = set_5;
    }
    
    if (key == '6'){
        asciiCharacters = set_6;
    }
    
    if (key == '7'){
        asciiCharacters = set_7;
    }
    
    if (key == 'q'){
        font.load("verdana.ttf", size,true,true);
    }
    
    if (key == 'w'){
        font.load("MiradorVF.ttf", size,true,true);
    }
    
    if (key == 'e'){
        ofTrueTypeFontSettings font_settings("Apple Color Emoji.ttc",30);
        // ofTrueTypeFontSettings font_settings("NotoColorEmoji-Regular.ttf",20);
         
         font_settings.antialiased = true;
         font_settings.addRanges(ofAlphabet::Emoji);
         this->font.load(font_settings);
    }
    
    if (key == 'r'){
        font.load("Courier New Bold.ttf", size,true,true);
    }
    
    if (key == 'g'){
        show_gui=!show_gui;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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


