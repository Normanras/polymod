#include "Arduino.h"
#include "VCF.h"
#include "Socket.h"

VCF::VCF() {
  float freq = 1300;
  float Q = 0.9;
  _filter.frequency(freq);
  _filter.resonance(Q);
  _filter.octaveControl(8);

  _patchCable1 = new AudioConnection(_cvMixer,0,_filter,1);
  
  sockets[6].setInput(_filter, 0); // input
  sockets[4].setInput(_cvMixer, 0); // freq CV
  sockets[2].setInput(_cvMixer, 1); // freq CV (attenuated)
  sockets[1].setOutput(_filter, 0); // low pass
  sockets[7].setOutput(_filter, 1); // band pass
  sockets[0].setOutput(_filter, 2); // high pass
}

void VCF::update() {
  float freqVal = controls[4].getSmoothedValue();
  _filter.frequency(freqVal*freqVal*4000);
  _filter.resonance(controls[6].getSmoothedValue()*4.3+0.7);
  _cvMixer.gain(1,controls[7].getSmoothedValue());
}

