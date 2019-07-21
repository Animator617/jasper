/*
 *  This file is part of the Jasper KI project by Animator617 (C)
 *  Do not copy edit modify or sell parts of or the hole projekt 
 * 
 *  This project and all parts 
 *  of it is secured by the Shadowbit-Project-License (C)
 *  Copyright : Animator617 (c) 2013 - 2019 
 * 
 */

/* 
 * File:   main.cpp
 * Author: Animator617
 *
 * Created on 20. April 2019, 10:42
 */
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * beginning i have following model i going to create
 *               (1)               
 * (3 -1 2 0) * (2) (f(x) = x) = (3*1+-1*2+2*3+0*4) = 7
 *               (3)               
 *               (4)            
 *
 * that the matrix of the KNN i going to build    
 * than i added an sigmoid func and an secound 
 * output
 */

// ############################################################################################ //
// noe the neuron class
class Neuron {
public:
    virtual float getValue();
};

// ############################################################################################ //
// function class
class Func {
public:
    /*
    Func() {
        float a;
        a = 1 / ( 1 + exp(-2));
        cout << a << endl;
    }
    */
    float Sigmoid(float x) { // it work 
        float a;
        a = 1 / ( 1 + exp(-x));
        //cout << a << endl; 
        //Output bei 7.0 = 0.999089
        return a;
    }
    float Konjunktion() { // AND
        return 0;
    }
    
    float Disjunktion() { // OR
        return 0;
    }
    
    float Negation() { // NOT
        return 0;
    }
    //float 
    //double exp(double a);
};

// ############################################################################################ //
// now maike an input neuron
class InputNeuron {
private:
    string text_ = "Neuron";
    float Value = 0;
public:
    float getValue() {
        return Value;
    }
    
    void setValue(float value) {
        this->Value = value;
    }
    
    // for testing // 
    float getValueNew() {
        return this->Value;
    }
    
    // for writing to file
    std::ostream& write(std::ostream& os) const {
        os << text_ << std::ends;
        os.write(reinterpret_cast<const char*>(&Value), sizeof(Value));

        return os;
    }
    std::istream& read(std::istream& is) {
        std::getline(is, text_, '\0');
        is.read(reinterpret_cast<char*>(&Value), sizeof(Value));
        return is;
    }
    std::ostream& print(std::ostream& os) {
        return os << text_ << " : " << Value << std::endl;
    }
};

// ############################################################################################ //
// now creating the connection class
class Connection {
private:
    //InputNeuron* neuron;
    string text_ = "Connection";
    float Weight;
    float Input;
public:
    Connection(float weight) {
        //this->neuron = neuron;
        this->Weight = weight;
    }
    ~Connection() {};
    float getValue() {
        return Input * Weight;
    }
    void AddWeight(float weight) {
        //this->neuron = neuron;
        this->Weight = weight;
    }
    
    void AddInput(float Input) {
        this->Input = Input;
    }
    // for testing //
    float getWeight() {
        return this->Weight;
    }
    float getInput() {
        return this->Input;
    }
    
    // for riting toi file
    std::ostream& write(std::ostream& os) const {
        os << text_ << std::ends;
        os.write(reinterpret_cast<const char*>(&Input), sizeof(Input));
        os.write(reinterpret_cast<const char*>(&Weight), sizeof(Weight));
        return os;
    }
    std::istream& read(std::istream& is) {
        std::getline(is, text_, '\0');
        is.read(reinterpret_cast<char*>(&Input), sizeof(Input));
        is.read(reinterpret_cast<char*>(&Weight), sizeof(Weight));
        return is;
    }
    std::ostream& print(std::ostream& os) {
        return os << text_ << " : " << Input << ":" << Weight << std::endl;
    }
};

// ############################################################################################ //
// now the working neuron class 
class WorkingNeuron: public Func { // for activation functions
private:
    vector<Connection*> ArrayCon;
    //Connection **ArrayCon = new Connection*;
    int SZ = 0; // define the momentarry size default is 0
    
    string text_ = "WorkingNEuron";
    
    void Add(float weight) {
        int temp_SZ = this->SZ;
        ArrayCon.push_back(new Connection(weight));
        this->SZ++;
    }
    
