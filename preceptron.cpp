#include <iostream>
#include <vector>
#include <time.h>

using std::string;
using std::vector;

// This preceptron takes leg count and body size as a input and determines if it is a dog or human
//  For dog leg count should be 4 and body size should be <= 5
vector<vector<int>> X_train = {
    {4, 4},
    {2, 8},
    {4, 1},
    {4, 3},
    {2, 6},
    {4, 5},
    {5, 10},
};

// 0 = dog 1 == human
vector<int> Y_train = {
    0,
    1,
    0,
    0,
    1,
    0,
    1,
};

vector<string> labels = {
    "Dog",
    "Human",
};

int activation_function(float z_)
{
    if (z_ > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

class Model
{
private:
    vector<float> weights;

public:
    // Predict method sum of (inputs_i * weights_i) return it with a activation function
    int predict(vector<int> inputs)
    {
        float z = 0.0f;
        for (int i = 0; i < inputs.size(); i++)
        {
            z += inputs[i] * weights[i];
        }

        return activation_function(z);
    };
    void train(vector<vector<int>> x_train_dataset, vector<int> y_train_dataset, int epochs, float learning_rate)
    {
        srand(time(0));

        // Populate weights with a random number between 0 and 1;
        // we take x_train_dataset[0].size() because we want the weights to be equal to the number of inputs
        for (int w = 0; w < x_train_dataset[0].size(); w++)
        {
            weights.push_back(((float)rand()) / RAND_MAX);
        }

        float accuracy = 0.0f;

        // Main traning loop
        for (int i = 0; i < epochs; i++)
        {
            // Traning sample loop
            float result = 0.0f;
            int number_of_correct_prediction = 0;

            for (int j = 0; j < x_train_dataset.size(); j++)
            {
                int y_cap = predict(x_train_dataset[j]);
                float loss = y_train_dataset[j] - y_cap;

                // if prediction is right increment the number of correct prediction
                if (y_cap == y_train_dataset[j])
                {
                    number_of_correct_prediction++;
                }

                // update the weights
                for (int k = 0; k < weights.size(); k++)
                {
                    // Preceptron learning rule weights += learning rate * loss * current input
                    weights[k] += learning_rate * loss * x_train_dataset[j][k];
                }

                result += loss * loss;
            }
            result /= x_train_dataset.size();
            accuracy = (float)number_of_correct_prediction / y_train_dataset.size() * 100;

            printf("epoch %d accuracy %f loss %f\n", i, accuracy, result);
        }

        printf("=================================================================\n");
    };
};

int main()
{
    Model model;

    model.train(X_train, Y_train, 10, 0.01f);

    std::cout << "Predicted outcome : " << labels[model.predict(vector<int>{4, 5})] << "\n";

    return 0;
}

// 1 == human 0 == dog