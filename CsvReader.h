/*
 * CsvReader.h
 *
 *  Created on: 15/mar/2020
 *      Author: francescopc
 */

#ifndef CSVREADER_H_
#define CSVREADER_H_

#include<string>
#include"Types.h"


class Csv_Reader {
public:
	Csv_Reader(const std::string& filename);

	unsigned numberOfLines();
	void read_file(tfloat3* cord, tfloat5* data);

private:
	std::string FileName;
};

#endif /* CSVREADER_H_ */
