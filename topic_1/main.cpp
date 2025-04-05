#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

const int RANDOM_RESOLUTION = 1e6;

int main(){
    cout << "You will have to provide the inverse C.D.F function values, denoted F^-1(x) where F(x) = P(X <= x)." << endl;
    int samp_count;
    cout << "F^-1(x) sample point count: ";
    cin >> samp_count;
    map<double, double> cumuProbToVal;
    double prev = -10000000;
    for (int i = 1 ; i <= samp_count ; i++){
        double x = i;
        x /= samp_count;
        cout << fixed << setprecision(3) << "F^-1(" << x << ") value: ";
        double val;
        cin >> val;
        if (val >= prev){
            cumuProbToVal[x] = val;
            prev = val;
        }
        else {
            cout << "Error: F^-1(x) has to be monotonously increasing !";
            return 0;
        }
    }

    int n_sample;
    cout << "Enter sample size: ";
    cin >> n_sample;
    vector<double> samples(n_sample);

    srand(time(0));
    for (int i = 0 ; i < n_sample ; i++){
        double r = (rand() % RANDOM_RESOLUTION);
        r = r / RANDOM_RESOLUTION;
        auto it = cumuProbToVal.lower_bound(r);
        samples[i] = it->second;
    }

    cout << "#### RESULT ####" << endl;
    double sum = 0;
    for (int i = 0 ; i < samples.size() - 1 ; i++){
        cout << samples[i] << ", ";
        sum += samples[i];
    }
    cout << samples[samples.size() - 1];
    sum += samples[samples.size() - 1];
    cout << endl;
    cout << "Mean: " << sum/n_sample;
}