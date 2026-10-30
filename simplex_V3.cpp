/**
this is a simple implementation of simplex method in c++.
this code for just primal simplex Method.
it extended to n variables and m constraints.
it is a work in progress and will be updated.
I work on it as a test project for my own learning and understanding of the simplex method.

vector<double*> tableau is used to store the tableau of the simplex method.
the first row of the tableau is used to store the objective function coefficients.
the inner constrain number of rows are used to store the constraint coefficients and the right-hand side values.
the before last row is used to store Zj.
the last row is used to store Cj-Zj.
A new vector is used to store the basic variable places from the objective row.
**/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class SimplexSolver{
    vector<double*> tableau;
    vector<int> basic;
    int variablesNo , constrainsNo;
    int rows , columns;
    int objective;
    public:
    SimplexSolver(int noOfVariables , int noOfConstrains){
        variablesNo = noOfVariables;
        constrainsNo = noOfConstrains;
        rows = noOfConstrains + 3;
        objective = noOfVariables + noOfConstrains;
        columns = objective +1;
    for(int i=0;i<rows;i++){
        tableau.push_back(new double[columns]);
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            tableau[i][j]=0;
        }
    }
    for(int i=0;i<constrainsNo;i++){
        basic.push_back(noOfVariables+i);
    }
}
~SimplexSolver(){
    for(int i=0;i<rows;i++){
        delete[] tableau[i];
    }
}
void inputData(){
cout<<"Enter the objective variables Coefficient values: "<<endl;
    for(int i=0;i<objective;i++){
        cin>>tableau[0][i];
    }
    for(int i=1;i<=constrainsNo;i++){
    cout<<"Enter the constraint "<<i<<" values: "<<endl;
    for(int j=0;j<columns;j++){
        cin>>tableau[i][j];
    }
}
    for(int i=0;i<objective;i++){
        tableau[rows-1][i]=tableau[0][i]-tableau[rows-2][i];
    }
    cout<<endl;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            cout<<tableau[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void solve(){
bool isOptimal = false ;
int pivotColumn = 0 , pivotRow = 0 ;
double temp = 0, pivotNumber = 0;
vector<double> pivotRowV,pivotColumnV,ratio;
    while(!isOptimal){
        //checks pivot column
        temp=-INFINITY;
        for(int j=0;j<objective;j++){
            if(temp<tableau[rows-1][j] && tableau[rows-1][j]>0){
                temp=tableau[rows-1][j];
                pivotColumn=j;
            }
        }
        //checks pivot row
        temp= INFINITY;
        ratio.clear();
        for(int i = 1;i<=constrainsNo;i++){
            if(tableau[i][pivotColumn]>0){
            double currentRatio =tableau[i][columns-1]/tableau[i][pivotColumn];
            ratio.push_back(currentRatio);
            if(temp>currentRatio){
                temp=currentRatio;
                pivotRow=i;
            }}
            else{
                ratio.push_back(-1);
            }
        }
        //rewrite pivot columns and pivot rows for some logic
        pivotRowV.clear();
        pivotNumber=tableau[pivotRow][pivotColumn];
        for(int i=0;i<columns;i++){
            pivotRowV.push_back(tableau[pivotRow][i]);
        }
        pivotColumnV.clear();
        for(int i =1;i<=constrainsNo;i++){
            pivotColumnV.push_back(tableau[i][pivotColumn]);
        }
        //the new iteration pivot row
        for(int j=0;j<columns;j++){
            tableau[pivotRow][j]/=pivotNumber;
            pivotRowV[j]=tableau[pivotRow][j];
        }
        //calculate all rows in the second iteration
        for(int i=1;i<=constrainsNo;i++){
                double correspondingOld = tableau[i][pivotColumn];
            for(int j=0;j<columns;j++){
                if(i!=pivotRow){
                    tableau[i][j]-=(correspondingOld*tableau[pivotRow][j]);
                }
            }
        }
        //change the basic variable
        basic[pivotRow-1]=pivotColumn;
        //calculate Zj
        for(int j=0;j<columns;j++){
            tableau[rows-2][j]=0;
            for(int i= 1;i<=constrainsNo;i++){
                tableau[rows-2][j]+=tableau[i][j]*tableau[0][basic[i-1]];
            }
        }
        //calculate Cj-Zj
        for(int j=0;j<columns-1;j++){
            tableau[rows-1][j]=tableau[0][j]-tableau[rows-2][j];
        }
        
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                cout<<tableau[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        isOptimal=true;
        for(int j=0;j<objective;j++){
            if(tableau[rows-1][j]>0){
                isOptimal=false;
                break;
            }
        }
    }
}
void printResult() {
    cout << "\n===============================" << endl;
    cout << "       OPTIMAL SOLUTION        " << endl;
    cout << "===============================" << endl;
    
    // Create a vector to store the value of every variable (size equals 'objective')
    vector<double> varValues(objective, 0.0);
    
    // Map basic variables to their RHS values and explicitly check their type
    for(int i = 0; i < constrainsNo; i++) {
        int varIndex = basic[i];
        
        if (varIndex < objective) {
            varValues[varIndex] = tableau[i + 1][columns - 1];
        }
    }
    
    // Print original decision variables
    cout << "Decision Variables:" << endl;
    for(int i = 0; i < variablesNo; i++) {
        cout << "  x" << (i + 1) << " = " << varValues[i] << endl;
    }
    
    // Print slack/surplus variables
    cout << "\nSlack/Surplus Variables:" << endl;
    for(int i = variablesNo; i < objective; i++) {
        cout << "  s" << (i - variablesNo + 1) << " = " << varValues[i] << endl;
    }
    
    // Print optimal objective value (Z) from the Zj row's RHS
    double optimalZ = tableau[rows - 2][columns - 1];
    cout << "\nOptimal Objective Value (Z) = " << optimalZ << endl;
    cout << "===============================" << endl;
}
};
int main(){
    string s;
    int varNum,consNum;
    cout<<"Enter Number of variables and constrains \n";
    cin>>varNum>>consNum;
    SimplexSolver simplexSolver(varNum,consNum);
    simplexSolver.inputData();
    simplexSolver.solve();
    simplexSolver.printResult();
    cout<<"done!\nEnter 1 to exit\n";
    cin>>s;
    return 0;
}