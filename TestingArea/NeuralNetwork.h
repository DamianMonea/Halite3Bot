#include <iostream>
#include <vector>
#include "Layers.h"

int** matrixMult(int **x, int n1, int m1,
                int **y, int n2, int m2,
                int** r) {
    int i, j, k;    
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m1; j++) {
            for (k = 0; k < m1; k++) {
                r[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return r;
}

class NeuralNetwork {

private:
    
    // An array of arrays, each array representing a layer of neurons.
    double **layers;
    int *layerSizes;

    // An array of 2D arrays that represents the weight matrices    
    double ***weights;

    int nrLayers, layerCount;
public:

    NeuralNetwork(int numberOfLayers) {
        layers = new double*[numberOfLayers];
        layerSizes = new int[numberOfLayers];
        nrLayers = numberOfLayers;
        layerCount = 0;
    }

    ~NeuralNetwork() {
        int i;
        for (i = 0; i < nrLayers; i++)
            delete[] layers[i];
        delete[] layers;
        delete[] layerSizes;
    }

    void addLayer(int neuronCount) {
        layerSizes[layerCount] = neuronCount;
        layers[layerCount] = new double[neuronCount];
        layerCount+=1;
    }

    void testAll() {

    }

    void build() {
        int i;
    }

    void train() {

    }
};