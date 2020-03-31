/*
 * CsvReader.cpp
 *
 *  Created on: 15/mar/2020
 *      Author: francescopc
 */

#include "CsvReader.h"
#include <iostream>
#include <fstream>
#include <string>

Csv_Reader::Csv_Reader(const std::string& filename): FileName(filename) {
}

unsigned Csv_Reader::numberOfLines(){
		std::ifstream myfile(FileName);
		std::string line;
		unsigned n=0;

		if (myfile.is_open()){
			while(!myfile.eof()){
				getline(myfile,line);
				n++;
			}
		}
		return n-2;

	}


void Csv_Reader::read_file(tfloat3* cord, tfloat5* data){
		std::ifstream myfile(FileName);
		std::string line;

	    getline(myfile,line);
	    if(myfile.is_open()){
	        for (unsigned i=0; i<10000; i++){
	            getline(myfile,line,';');
	            cord[i].x=std::stod(line);
	            getline(myfile,line,';');
	            cord[i].y=std::stod(line);
	            getline(myfile,line,';');
	            cord[i].z=std::stod(line);
	            getline(myfile,line,';');
	            getline(myfile,line,';');
	            data[i].u=std::stod(line);
	            getline(myfile,line,';');
	            data[i].v=std::stod(line);
	            getline(myfile,line,';');
	            data[i].w=std::stod(line);
	            getline(myfile,line,';');
	            data[i].d=std::stod(line);
	            getline(myfile,line,';');
	            data[i].p=std::stod(line);
	            getline(myfile,line,';');
	            getline(myfile,line,';');
	            }
	        }
}




