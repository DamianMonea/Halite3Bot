#include "Neuron.h"
#include <vector>

using namespace std;

enum class layerType{ input, hidden, output};

int hardlim(double n) {
    if (n < 0)
        return 0;
    return 1;
}

int harlims(double n) {
    if (n < 0)
        return -1;
    return 1;
}

double purelin(double n) {
    return n;
}

double satlin(double n) {
    if (n < 0)
        return 0;
    if (n > 1)
        return 1;
    return n;
}

double satlins(double n) {
    if (n < -1)
        return -1;
    if (n > 1)
        return 1;
    return n;
}

double logsig(double n) {
    return 1 / (1 + exp((-1) * n));
}

double tansig(double n) {
    return (exp(n) - (exp((-1) * n))/(exp(n)+exp((-1) * n)));
}

double relu(double n) {
    if (n <= 0)
        return 0;
    return n;
}

vector<double> softmax(vector<double> x) {
    vector<double> res;
    int n = x.size();
    int i;
    double s = 0;
    for (i = 0; i < n; i++) {
        s += exp(x[i]);
    }
    for (i = 0; i < n; i++) {
        res.push_back(x[i]/s);
    }
    return res;
}


class Layer{
public:
    int spareID;
    layerType type;

    virtual void test() { }

    virtual void setPrev(Layer *next) {}

    virtual void setNext(Layer *prev) {}

    virtual Layer* getPrev() { }
    
    virtual Layer* getNext() { }

    virtual void check() { }

    virtual Neuron* getNeurons() { }

    virtual void setType() { }

    virtual void getType() { }

};

class Dense : public Layer{
private:
    Layer *previous, *next;
    Neuron *neurons;
    double *inputs;
    int neuronCount;
public:
    Dense(int units) {
        neurons = new Neuron[units];
        previous = NULL;
        next = NULL;
    }

    Dense() {
        neurons = NULL;
        previous = NULL;
        next = NULL;
    }

    void test() {
        cout<<"This is a dense layer"<<endl;
    }

    void setNext(Layer *next) {
        int i;
        for (i = 0; i < neuronCount; i++) {
            this->neurons[i].setNextNeurons(next->getNeurons());
        }
        this->next = next;
    }

    void setPrev(Layer *prev) {
        int i;
        for (i = 0; i < neuronCount; i++) {
            this->neurons[i].setPrevNeurons(prev->getNeurons());
        }
        this->previous = prev;
    }

    Layer* getPrev() {
        return this->previous;
    }

    Layer* getNext() {
        return this->next;
    }

    Neuron* getNeurons() {
        return neurons;
    }

    void check() {
        if (previous != NULL) {
            cout<< "Previous: ";
            previous->test();
        }
        test();
        if (next != NULL) {
            cout<< "Next: ";
            next->test(); 
        }

        cout<<endl;
    }
};

class Activation : public Layer {

private:

public:

};