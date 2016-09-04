#include "Oscillator.hh"
#include "LimbMaster.hh"
#include <unistd.h>
#include <fstream>

class CPG{
private:
    std::vector<Oscillator> m_oscillators;
    FILE* out1;
    FILE* out2;
    FILE* out3;
    FILE* out4;
    FILE* out5;
    FILE* out6;

    LimbMaster* lm;
public:
    CPG();
    void load_config(char*);
    void run();
    double calculateLMAngle(double);
    double calculateSWAngle(double);
    double calculateHipAngle(double, double);
    double calculateKneeAngle(double);
    double calculateAnkleAngle(double, double);

    static constexpr double kALM = 30.0;
    static constexpr double kASW = 4.0;
};
