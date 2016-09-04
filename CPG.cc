#include "CPG.hh"
#include "Constants.hh"

CPG::CPG(){
    this->load_config("conf");
    lm = new LimbMaster();
}

void CPG::load_config(char* path){
    //id name type
    std::ifstream input(path);

    unsigned id;
    std::string name;
    std::string type;

    while(input >> id){
        input >> name >> type;
        this->m_oscillators.push_back(Oscillator(id, name, type));
    }
}

void CPG::run(){
    int i = 0;
    char p1[12];
    char p2[12];
    char p3[12];
    char p4[12];
    char p5[12];
    char p6[12];

    sprintf(p1, "data/lknee.dat");
    sprintf(p2, "data/rknee.dat");
    sprintf(p3, "data/lhip.dat");
    sprintf(p4, "data/rhip.dat");
    sprintf(p5, "data/lankle.dat");
    sprintf(p6, "data/rankle.dat");

    out1 = fopen(p1, "w");
    out2 = fopen(p2, "w");
    out3 = fopen(p3, "w");
    out4 = fopen(p4, "w");
    out5 = fopen(p5, "w");
    out6 = fopen(p6, "w");

    while(i < 500){
        for(std::vector<Oscillator>::iterator it = m_oscillators.begin(); it != m_oscillators.end(); ++it){
            std::cout<< "[" << i << "][" << it->get_id() <<"]" << "[" << it->fb1 << "," << it->fb2 << "]";
            it->calculate();

            if(it->get_id() % 2){ //synchronize counter-oscillators
                (it+1)->fb1 = it->get_n1().y[it->cnt - 1];
                (it+1)->fb2 = it->get_n2().y[it->cnt - 1];

            }else{
                (it-1)->fb1 = it->get_n1().y[it->cnt - 1];
                (it-1)->fb2 = it->get_n2().y[it->cnt - 1];
            }

            if(it->get_id() == 1){
                //calculate left knee
                double angle = this->calculateKneeAngle(it->get_n1().y[it->cnt - 1] - it->get_n2().y[it->cnt - 1]);
                fprintf(out1, "%i %f\n", it->cnt - 1, angle);
                lm->move_knee_p(2, angle);
            }else if(it->get_id() == 2){
                //calculate right knee
                double angle = this->calculateKneeAngle(it->get_n1().y[it->cnt - 1] - it->get_n2().y[it->cnt - 1]);
                fprintf(out2, "%i %f\n", it->cnt - 1, angle);
                lm->move_knee_p(1, angle);
            }else if(it->get_id() == 3){
                //calculate left hip
                double angle = this->calculateHipAngle(it->get_n1().y[it->cnt - 1] - it->get_n2().y[it->cnt - 1],
                    (it - 2)->get_n1().y[it->cnt - 1] - (it - 2)->get_n2().y[it->cnt - 1]);
                lm->move_hip_p(2, angle);
                fprintf(out3, "%i %f\n", it->cnt - 1, angle);
                double angle2 = this->calculateAnkleAngle(lm->get_hip_p(2), lm->get_knee_p(2));
                fprintf(out5, "%i %f\n", it->cnt - 1, angle2);
                lm->move_ankle_p(2, angle2);
            }else{
                //calculate right hip
                double angle = this->calculateHipAngle(it->get_n1().y[it->cnt - 1] - it->get_n2().y[it->cnt - 1],
                    (it - 2)->get_n1().y[it->cnt - 1] - (it - 2)->get_n2().y[it->cnt - 1]);
                lm->move_hip_p(1, angle);
                fprintf(out4, "%i %f\n", it->cnt - 1, angle);
                double angle2 = this->calculateAnkleAngle(lm->get_hip_p(1), lm->get_knee_p(1));
                fprintf(out6, "%i %f\n", it->cnt - 1, angle2);
                lm->move_ankle_p(1, angle2);
            }


            if(it->get_id() <= 2){
                //sync with swing oscillators
                (it+2)->fb1 = it->get_n2().y[it->cnt - 1];
                (it+2)->fb2 = it->get_n1().y[it->cnt - 1];
            }
        }
        usleep(40000);
        i++;
    }

    fclose(out1);
    fclose(out2);
    fclose(out3);
    fclose(out4);
}

double CPG::calculateKneeAngle(double v){
    return (this->calculateLMAngle(v) + 25) ;//* 0.0174533;
}

double CPG::calculateHipAngle(double v1, double v2){
    return (-this->calculateSWAngle(v1) - this->calculateLMAngle(v2));// * 0.0174533;
}

double CPG::calculateAnkleAngle(double v1, double v2){
    return (v1 + v2);
}

double CPG::calculateLMAngle(double v){
    return kALM * v;
}

double CPG::calculateSWAngle(double v){
    return kASW * v;
}
