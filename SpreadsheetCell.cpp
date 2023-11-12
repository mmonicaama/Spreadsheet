#include "SpreadsheetCell.h"

#include <iostream>
#include <sstream>

SpreadsheetCell::SpreadsheetCell()
	: m_data{""}
{
}

SpreadsheetCell::SpreadsheetCell(const std::string& str)
	: m_data{ str }
{
}

void SpreadsheetCell::setStringValue(const std::string& str)
{
	m_data = str;
}

std::string SpreadsheetCell::getStringValue() const
{
	return m_data;
}

int SpreadsheetCell::getIntValue() const
{
	int num{};
	std::stringstream ss(m_data);
	if (ss.fail()) {
		std::cout << "Conversion failed: invalid format" << std::endl;
		return 1; 
	}
	ss >> num;
	return num;
}

double SpreadsheetCell::getDoubleValue() const
{
	double num{};
	std::stringstream ss(m_data);
	if (ss.fail()) {
		std::cout << "Conversion failed: invalid format" << std::endl;
		return 1.0;
	}
	ss >> num;
	return num;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this != &rhs) {
		m_data = rhs.m_data;
	}
	return *this;
}

SpreadsheetCell::operator int() const
{
	return getIntValue();
}

SpreadsheetCell::operator double() const
{
	return getDoubleValue();
}

SpreadsheetCell& SpreadsheetCell::operator++()
{
	std::string str = "++" + m_data;
	m_data = str;
	return *this;
}

SpreadsheetCell SpreadsheetCell::operator++(int dummy)
{
	SpreadsheetCell tmp{*this};
	m_data += "++";
	return tmp;
}

SpreadsheetCell& SpreadsheetCell::operator--()
{
	std::string str = "--" + m_data;
	m_data = str;
	return *this;
}

SpreadsheetCell SpreadsheetCell::operator--(int dummy)
{
	SpreadsheetCell tmp{ *this };
	m_data += "--";
	return tmp;
}

std::ostream& operator<<(std::ostream& os, const SpreadsheetCell& cell)
{
	os << "Value : " << cell.getStringValue() << std::endl;
	return os;
}