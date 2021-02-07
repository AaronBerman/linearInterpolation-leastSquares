#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include "main.h"

using namespace std;

void printMyMatrix(const vector<std::vector<double>>& M);

int main(int argc, char** argv){
	
	//Error handling for file execution and usage details
	 if(argc != 2){
        cerr << "Usage: " << argv[0] << " matrix_file" << endl;
        return 1;
    }
    //Open matrix file
    ifstream inFile(argv[1]);
    if(!inFile){
        cerr << "Error: " << argv[1] << " could not be opened." << endl;
        return 2;
    }


    //Read in x and f(x) from a file
    list<double> x, fx;
    list<double>::iterator itr;
    int a, b, length;

    while (inFile >> a >> b){
        x.push_back(a);
        fx.push_back(b);
    }
    length = fx.size();
    inFile.close();

    //create a list of pi0 equal in length to x and f(x) 
    list<double> listPi0;
    const double pi0 = 1.0;
    for (int i = 0; i < length; i++){
    	listPi0.push_back(pi0);
    }

    // create and open an output file
    fstream output;
	output.open("data.txt",ios::out);
    
    //create matrix containers and populate from the lists
    myMatrix X(length, 2);
    myMatrix Y(length, 1);

    X.addContent(0, listPi0);
    X.addContent(1, x);
    Y.addContent(0, fx);

    //Write outputs to a file wih labels
    output << "X matrix"<< endl;
    X.Display(output);
    output << "\nY matrix"<< endl;
    Y.Display(output);

    //create the transform and multiplication matrix containers
    myMatrix XT(X.getCols(), X.getRows());
    myMatrix XTX(XT.getRows(), X.getCols());
    myMatrix XTY(XT.getRows(), Y.getCols()); 

    //change X from rows:columns to columns:rows
    XT.transform(X);
	output << "\nXT matrix"<< endl;
    XT.Display(output);

    //matrix multiplication of a multicolumn:2row matrices * 2column:multirow
    XTX.multiply(XT,X);
    output << "\nXTX matrix"<< endl;
    XTX.Display(output);

    //matrix multiplication of a multicolumn:2row matrices * 1column:multirow
    XTY.multiply(XT,Y);
	output << "\nXTY matrix"<< endl;
    XTY.Display(output);
    
    //create the augmented matrix container
    myMatrix augXY( XTX.getRows(), XTX.getCols() + XTY.getCols());

    //populate the augmented matrix
    augXY.createAugmented(XTX, XTY);
	output << "\nAugmented XTX|XTY matrix"<<endl;
    augXY.Display(output);

    //sort the augmented matrix
    augXY.sortRow();    
    output << "\nAugmented XTX|XTY matrix (sorted)"<<endl;
    augXY.Display(output);

    //reduce and backsolve the matrix
    for( int i = 0; i < augXY.getRows() ; i++){
    	augXY.scale(i);  
    	output << "\nAugmented XTX|XTY matrix (sorted and reduced) " + to_string(i+1) << " times." <<endl;
    	augXY.Display(output);
    	if (i < (augXY.getRows()-1)){
    		augXY.reduce();
    	}
	}

	augXY.backSolve();
	output << "\nAugmented XTX|XTY matrix (sorted, reduced, and backsolved)"<<endl;
	augXY.Display(output);

    //output the Approximation
    output << "\n"<<  "\nLeast squares approximation"<< endl;
    output << "Phi Hat = " << augXY.getC0() << " + " << augXY.getC1() << "x" << endl;
    output.close();

    cout << "Phi Hat = " << augXY.getC0() << " + " << augXY.getC1() << "x" << endl;
	return 0;
}

