#include "ShoppingList.h"

QueryReturn* ShoppingList::Callback()
{

	QueryReturn result {};
	return result;
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
	io_stringstream << "SELECT ";
	std:;string query = io_stringstream.str();
	QueryReturn result = sqlite3_exec(db, query.c_str(), &Callback, ))
	if (/*exec == !Fail*/){
		std::string* meals = result.data; //edit line to correct sysntax with QueryReturn
		meals.push();
		return meals;
	}
	else
	{
		std::cout << "Could not get meals from database";
	}
	std::string ingredients[1];
	ingredients[0] = "asdf";
	return ingredients;
}

std::string* ShoppingList::GetIngredients(std::string ingredients_name)
{
	std::string ingredients[1];
	ingredients[0] = "asdf";
	return ingredients;
}

bool ShoppingList::IsMeal(std::string meal_name)
{
	return false;
}

ShoppingList::~ShoppingList()
{
	sqlite3_close(db);
}