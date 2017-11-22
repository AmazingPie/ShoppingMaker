#ifndef QUERYRETURN_H
#define QUERYRETURN_H

#include <string>

struct QueryReturn
{
	int m_fields_size;
	int m_column_amount;
	std::string *m_fields;
	std::string *m_columns;
};

#endif