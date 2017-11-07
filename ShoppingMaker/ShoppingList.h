#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <string>
#include <sstream>
#include <sqlite3.h>
#include <iostream>
#include "QueryReturn.h"

class ShoppingList
{
private:
	sqlite3 *db;
	std::stringstream io_stringstream;
	int index_count;

	QueryReturn* Callback();

public:
	ShoppingList();

	/*creates a randomised txt file with the shopping for the current week with the dishes and the ingredients needed and returns a string array*/
	std::string* GenerateList();
	/**/
	void AddMeal(std::string entry);
	/**/
	void AddIngredient(std::string meal_name, std::string ingredient);
	/**/
	void DeleteMeal(std::string meal_name);
	/**/
	void DeleteIngredient(std::string ingredient_name);
	/**/
	void EditMeal(std::string old_entry, std::string new_entry);
	/**/
	void EditIngredients(std::string ingredient_name);
	/*Returns a list of the names of all current meals in the database.
	-The first index is always the size of the array*/
	std::string* GetMeals();
	/**/
	std::string* GetIngredients(std::string ingredients_name);
	/**/
	bool IsMeal(std::string meal_name);

	~ShoppingList();
};
#endif

/*
Needed Functions:
-GenerateList
creates a randomised txt file with the shopping for the current week with the dishes and the ingredients needed and returns a string array

-AddIndex
Adds a new entry (dish) the index file, appended to the eof

-AddIngredients
Adds a set of ingredients to the recipe at index

-DeleteIndex
Deletes index entry at given index

-DeleteIngredients
Completely removes a set of ingredients at given index

-EditIndex
Replaces the entry at given index with new string

-EditIngredients
will either completely replace ingredient list or will append one at the end of list

-GetIndex
Retreives the entry at the given index

-GetIngredients
Retrieves the ingredients at given index

*/