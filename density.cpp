/*This analysis code is meant for a single metal-water interface. YOU NEED AN XYZ FILE.*/

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
	cout << "Lattice constants (x y z) in Angstroms:\n==> ";
	cin >> xlat >> ylat >> zlat;
	cout << "Bin size:\n==> ";
	cin >> binsize;

	ifstream input;
	input.open(infile.c_str());
	
	string content;
	vector <double> x, y, z;
	double xval, yval, zval;

	// Go through the input file and extract the oxygen atoms
	//################################################
	while (!input.eof())
	{
		input >> content;
		if (content == "O")
		{
			input >> xval >> yval >> zval;
			x.push_back(xval);
			y.push_back(yval);
			z.push_back(zval);
		} 
	}
	//##############################################
	
	// Wrap the coordinates
	//#########################################
	for (int i = 0; i < x.size(); i ++)
	{
		if (x[i] > xlat)
		{
			x[i] -= xlat;
		}
		if (x[i] < 0.0)
		{
			x[i] += xlat;
		}
		if (y[i] > ylat)
                {
                        y[i] -= ylat;
                }
                if (y[i] < 0.0)
                {
                        y[i] += ylat;
                }
		if (z[i] > zlat)
                {
                        z[i] -= zlat;
                }
                if (z[i] < 0.0)
                {
                        z[i] += zlat;
                }
	}
	//#########################################
	
	// declare the bins; set the values to 0
	//###############################################################################
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
	//################################################################################

	// write the bins
	//###################################
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
	//#####################################

	// write out the data to the designated data files so it can be plotted
	//##################################################################
	ofstream xdens, ydens, zdens;
	xdens.open("xdensity.dat");
	ydens.open("ydensity.dat");
	zdens.open("zdensity.dat");

	double conversion = 18.0e-6/(6.023e23*1.0e-30); // go to from mol/A^3 to g/cc
	
	double xinc = xlat/binsize, yinc = ylat/binsize, zinc = zlat/binsize;
	double xvolume = xinc*ylat*zlat, yvolume =xlat*yinc*zlat, zvolume = xlat*ylat*zinc;

	for (int i = 0; i < int (xlat/binsize); i ++)
	{
		xdens << i*binsize << "\t" << xbin[i]*conversion/xvolume << endl;
		xdens << (i+1)*binsize << "\t" << xbin[i]*conversion/xvolume << endl;
	}
	for (int i = 0; i < int (ylat/binsize); i ++)
        {
                ydens << i*binsize << "\t" << (ybin[i]*conversion)/yvolume << endl;
                ydens << (i+1)*binsize << "\t" << ybin[i]*conversion/yvolume << endl;
        }
	for (int i = 0; i < int (zlat/binsize); i ++)
        {
                zdens << i*binsize << "\t" << zbin[i]*conversion/zvolume  << endl;
                zdens << (i+1)*binsize << "\t" << zbin[i]*conversion/zvolume << endl;
        }
	//###################################################################
	
	xdens.close();
	ydens.close();
	zdens.close();
	input.close();
	return 0;
}		
			
		
