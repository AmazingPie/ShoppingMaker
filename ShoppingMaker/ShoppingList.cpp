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

int ShoppingList::RandomInt(int lower_bound, int upper_bound)
{
	std::random_device rd;
	std::mt19937 rand_num(rd());
	auto bounded_rand_num = std::bind(std::uniform_int_distribution<int(lower_bound, upper_bound)>, rand_num());
	return bounded_rand_num()
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
	io_stringstream.str("");
	io_stringstream << "SELECT MealId" <<
			"FROM Meals"; 
	std::string query = io_stringstream.str();
	QueryReturn *results;
	if (sqlite3_exec(db, query.c_str(), Callback, &results, NULL) != SQLITE_OK)
	{
		std::cout << "Meals failed to select";
	}
	else
	{
		std::cout << "Meals selected successfully";
	}

	std::string *meal_list = GetMeals();
	std::random_device rd;
	std::mt19937 random_num(rd());
	auto rand_meal_num = std::bind(std::uniform_int_distribution<int(0, results->m_fields_size - 1)>, random_num());
	meal_list[rand_meal_num];

	return meal_list;
}

void ShoppingList::AddMeal(std::string entry)
{
	io_stringstream.str("");
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
}

void ShoppingList::AddIngredient(std::string meal_name, std::string ingredient, std::string quantity)
{
	io_stringstream.str("");
	io_stringstream << "INSERT INTO Ingredients (IngName, IngQuantity)" <<
			"VALUES ( '" << ingredient << "', '" << quantity << "' )";
	std::string query = io_stringstream.str();
	if sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Insert statement failed to execute" << std::endl;
	}
	else 
	{
		std::cout << "Insert statement executed successfully" << std::endl;
	}
	io_stringstream.str("");
	io_stringstream << "SELECT IngId" <<
			"FROM Ingredients" <<
			"WHERE IngName = '" << ingredient << "'";
	std::string query = io_stringstream.str();
	QueryReturn *results;
	if (!sqlite3_exec(db, query.c_str(), Callback, &results, NULL))
	{
		std::cout << "Select statement executed successfully";

		io_stringstream.str("");
		io_stringstream << "INSERT INTO Meals (IngId)" <<
				"VALUES ( '" << results->m_fields[0] << "' )";
		std::string query = io_stringstream.str();
		if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
		{
			std::cout << "Insert statement failed to execute";
		}
		else
		{
			std::cout << "Insert statement executed successfully";
		}
	}
}

void ShoppingList::DeleteMeal(std::string meal_name)
{
	io_stringstream.str("");
	io_stringstream << "DELETE FROM Meals" <<
			"WHERE MealName = '" << meal_name << "';"; 
	std::string query = io_stringstream.str();
	if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Meal '" << meal_name << "' failed to delete";
	}
	else
	{
		std::cout << "Meal '" << meal_name << "' deleted successfully";
	}
}

void ShoppingList::DeleteIngredient(std::string ingredient_name)
{
	io_stringstream.str("");
	io_stringstream << "DELETE FROM Ingredients" <<
			"WHERE IngName = '" << ingredient_name << "';"; 
	std::string query = io_stringstream.str();
	if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Ingredient '" << ingredient_name << "' failed to delete";
	}
	else
	{
		std::cout << "Ingredient '" << ingredient_name << "' deleted successfully";
	}

}

void ShoppingList::EditMeal(std::string old_entry, std::string new_entry)
{
	io_stringstream.str("");
	io_stringstream << "UPDATE Meals" <<
			"SET MealName = '" << new_entry <<"'" <<
			"WHERE MealName = '" << old_entry << "';"; 
	std::string query = io_stringstream.str();
	if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Meal '" << old_entry << "' failed to update";
	}
	else
	{
		std::cout << "Meal '" << old_entry << "' updated successfully";
	}
}

void ShoppingList::EditIngredients(std::string old_name, std::string new_name, std::string new_quantity)
{
	io_stringstream.str("");
	io_stringstream << "UPDATE Ingredients" <<
			"SET IngName = '" << new_name << "', IngQuantity = '" << new_quantity << "'" <<
			"WHERE IngName = '" << old_name << "';"; 
	std::string query = io_stringstream.str();
	if (sqlite3_exec(db, query.c_str(), NULL, NULL, 0) != SQLITE_OK)
	{
		std::cout << "Ingredient '" << old_name << "' failed to update";
	}
	else
	{
		std::cout << "Ingredient '" << old_name << "' updated successfully";
	}
}

std::string* ShoppingList::GetMeals()
{
	io_stringstream.str("");
	io_stringstream << "SELECT MealId, MealName" <<
			"FROM Meals;";		//CHECK STATEMENT
	std::string query = io_stringstream.str();
	QueryReturn *results;
	if (!sqlite3_exec(db, query.c_str(), Callback, &results, NULL))
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