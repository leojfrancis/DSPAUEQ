#include <complex>
#include <vector>
double pi = 4 * atan(1.0);
using namespace std;

bool isPowerOfTwo(int n)
{
    return (ceil(log2(n)) == floor(log2(n))) && (n != 0);
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

vector<complex<double>> FFT(vector<complex<double>> arr) // needs 2^n no of samples input!!
{
    int n = arr.size();
    if (isPowerOfTwo(n) == false)
    {
        cout << "Error: Input size is not a power of 2 Padding Zeros" << endl;
        for (int p = 0; p < ceil(log2(n)) - n; p++)
        {
            arr.push_back(complex<double>(0, 0));
        }
    }
    if (n == 1)
    {
        return arr;
    }
    // split into even and odd subsums
    int half = n / 2;
    vector<complex<double>> Xeven(half, 0);
    vector<complex<double>> Xodd(half, 0);

    for (int i = 0; i != half; i++)
    {
        Xeven[i] = arr[2 * i];
        Xodd[i] = arr[2 * i + 1];
    }
    vector<complex<double>> Feven(half, 0);
    Feven = FFT(Xeven);
    vector<complex<double>> Fodd(half, 0);
    Fodd = FFT(Xodd);
    // need a single sample at end
    vector<complex<double>> freqbin(n, 0);
    for (int k = 0; k != half; k++)
    {
        complex<double> cmpexp = polar(1.0, -2 * pi * k / n) * Fodd[k];
        freqbin[k] = Feven[k] + cmpexp;
        freqbin[k + half] = Feven[k] - cmpexp;
    }
    return freqbin;
}

vector<complex<double>> FFT_OLD(vector<complex<double>> arr)
{
    int n = arr.size();
    if (n == 1)
        return arr;
    vector<complex<double>> even = FFT(vector<complex<double>>(arr.begin(), arr.begin() + n / 2));
    vector<complex<double>> odd = FFT(vector<complex<double>>(arr.begin() + n / 2, arr.end()));
    vector<complex<double>> retarr;
    for (int k = 0; k < n / 2; k++)
    {
        complex<double> t = polar(1.0, -2 * pi * k / n) * odd[k];
        retarr.push_back(even[k] + t);
        retarr.push_back(even[k] - t);
    }
    return retarr;
}