    float Value = 0;
    
    string FuncKind = "no";
public:
    // nun setting up the function that belongs
    WorkingNeuron(string Func) {
        this->FuncKind = Func;
    }
    float getValue() {
        float sum = 0;
        float out = 0;
        for(int i=0; i < SZ; i++) {
            sum += ArrayCon.at(i)->getValue();
        }
        if (FuncKind == "Sigmoid") {
            out += Sigmoid(sum);
        } else {
            out += sum;
        }
        
        this->Value = out;
        
        return out;
    }
    
    void addConnection(float weight) {
        Add(weight);
    }
    
    void addWeight(float weight, int NR) {
        ArrayCon.at(NR)->AddWeight(weight);
    }
    
    void addInput(float Input, int NR) {
        ArrayCon.at(NR)->AddInput(Input);
    }
    // for testing //
    float getConnWeight(int ConNR) {
        return ArrayCon.at(ConNR)->getWeight();
    }
    float getConInput(int ConNR) {
        return ArrayCon.at(ConNR)->getInput();
    }
    
    // for riting toi file
    std::ostream& write(std::ostream& os) const {
        os << text_ << std::ends;
        os.write(reinterpret_cast<const char*>(&Value), sizeof(Value));
        return os;
    }
    std::istream& read(std::istream& is) {
        std::getline(is, text_, '\0');
        is.read(reinterpret_cast<char*>(&Value), sizeof(Value));
        return is;
    }
    std::ostream& print(std::ostream& os) {
        return os << text_ << " : " << Value << std::endl;
    }
    
    int WriteConnectionToFile(string file) {
        int cnMax = this->SZ;

        // opening the file
        std::ofstream file_w(file, std::ios::binary);
        if( !file_w) {
            cout << "Fehler bei ?ffnen\n";
            return 1;
        }

        // write to file
        for (int c=0; c < cnMax; c++) {
            this->ArrayCon.at(c)->write(file_w);
            // testing //
            cout << "written" << endl;
        }
        file_w.close();

        return 0;
    }
};

// ############################################################################################ //
// the hidden neuron class
class HiddenNeuron: public Func {
private:
    Connection **ArrayCon = new Connection*;
    int SZ = 0; // define the momentarry size default is 0
    
    void Add(float weight) {
        int temp_SZ = this->SZ;
        ArrayCon[temp_SZ] = new Connection(weight);
        this->SZ++;
    }
    string FuncKind = "no";
public:
    // nun setting up the function that belongs
    HiddenNeuron(string Func) {
        this->FuncKind = Func;
    }
    float getValue() {
        float sum = 0;
        float out = 0;
        for(int i=0; i < SZ; i++) {
            sum += ArrayCon[i]->getValue();
        }
        if (FuncKind == "Sigmoid") {
            out += Sigmoid(sum);
        } else {
            out += sum;
        }
        return out;
    }
    void addConnection(float weight) {
        Add(weight);
    }
    
    void addWeight(float weight, int NR) {
        ArrayCon[NR]->AddWeight(weight);
    }
    
    void addInput(float Input, int NR) {
        ArrayCon[NR]->AddInput(Input);
    }
    
    int WriteHiddenConnectionToFile(string file) {
        int nMax = this->SZ;

        // opening the file
        std::ofstream file_w(file, std::ios::binary);
        if( !file_w) {
            cout << "Fehler bei ?ffnen\n";
            return 1;
        }

        // write to file
        for (int c=0; c < nMax; c++) {
            //this->ArrayCon.at(c)->write(file_w);
            // testing //
            cout << "written" << endl;
        }
        file_w.close();

        return 0;
    }
    
};

// ############################################################################################ //
// hidden Layer class to define special behavioure of single layers
class HiddenLayer {
private:
    HiddenNeuron **ArrayHidden = new HiddenNeuron*;
    
    int SZ_HID = 0;
    
    void AddHid() { //HiddenNeuron wn
        int temp_SZ_HID = this->SZ_HID;
        ArrayHidden[temp_SZ_HID] = new HiddenNeuron("no");
        this->SZ_HID++;
    }
    
