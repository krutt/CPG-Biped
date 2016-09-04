cpg-biped: main.cc CPG.cc Oscillator.cc Neuron.cc driver/SerialController.cc LimbMaster.cc
	g++ -o magic main.cc CPG.cc Oscillator.cc Neuron.cc driver/SerialController.cc LimbMaster.cc
