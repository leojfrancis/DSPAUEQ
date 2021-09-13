#include <complex>
#include <vector>
#include <algorithm>
#include "../tqdm/tqdm.h"
using namespace std;

#define comp_vec vector<complex<double>>
#define d_vec vector<double>

/*
 *   Utility
 * 
 */

tqdm pbar; // tqdm is a utility

/*
Substring slicing the signal based on offset and window length
input : vector<double> x,  int inputOffset (default 0) , int WindowSize (default 512)
*/
d_vec slicer(d_vec x, int offset=0, int WINDOW=512){
   d_vec y(WINDOW);
   for(int i=offset; i<offset+WINDOW; i++)
      y[i - offset] = x[i];
   return y;
}

/*
Adds additional samples between points aka Interpolation
source : http://paulbourke.net/miscellaneous/interpolation/

input  : vector<double> in , float resample
output : new interpolated signal
*/
d_vec lerp(d_vec in,float resample){
   // need a linear interpolator
}

bool isPowerOfTwo(int n) // cuz fft really likes to simp powers of 2 values
{
   return (ceil(log2(n)) == floor(log2(n))) && (n != 0);
}

d_vec CmpMagnitude(vector<complex<double>> myFFTOUTPUT)
{
   vector<double> myFFTOUTPUT_abs;
   for (int i = 0; i < myFFTOUTPUT.size(); i++)
   {
      myFFTOUTPUT_abs.push_back(abs(myFFTOUTPUT[i]));
   }
   return myFFTOUTPUT_abs;
}

vector<double> DivByN(vector<double> myFFTOUTPUT_abs, int N = 0)
{
   if (N == 0)
   {
      N = myFFTOUTPUT_abs.size(); // sanity no zero division ;-;
   }
   vector<double> DivbyNReturn;
   for (int i = 0; i < myFFTOUTPUT_abs.size(); i++)
   {
      DivbyNReturn.push_back(myFFTOUTPUT_abs[i] / (double)N);
   }
   return DivbyNReturn;
}

vector<complex<double>> ConvertToComplex(vector<double> RealArr)
{
   vector<complex<double>> retarr;
   for (int i = 0; i < RealArr.size(); i++)
   {
      retarr.push_back(complex<double>(RealArr[i], 0)); // indx1 + j0
   }
   return retarr;
}