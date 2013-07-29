/*This analysis code is meant for a single metal-water interface. You NEED the xdatcar file from vasp calculations. Because the headers are different for different versions of vasp, you must just remove the headers and the timestep strings (like direct configuration) from the XDATCAR files. This can be done in vim by simlpy removing the header and then entering in the command ":g/"string here"/d".*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	string infile, atomname;
	double xlat, ylat, zlat, binsize;

	cout << "XYZ file:\n==> ";
	cin >> infile;
	cout << "Atom name:\n==> ";
	cin >> atomname;
	cout << "Max ranges (e.g x y z) in Angstroms:\n==> ";
	cin >> xlat >> ylat >> zlat;
	cout << "Bin size:\n==> ";
	cin >> binsize;

	ifstream input;
	input.open(infile.c_str());
	
	string content;
	vector <double> x, y, z;
	double xval, yval, zval;

	while (!input.eof())
	{
		input >> content;
		if (content == atomname)
		{
			input >> xval >> yval >> zval;
			x.push_back(xval);
			y.push_back(yval);
			z.push_back(zval);
		} 
	}
	
	// declare the bins; set the values to 0
	double xbin[int(xlat/binsize)], ybin[int(ylat/binsize)], zbin[int(zlat/binsize)];
	for (int i = 0; i < int(xlat/binsize); i ++)
	{
		xbin[i] = 0;
	}
	for (int i = 0; i < int(ylat/binsize); i ++)
        {
                ybin[i] = 0;
        }
	for (int i = 0; i < int(zlat/binsize); i ++)
        {
                zbin[i] = 0;
        }


	// write the bins
	for (int i = 0; i < x.size(); i ++)
	{
		int bin_num = x[i]/binsize;
		xbin[bin_num] ++;
	}
	for (int i = 0; i < y.size(); i ++)
        {
                int bin_num = y[i]/binsize;
                ybin[bin_num] ++;
        }
	for (int i = 0; i < z.size(); i ++)
        {
                int bin_num = z[i]/binsize;
                zbin[bin_num] ++;
        }
	

	// write out the data to the designated data files so it can be plotted
	ofstream xdens, ydens, zdens;
	xdens.open("xdensity.dat");
	ydens.open("ydensity.dat");
	zdens.open("zdensity.dat");

	for (int i = 0; i < int (xlat/binsize); i ++)
	{
		xdens << i*binsize << "\t" << xbin[i]/x.size() << endl;
		xdens << (i+1)*binsize << "\t" << xbin[i]/x.size() << endl;
	}
	for (int i = 0; i < int (ylat/binsize); i ++)
        {
                ydens << i*binsize << "\t" << ybin[i]/y.size() << endl;
                ydens << (i+1)*binsize << "\t" << ybin[i]/y.size() << endl;
        }
	for (int i = 0; i < int (zlat/binsize); i ++)
        {
                zdens << i*binsize << "\t" << zbin[i]/z.size() << endl;
                zdens << (i+1)*binsize << "\t" << zbin[i]/z.size() << endl;
        }

	xdens.close();
	ydens.close();
	zdens.close();
	input.close();
	return 0;
}		
			
		
