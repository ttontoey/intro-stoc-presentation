#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void print_walk_sim(int t, int pos, int bar_l, int bar_r){
    cout << "t=" << t << ": [";
    for (int i=1 ; i <= bar_r ; i++){
        if (i == bar_l){
            cout << "X";
        }
        else if (i == bar_r){
            cout << "X";
        }
        else if (i == pos){
            cout << "O";
        }
        else {
            cout << "-";
        }
    }
    cout << "]";
}

void rand_walk_sim(int &S_n, int &bar_l, int &bar_r, int &t, bool print){
    if (print){
        cout << endl << "### RANDOM WALK SIMULATION ###" << endl;
        print_walk_sim(0, S_n, bar_l, bar_r);
        cout << endl;
    }
    while (S_n != bar_l && S_n != bar_r){
        int X_n = rand() % 2 == 0 ? -1 : 1;
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
    cout << "Starting point: ";
    cin >> a;
    cout << "Left absorption barrier: ";
    cin >> bar_l;
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
    int mode;
    cout << "[1] Animate [2] Monte-Carlo for Hitting Times/Probs" << endl;
    cout << "Choose mode: ";
    cin >> mode;
    int S_n = a;
    int t = 0;
    if (mode == 1){
        rand_walk_sim(S_n, bar_l, bar_r, t, true);
    }
    else if (mode == 2){
        int sim;
        cout << "Simulation(s) to run: ";
        cin >> sim;
        int bar_l_hit = 0, bar_r_hit = 0;
        int hitting_time_sum = 0;
        for (int i = 0 ; i < sim ; i++){
            rand_walk_sim(S_n, bar_l, bar_r, t, false);
            if (S_n == bar_l){
                bar_l_hit++;
            }
            if (S_n == bar_r){
                bar_r_hit++;
            }
            hitting_time_sum += t;
            S_n = a;
            t = 0;
        }
        double hitting_time = hitting_time_sum;
        hitting_time /= sim;
        double bar_l_prob = bar_l_hit;
        bar_l_prob /= (bar_l_hit + bar_r_hit);
        double bar_r_prob = bar_r_hit;
        bar_r_prob /= (bar_l_hit + bar_r_hit);
        cout << endl << "### NUMERICAL RESULT ###" << endl;
        cout << " - Hitting time: " << hitting_time << endl;
        cout << " - Prob hitting the left barrier: " << bar_l_prob << endl;
        cout << " - Prob hitting the right barrier: " << bar_r_prob << endl;
    }


    

    

        
    

}