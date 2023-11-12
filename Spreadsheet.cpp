#include "Spreadsheet.h"

#include <iostream>
#include <algorithm>

Spreadsheet::Spreadsheet()
	: m_cells{nullptr}
	, m_rows{0}
	, m_cols{0}
{
}

Spreadsheet::Spreadsheet(int rows, int cols)
	: m_rows(rows)
	, m_cols(cols)
{
	m_cells = new SpreadsheetCell * [m_rows];
	for (int i = 0; i < m_rows; ++i) {
		m_cells[i] = new SpreadsheetCell[m_cols];
	}

	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			m_cells[i][j].setStringValue("");
		}
	}
}

Spreadsheet::~Spreadsheet()
{
	for (int i = 0; i < m_rows; ++i) {
		delete[] m_cells[i];
	}
	delete[] m_cells;
}

void Spreadsheet::addRow(int size)
{
	SpreadsheetCell** tmp = new SpreadsheetCell * [m_rows + size];
	for (int i = 0; i < m_rows + size; ++i) {
		if (i < m_rows) {
			tmp[i] = m_cells[i];
		}
		else {
			tmp[i] = new SpreadsheetCell[m_cols];
		}
	}
	delete[] m_cells;
	m_cells = tmp;
	m_rows += size;
}

void Spreadsheet::addColumn(int size)
{
	for (int i = 0; i < m_rows; ++i) {
		SpreadsheetCell* tmp = new SpreadsheetCell[m_cols + size];
		for (int j = 0; j < m_cols + size; ++j) {
			if (j < m_cols) {
				tmp[j] = m_cells[i][j];
			}
			else {
				SpreadsheetCell cell;
				tmp[j] = cell;
			}
		}
		
		delete[] m_cells[i];
		m_cells[i] = tmp;
	}
	m_cols += size;
}

void Spreadsheet::removeRow(int index)
{
	if (!validRowIndex(index)) {
		std::cout << "Error : invalid index" << std::endl;
		return;
	}

	SpreadsheetCell** tmp = new SpreadsheetCell * [m_rows - 1];
	delete[] m_cells[index];
	for (int i = 0; i < index; ++i) {
		tmp[i] = m_cells[i];
	}
	for (int i = index; i < m_rows - 1; ++i) {
		tmp[i] = m_cells[i + 1];
	}
	delete[] m_cells;
	m_cells = tmp;
	--m_rows;
}

void Spreadsheet::removeColumn(int index)
{
	if (!validColIndex(index)) {
		std::cout << "Error : invalid index" << std::endl;
		return;
	}

	for (int i = 0; i < m_rows; ++i) {
		SpreadsheetCell* tmp = new SpreadsheetCell[m_cols - 1];
		for (int j = 0; j < index; ++j) {
			tmp[j] = m_cells[i][j];
		}
		for (int j = index; j < m_cols - 1; ++j) {
			tmp[j] = m_cells[i][j + 1];
		}
		delete[] m_cells[i];
		m_cells[i] = tmp;
	}
	--m_cols;
}

SpreadsheetCell* Spreadsheet::getCell(int row, int col) const
{
	if (!validRowIndex(row) || !validColIndex(col)) {
		std::cout << "Error : invalid index" << std::endl;
		return nullptr;
	}
	return &m_cells[row][col];
}

void Spreadsheet::setCell(int row, int col, const std::string& str)
{
	if (!validRowIndex(row) || !validColIndex(col)) {
		std::cout << "Error : invalid index" << std::endl;
		return;
	}
	m_cells[row][col].setStringValue(str);
}

void Spreadsheet::print() const
{
	std::cout << "+" << std::string(m_cols * 15, '-') << "+" << std::endl;

	for (int i = 0; i < m_rows; ++i) {
		std::cout << "|";
		for (int j = 0; j < m_cols; ++j) {
			std::cout << " " << m_cells[i][j].getStringValue();
			std::cout << std::string(12 - m_cells[i][j].getStringValue().size(), ' ') << "|";
		}
		std::cout << std::endl;

		std::cout << "+" << std::string(m_cols * 15, '-') << "+" << std::endl;
	}
}

bool Spreadsheet::validRowIndex(int index) const
{
	return !(index < 0 || index >= m_rows);
}

bool Spreadsheet::validColIndex(int index) const
{
	return !(index < 0 || index >= m_cols);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	if (this != &rhs) {
		for (int i = 0; i < m_rows; ++i) {
			delete[] m_cells[i];
		}
		delete[] m_cells;

		m_rows = rhs.m_rows;
		m_cols = rhs.m_cols;

		m_cells = new SpreadsheetCell * [m_rows];
		for (int i = 0; i < m_rows; ++i) {
			m_cells[i] = new SpreadsheetCell[m_cols];
		}

		for (int i = 0; i < m_rows; ++i) {
			for (int j = 0; j < m_cols; ++j) {
				m_cells[i][j] = rhs.m_cells[i][j];
			}
		}
	}

	return *this;
}

Spreadsheet Spreadsheet::operator+(const Spreadsheet& rhs) const
{
	int rows = m_rows + rhs.m_rows;
	int cols = std::max(m_cols, rhs.m_cols);
	Spreadsheet res(rows, cols);

	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			res.m_cells[i][j].setStringValue(m_cells[i][j].getStringValue());
		}
	}
	
	for (int i = m_rows; i < rows; ++i) {
		for (int j = 0; j < rhs.m_cols; ++j) {
			res.m_cells[i][j].setStringValue(rhs.m_cells[i - m_rows][j].getStringValue());
		}
	}
	
	return res;
}

SpreadsheetCell* Spreadsheet::operator[](int index) {
	if (!validRowIndex(index)) {
		throw std::out_of_range("Row index out of range");
	}
	return m_cells[index];
}

std::ostream& operator<<(std::ostream& os, const Spreadsheet& spreadsheet)
{
	spreadsheet.print();
	return os;
}