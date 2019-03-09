#include <iostream>
#include <vector>
#include "Layers.h"

class NeuralNetwork {

private:
    Layer *input, *output;
    Layer **layers;
    int layerCount, nrLayers;
public:

    NeuralNetwork(int numberOfLayers) {
        layers = new Layer*[numberOfLayers];
        nrLayers = numberOfLayers;
        layerCount = 0;
    }

    void addLayer(Dense newLayer) {
        layers[layerCount] = &newLayer;
        if (layerCount > 0 && layerCount < nrLayers)
            layers[layerCount]->type = layerType::hidden;
        else
            if (layerCount == nrLayers)
                layers[layerCount - 1]->type = layerType::output;
            else
                if (layerCount == 0)
                    layers[0]->type = layerType::input;
        layerCount += 1;
        
    }

    void testAll() {
        int i;
        for (i = 0; i < layerCount; i++) {
            layers[i]->check();
        }
    }

    void testLayerLinkage() {
        int i;
        for (i = 0; i < layerCount; i++) {
            layers[i]->spareID = i;
        }
        layers[0]->setNext(layers[1]);
        for (i = 1; i < layerCount - 1; i++) {
            layers[i]->setNext(layers[i + 1]);
            layers[i]->setPrev(layers[i-1]);
        }
        layers[layerCount - 1]->setPrev(layers[layerCount - 2]);
        for (i = 0; i < layerCount; i++) {
            cout<<"Current ID: "<<layers[i]->spareID<<endl;
            if (layers[i]->getNext() != NULL) {
                cout<<"  Next: "<<layers[i]->getNext()->spareID<<endl;
            }
            if (layers[i]->getPrev() != NULL) {
                cout<<"  Prev: "<<layers[i]->getPrev()->spareID<<endl;
            }
        }
    }

    void build() {
        int i;
        input = layers[0];
        output = layers[layerCount - 1];
        // testLayerLinkage();
    }

    void train() {

    }
};