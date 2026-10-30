/**

this is a simple implementation of simplex method in c++.

this code for just 2 variables and 2 constraints.

it can be extended to n variables and m constraints.

it is a work in progress and will be updated soon.

I work on it as a test project for my own learning and understanding of the simplex method.



vector<double*> tableau is used to store the tableau of the simplex method.

the first row of the tableau is used to store the objective function coefficients.

the second and third rows are used to store the constraint coefficients and the right-hand side values.

the fourth row is used to store Zj.

the fifth row is used to store Cj-Zj.

the sixth row is used to store the basic variable values.

**/

#include <iostream>

#include <string>

#include <vector>

using namespace std;

void simplexInput(vector<double*>& tableau){

    for(int i=0;i<6;i++){

        tableau.push_back(new double[5]);

    }

    for(int i=0;i<6;i++){

        for(int j=0;j<5;j++){

            tableau[i][j]=0;

        }

    }

    cout<<"Enter the objective variables Coefficient values: "<<endl;

    for(int i=0;i<4;i++){

        cin>>tableau[0][i];

    }

    cout<<"Enter the first constraint values: "<<endl;

    for(int j=0;j<5;j++){

        cin>>tableau[1][j];

    }

    cout<<"Enter the second constraint values: "<<endl;

    for(int j=0;j<5;j++){

        cin>>tableau[2][j];

    }

    for(int i=0;i<4;i++){

        tableau[4][i]=tableau[0][i]-tableau[3][i];

    }

    cout<<endl;

    for(int i=0;i<6;i++){

        for(int j=0;j<5;j++){

            cout<<tableau[i][j]<<" ";

        }

        cout<<endl;

    }

    cout<<endl;



}

void simplexLogic(vector<double*> &tableau){

bool isOptimal = false ;

int pivotColumn = 0 , pivotRow = 0 , otherRow = 0,newBasic = 0;

double firstRatio = 0 , secondRatio = 0,temp = 0, pivotNumber = 0, correspondingOld = 0;

    while(!isOptimal){

        temp=-1;

        for(int j=0;j<4;j++){

            if(temp<tableau[4][j] && tableau[4][j]>0){

                temp=tableau[4][j];

                pivotColumn=j;

            }

        }

        firstRatio=tableau[1][4]/tableau[1][pivotColumn];

        secondRatio=tableau[2][4]/tableau[2][pivotColumn];

        pivotRow=(firstRatio<secondRatio?1:2);

        pivotNumber=tableau[pivotRow][pivotColumn];

        otherRow=(pivotRow==1?2:1);

        correspondingOld=tableau[otherRow][pivotColumn];

        tableau[5][pivotRow-1]=tableau[0][pivotColumn];

        for(int j=0;j<5;j++){

            tableau[pivotRow][j]/=pivotNumber;

        }

        for(int j=0;j<5;j++){

            tableau[otherRow][j]-=(correspondingOld*tableau[pivotRow][j]);

        }

        //calculate Zj

        for(int j=0;j<5;j++){

            tableau[3][j]=0;

            for(int i= 1;i<=2;i++){

                tableau[3][j]+=tableau[i][j]*tableau[5][i-1];

            }

        }

        //calculate Cj-Zj

        for(int j=0;j<4;j++){

            tableau[4][j]=tableau[0][j]-tableau[3][j];

        }

       

        for(int i=0;i<6;i++){

            for(int j=0;j<5;j++){

                cout<<tableau[i][j]<<" ";

            }

            cout<<endl;

        }

        cout<<endl;

        isOptimal=true;

        for(int j=0;j<4;j++){

            if(tableau[4][j]>0){

                isOptimal=false;

                break;

            }

        }

    }

}

int main(){

    string s;

    vector<double*> tableau;

    simplexInput(tableau);

    simplexLogic(tableau);

    cout<<"done!\nEnter 1 to exit\n";

    cin>>s;

    return 0;

} 

