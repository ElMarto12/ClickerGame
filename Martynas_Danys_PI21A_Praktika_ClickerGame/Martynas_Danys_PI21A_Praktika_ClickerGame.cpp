#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class ContentGenerator{
public:
	vector<string> Data;

	string FilePath = "GameData.csv";

	void ImportData() {

		ifstream File;

		File.open(FilePath);

		if (File.fail()) {

			cout << "Error !! Game Data not reached " << FilePath << endl;
			return;

		}

		// Put all read data to Vector array
		while (File.peek() != EOF) {

			string record;

			getline(File, record, ',');

			Data.push_back(record);


		}

		File.close();

	}

	int GetData(int select) {

		int value;

		// Conversion from string to integer // select is element number of vector array
		value = stoi(Data.at(select));

		return value;


	}

	void ExportData() { //-------- To update data in Vector, must use ImportData, othervise it still same as originally was

		ofstream File(FilePath, ios::app);

		string xp_number;

		cout << "Insert amount of xp points to reach another level: "; cin >> xp_number;

		File << xp_number << "," << "\n";

		File.close();

	}


	void TraverseVector() {

		// Traverses through all Vector elements, despite data type || !! Data in Vector, at this point, not nessisarily can be integer or any other type !! ||
		for (auto itr : Data) {

			cout << itr << " ";

		}

	}

};

class Expierience : ContentGenerator{
protected:
	int experience = 0;
	int level = 1;
	int level_count = 0;

public:
	
	int GetExp() {

		int* ptr;

		ptr = &experience;

		return *ptr;

	}

	int UpdateLevel() {
	
		// Every time updates data from data file

		ImportData();

	
		// Gets amount of exp number from file, to update to another level
		if (GetExp() >= GetData(level_count)) {

			level_count++;

			level++;

		}
		else {
			
			return level;

		}

		return level;

	}


};



class Player {
protected:
	string name;
	int score = 0;

public:
	string GetName() {

		return name; 

	}

	int GetScore(){

		int* ptr;

		ptr = &score;

		return *ptr;

	}

};

class LootGenerator : Expierience, Player{
protected:
	int items[10] = { 10, 50, 100, 20, 5, 90, 40, 15, 25, 200 };
	
public:

	int CountIteration_Xp = 0;
	int CountIteration_Score = 0;
	
	int Diff_Xp = 0;
	int Diff_Score = 0;

	bool Loot_Status_Xp = false;
	bool Loot_Status_Points = false;


	int GetLoot_Xp() {

		int GeneratedItem = items[rand() % 10];

		return GeneratedItem;
	}

	int GetLoot_Points() {

		int GeneratedItem = items[rand() % 10];

		return GeneratedItem;

	} 

	void PrintLootInfo() {

		if (Loot_Status_Xp == true) {

			cout << "Hey !! You earned some additional Xp points: " << Diff_Xp << endl;

			// resets parameters: Status to false, Diff to 0, 
			Loot_Status_Xp = false;
			Diff_Xp = 0;
			

		}
		else if (Loot_Status_Points == true) {

			cout << "Hey !! You earned some additional Points: " << Diff_Score << endl;

			Loot_Status_Points = false;

			Diff_Score = 0;

		}

		
		return; 
	}
};

class Items{
protected:
	//Items for score
	vector<int> item, price;
	int Score_ItemArray[5] = {100, 50, 30, 20, 15 };
	int Score_Price[5] = { 2000, 1000, 800, 600, 300};

	//Items for xp
	vector<int> xp_item, xp_price;
	int Xp_ItemArray[5] = { 10, 40, 60, 100, 1000 };
	int Xp_Price[5] = { 500, 800, 1000, 1500, 3000 };

public:

	void Score_ImportItems() {

		int items;
		int prices;

		for (int i = 0; i < 5; i++) {

			//Gets element from array and stores in integer type variable
			items = Score_ItemArray[i];
			prices = Score_Price[i];

			//Puts elements to vector array
			item.push_back(items);
			price.push_back(prices);

		}

	}

	void Xp_ImportItems() {

		int items;
		int prices;

		for (int i = 0; i < 5; i++) {

			items = Xp_ItemArray[i];
			prices = Xp_Price[i];

			xp_item.push_back(items);
			xp_price.push_back(prices);

		}
		
	}

