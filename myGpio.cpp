#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "myGpio.h"

using namespace std;

GPIOClass::GPIOClass()
{
    this->gpionum = "4"; //default
}

GPIOClass::GPIOClass(string gnum)
{
    this->gpionum = gnum;  //Init mit number
}

//ofstream - open file to write
//inform the system about the exported GPIO
int GPIOClass::export_gpio()
{
    string export_str = "/sys/class/gpio/export";
    ofstream exportgpio(export_str.c_str()); //C++ string to C string
	
    if (!exportgpio.good()){
       cout << " OPERATION FAILED: Unable to export GPIO"<< this->gpionum <<" ."<< endl;
       return -1;
    }

    exportgpio << this->gpionum ; //write GPIO number to export
    exportgpio.close(); 
    return 0;
}

//ofstream - open file to write
//inform the system about the unexported GPIO
int GPIOClass::unexport_gpio()
{
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio(unexport_str.c_str()); /
    if (!unexportgpio.good()){
        cout << " OPERATION FAILED: Unable to unexport GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    unexportgpio << this->gpionum ; //write GPIO number to unexport
    unexportgpio.close(); 
    return 0;
}

//ofstream - open file to write
//write the direction of GPIO in file direction
int GPIOClass::setdir_gpio(string dir)
{
    string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
    ofstream setdirgpio(setdir_str.c_str()); // open direction file for gpio
        if (!setdirgpio.good()){
            cout << " OPERATION FAILED: Unable to set direction of GPIO"<< this->gpionum <<" ."<< endl;
            return -1;
        }

        setdirgpio << dir; //write direction to direction file
        setdirgpio.close(); 
        return 0;
}


//ofstream - open file to write
//write the GPIO value in file value
int GPIOClass::setval_gpio(string val)
{

    string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
        if (!setvalgpio.good()){
            cout << " OPERATION FAILED: Unable to set the value of GPIO"<< this->gpionum <<" ."<< endl;
            return -1;
        }

        setvalgpio << val ;//write value to value file
        setvalgpio.close();// close value file
        return 0;
}


//ifstream - open file to read
//read the GPIO value from file value
int GPIOClass::getval_gpio(string& val){

    string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
    ifstream getvalgpio(getval_str,std::ifstream::in);//getval_str.c_str());// open value file for gpio
    if (!getvalgpio.good()){
        cout << " OPERATION FAILED: Unable to get value of GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
            }

    getvalgpio >> val ;  //read gpio value

    if(val != "0")
        val = "1";
    else
        val = "0";

    getvalgpio.close(); //close the value file
    return 0;
}

string GPIOClass::get_gpionum(){

return this->gpionum;

}