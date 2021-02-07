#include "myMatrix.h"
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>

/**
*Default Constructor.
*/
myMatrix::myMatrix()
{
	rows = 0;
	cols = 0;
	nMatrix.resize(1);

	std::cout << nMatrix[0][0];
}

/**
*Alternative constructor with two arguments.
*@param x the number of rows.
*@param y the number of columns.
*/
myMatrix::myMatrix(int x, int y)
{
	rows = x;
	cols = y;
	nMatrix.resize(rows);
	for (int i = 0; i < rows; i++) { 
  
        // declare  the i-th row to size of column 
        nMatrix[i] = std::vector<double>(cols); 
        for (int j = 0; j < cols; j++) {
            nMatrix[i][j] = 0;
            } 
    } 
}

/**
*Destructor
*/
myMatrix::~myMatrix()
{

}

/**
*Add data to the j column.
*@param j is the the column number.
*@param data is the list of values to be added.
*/
void myMatrix::addContent(int j, std::list<double> data)
{
	std::list<double>::iterator titr;
	titr = data.begin();
	int i = 0;
	while( titr != data.end() ) {
		nMatrix[i][j] = *titr;
		titr++;
		i++;
	}
}

/**
* Perform a matrix transform.
*@param M is the original matrix.
*/
void myMatrix::transform(myMatrix M)
{
for (int i = 0; i < cols; i++)
    {
    	for (int j = 0; j < rows; j++)
    	{
    		nMatrix[j][i] = M.nMatrix[i][j];
    	}
    }
}
	
/**
* Dot product of two matrices (order matters.)
*@param M the first matrix.
*@param N the matirx to be multiplied with M.
*/
void myMatrix::multiply(myMatrix M, myMatrix N)
{
	for (int i = 0; i < M.getRows(); i++)
    	{
    		for (int j = 0; j < N.getCols(); j++)
    		{
    			for (int k =0; k < N.getRows(); k++)
    			{
    				nMatrix[i][j] += M.nMatrix[i][k] * N.nMatrix[k][j];
     			}
     			if (nMatrix[i][j] < 1 && nMatrix[i][j] > -1){
						nMatrix[i][j] = 0;}
    		}
    	}
}

/**
*Append two matrices together.
*@param M the left matrix.
*@param N the rigth matrix.
*/
void myMatrix::createAugmented(myMatrix M, myMatrix N)
{
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (j < cols-1){
				nMatrix[i][j] = M.nMatrix[i][j];
			}
			else{
				nMatrix[i][j] = N.nMatrix[i][0];
			}
		}
	}
}

/**
*Sort rows from least to greatest in the first column.
*/
void myMatrix::sortRow()
{
	double temp;
    for (int i = 0; i < rows-1; i++){
        for (int j = i+1; j < rows; j++){
        	if (nMatrix[i][0] < nMatrix[j][0]){
            	for (int k=0; k < cols; k++){
                	temp      = nMatrix[i][k];
                	nMatrix[i][k] = nMatrix[j][k];
                	nMatrix[j][k] = temp;
               	}		
        	}
        }
    }
}	

/**
*Scale the first row so the first number is 1.
*@param x is the row to be scaled. 
*/
void myMatrix::scale(int x)
{
	 //set 0,0 to 1 and scale the row accordingly. scale row 0 so the first field is 1.
    double temp;
    	int i = x;
    	for (int j = x; j < cols; j++) {
    		if (i == j){
    			temp = nMatrix[i][j];
    			nMatrix[i][j] = 1;
    		}
    		else{
    			nMatrix[i][j] = nMatrix[i][j] / temp;
    		}
     	}
   }

/**
*Reduce the row so the first number is 0.
*/
void myMatrix::reduce(){
    //set 1,0 to 0 and subtract r1 * 1,0s value from r2
    double temp;
    for (int j = 1; j < rows; j++){
    	for (int k = 0; k < cols; k++) {
    		if (j > k) {
    			temp = nMatrix[j][k];
    			nMatrix[j][k] = 0;
    		}
    		else{
    			nMatrix[j][k] = nMatrix[j][k] - (temp * nMatrix[j-1][k]);
    		}
    	}
    }
}

/**
*Backsolve for the C0 value.
*/
void myMatrix::backSolve(){ //back solve
	double temp;
    for (int i = 0; i < rows-1; i++){
    	for (int j = 1; j < cols; j++){
    		if (j == 1){
    			temp = nMatrix[i][j];
    			nMatrix[i][j] = 0;
    		}
    		else {
    			nMatrix[i][j] = nMatrix[i][j] - (temp * nMatrix[i+1][j]);
    		}
    	}
	}
}

/**
*Display the matrix.
*@param &outs a constant output variable for use in output stream, cout, or cerr.
*/
void myMatrix::Display(std::ostream &outs) const
{
    for (int i = 0; i < rows; i++)
    {
    	for (int j = 0; j < cols; j++)
    	{
         	outs << std::right << std::setw(3) << nMatrix[i][j] << " ";
         }
         outs << std::endl;
    }
}
