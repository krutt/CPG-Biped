#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
#include "Neuron.hh"
#include <stdio.h>

using namespace std;
class Oscillator{
private:
    std::string m_name;
    std::string m_type;
    unsigned m_id;
    Neuron n1;
    Neuron n2;

    FILE* out1;
    FILE* out2;
    FILE* out3;
    FILE* out4;
    //FILE* out5;
public:
    inline std::string get_name(){ return m_name; }
    inline unsigned get_id() { return m_id; }
    inline Neuron& get_n1(){ return n1; }
    inline Neuron& get_n2(){ return n2; }

    inline void set_name(std::string s){ m_name = s; }
    inline void set_id(unsigned i){ m_id = i; }
    inline void set_n1(Neuron n){ n1 = n; }
    inline void set_n2(Neuron n){ n2 = n; }

    static constexpr double kStep = 0.1; //smoothness
    static constexpr double kWeight = 1.5;
    static constexpr double kT1 = 1.2;
    static constexpr double kT2 = 5.2;
    static constexpr double kCLM = 1.4;
    static constexpr double kCSW = 2;
    static constexpr double kB = 2.5;
    static constexpr double kA = 0.5;

    double fb1;
    double fb2;

    long cnt;
    Oscillator(unsigned);
    Oscillator(unsigned, std::string, std::string);
    ~Oscillator();

    void ini();

    void calculate();

};