	void Print_Items_Xp() {

		for (int i = 0; i < item.size(); i++) {

			cout << xp_item[i] << " " << xp_price[i] << endl;
		}

	}

	void Print_Items_Score() {
		
		// Print items and price
		for (int i = 0; i < item.size(); i++) {

			cout << item[i] << " " << price[i] << endl;

		}

	}



};


class Game : Player, Expierience, Items{
public:
	bool IsGoing = true;

	int Shop_select;
	int select;
	string selection;

	bool running() {

		return IsGoing;

	}

	void MainMenu() {

		cout << "#########################################" << endl;
		cout << "##                                     ##" << endl;
		cout << "##        CLICKER GAME v 1.0           ##" << endl;
		cout << "##                                     ##" << endl;
		cout << "#########################################" << endl;
		cout << "=========================================" << endl;
		cout << "||  1. Start Game                      ||" << endl;
		cout << "=========================================" << endl;
		cout << "||  2. Instructions                    ||" << endl;
		cout << "=========================================" << endl;
		cout << "||  3. Highscore                       ||" << endl;
		cout << "=========================================" << endl;
		cout << "||  0. Exit                            ||" << endl;
		cout << "=========================================" << endl;

	}

	void Instructions() {

		cout << "testing" << endl;

	}

	void Start(){
		
		cout << "##############################################" << endl;
		cout << "#  Write your name:                          #" << endl;
		cout << "##############################################" << endl;
	
		cin >> name;

		HUD();

	}

	void HUD() {


		system("cls");

		Score_ImportItems();
		Xp_ImportItems();

		LootGenerator Obj;

		do {

			system("cls");

			cout << "|| Your Name : " << GetName() << endl;
			cout << "|| Points: " << GetScore() << endl;
			cout << "|| Experience: " << GetExp() << endl;
			cout << "|| Level: " << UpdateLevel() << endl;

			//Prints info of got loot
			Obj.PrintLootInfo();

			cout << "####################################################################################" << endl;
			cout << "#  1. Click  ||  2. Shop  ||  3. Inventory  ||  4. Achievments  ||  0. Exit Game   #" << endl;
			cout << "####################################################################################" << endl;

			cin >> select;

			switch (select)
			{
			case 1:
				if (Obj.CountIteration_Score == 10) {

					//Stores got value from randomly generated number
					int random = Obj.GetLoot_Points();

					//Sets status to true, so it could print how much points were earned
					//Stores value to diff_score, to get exact number to print
					Obj.Loot_Status_Points = true;
					Obj.Diff_Score = random;

					// calculates and adds score and xp
					score = random + score;
					experience = experience + 2;


					// resets iteration counter for score
					Obj.CountIteration_Score = 0;

				}
				else if (Obj.CountIteration_Xp == 15) {

					int random = Obj.GetLoot_Xp();

					Obj.Loot_Status_Xp = true;
					Obj.Diff_Xp = random;

					experience = random + experience;
					score++;

					Obj.CountIteration_Xp = 0;

				}
				else {

					score++;
					experience = experience + 2;

					Obj.CountIteration_Xp++;
					Obj.CountIteration_Score++;

				}
				break;
			case 2:
				system("cls");

				ShopMenu();

				break;
			default:
				break;
			}


		} while (select != 0);
	}

	void ShopMenu() {

		system("cls");

		cout << "#############################" << endl;
		cout << "#                           #" << endl;
		cout << "#       Clicky Shop         #" << endl;
		cout << "#                           #" << endl;
		cout << "#############################" << endl;

		Print_Items_Score();
		Print_Items_Xp();

		cin >> Shop_select;

	}
};


int main() {


	Game loop;

	// Game Loop
	while (loop.running()) {

		loop.MainMenu();
		
		cin >> loop.select;
		
		//Game start
		if (loop.select == 1) {

			system("cls");

			loop.Start();

		}

		//Instructions menu
		if (loop.select == 2) {

			system("cls");

			while (loop.selection != "b") {

				system("cls");
				
				loop.Instructions();

				cin >> loop.selection; 


			}

		}
		

		//Game exit
		if (loop.select == 0) {

			loop.IsGoing = false;

		}

	}

	

}