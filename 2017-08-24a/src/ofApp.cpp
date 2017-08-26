#include "ofApp.h"
/* Begin description
{
    Back to sketching!
}
End description */

/* Snippet begin */
void ofApp::setup(){
    ofSetWindowShape(640, 480);

    vid.setup("out/2017-08-24a", 1200);
    vid.isolateDrawingStyle();
    vid.useTimeFrom(&avSync);
    vid.enableRenderMode(60);
    aud.setup(false);
    audioManager = aud.getAudioUnitManager();
    ofSleepMillis(3000);
    visible = true;
    noteOn = false;

    position.x = ofGetWidth() * 0.5;
    position.y = ofGetHeight() * 0.5;

    synth.setup("Synth 1", 'aumu', 'ncut', 'TOGU');
    audioManager->createChain(&chain).link(&synth).toMixer();
    synth.set(TALNoiseMaker_chorus1enable, 1);
    synth.set(TALNoiseMaker_chorus2enable, 1);

    ofAddListener(audioManager->bpm.beatEvent, this, &ofApp::beat);
    audioManager->bpm.start();
}

void ofApp::beat(void){
    avSync.setupOnce();
    
    if(noteOn){
        aud.sendMidi("C5 OFF", &chain);
        avSync.logCommand("off");
    }else{
        cutoff = ofRandom(0.3, 1);
        tune = ofRandom(1) < 0.5 ? 0.2 : 0.8;
        synth.set(TALNoiseMaker_cutoff, cutoff);
        synth.set(TALNoiseMaker_osc1tune, tune);
        aud.sendMidi("C5 ON", &chain);

        avSync.logCommand("on", cutoff, tune);
    }
    noteOn = !noteOn;
}

void ofApp::update(){
    for(auto& command : avSync.getCommandsForCurrentFrame()){
        if(command.is("on")){
            float _cutoff = command.args[0];
            float _tune = command.args[1];
                                  
            visible = true;
            size.x = ofMap(_cutoff, 0, 1, 0, ofGetWidth());
            size.y = ofMap(_tune, 0, 1, 0, ofGetHeight());
        }else if(command.is("off")){
            visible = false;
        }
    }
}

void ofApp::draw(){
    vid.begin();
    {
        ofBackground(ofColor::black);
        ofSetRectMode(OF_RECTMODE_CENTER);
        if(visible){
            for(int i = 0; i < 200; i+=12){
                ofSetColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255-(i*15)));
                ofDrawRectangle(position, size.x - i, size.y - i);
            }
        }
    }
    vid.endCaptureDraw();
}
/* Snippet end */

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    
}

void ofApp::mouseMoved(int x, int y){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
