#include "Oscillator.hh"

Oscillator::Oscillator(unsigned id){
    //this(id, std::string("undefined"), std::string("undefined"));
}

Oscillator::Oscillator(unsigned id, std::string name, std::string type){
    this->m_id = id;
    this->m_name = name;
    this->m_type = type;

    std::cout << "Initialized oscillator with values " << id << " " << name << " " << type << std::endl;

    char p1[12];
    char p2[12];
    char p3[12];
    char p4[12];
    char p5[12];

    sprintf(p1, "data/n1_%i.dat", m_id);
    sprintf(p2, "data/n2_%i.dat", m_id);
    sprintf(p3, "data/o_%i.dat", m_id); //oscillator
    sprintf(p4, "data/phase%i.dat", m_id); //joint angles

    out1 = fopen(p1, "w");
    out2 = fopen(p2, "w");
    out3 = fopen(p3, "w");
    out4 = fopen(p4, "w");

    ini();
}

Oscillator::~Oscillator(){
    //fclose(out1);
    //fclose(out2);
}

void Oscillator::ini(){
    cnt = 0;

    n1.u[0] = (m_id % 2) ? 0 : 1;
    n1.v[0] = (m_id % 2) ? 0 : 1;
    n1.y[0] = 0;
    fb1 = 0; //pass the output of the homologous-neuron of the brother oscillator

    n2.u[0] = (m_id % 2) ? 1 : 0;
    n2.v[0] = (m_id % 2) ? 1 : 0;
    n2.y[0] = 0;

    fb2 = 0; //pass the output of the homologous-neuron of the brother oscillator
}

void Oscillator::calculate(){

    n1.du[cnt] = (-n1.u[cnt] - (kWeight * n2.y[cnt]) - (kB * n1.v[cnt]) +  (m_id <= 2 ? kCLM : kCSW) - kA * fb1) / kT1;
    n1.u[cnt + 1] = n1.u[cnt] + (kStep * n1.du[cnt]);
    n1.y[cnt + 1] = n1.u[cnt + 1] > 0 ? n1.u[cnt + 1] : 0;
    n1.dv[cnt] = (-n1.v[cnt] + n1.y[cnt + 1]) / kT2;
    n1.v[cnt + 1] = n1.v[cnt] + (kStep * n1.dv[cnt]);

    n2.du[cnt] = (-n2.u[cnt] - (kWeight * n1.y[cnt]) - (kB * n2.v[cnt]) + (m_id <= 2 ? kCLM : kCSW) - kA * fb2)/ kT1;
    n2.u[cnt + 1] = n2.u[cnt] + (kStep * n2.du[cnt]);
    n2.y[cnt + 1] = n2.u[cnt + 1] > 0 ? n2.u[cnt + 1] : 0;
    n2.dv[cnt] = (-n2.v[cnt] + n2.y[cnt + 1]) / kT2;
    n2.v[cnt + 1] = n2.v[cnt] + (kStep * n2.dv[cnt]);

    fprintf(out1, "%i %f\n", cnt, n1.y[cnt]);
    fprintf(out2, "%i %f\n", cnt, n2.y[cnt]);
    fprintf(out3, "%i %f\n", cnt, n1.y[cnt] - n2.y[cnt]);

    fprintf(out4, "%i %i\n", cnt, (n1.y[cnt] > n2.y[cnt] ? 1 : 0));
    //fprintf(out4, "%i %f\n", cnt, (m_id <= 2) ? this->calculateLMAngle(n1.y[cnt] - n2.y[cnt]) : this->calculateSWAngle(n1.y[cnt] - n2.y[cnt]));

    std::cout << " du " << n1.du[cnt] << " u " << n1.u[cnt] << " y1: " << n1.y[cnt] << " y2: " << n2.y[cnt] << std::endl;
    cnt++;

}
