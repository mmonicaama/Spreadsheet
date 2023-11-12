#ifndef SPREADSHEETCELL_H
#define SPREADSHEETCELL_H

#include <string>

class SpreadsheetCell
{
public:
	SpreadsheetCell();
	explicit SpreadsheetCell(const std::string&);

	void setStringValue(const std::string&);
	std::string getStringValue() const;
	int getIntValue() const;
	double getDoubleValue() const;

public:
	SpreadsheetCell& operator=(const SpreadsheetCell&);
	operator int() const;
	operator double() const;
	SpreadsheetCell& operator++();
	SpreadsheetCell operator++(int);
	SpreadsheetCell& operator--();
	SpreadsheetCell operator--(int);

private:
	std::string m_data;
};

std::ostream& operator<<(std::ostream&, const SpreadsheetCell&);

#endif // SPREADSHEETCELL_h