    void AddHid(string Func) { // HiddenNeuron
        int temp_SZ_HID = this->SZ_HID;
        ArrayHidden[temp_SZ_HID] = new HiddenNeuron(Func);
        this->SZ_HID++;
    }
public:
    void ConnectAll() {
        
    }
};

// ############################################################################################ //
// this class initialise the neurall network
class NeuralNetwork {
private:
    vector<InputNeuron*> ArrayInput;
    vector<WorkingNeuron*> ArrayOutput;
    vector<HiddenLayer*> ArrayHidLay;
    //InputNeuron **ArrayInput = new InputNeuron*;
    //WorkingNeuron **ArrayOutput = new WorkingNeuron*;
    //HiddenLayer **ArrayHidLay = new HiddenLayer*;
    
    int SZ_IN = 0;
    int SZ_OUT = 0;
    int SZ_HIDLAY = 0;
    
    
    void AddIn() {
        int temp_SZ_IN = this->SZ_IN;
        ArrayInput.push_back(new InputNeuron());
        this->SZ_IN++;
    }
    
    void AddIn(float NewValue) {
        int temp_SZ_IN = this->SZ_IN;
        ArrayInput.push_back(new InputNeuron());
        ArrayInput.at(temp_SZ_IN)->setValue(NewValue);
        this->SZ_IN++;
    }
    
    void AddOut() { //WorkingNeuron wn
        int temp_SZ_OUT = this->SZ_OUT;
        ArrayOutput.push_back(new WorkingNeuron("no"));
        this->SZ_OUT++;
    }
    
    void AddOut(string Func) { // WorkingNeuron
        int temp_SZ_OUT = this->SZ_OUT;
        ArrayOutput.push_back(new WorkingNeuron(Func));
        this->SZ_OUT++;
    }
    
public:
    void CreateNewOutput() { //WorkingNeuron
        //WorkingNeuron wn; //= new WorkingNeuron();
        AddOut(); // del wn 
        //return wn;
    }
    void CreateNewOutput(string Func) {
        AddOut(Func);
    }
    
    void CreateNewInput(float NewValue) {
        //InputNeuron in;
        AddIn(NewValue);
    }
    // Full mesh without HiddenNeurons
    void CreateFullMesh() {
        float tp = 0;
        for(int i=0; i < SZ_OUT; i++) { // für die anzahl con outputs
            for(int x=0; x < SZ_IN; x++) { // für die anzahl von inputs
               // InputNeuron* in = ArrayInput[x];
                ArrayOutput.at(i)->addConnection(tp);
                float Input = ArrayInput.at(x)->getValueNew();
                ArrayOutput.at(i)->addInput(Input, x);
            }
        }
    }
    
    void CreateFullMesh(float w1, float w2, float w3, float w4) {
        float Array[4] = {w1, w2, w3, w4};
        for(int x=0; x < SZ_OUT; x++) {
            for(int i=0; i < SZ_IN; i++) {
                //InputNeuron* in = ArrayInput[i];
                ArrayOutput.at(x)->addWeight(Array[i], i);
            }
        }
    }
    
    // full mesh with Hidden Neurons
    /*
     * connection model all neurons of 
     * inputlayer with all neurons of first layer
     * and all of first layer with all of secound layer 
     * and so on 
     */
    /*
    void CreateFullMeshHid() {
        float tp = 0;
        for(int i=0; i < SZ_OUT; i++) { // für die anzahl con outputs
            for(int x=0; x < SZ_HID; x++) { // für die anzahl von inputs
               // InputNeuron* in = ArrayInput[x];
                ArrayOutput[i]->addConnection(tp);
                float Input = ArrayInput[x]->getValueNew();
                ArrayOutput[i]->addInput(Input, x);
            }
        }
    }
    
    void CreateFullMeshHid(float w1, float w2, float w3, float w4) {
        float Array[4] = {w1, w2, w3, w4};
        for(int x=0; x < SZ_OUT; x++) {
            for(int i=0; i < SZ_IN; i++) {
                //InputNeuron* in = ArrayInput[i];
                ArrayOutput[x]->addWeight(Array[i], i);
            }
        }
    }
    */
    
