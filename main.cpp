/*
 *  This file is part of the Jasper KI project by Animator617 (C)
 *  Do not copy edit modify or sell parts of or the hole projekt 
 * 
 *  This project is secured by the Shadowbit-Project-License (C)
 *  Copyright : Animator617 (c) 2013 - 2019 
 * 
 */

/* 
 * File:   main.cpp
 * Author: Animator617 (c)
 * Project: Jasper
 * 
 * Created on 10. Juli 2019, 13:57
 */


// PYTHON INCL //
#define PY_SSIZE_T_CLEAN
#include <windows.h>

/*
// if __CYGWIN__ is defined i need to undefine it 
#ifdef __CYGWIN__
#undef __CYGWIN__
#endif
*/

#ifdef WIN_32
#   include "python/python_WIN32/Include/Python.h"
#else
#   include "python/python/Include/Python.h"
#endif

// INCLUDE LIBS.
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
//#include <Python.h>
//#include <cstdlib>

using namespace std;

// MY FILES
#include "main/main.tcc"
#include "brain/brain.h"
#include "brain/brain.tcc"
#include "protocol/protocol.tcc"
#include "file_system/FolderManager/FolderManager.hpp"
//#include "file_system/file_system.tcc"
//#include "file_system/FileManager/FileManager.hpp"

// for testing //
#include "python/test/test_run.h"

// NEEDED CLASSES

/*
 *
 */
/*
 * The new idea is that when im using the idea i used before io would need 
 * terrabites of ram and thats not what i looking fore 
 * that woud be unpossible to implement into 
 * smaller computers and lice a smartphone or an raspberry pie
 * so i had the idea that when initializing an new perceptron brain 
 * area or neuron this will get saved in files saved on the dirve 
 * and everytime these objects and object trees are needed the object will get initialiced new but than with the 
 * values form the files 
 * for example the brain has to learn to decide is that a dog or a cat in front of the camra therfor 
 * jasper creates an new brain area and initialize a new perceptron than 
 * creating the layers lines cluster and neurons 
 * than assign the values to these objects 
 * than saving all that into a file 
 * than when needing it again 
 * therefor is to know that for an gothrew of an perceptron aways the value 
 * of an neuron of the actual layer of the layer before and the next layer need to get loaded 
 * these values get loaded from files added and get back stored and unnieded objects get destroyed again 
 * and so on. This way isn't the hole brain or perceptron saved in RAM  instead only a few neurons and perceptrons are saved 
 * there fore i need to create an directory where the programm get known what files belong to what layer neuron perceptron and so on 
 * also i need to add to each class an save read and print function for handling with it and i need to ad several funktions to 
 * the above class that controll the class under it 
 * but than it should work awsome also on pc with small ram 
 * yey 
 */

/*
 * When deleating a file 
 * go nbproject/configurations.xml 
 * and deleate all entries belong to the deleated file
 * than it works well again :)
 */
/*
 * These functions are written in the main folder 
 * imported with the main struckt
 * int IsQuit(string input); // define when the program should close
 * int IsEndGerman(string input); // define what massage should come when the programm is closed
 * int WhatProtocol(string input); // define what protocoll should run 
 * int RunProtocol(string input); // run the selected protocoll
 */


int TestFolderCreation(string folder, const char *folderP, const char *path); // creates an new folder in the first named folder

