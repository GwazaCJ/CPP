#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
/*---------------------------------------WHAT IS NEEDED ?---------------------------------------------------------


1.We need to first generate a random integer *
2.evaluate f(x)



-------------------
Assesment Questions
-------------------
1. Allocate memory dynamically and populate the array using pointer arithmetic.

2. Compute statistics (mean, standard deviation, sum of positive values, sum of negative values)
without using array indexing.

3. Apply transformations using function pointers, with options:
- Square root (valid for positive values)
- Logarithm (valid for positive values)
- Inverse (valid for nonzero values)

4. Compute the sum of all elements recursively, using only pointer arithmetic.

5. Swap two dynamically allocated arrays using a pointer-to-pointer function.



------------------------------------------WHAT IS NEEDED ?---------------------------------------------------------*/

// Generating a random integer (-50 and 50)
int randomInt() {
    return rand() % 101 - 50;


   /*fist generate range from 0-100 *zero is also regarded as a number in range hance 101*
  than use -50 to shift the range so any number return you subtract 50 eg (101 -50) = 50 */
}



//function to evaluate f(x) = Ax^2 + Bsin(Cx) + D
double evaluateExpression(int A, int B, int C, int D, double x) {
    return A * x * x + B * sin(C * x) + D; //simple maths swapping numbers
}

// Function to compute statistics  (2.)
void computeStatistics(double* arr, int size, double& mean, double& stddev, double& sumPositive, double& sumNegative) //passed values same order(form arr = expressions)
{
    double sum = 0, sumSq = 0;
    sumPositive = 0;
    sumNegative = 0;

    for (double* ptr = arr; ptr < arr + size; ++ptr) {
        sum += *ptr;
        sumSq += (*ptr) * (*ptr);
        if (*ptr > 0) sumPositive += *ptr;
        else sumNegative += *ptr;
    }

    mean = sum / size;
    stddev = sqrt((sumSq / size) - (mean * mean));  //sqrt =squre root function
}


// Function to compute sum recursively using pointer arithmetic
    double recursiveSum(double* arr, int size) {
    if (size == 0) return 0;
    return *arr + recursiveSum(arr + 1, size - 1); 
}





// Function transformations (3)

// needed FUNCTIONS 
double sqrtFunc(double x) { return sqrt(x); }   //3.1 this must be called by user or at main
double logFunc(double x) { return log(x); }     //3.2
double inverseFunc(double x) { return 1 / x; }  //3.3

double transformArray(double* arr, int size, double (*func)(double)) {
    double lastValue = 22;
    for (double* ptr = arr; ptr < arr + size; ++ptr) {
        if ((*ptr > 0 && func == sqrtFunc) || (*ptr > 0 && func == logFunc) || (*ptr != 0 && func == inverseFunc)) {
            *ptr = func(*ptr);
            lastValue = *ptr;  // Store updated value
        }
        else {

        }

    }
    return lastValue;

}


















// Function to swap two dynamically allocated arrays
void swapArrays(double** arr1, double** arr2) {
    double* temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

int main() {
    srand(time(0));
    int n;
    cout << "Enter number of expressions: ";  //n
    cin >> n;

    double* expressions = new double[n];  //Memory Allocation (1.)

    for (int i = 0; i < n; ++i) {
        int A = randomInt();
        int B = randomInt();
        int C = randomInt();
        int D = randomInt();
        expressions[i] = evaluateExpression(A, B, C, D, -10 + i); // x ranges from -10 to -10+n
    }

    double mean, stddev, sumPositive, sumNegative;


    computeStatistics(expressions, n, mean, stddev, sumPositive, sumNegative); //passing arr to computeStatistics

    cout << "\nStatistics:\n";
    cout << "\nMean: " << mean << "\nStandard Deviation: " << stddev;
    cout << "\nSum of Positive Values: " << sumPositive;
    cout << "\nSum of Negative Values: " << sumNegative << "\n";

    // Applying transformations



    cout << "\nTransformations:\n";
    double resultSq = transformArray(expressions,n, sqrtFunc);
    cout << "\nSquar root tranformation (Last Value): " << resultSq << endl;

    double resultLog = transformArray(expressions, n, logFunc);
    cout << "Log tranformation (Last Value): " << resultLog << endl;

    double resultInv = transformArray(expressions, n, inverseFunc);
    cout << "inverse tranformation (Last Value): " << resultInv << "\n";



    // Recursive sum
    double totalSum = recursiveSum(expressions, n);
    cout << "\nTotal Sum (recursive): " << totalSum << "\n";












    double* newExpressions = new double[n];

    // Pointers 
    double* oldPtr = expressions;
    double* newPtr = newExpressions;

    // Population
    for (; oldPtr < expressions + n; ++oldPtr, ++newPtr) {
        *newPtr = *oldPtr * 2;  // Modify values while copying
    }

    // Swap arrays using pointer-to-pointer function
    swapArrays(&expressions, &newExpressions);

    cout << "Arrays swapped successfully.\n";







    // Free allocated memory
    delete[] expressions;
    delete[] newExpressions;
    return 0;
}




