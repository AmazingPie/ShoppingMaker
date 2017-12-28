//ShoppingMaker.cpp
//

#include "ShoppingList.h"
#include <iostream>

/*Adds a new meal with ingredients to the database of shopping_list*/
void AddMeal(ShoppingList *shopping_list)
{
	std::cout << "What is this meals name?" << std::endl;
	std::string index_name = "";
	std::cin >> index_name;
	//shopping_list.AddMeal(index_name);
	std::cout << "List the ingredients one by one (type exit to finish) \n *quantities are entered seperately\n";
	std::string ingredient = "";
	std::cin >> ingredient;
	std::cout "Now enter the quantity/amount of the ingredient\n"
	std::string quantity = "";
	std::cin >> quantity;
	while (ingredient != "exit")
	{
		//shopping_list.AddIngredient(index_name, ingredient, quantity);
		std::cout << "Ingredient: ";
		std::cin >> ingredient;
		std::cout << "Quantity: "
		std::cin >> quantity;
	}
}

/*Displays all current meals and returns a validated meal from the database of shopping_list*/
std::string FindMeal(ShoppingList *shopping_list)
{
	std::cout << "These are the current meals we have in the database: \n";
	std::string* meal_list = shopping_list->GetMeals();
	if (meal_list == NULL) 
	{
		std::cout << "Error: meals cannot be retrieved (perhaps there are no meals in database?)" << std::endl;
		return NULL;
	}
	for (int i = 1; i < std::stoi(meal_list[0]); ++i)		//the first index from GetMeal is always the array size
	{
		std::cout << meal_list[i] << "\n";
	}
	while (true)
	{
		std::cout << "What is the original meals name?" << std::endl;
		std::string meal_name = "";
		std::cin >> meal_name;
		if (shopping_list->IsMeal(meal_name))
		{
			return meal_name;
		}
		else
		{
			std::cout << "That meal was not found the database" << std::endl;
		}
	}
}

/*Ensure a valid choice is being made*/
int InputNumber(int max_num)
{
	int choice = 0;
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > max_num)
	{
		std::cout << "That is not a valid choice (choices are number only)";
		std::cin.clear();
		std::cin >> choice;
	}
	return choice;
}

int main()
{
	ShoppingList *shopping_list;
	while (true)
	{
		std::cout << "Welcome to the shopping maker.\n What action would you like to perform" <<
			"\n 1) Generate Shopping List" <<
			"\n 2) Add new Meal" <<
			"\n 3) Edit..." <<
			"\n 4) Exit";

		std::string old_name = "";
		std::string new_name = "";
		std::string meal_name = "";
		std::string new_ingredient;
		std::string* ingredient_list;
		std::string edit_choice = "";
		ShoppingList shopping_list{};
		switch (InputNumber(4))
		{
		case (1):
			shopping_list.GenerateList();
			break;
		case (2):
			AddMeal(&shopping_list);
			break;
		case (3):
			std::cout << "\n 1) Edit Meal Name" <<
				"\n 2) Edit Ingredients" <<
				"\n 3) Delete Meal"
				"\n 4) Back...";

			switch (InputNumber(4))
			{
			case (1):
				old_name = FindMeal(&shopping_list);
				if (old_name == NULL)
				{
					break;
				}
				std::cout << "What is the new name for the meal" << std::endl;
				new_name = "";
				std::cin >> new_name;
				//shopping_list.EditMeal(old_name, new_name);
				break;
			case (2):
				meal_name = FindMeal(&shopping_list);
				if (meal_name == NULL)
				{
					break;
				}
				std::cout << "Use y/n to specify which ingredients to change";
				ingredient_list = shopping_list.GetIngredients(meal_name);
				
				for (int i = 1; i < std::stoi(ingredient_list[0]); ++i)
				{
					std::cout << ingredient_list[i] << ": ";
					std::cin >> edit_choice;
					if (edit_choice == "y")
					{
						std::cout << "\nEnter replacement ingredient (leave blank to delete)";
						new_ingredient = "";
						std::cin >> new_ingredient;
						shopping_list.DeleteIngredient(ingredient_list[i]);
						if (new_ingredient != "\r")
						{
							shopping_list.AddIngredient(meal_name, new_ingredient);
						}
					}
				}
				break;
			case (3):
				meal_name = FindMeal(&shopping_list);
				if (meal_name == NULL)
				{
					break;
				}

				shopping_list.DeleteMeal(meal_name);
				break;
			case (4):
				return 0;
			}
		}
	}
	return 0;
}

/*
When get GetMeal is called it must return the size of the array as the first index

JUST ATTEMPTED SOLUTION, CHECK BUILD
/There is a problem with the callback functon whereby it creates and populates a new different table to the pointer that is passed in
/which means that the table that is passed in is never filled

May be an idea to split ShoppingList up into ShoppingList (interface between main and database functions) and another class that handles basic
database functions

Would be much more efficent in AddMeal to take in all ingredients to a buffer array first and then flush to the database all at once
*/