int main() {
    // The Values for initialise the Brain
    // New Set up to simply change settet values
    // name of the brain area
    string areaname = "testing";

    // Input
    int in_x = 0;
    int in_y = 0;

    // output
    int out_x = 0;
    int out_y = 0;

    // hidden
    /// this is already to heavy for the netbook
    // hopfully dos it work on my PC

    string ishidden = "no hidden"; // with hidden = yes / no hidden = no
    int hid_x = 0; // layers
    int hid_y = 0; // lines
    int hid_z = 0; // neurons per line

    // with cluters
    string iscluster = "yes"; // yes / no
    int nr_c = 0; // numberof clusers

    int pos_x[] = {1,0}; // position in layers
    int pos_y[] = {1,0}; // position line
    int pos_z[] = {0,0}; // position neuron

    int c_x[] = {1,1,0};
    int c_y[] = {1,1,0};
    int c_z[] = {1,1,0};
    
    // Start of Jasper 
    // first colling the start batch
    //system("batch/FirstBatch_test/test.bat");
    system("batch/StartUpBatch/MainStartBatch.bat");
    
    // than start the virtual python envirunment
    system("batch/StartUpBatch/PythonStartBatch.bat");
    
    // remineder 
    
    cout << "reminder in main.cpp" << endl;
    
    // Project TEST Jasper KNN has the code included to save and store datas from classes inside of dat files 
    // now i need to write code that make it usable for me again 
    // there for i hae written code i find here :
    // F:\0_0_J.A.C.K\Testings\Class to file\Test Class to file 
    
    // reminder end
    
    
    
    // TESTING SPACE //
    NS_JASPER_BRAIN::brainHTest();
    
    //ManageBrain MB;
    //brainHTest();
    ManageBrain MB;
    MB.TestManageBrain();
    MB.CreateNewBrainArea(
            areaname,
            ishidden,
            in_x, in_y,
            out_x, out_y
    );
    MB.addPerceptron(
            areaname,
            ishidden,
            in_x, in_y,
            out_x, out_y
    );
    
    TestFolderCreation("src", "src", "src/temp");

    
    //utils::mkdir("\testing\temp");
    
    
    // python testing 
    //jpytest(1, "hallo");
    //jpytest();
    jpytest(); // PROBLEM : (.text+0x364): relocation truncated to fit: R_X86_64_PC32 against undefined symbol `jpytest'
               // Problem solved under Windows 32 bit but error still exist on Windows 64 bit
    
    // END TESTING SPACE //
    cout << "\n Hey I'm Jasper" << endl;
    
    cout << "hello world" << endl;
    
    string input;
    
    Start:
    
    getline(cin, input);
    
    cout << input << endl;
        
    //Initialice classes
    Ultimate ULT;
    protocol P(input); // directly initialize
    
    
    if (ULT.IsQuit(input) == 1) {
        goto End;
    } else {
        goto Start;
    }
    
    End:
    
    if(ULT.IsEndGerman(input) == 1) {
        cout << "Auf Wieder Sehen. Ich hoffe wir reden mal wieder.\n"
             << "** Jasper **" << endl;
    } else {
        cout << "Good by. I'll hope we can talk again. \n"
             << "** Jasper **" << endl;
    }
    
    // now shuting down the python envirument
    system("batch/EndBatch/PythonEndBatch.bat");
    
    return 0;
}



// this funtion create an new folder in the with string folder defind folder 
// the new folder name is defined with  the foldername string
int TestFolderCreation(string folder, const char *folderP, const char *path) {
/*
    std::ostringstream oss;
    oss << folder << "/" << foldername;
    string folderpath = oss.str();
*/
    // initialice the needed class
    FolderManager FM;
    
    
    if (FM.folder_exists(folder)) {
        if (FM._mkdir(path)) {
            cout << "the folder already exist" << endl;
        } else {
            cout << "the folder dosnt exist so i create it" << endl; 
            FM._mkdir(path);
            cout << "ive create it" << endl;
            
            if (FM.folder_exists(folder)) {
                cout << "now the folder exist" << endl;
            } else {
                cout << " somethinmg went wrong im sorry" << endl;
            }
        } 
    } else {
        cout << "the folder dont exist i try to create it" << endl;
        FM._mkdir(folderP);
        if (FM.folder_exists(folder)) {
            cout << "The folder exist now so i create the requested it" << endl;
            FM._mkdir(path);
            cout << "ive create it" << endl;
            
            if (FM.folder_exists(folder)) {
                cout << "now the folder exist" << endl;
            } else {
                cout << " somethinmg went wrong im sorry" << endl;
            }
        } else {
            cout << "so i cant create it so we have an problem i think" << endl;
        }
    }
    cout << "you're Jasper" << endl;

    return 0;
}
