#include <iostream>
#include <vector>
#include <random>
using namespace std;


random_device rd;                 // non-deterministic seed
mt19937 gen(rd());                // Mersenne Twister RNG

// Create a uniform real distribution between 0 and 1
uniform_real_distribution<> dis(0.0, 1.0);

class Box {
public:
    int input;
    vector<int> layer; // قائمة ديناميكية
    int output;
    vector<vector<vector<double>>> w;
    // Constructor: يأخذ أي قائمة حجمها ديناميكي
    Box(int input_val, const vector<int>& layer) {
        input = input_val;
        this->layer = layer; // نسخ القائمة بالكامل
        output = layer[-1];

        

            
        // --- first hidden layer ---
        w.push_back(vector<vector<double>>());
        for (int i = 0; i < layer[0]; i++) {
            vector<double> neuron_weights;
            for (int x = 0; x < input; x++) {
                neuron_weights.push_back(dis(gen));
            }
            neuron_weights.push_back(1.0); // bias
            w[0].push_back(neuron_weights);
        }

        // --- next hidden layers ---
        for (int l = 1; l < layer.size(); l++) {
            w.push_back(vector<vector<double>>());
            for (int i = 0; i < layer[l]; i++) {
                vector<double> neuron_weights;
                for (int x = 0; x < layer[l - 1]; x++) {
                    neuron_weights.push_back(dis(gen));
                }
                neuron_weights.push_back(1.0); // bias
                w[l].push_back(neuron_weights);
            }
        }
    }

    vector<double> predict(const vector<double>& input_value) {
        vector<vector<double>> last_layer;
        last_layer.push_back(vector<double>()); // first layer output

        // --- first layer ---
        for (auto& neuron : w[0]) {
            double sum = 0.0;
            for (int e = 0; e < input_value.size(); e++)
                sum += input_value[e] * neuron[e];
            sum += neuron.back(); // bias
            last_layer[0].push_back(sum);
        }

        // --- next layers ---
        for (int i = 1; i < w.size(); i++) {
            last_layer.push_back(vector<double>()); // new layer
            for (auto& neuron : w[i]) {
                double sum = 0.0;
                for (int e = 0; e < last_layer[i - 1].size(); e++)
                    sum += last_layer[i - 1][e] * neuron[e];
                sum += neuron.back(); // bias
                last_layer[i].push_back(sum);
            }
        }

        return last_layer.back(); // output of last layer
    }
    
};

int main() {
    int n = 0;
 cin >> n;
Box myBox(3, {99, 99, 99,99,99,99,2});
vector<double> input = {1.0, 0.5, -1.2};
vector<double> output = myBox.predict(input);

for(auto&out:output){
    cout<<out<<endl;
}
    cin >> n;
    return 0;
}

//g++ node.cpp -o node