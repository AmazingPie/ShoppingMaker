#include "ShoppingList.h"

int ShoppingList::Callback(void *query_struct, int column_amount, char **fields, char **cols)
{
	//populate the return_table with the data needed
	query_struct = static_cast<QueryReturn*>(query_struct);		//THIS MAY OR MAY NOT WORK
	query_struct->m_column_amount = column_amount;
	query_struct->m_fields_size = 0;		//might want to replace this with an actual constructor
	for (int i = 1; i < sizeof(fields); ++i, ++query_struct->m_fields_size)
	{
		query_struct->m_fields[i] = fields[i];
		query_struct->m_columns[i] = cols[i];
	}
	
	return 0;
}

ShoppingList::ShoppingList()
{
	if (sqlite3_open("food.db", &db))
	{
		std::cout << "Database cannot be opened /n" << sqlite3_errmsg(db);
	}
	else
	{
		std::cout << "Database opened successfully" << std::endl;
	}
}

std::string* ShoppingList::GenerateList()
{
	std::string list[1];
	list[0] = "asdf";
	return list;
}

void ShoppingList::AddMeal(std::string entry)
{
	io_stringstream << "INSERT INTO Meals ( MealName )" <<
		"VALUES ( '" << entry << "' );";
	std::string query = io_stringstream.str();
	if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Insert statement failed to execute" << std::endl;
	}
	else
	{
		std::cout << "Insert statement executed successfully" << std::endl;
	}
	io_stringstream.str("");
}

void ShoppingList::AddIngredient(std::string meal_name, std::string ingredient)
{
	

}

void ShoppingList::DeleteMeal(std::string meal_name)
{

}

void ShoppingList::DeleteIngredient(std::string ingredients_name)
{


}

void ShoppingList::EditMeal(std::string old_entry, std::string new_entry)
{

}

void ShoppingList::EditIngredients(std::string ingredients_name)
{

}

std::string* ShoppingList::GetMeals()
{
	io_stringstream << "SELECT meal_id, meal_name
			FROM Meals;";		//CHECK STATEMENT
	std::string query = io_stringstream.str();
	QueryReturn *results;
	bool fail = sqlite3_exec(db, query.c_str(), Callback, &results, NULL);
	if (!fail)
	{
		std::string* meals = results->m_fields;
		meals[0] = (results->m_fields_size);
		return meals;
	}
	else
	{
		std::cout << "Could not get meals from database";
	}
	return NULL;
}

std::string* ShoppingList::GetIngredients(std::string ingredients_name)
{
	return NULL;
}

bool ShoppingList::IsMeal(std::string meal_name)
{
	return false;
}

ShoppingList::~ShoppingList()
{
	sqlite3_close(db);
}