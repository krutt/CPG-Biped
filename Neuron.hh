#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>


class Neuron{
private:

public:
    Neuron(){ }
    double du [0x1F6*2];
    double u [0x1F6*2];
    double y [0x1F6*2];
    double dv [0x1F6*2];
    double v [0x1F6*2];
};
