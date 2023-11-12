#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include "SpreadsheetCell.h"

class Spreadsheet
{
public:
	Spreadsheet();
	Spreadsheet(int, int);
	~Spreadsheet();

	void addRow(int);
	void addColumn(int);
	void removeRow(int);
	void removeColumn(int);
	SpreadsheetCell* getCell(int, int) const;
	void setCell(int, int, const std::string&);
	void print() const;

public:
	Spreadsheet& operator=(const Spreadsheet&);
	Spreadsheet operator+(const Spreadsheet&) const;
	SpreadsheetCell* operator[](int);

private:
	bool validRowIndex(int) const;
	bool validColIndex(int) const;

private:
	SpreadsheetCell** m_cells;
	int m_rows;
	int m_cols;
};

std::ostream& operator<<(std::ostream&, const Spreadsheet&);

#endif // SPREADSHEET_H