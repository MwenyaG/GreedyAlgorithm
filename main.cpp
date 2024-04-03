#include <iostream>
#include <iomanip> //for using the set precision function
#include <cmath> //this is used for mathematical calculations
#include <chrono>//this is used to get time in microseconds

using namespace std;
using namespace chrono;

//Initialization of myArray as array
//Initialization of leftPiv for elements at the left side of array before pivot
//Initialization of rightPiv for elements at the right side of array before pivot
//Initialization of pivot1 to be left pivot
int partition(int *myArray, int leftPiv, int rightPiv, int *pivot1);

//declaration of swap function
void swap (int *x, int *y)
{
    int temp = *x; //setting x into the temp
    *x = *y; //x is then set to y
    *y = temp; //temp is now replaced by y
}


//declaration of QuickSort function
//this function will implement 2(dual) pivots
void Quicksort(int *myArray, int leftPiv, int rightPiv)
{
    if (leftPiv < rightPiv)// to check if the array is empty at initial stage
    {//intiliazing pivot1 and pivot 2 as left pivot and right pivot respectively
       int pivot1,
           pivot2;

           pivot2 = partition(myArray,leftPiv,rightPiv,&pivot1);
           Quicksort(myArray,leftPiv,pivot1-1);
           Quicksort(myArray,pivot1 + 1,pivot2 - 1);
           Quicksort(myArray,pivot2 + 1,rightPiv);
    }
}

int partition(int *myArray, int leftPiv, int rightPiv, int *pivot1)
{
    if (myArray[leftPiv] > myArray[rightPiv])
        swap(&myArray[leftPiv], &myArray[rightPiv]);
    //a is initialized to record numbers less than pivot
    //b is initialized to record numbers more than pivot
    //k is initialized as a temp
    //leftOfPiv is for number left of the pivot
    //rightOfPiv is for numbers right of the pivot
    int a,b,k,leftOfPiv,rightOfPiv;
    a = leftPiv + 1;
    b = rightPiv - 1, k = leftPiv + 1, leftOfPiv = myArray[leftPiv], rightOfPiv = myArray[rightPiv];
    while (k <= b)
        {
        // if elements are less than the left pivot
        if (myArray[k] < leftOfPiv) {
            swap(&myArray[k], &myArray[a]);
            a++;
        }

        // if elements are greater than or equal to the right pivot
        else if (myArray[k] >= rightOfPiv) {
            while (myArray[b] > rightOfPiv && k < b)
               b--;
            swap(&myArray[k], &myArray[b]);
            b--;
            if (myArray[k] < leftOfPiv) {
                swap(&myArray[k], &myArray[a]);
                a++;
            }
        }
        k++;
    }
    a--;
    b++;

    // bring pivots to their appropriate positions.
    swap(&myArray[leftPiv], &myArray[a]);
    swap(&myArray[rightPiv], &myArray[b]);

    *pivot1 = a; //to return the indices of the pivots

    return b;
}

int main()
{
    int number; //initialized number of parcel IDs
    char selection1, //initialized selection 1 and 2 for menu
         selection2;
    double x;



    cout << "Please, enter the number parcel IDs you want to generate: ";
    cin>>number; //to enter number of Parcel IDs, to generate
    cout<<"____________________________________________________________"<<endl;
    cout << "\t\t\t****Menu****"<<endl;
    cout<<"____________________________________________________________"<<endl;
    cout << "please Enter ('y' or 'n') for preferred arrangement"<<endl;
    cout << "Option 1: View the Unsorted Parcels: (y or n)";
    cin >> selection1;
    cout << "Option 2: View the Sorted Parcels: (y or n):";
    cin>> selection2;
    cout << "\n";

    int *parcel; //initialized parcel with pointer
    double *orderPrice; //initialized order price with pointer

    parcel=new int[number]; //implementation of heap for generation of large input numbers for parcels
    orderPrice= new double[number]; //implementation of heap for generation of large input numbers for order price

    double total;//to initialize total
    auto timeStart = high_resolution_clock::now(); //function for recording time
                                                    //time is recorded for sorting algorithm

    for (int i=0; i<number; i++)
    {
                                        //rand is used for printing random numbers
        parcel[i] = (rand()%9999); // parcels will be printed random numbers following the format 9999..

        double price=(rand()%999)/2.5;  //prices will be printed following the format RM999.99
        orderPrice[i]=price; //price is set to order price in array
        total=price;
    }

    //two selections are made in menu
    //condition for first selection
    if (selection1 == 'y') //if selection is equal to 'y'
    {
        cout << "The Unsorted list of parcels is : ";
        for(int i=0;i<number;i++)
        {
            cout<<"\t\t\t";
            cout << parcel[i]; //to print the random parcel number
        }
        cout<<endl;
        cout << "\nThe total cost of parcels in RM: " << total; //to print  total cost
    }
    cout << "\n" <<endl;
    Quicksort(parcel,0,number-1); //Quicksort is called for sorted list
    auto timeStop = high_resolution_clock::now(); //time is concluded after Quicksort
    auto overallTime = duration_cast<microseconds>(timeStop - timeStart); // the function to get time in microseconds

    if(selection2 == 'y')
    {
        cout << "The Sorted list of parcels is: ";
        for(int i=0;i<number;i++)
        {
            cout<<"\t\t\t";
            cout << parcel[i];//to print the generated parcels
        }
        cout<<endl;
        cout << "\nTotal cost of Parcels in RM: " <<total; //to print total price of parcels
    }
    cout<<fixed<<setprecision(5);
    cout <<"\n\nTotal time taken to Sort : "<<overallTime.count()<< " microseconds\n"<<endl;
}

