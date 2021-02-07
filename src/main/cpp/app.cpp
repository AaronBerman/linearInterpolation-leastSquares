#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iomanip>
#include "app.h"

using namespace std;

void printMyMatrix(const vector<std::vector<double>>& M);

int main(int argc, char** argv){
	
	/**
    *Error handling for file execution and usage details
	*/ 
     if(argc != 2){
        cerr << "Usage: " << argv[0] << " CPUtempsFile.txt" << endl;
        return 1;
    }
    string arg1(argv[1]);
    ifstream inFile(arg1);
    if(!inFile){
        cerr << "Error: " << arg1 << " could not be opened." << endl;
        return 2;
    }

    list<double> coreOne, coreTwo, coreThree, coreFour, time;
    list<double>::iterator itr;
    double tempForOne, tempForTwo, tempForThree, tempForFour;
    int length;
    const int nextTime = 30;
    
    int interval = 0;
    while (inFile >> tempForOne >> tempForTwo >> tempForThree >> tempForFour){
    	coreOne.push_back(tempForOne);	//create a list with the contents of core 1
    	coreTwo.push_back(tempForTwo);	//create a list with the contents of core 2
    	coreThree.push_back(tempForThree);	//create a list with the contents of core 3
    	coreFour.push_back(tempForFour);	//create a list with the contents of core 4
    	
        time.push_back(interval);	//create a list with the interval over the duration 
        interval += nextTime;		//increase interval by 30 seconds
    }

    length = time.size();
    inFile.close();

    //create a list of pi0 equal in length to time 
    list<double> listPi0;
    const double pi0 = 1.0;
    for (int i = 0; i < length; i++){
    	listPi0.push_back(pi0);
    }

    //create matrix containers and populate from the lists
    myMatrix coreOneX(length, 2);
    myMatrix coreOneY(length, 1);
    myMatrix coreTwoX(length, 2);
    myMatrix coreTwoY(length, 1);
    myMatrix coreThreeX(length, 2);
    myMatrix coreThreeY(length, 1);
    myMatrix coreFourX(length, 2);
    myMatrix coreFourY(length, 1);

    coreOneX.addContent(0, listPi0);
    coreOneX.addContent(1, time);
    coreOneY.addContent(0, coreOne);
    coreTwoX.addContent(0, listPi0);
    coreTwoX.addContent(1, time);
    coreTwoY.addContent(0, coreTwo);
    coreThreeX.addContent(0, listPi0);
    coreThreeX.addContent(1, time);
    coreThreeY.addContent(0, coreThree);
    coreFourX.addContent(0, listPi0);
    coreFourX.addContent(1, time);
    coreFourY.addContent(0, coreFour);

     //create the transform and multiplication matrix containers
    myMatrix coreOneXT(coreOneX.getCols(), coreOneX.getRows());
    myMatrix coreOneXTX(coreOneXT.getRows(), coreOneX.getCols());
    myMatrix coreOneXTY(coreOneXT.getRows(), coreOneY.getCols());
    myMatrix coreTwoXT(coreTwoX.getCols(), coreTwoX.getRows());
    myMatrix coreTwoXTX(coreTwoXT.getRows(), coreTwoX.getCols());
    myMatrix coreTwoXTY(coreTwoXT.getRows(), coreTwoY.getCols()); 
    myMatrix coreThreeXT(coreThreeX.getCols(), coreThreeX.getRows());
    myMatrix coreThreeXTX(coreThreeXT.getRows(), coreThreeX.getCols());
    myMatrix coreThreeXTY(coreThreeXT.getRows(), coreThreeY.getCols()); 
    myMatrix coreFourXT(coreFourX.getCols(), coreFourX.getRows());
    myMatrix coreFourXTX(coreFourXT.getRows(), coreFourX.getCols());
    myMatrix coreFourXTY(coreFourXT.getRows(), coreFourY.getCols());  

    //change X from rows:columns to columns:rows
    coreOneXT.transform(coreOneX);
    coreTwoXT.transform(coreTwoX);
    coreThreeXT.transform(coreThreeX);
    coreFourXT.transform(coreFourX);
	
    //matrix multiplication of a multicolumn:2row matrices * 2column:multirow
    coreOneXTX.multiply(coreOneXT,coreOneX);
    coreTwoXTX.multiply(coreTwoXT,coreTwoX);
    coreThreeXTX.multiply(coreThreeXT,coreThreeX);
    coreFourXTX.multiply(coreFourXT,coreFourX);

    //matrix multiplication of a multicolumn:2row matrices * 1column:multirow
    coreOneXTY.multiply(coreOneXT,coreOneY);
    coreTwoXTY.multiply(coreTwoXT,coreTwoY);
    coreThreeXTY.multiply(coreThreeXT,coreThreeY);
    coreFourXTY.multiply(coreFourXT,coreFourY);
    
    //create the augmented matrix container
    myMatrix coreOneaugXY( coreOneXTX.getRows(), coreOneXTX.getCols() + coreOneXTY.getCols());
    myMatrix coreTwoaugXY( coreTwoXTX.getRows(), coreTwoXTX.getCols() + coreTwoXTY.getCols());
    myMatrix coreThreeaugXY( coreThreeXTX.getRows(), coreThreeXTX.getCols() + coreThreeXTY.getCols());
    myMatrix coreFouraugXY( coreFourXTX.getRows(), coreFourXTX.getCols() + coreFourXTY.getCols());
   

    //populate the augmented matrix
    coreOneaugXY.createAugmented(coreOneXTX, coreOneXTY);
    coreTwoaugXY.createAugmented(coreTwoXTX, coreTwoXTY);
    coreThreeaugXY.createAugmented(coreThreeXTX, coreThreeXTY);
    coreFouraugXY.createAugmented(coreFourXTX, coreFourXTY);

    //sort the augmented matrix
    coreOneaugXY.sortRow(); 
    coreTwoaugXY.sortRow();
    coreThreeaugXY.sortRow();
    coreFouraugXY.sortRow();

    //reduce and backsolve the matrix coreOne
    for( int i = 0; i < coreOneaugXY.getRows() ; i++){
    	coreOneaugXY.scale(i); 
    	if (i < (coreOneaugXY.getRows()-1)){
    		coreOneaugXY.reduce();
    	}
	}
	//reduce and backsolve the matrix coreTwo
    for( int i = 0; i < coreTwoaugXY.getRows() ; i++){
    	coreTwoaugXY.scale(i); 
    	if (i < (coreTwoaugXY.getRows()-1)){
    		coreTwoaugXY.reduce();
    	}
	}
	//reduce and backsolve the matrix coreThree
    for( int i = 0; i < coreThreeaugXY.getRows() ; i++){
    	coreThreeaugXY.scale(i); 
    	if (i < (coreThreeaugXY.getRows()-1)){
    		coreThreeaugXY.reduce();
    	}
	}
	//reduce and backsolve the matrix coreFour
    for( int i = 0; i < coreFouraugXY.getRows() ; i++){
    	coreFouraugXY.scale(i); 
    	if (i < (coreFouraugXY.getRows()-1)){
    		coreFouraugXY.reduce();
    	}
	}

	//backsolve the matrices
	coreOneaugXY.backSolve();
	coreTwoaugXY.backSolve();
	coreThreeaugXY.backSolve();
	coreFouraugXY.backSolve();

    // create and open an output file
    //{basename}-core-0.{txt}
	//{basename}-core-1.{txt}
	//{basename}-core-2.{txt}
	//{basename}-core-3.{txt}

	for (int i = 0; i<4 ; i++)
		arg1.pop_back();
	fstream output1, output2, output3, output4;
	output1.open(arg1 +"-core-0.txt",ios::out);
	output2.open(arg1 +"-core-1.txt",ios::out);
	output3.open(arg1 +"-core-2.txt",ios::out);
	output4.open(arg1 +"-core-3.txt",ios::out);

	//xk<=x<xk+1xk<=x<xk+1; yi=c0+c1xyi=c0+c1x ; type
    //Interpolation loops
    for (int i = 0; i < length-1; i++) {
		double Pn, yIntercept;
		Pn = (coreOneY.getXk(i+1,0)-coreOneY.getXk(i,0))/(coreOneX.getXk(i+1,1)-coreOneX.getXk(i,1));
        yIntercept = coreOneY.getXk(i,0)-Pn*coreOneX.getXk(i,1);

		output1 << coreOneX.getXk(i, 1) << "<=x<" << coreOneX.getXk(i+1,1) 
				<< "; y"	+ to_string(i) << "=" <<  yIntercept
				<< "+" << Pn << "x; interpolation" << endl;
	}
     for (int i = 0; i < length-1; i++) {
        double Pn, yIntercept;
        Pn = (coreTwoY.getXk(i+1,0)-coreTwoY.getXk(i,0))/(coreTwoX.getXk(i+1,1)-coreTwoX.getXk(i,1));
        yIntercept = coreTwoY.getXk(i,0)-Pn*coreTwoX.getXk(i,1);

        output2 << coreTwoX.getXk(i, 1) << "<=x<" << coreTwoX.getXk(i+1,1) 
        		<< "; y" + to_string(i) << "=" << yIntercept 
        		<< "+" << Pn << "x; interpolation" << endl;
    }
     for (int i = 0; i < length-1; i++) {
        double Pn, yIntercept;
        Pn = (coreThreeY.getXk(i+1,0)-coreThreeY.getXk(i,0))/(coreThreeX.getXk(i+1,1)-coreThreeX.getXk(i,1));
        yIntercept = coreThreeY.getXk(i,0)-Pn*coreThreeX.getXk(i,1);

        output3 << coreThreeX.getXk(i, 1) << "<=x<" << coreThreeX.getXk(i+1,1) 
        		<< "; y" + to_string(i) << "=" << yIntercept
        		<< "+" <<Pn << "x; interpolation" << endl;
    }
     for (int i = 0; i < length-1; i++) {
        double Pn, yIntercept;
        Pn = (coreFourY.getXk(i+1,0)-coreFourY.getXk(i,0))/(coreFourX.getXk(i+1,1)-coreFourX.getXk(i,1));
        yIntercept = coreFourY.getXk(i,0)-Pn*coreFourX.getXk(i,1);

        output4 << coreFourX.getXk(i, 1) << "<=x<" << coreFourX.getXk(i+1,1) 
        		<< "; y" + to_string(i) << "=" << yIntercept 
                << "+" << Pn << "x; interpolation" << endl;
    }

    //least squares approximations
	output1 << time.front() << "<=x<" << time.back() <<"; y=" << coreOneaugXY.getC0()
			<< "+" << coreOneaugXY.getC1()   << "x; least-squares"  << endl;
	output2 << time.front() << "<=x<" << time.back() <<"; y=" << coreTwoaugXY.getC0() 
			<< "+" << coreTwoaugXY.getC1()   << "x; least-squares"  << endl;
	output3 << time.front() << "<=x<" << time.back() <<"; y=" << coreThreeaugXY.getC0() 
			<< "+" << coreThreeaugXY.getC1() << "x; least-squares"  << endl;
	output4 << time.front() << "<=x<" << time.back() <<"; y=" << coreFouraugXY.getC0() 
			<< "+"  << coreFouraugXY.getC1()  << "x; least-squares"  << endl;

    output1.close();
    output2.close();
    output3.close();
    output4.close();

    return 0;
}