    float getOutPut(int OutNR) {
        //WorkingNeuron wn;
        return ArrayOutput.at(OutNR)->getValue();
    }
    // Hidden Neurons
    // using several ints to set up number of layers
    // and define number of neurons per layer 
    void CreateHiddenLayers(int Layers, int Neurons) {
        //cout << "hey" << endl;
        int test_count = 0;
        
    }
   
    // for testing //
    void getConnWeights() { // <- not working 
        for(int x=0; x < SZ_OUT; x++) {
            for(int i=0; i < SZ_IN; i++) {
                //InputNeuron* in = ArrayInput[i];
                //cout << ArrayOutput[x]->getWeight(); << endl
            }
        }
    }
    
    void getOutput(int OutNR) {
        cout << ArrayOutput.at(OutNR) << endl;
    }
    
    float getConnWeightMain(int wnNR, int ConNR) {
        return ArrayOutput.at(wnNR)->getConnWeight(ConNR);
    }
    
    float getInputNew(int InputNR) {
        return ArrayInput.at(InputNR)->getValueNew();
    }
    float getConInput(int OutNR, int ConNR) {
        return ArrayOutput.at(OutNR)->getConInput(ConNR);
    } 
    
    // Now printing the values to file 
    
    // first the Input Neuron
    int WriteInputToFile(string file) {
        int inMax = this->SZ_IN;

        // opening the file
        std::ofstream file_w(file, std::ios::binary);
        if( !file_w) {
            cout << "Fehler bei ?ffnen\n";
            return 1;
        }

        // write to file
        for (int c=0; c < inMax; c++) {
            this->ArrayInput.at(c)->write(file_w);
            // testing //
            cout << "written" << endl;
        }
        file_w.close();

        return 0;
    }
    
    // now the output neuronen ( working neurons )
    int WriteOutputNeuronsToFile(string file) {
        int onMax = this->SZ_OUT;

        // opening the file
        std::ofstream file_w(file, std::ios::binary);
        if( !file_w) {
            cout << "Fehler bei ?ffnen\n";
            return 1;
        }

        // write to file
        for (int c=0; c < onMax; c++) {
            this->ArrayOutput.at(c)->write(file_w);
            // testing //
            cout << "written" << endl;
        }
        file_w.close();

        return 0;
    }
    
    // write the connection values of the working neuron to an dat file
    void WriteConnectionToFile(string file) { // here only using the name without file extension
        for( int a=0; a < this->SZ_OUT; a++) {
            std::ostringstream oss;
            oss << file << a << ".dat";
            string filename = oss.str();
            this->ArrayOutput.at(a)->WriteConnectionToFile(filename);
        }
        cout << this->SZ_OUT << endl;
    }
};

// ############################################################################################ //
// now run the code
int main() {
    
    NeuralNetwork nn; // start building the KNN
    
    
    nn.CreateNewOutput(); // creates the output
    nn.CreateNewOutput("Sigmoid"); // create the output with
    // an activation function
   
    nn.CreateNewInput(1); //
    nn.CreateNewInput(2); // creates the inputs 
    nn.CreateNewInput(3); // and assign an value
    nn.CreateNewInput(4); //
    
    // cout << i1.getValue() << endl;
    nn.CreateHiddenLayers(1, 2);
    
    nn.CreateFullMesh(); // connect all neurons 
    
    nn.CreateFullMesh(3, -1, 2, 0); // ad the connection weights
    
    // the following test the values of the neurons
    cout << "conn weight is " <<  
    nn.getConnWeightMain(0, 0) << endl;
    
    cout << "Input is " << 
    nn.getInputNew(0) << endl;
    
    cout << "Con Input is " << 
    nn.getConInput(0, 0) << endl;
    
    
    cout << nn.getOutPut(0) << endl; // sollte 7.0 oder 7 sein 
    cout << nn.getOutPut(1) << endl; // sollte 0.999089 sein
    
    string InputDatFile = "InputNeurons.dat";
    string OutputDatFile = "OutputNeuron.dat";
    string ConnectionDatFile = "Connection"; // here only using the name without file extension
    
    nn.WriteInputToFile(InputDatFile);
    nn.WriteOutputNeuronsToFile(OutputDatFile);
    nn.WriteConnectionToFile(ConnectionDatFile); // here only using the name without file extension
    
}
