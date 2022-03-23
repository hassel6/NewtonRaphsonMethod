#include <iostream>
#include <cmath>

class node {
public:

    double dCoeff;
    node * next;

    node *setFunc( node * root, double myCoeffs[], int sizeArr );

    double funcF( node * root, double dX );
    double funcDerivF( node * root, double dX );

    void funcNewtonRaphson( node * func, double x0, int iter );
};

node* setFunc( node * root, double myCoeffs[], int sizeArr ) {
    int k = 0;
    while( sizeArr > k ) {
        if( root == NULL ) {
            root = new node;
            root -> next = NULL;
            root -> dCoeff = myCoeffs[ k ];
            //return root;
        }
        else {
            node * temp = new node, * iter = root;
            while( iter -> next != NULL ) {
                iter = iter -> next;
            }
            temp -> next = iter -> next;
            iter -> next = temp;
            temp -> dCoeff = myCoeffs[ k ];
        }
        k++;
    }
    return root;
}

double node::funcF( node * root, double dX ) {
    double result = 0.0;
    double x0 = 0.0;
    int i = 0;
    node * iter = root;

    while( iter != NULL ) {
        x0 = iter -> dCoeff;
        result = result + ( pow( dX, i++ )*x0 );
        iter = iter -> next;
    }
    std::cout << "F(" << dX << ") = " << result << std::endl;
    return (double)result;
}

double node::funcDerivF( node * root, double dX ){
    double result = 0.0;
    double x0 = 0.0;
    int i = 0;
    node * iter = root -> next;

    while( iter != NULL ) {
        x0 = iter -> dCoeff;
        result = result + ( x0 * (i+1) * pow( dX, i ) );
        iter = iter -> next;
        i++;
    }
    std::cout << "derivF(" << dX << ") = " << result << std::endl;
    return (double)result;
}

void node::funcNewtonRaphson( node * func, double x0, int iter ) {
    double x1 = 0.0;
    int j = 0;
    while( j <= iter ) {
        x1 = x0 - funcF( func, x0 ) / funcDerivF( func, x0 );
        x0 = x1;
        std::cout << j << ". Iterator = " << x1 << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        j++;
    }
}

int main() {

    node * function1 = NULL;

    // coefficient count
    const int coeffs = 4;
    // first value
    const double x0 = 12.0;
    // iterations
    const int iter = 5;

    // index order = c1*x^0  c2*x^1  c3*x^2  c4*x^3 ... cn*x^n+1
    double X[ coeffs ] = { 22.0, -16.0, -5.0, 1.0 };
    // set function
    function1 = setFunc( function1, X, coeffs );

    /* Params
    -1. param = node
    -2. param = first value
    -3. param = iteration count*/
    function1->funcNewtonRaphson( function1, x0, iter );
}
