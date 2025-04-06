#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>


using namespace std;

const int RANDOM_RESOLUTION = 1e6;

void print_walk_sim(int t, int pos, int bar_l, int bar_r){
    cout << "t=" << t << ": [";
    for (int i=1 ; i <= bar_r ; i++){
        if (i == bar_l){ cout << "X"; }
        else if (i == bar_r){ cout << "X"; }
        else if (i == pos){ cout << "O"; }
        else { cout << "-";}
    }
    cout << "]";
}

void rand_walk_sim(int &S_n, int &bar_l, int &bar_r, int &t, double &p, unsigned int seed, bool print){
    srand(seed);
    if (print){
        cout << endl << "### RANDOM WALK SIMULATION ###" << endl;
        print_walk_sim(0, S_n, bar_l, bar_r);
        cout << endl;
    }
    while (S_n != bar_l && S_n != bar_r){
        double random = ((rand() % RANDOM_RESOLUTION) * 1.0)/RANDOM_RESOLUTION;
        int X_n = random <= p ? 1 : -1;
        S_n += X_n;
        t += 1;
        if (print){
            print_walk_sim(t, S_n, bar_l, bar_r);
            cout << " X_n = " << X_n << endl;
        }
    }
}

int main(){
    cout << "Simple random walk with absorption simulation" << endl;
    int a, bar_l, bar_r;
    double p;
    cout << "Starting point: ";
    cin >> a;
    cout << "Left absorption barrier: 0" << endl;
    bar_l = 0;
    if (bar_l > a){
        cout << "Error: Left absorption barrier must be less than or equal to the starting point.";
        return 0;
    }
    cout << "Right absorption barrier: ";
    cin >> bar_r;
    if (bar_r < a){
        cout << "Error: Right absorption barrier must be greater or equal to the starting point.";
        return 0;
    }
    cout << "P(Moving right): ";
    cin >> p;
    if (p < 0 || p > 1){
        cout << "Error: P(Moving right) must be between 0 and 1.";
        return 0;
    }
    int mode;
    cout << "[1] Animate [2] Monte-Carlo for Hitting Times/Probs" << endl;
    cout << "Choose mode: ";
    cin >> mode;
    int S_n = a;
    int t = 0;
    if (mode == 1){
        rand_walk_sim(S_n, bar_l, bar_r, t, p, time(0), true);
    }
    else if (mode == 2){
        int sim;
        cout << "Simulation(s) to run: ";
        cin >> sim;
        char printSim;
        cout << "Print sim results? [Y/N]: ";
        cin >> printSim;
        int bar_l_hit = 0, bar_r_hit = 0, hitting_time_sum = 0;
        for (int i = 0 ; i < sim ; i++){
            rand_walk_sim(S_n, bar_l, bar_r, t, p, time(0) + i, printSim == 'Y');
            if (S_n == bar_l)
                bar_l_hit++;
            if (S_n == bar_r)
                bar_r_hit++;
            hitting_time_sum += t;
            S_n = a;
            t = 0;
        }

        double hitting_time_a, bar_r_prob_a;
        double q = 1 - p;
        if (p == 0 || p == 0.5){ 
            bar_r_prob_a = p == 0 ? 0 : (a * 1.0)/bar_r; 
            hitting_time_a = p == 0 ? a : (a * 1.0) * (bar_r - a);
        }
        else {
            bar_r_prob_a = (pow((q / p), a) - 1)/(pow((q / p), bar_r) - 1);
            hitting_time_a = (a / (q - p)) - ((bar_r / (q - p)) * bar_r_prob_a);
        }
        double bar_l_prob_a = 1 - bar_r_prob_a;
        cout << endl << "### ANALYTICAL RESULT ###" << endl;
        cout << fixed << setprecision(5) << " - Expected hitting time: " << hitting_time_a << endl;
        cout << fixed << setprecision(5) << " - P(Hitting the left barrier): " << bar_l_prob_a << endl;
        cout << fixed << setprecision(5) << " - P(Hitting the right barrier): " << bar_r_prob_a << endl;
        
        double hitting_time_n = (hitting_time_sum * 1.0) / sim;
        double bar_l_prob_n = (bar_l_hit * 1.0)/(bar_l_hit + bar_r_hit);
        double bar_r_prob_n = (bar_r_hit * 1.0)/(bar_l_hit + bar_r_hit);
        double hitting_time_err = hitting_time_a != 0 ? abs(hitting_time_n - hitting_time_a)/hitting_time_a * 100 : 0;
        double bar_l_prob_err = bar_l_prob_a != 0 ? abs(bar_l_prob_n - bar_l_prob_a)/bar_l_prob_a * 100 : 0;
        double bar_r_prob_err = bar_r_prob_a != 0 ? abs(bar_r_prob_n - bar_r_prob_a)/bar_r_prob_a * 100 : 0;

        cout << endl << "### NUMERICAL RESULT (by Monte-Carlo) ###" << endl;
        cout << fixed << setprecision(5) << " - Expected hitting time: " << hitting_time_n << " (";
        cout << fixed << setprecision(2) << "Error: " << hitting_time_err << "%)" << endl;
        cout << fixed << setprecision(5) << " - P(Hitting the left barrier): " << bar_l_prob_n << " (";
        cout << fixed << setprecision(2) << "Error: " << bar_l_prob_err << "%)" << endl;
        cout << fixed << setprecision(5) << " - P(Hitting the right barrier): " << bar_r_prob_n << " (";
        cout << fixed << setprecision(2) << "Error: " << bar_r_prob_err << "%)" << endl;
    }


    

    

        
    

}