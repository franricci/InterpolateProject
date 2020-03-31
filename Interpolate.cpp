#include<iostream>
#include<fstream>
#define _USE_MATH_DEFINES
#include<cmath>
#include "CsvReader.h"
#include "Types.h"
#include<cstring>
#include "CellDiv.h"
#include "InterpolateMLS.h"
#include "cblas.h"


int main(){

	Csv_Reader bho("PartFluid_0000.csv");

	unsigned Np= bho.numberOfLines();
	double mass=1.0/(Np);
	tfloat3 *xyz = new tfloat3[Np];
	tfloat5 *asd = new tfloat5[Np];
	bho.read_file(xyz,asd);
	unsigned Nc=100;
	unsigned hdp=2;
	unsigned q=2*hdp;




	CellDiv *div = new CellDiv(Nc,Np,1.0,0);
	double dx=div->dx;
	div->AllocateArrays();
	div->PreSort(xyz);
	div->SortPosition(xyz);
	div->SortVariables(asd);

//	std::ofstream file2;
//		file2.open("file.dat");
//		for (unsigned p=0; p<Np; p++){
//			file2 << xyz[p].x << " "<< xyz[p].z << std::endl;
//		}
//		file2.close();




	unsigned Np_per= div->CountPeriodicPart(q);
	unsigned Np_total=Np+Np_per;
	tfloat3 *coord 	= new tfloat3[Np_total];
	tfloat5 *data	= new tfloat5[Np_total];

	div->OuterLoop(coord, xyz,data, asd,q);
	std::ofstream file2;
	file2.open("file.dat");
	for (unsigned p=0; p<Np_total; p++){
		file2 << coord[p].x << " "<<coord[p].z << std::endl;
	}
	file2.close();


	div->FreeArrays();
	div->ChangeNp(Np_total);
	div->ChangeNc(Nc+2*q);
	div->ChangexMin(-dx*q);
	div->AllocateArrays();
	div->PreSort(coord);
	div->SortPosition(coord);
	div->SortVariables(data);


	InterpolateMLS Sol = InterpolateMLS(Np,Nc,q,mass,dx,hdp*dx);
	Sol.AllocateArray();
	Sol.Solve(coord,data,div->BeginCellTemp,div->PartsincellTemp);

	std::ofstream file1;
	file1.open("file1.dat");
	file1 << "TITLE=\"bho\""<<std::endl;
	file1 <<"VARIABLES= \"X\",\"Y\",\"U\",\"V\" " << std::endl;
	file1 << "zone I="<<Nc<<", J="<<Nc<<", f=POINT"<<std::endl;
		for (unsigned i=0; i<Nc; i++)
			for(unsigned j=0;j<Nc;j++){
			file1 << dx*i << " " << dx*j << " " << Sol.Sol[i+j*Nc].x  << " " << Sol.Sol[i+j*Nc].y  << std::endl;
		}
	file1.close();
	//std::cout << div->BeginCell







}
