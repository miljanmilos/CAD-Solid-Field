#include <igl/colon.h>
#include <igl/harmonic.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <igl/opengl/glfw/Viewer.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "tutorial_shared_path.h"

using namespace Eigen;
using namespace std;

MatrixXd V, U, D, Tmp;
MatrixXi F;
VectorXi b;
VectorXi zoneIndices;
int k = 2;

void readDisplacements(string file_path)
{
	ifstream file;
	string line;
	int nDisplacements;
	file.open(file_path);
	file >> nDisplacements; 
	b.resize(nDisplacements);
	U.resize(nDisplacements, 3);
	for (int i = 0; i < nDisplacements; i++)
		file >> b(i) >> U(i, 0) >> U(i, 1) >> U(i, 2);
	file.close();
}

void readZone(string file_path)
{
	ifstream file;
	string line;
	int nZone;
	file.open(file_path);
	file >> nZone;
	zoneIndices.resize(nZone);
	for (int i = 0; i < nZone; i++) file >> zoneIndices(i);
	file.close(); 
}

void writeDisplacements(string file_path)
{
	FILE* fOut = fopen(file_path.c_str(), "w");
	int nZone = zoneIndices.size();
	fprintf(fOut, "%5u\n", nZone);
	for (int i = 0; i < nZone; i++)
		{
			double tol = 1.e-10;
			double distx = D(zoneIndices(i), 0);
			double disty = D(zoneIndices(i), 1);
			double distz = D(zoneIndices(i), 2);
			fprintf(fOut, "%10.2e%10.2e%10.2e\n", fabs(distx) < tol ? 0.0 : distx,
												  fabs(disty) < tol ? 0.0 : disty, 
												  fabs(distz) < tol ? 0.0 : distz);
		}
	fclose(fOut);
}

int main(int argc, char* argv[])
{
	int nSteps = atoi(argv[1]);
	char buffer[5];
	string strbuffer;
	igl::readOBJ("Model.obj", V, F);
	readZone("zone.txt");
	for (int i = 1; i <= nSteps; i++)
	{
		readDisplacements("PrescribedDisplacements" + to_string(i) + ".txt");
		igl::harmonic(V, F, b, U, k, D);
		sprintf(buffer, "%04d", i);
		strbuffer = buffer; 
		writeDisplacements("DISPL"+ strbuffer +".DAT");
		Tmp = V + D;
		igl::writeOBJ("result" + to_string(i) + ".obj", Tmp, F);
	}
}
