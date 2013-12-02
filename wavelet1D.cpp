#include <stdio.h>
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <math.h>
#include <fstream>

//numerical recipes stuffs
#include "nr3.h"
#include "wavelet.h"
using namespace std;

double randDouble(double low, double high)
{	
	double temp;
	temp = ((double) rand() / (static_cast<double>(RAND_MAX) + 1.0))* (high - low) + low;
	return temp;
}

int main() {
	int i,n=4, N=256;
	int power=1;
	VecDoub x(N);
	VecDoub xoriginal(N);
	VecDoub x2(N);
	double twopi=8.0*atan(1.0);
	srand((unsigned) time(0));

	//create data set
	for(ind = 0 ; ind < N ; ind++){
		//x[i]=exp(-pow((i-N/2.0),2));
		//x[i]=pow((double) i,power);
		//    x[i]=5.0;
		//x[i]=sin(2.0*3.14159*i/(N/2.0))+randDouble(-0.1,0.1);    //iI used threhsold of 0.2 in the notes
		//    x[i]=(0*sin(twopi*i/N*2.0)+sin(5.0*twopi*i/N*2.0));//+sin(10.0*twopi*i/N*2.0))/3.0;
		//x[i]=10.0;
		//    x[i]=sin(2.0*3.14159*i/(N/2.0))+10.0;
		//cout << i << " " << x[i] << endl;
		//if(i<N/2)  x[i]=sin(10*twopi*i/N*2.0);
		//    if(i>N/2-1) x[i]=sin(5.0*twopi*i/N*2.0);//+sin(10.0*twopi*i/N*2.0))/3.0;
		//    x[i]=sin(twopi*i/N);//+sin(10.0*twopi*i/N*2.0))/3.0;

		int i = ind * 2 * twopi / N;

		// first one
		x[i] = ( sin(2*i/N) + sin(4*i/N) + sin(5*i/(N*2)) ) / 3;
		// second one
		// if (i < twopi/2) x[i] = sin(2*i/N);
		// else (i < twopi) x[i] = sin(4*i/N);
		// else sin(5*i/N);

		xoriginal[i]=x[i]; //here I keep a copy of the original data since WT replaces x[:]
	}

	//file with data
	ofstream datain;
	datain.open("input.dat");
	for(i=0;i<N;i++) datain << x[i] << endl;
	datain.close();


	//this this the way numerical recipes works

	//daubechies "4"
	//  Daub4 MyWave;
	//for daubechies 4, we would use following line
	//  MyWave.filt(x,N,-1);

	//daubechies "20"
	Daubs Wave2(20);

	//this is the way daubechies is computed (note the +1 for "forward")
	wt1(x,+1,Wave2);


	//filter (this example simply removes all the WT data in the first half of the vector)
	double threshold=0.1;
	int nnz=0;
	for(int i=0;i<N;i++){
		//      if(abs(x[i])<threshold) {
		if(i<N/2) {
			x2[i]=0.0;
		}
		else
			{
				nnz++;
				x2[i]=x[i];
			}
    
	}
	cout << "Threshold used =" << threshold <<endl;
	cout << "Number of non-zero coefficients =" << nnz << endl;
	//output filtered data
	ofstream dataout;
	dataout.open("waveout.dat");
	for(i=0;i<N;i++) dataout << (abs(x[i]))/sqrt(0.5*N) << " " << abs(x2[i])/sqrt(0.5*N) << endl;
	dataout.close();

	//for daubechies 4, we would use following line
	//  MyWave.filt(x,N,-1);

	//this is the way daubechies is computed (note the -1 for "backward")
	wt1(x2,-1,Wave2);

	//output the data
	dataout.open("output2.dat");
	for(i=0;i<N;i++) dataout << abs(x2[i]-xoriginal[i]) << " " << x2[i] << endl;
	dataout.close();

}
