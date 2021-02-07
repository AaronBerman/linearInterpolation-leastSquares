#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <list>
#include <vector>
#include <iostream>

/**
*matrix solver class
*/
class myMatrix 
{
public:

	myMatrix();
	myMatrix(int x, int y);
	virtual ~myMatrix();

	/**
	* @return the number of rows in the vector.
	*/
	int getRows() const {return rows;}
	
	/**
	* @return the number of columns in the vector.
	*/
	int getCols() const {return cols;}

	/**
	* @return the C0 term after all computations have been completed.
	*/
	double getC0() const {return nMatrix[0][2];}

	/**
	* @return the C1 term after all the computations have been completed.
	*/
	double getC1() const {return nMatrix[1][2];}

	/**
	* @param n is a value for a row in the matrix.
	* @param m is a value for a column in the matrix.
	* @return the value stored in the matrix.
	*/
	double getXk(int n, int m) const {return nMatrix[n][m];}
	
	/**
	* @return 1.
	*/
	double getYi() {return 1;}

	/**
	* @param x value to set the number of rows.
	*/
	void setRows(int x) {rows = x;}

	/**
	* @param y values to set the number of columns.
	*/
	void setCols(int y) {cols = y;}

	void addContent(int i, std::list<double> data);
	void transform(myMatrix M);
	void multiply(myMatrix M, myMatrix N);
	void createAugmented(myMatrix M, myMatrix N);
	void sortRow();
	void scale(int x);
	void reduce();
	void backSolve();
	void Display(std::ostream &outs) const;

private:
	int rows;
	int cols;
	std::vector<std::vector<double> > nMatrix;

};
std::ostream& operator<<(std::ostream &outs, const myMatrix &prt);
//--------------------------------------------------------------------------
/**
* Inline operator overload for the display function.
*/
inline
std::ostream& operator<<(std::ostream &outs, const myMatrix &prt)
{
    prt.Display(outs);

    return outs;
}
#endif