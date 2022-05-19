#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

class Expierience : ContentGenerator {
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

class Player{
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
	int Score_ItemArray[5] = { 100, 50, 30, 20, 15 };
	int Score_Price[5] = { 2000, 1000, 800, 600, 300 };

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

			cout << "|| " << i << " Additional Xp Points : " << xp_item[i] << " " << "Price : " << xp_price[i] << endl;
		}

	}

	void Print_Items_Score() {
		
		// Print items and price
		for (int i = 0; i < item.size(); i++) {
			 
			cout << "|| " << i << " Increase Rate by : " << item[i] << " " << "Price : " << price[i] << endl;

		}

	}

};

class Inventory: Items, Player {
public:
	vector<int> s_items, s_price;
	vector<int> xp_items;

	void Score_ItemsList() {

		for (int i = 0; i < s_items.size(); i++) {

			cout << "|| " << i << " Your rate increase Item : " << s_items[i] << " Sell value : " << s_price[i] << endl;

		}
	}

	void Xp_ItemsList() {

		for (int i = 0; i < xp_items.size(); i++) {

			cout << "|| " << i << " Your Additional XP : " << xp_items[i] << endl;

		}
	}

};

class Game : Player, Expierience, Items{
public:
	bool IsGoing = true;

	int Shop_select, select, choose, temp, inv_select;
	string selection;

	Inventory inv;

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

		cout << "############################################" << endl;
		cout << "# * The Game is about clicking             #" << endl;
		cout << "# ---------------------------------------- #" << endl;
		cout << "# By pressing click, you will gain Points  #" << endl;
		cout << "#          Also gain experience            #" << endl;
		cout << "#                                          #" << endl;
		cout << "#    With Points you can access Shop       #" << endl;
		cout << "#  Increase Rate to gain points per click  #" << endl;
		cout << "#   Or buy additional experience points    #" << endl;
		cout << "#                                          #" << endl;
		cout << "# In Inventory, you can manage your items  #" << endl;
		cout << "#              Sell or Use                 #" << endl;
		cout << "#----------------------------------------- #" << endl;
		cout << "#       Press Start Game and enjoy         #" << endl;
		cout << "############################################" << endl;
		cout << "||  Press B to go back                    ||" << endl;
		cout << "============================================" << endl;
		

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

		Xp_ImportItems();
		Score_ImportItems();

		LootGenerator Obj;

		do {

			system("cls");

			cout << "|| Your Name : " << GetName() << endl;
			cout << "|| Points: " << GetScore() << endl;
			cout << "|| Experience: " << GetExp() << endl;
			cout << "|| Level: " << UpdateLevel() << endl;

			//Prints info of got loot
			Obj.PrintLootInfo();

			cout << "################################################################" << endl;
			cout << "#  1. Click  ||  2. Shop  ||  3. Inventory  ||  0. Exit Game   #" << endl;
			cout << "################################################################" << endl;

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
				else if (inv.s_items.empty() == false) {

					//Traverses through inventory items vector, and every found value adds to score
					for (int i = 0; i < inv.s_items.size(); i++) {

						score = score + inv.s_items[i];

					}
					experience = experience + 2;

								
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
			case 3:
				system("cls");
					
				InventoryMenu();

				break;
			case 0:
				
				break;
			default:
				break;
			}


		} while (select != 0);
	}

	void ShopMenu() {

		while (true) {

			system("cls");

			cout << "###################################" << endl;
			cout << "#                                 #" << endl;
			cout << "#           Clicky Shop           #" << endl;
			cout << "#                                 #" << endl;
			cout << "###################################" << endl;
			cout << "===================================" << endl;
			cout << "|| Points: " << GetScore() << endl;
			cout << "===================================" << endl;
			cout << "###################################" << endl;
			cout << "|| 1. Point Items || 2. Xp Items ||" << endl;
			cout << "###################################" << endl;
			cout << "||  Enter any number to go back  ||" << endl;
			cout << "===================================" << endl;

			cin >> Shop_select;

			if (Shop_select == 1) {

				Points_Shop();

			}

			if (Shop_select == 2) {

				Xp_Shop();

			}

			break;
		}

	}

	void Points_Shop() {
		

		system("cls");

		cout << "###################################" << endl;
		cout << "#                                 #" << endl;
		cout << "#           Clicky Shop           #" << endl;
		cout << "#                                 #" << endl;
		cout << "###################################" << endl;
		cout << "===================================" << endl;
		cout << "|| Points: " << GetScore() << endl;
		cout << "===================================" << endl;
		cout << "===================================" << endl;
		cout << "|| Point Items :                 ||" << endl;
		cout << "===================================" << endl;
		Print_Items_Score();
		cout << "!! Select only Items, which are available !!" << endl;

		cin >> choose;

		if (choose == 0) {

			if (GetScore() >= price[choose]) {

				//inserts bought item to inventory vector
				inv.s_items.push_back(item[choose]);
				inv.s_price.push_back(price[choose]);

				score = score - price[choose];

				//erases item from shop and also price
				item.erase(item.begin() + choose);
				price.erase(price.begin() + choose);

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}
			

		}

		if (choose == 1) {

			if (GetScore() >= price[choose]) {

				//inserts bought item to inventory vector
				inv.s_items.push_back(item[choose]);
				inv.s_price.push_back(price[choose]);

				score = score - price[choose];

				//erases item from shop and also price
				item.erase(item.begin() + choose);
				price.erase(price.begin() + choose);

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		if (choose == 2) {

			if (GetScore() >= price[choose]) {

				//inserts bought item to inventory vector
				inv.s_items.push_back(item[choose]);
				inv.s_price.push_back(price[choose]);

				score = score - price[choose];

				//erases item from shop and also price
				item.erase(item.begin() + choose);
				price.erase(price.begin() + choose);

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		if (choose == 3) {

			if (GetScore() >= price[choose]) {

				//inserts bought item to inventory vector
				inv.s_items.push_back(item[choose]);
				inv.s_price.push_back(price[choose]);

				score = score - price[choose];

				//erases item from shop and also price
				item.erase(item.begin() + choose);
				price.erase(price.begin() + choose);

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}
		}
		if (choose == 4) {

			if (GetScore() >= price[choose]) {

				//inserts bought item to inventory vector
				inv.s_items.push_back(item[choose]);
				inv.s_price.push_back(price[choose]);

				score = score - price[choose];

				//erases item from shop and also price
				item.erase(item.begin() + choose);
				price.erase(price.begin() + choose);

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		else {

			ShopMenu();
		}
	}

	void Xp_Shop() {

		system("cls");

		cout << "###################################" << endl;
		cout << "#                                 #" << endl;
		cout << "#           Clicky Shop           #" << endl;
		cout << "#                                 #" << endl;
		cout << "###################################" << endl;
		cout << "===================================" << endl;
		cout << "|| Points: " << GetScore() << endl;
		cout << "===================================" << endl;
		cout << "===================================" << endl;
		cout << "|| XP Items :                 ||" << endl;
		cout << "===================================" << endl;
		Print_Items_Xp();
		cout << "!! Select only Items, which are available !!" << endl;

		cin >> choose;

		if (choose == 0) {

			if (GetScore() >= xp_price[choose]) {

				//inserts bought item to inventory vector
				inv.xp_items.push_back(xp_item[choose]);
			
				score = score - xp_price[choose];

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}


		}

		if (choose == 1) {

			if (GetScore() >= xp_price[choose]) {

				//inserts bought item to inventory vector
				inv.xp_items.push_back(xp_item[choose]);

				score = score - xp_price[choose];

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		if (choose == 2) {

			if (GetScore() >= xp_price[choose]) {

				//inserts bought item to inventory vector
				inv.xp_items.push_back(xp_item[choose]);

				score = score - xp_price[choose];

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		if (choose == 3) {

			if (GetScore() >= xp_price[choose]) {

				//inserts bought item to inventory vector
				inv.xp_items.push_back(xp_item[choose]);

				score = score - xp_price[choose];

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}
		}
		if (choose == 4) {

			if (GetScore() >= xp_price[choose]) {

				//inserts bought item to inventory vector
				inv.xp_items.push_back(xp_item[choose]);

				score = score - xp_price[choose];

			}
			else {

				cout << "Sorry !! You don't have enough Points " << endl;
				cout << "Enter any number to continue...." << endl;
				cin >> temp;

			}

		}

		else {

			ShopMenu();

		}
	}

	void InventoryMenu() {

		while (true) {

			system("cls");

			cout << "#################################" << endl;
			cout << "#                               #" << endl;
			cout << "#      Clicked Inventory        #" << endl;
			cout << "#                               #" << endl;
			cout << "#################################" << endl;
			cout << "\n";
			cout << "#################################" << endl;
			cout << "|| 1. Check Points Items       ||" << endl;
			cout << "#################################" << endl;
			cout << "|| 2. Check Xp Items           ||" << endl;
			cout << "#################################" << endl;
			cout << "\n";
			cout << "=================================" << endl;
			cout << "|| Enter any number to go back ||" << endl;
			cout << "=================================" << endl;

			cin >> inv_select;

			if (inv_select == 1) {

				Points_Menu();

			}

			if (inv_select == 2) {

				XP_Menu();

			}

			break;
		}

	}

	void Points_Menu() {

		system("cls");

		cout << "#################################" << endl;
		cout << "#                               #" << endl;
		cout << "#      Clicked Inventory        #" << endl;
		cout << "#                               #" << endl;
		cout << "#################################" << endl;
		cout << "\n";
		cout << "#################################" << endl;
		cout << "# Your Points Items:            #" << endl;
		cout << "#################################" << endl;
		inv.Score_ItemsList();
		cout << "---------------------------------" << endl;
		cout << "|| Select Item To Sell         ||" << endl;
		cout << "---------------------------------" << endl;
		cout << "=================================" << endl;
		cout << "|| Enter any number to go back ||" << endl;
		cout << "=================================" << endl;

		cin >> inv_select;

		if (inv_select == 0) {

			// Puts back Item and Price to Shop
			item.push_back(inv.s_items[inv_select]);
			price.push_back(inv.s_price[inv_select]);

			// Adds back amount of Points to score
			score = score + inv.s_price[inv_select];

			//Removes Item from inventory
			inv.s_items.erase(inv.s_items.begin() + inv_select);
			inv.s_price.erase(inv.s_price.begin() + inv_select);

			cout << "Your Item is Sold !! " << endl;

			cin >> inv_select;
		}

		if(inv_select == 1) {
		
			item.push_back(inv.s_items[inv_select]);
			price.push_back(inv.s_price[inv_select]);

			score = score + inv.s_price[inv_select];

			inv.s_items.erase(inv.s_items.begin() + inv_select);
			inv.s_price.erase(inv.s_price.begin() + inv_select);

			cout << "Your Item is Sold !! " << endl;

			cin >> inv_select;
		}

		if (inv_select == 2) {

			item.push_back(inv.s_items[inv_select]);
			price.push_back(inv.s_price[inv_select]);

			score = score + inv.s_price[inv_select];

			inv.s_items.erase(inv.s_items.begin() + inv_select);
			inv.s_price.erase(inv.s_price.begin() + inv_select);

			cout << "Your Item is Sold !! " << endl;

			cin >> inv_select;

		}

		if (inv_select == 3) {

			item.push_back(inv.s_items[inv_select]);
			price.push_back(inv.s_price[inv_select]);

			score = score + inv.s_price[inv_select];

			inv.s_items.erase(inv.s_items.begin() + inv_select);
			inv.s_price.erase(inv.s_price.begin() + inv_select);

			cout << "Your Item is Sold !! " << endl;

			cin >> inv_select;

		}

		if (inv_select == 4) {

			item.push_back(inv.s_items[inv_select]);
			price.push_back(inv.s_price[inv_select]);

			score = score + inv.s_price[inv_select];

			inv.s_items.erase(inv.s_items.begin() + inv_select);
			inv.s_price.erase(inv.s_price.begin() + inv_select);

			cout << "Your Item is Sold !! " << endl;

			cin >> inv_select;

		}

		InventoryMenu();

	}

	void XP_Menu() {

		system("cls");

		cout << "#################################" << endl;
		cout << "#                               #" << endl;
		cout << "#      Clicked Inventory        #" << endl;
		cout << "#                               #" << endl;
		cout << "#################################" << endl;
		cout << "\n";
		cout << "#################################" << endl;
		cout << "# Your XP Items:                #" << endl;
		cout << "#################################" << endl;
		inv.Xp_ItemsList();
		cout << "---------------------------------" << endl;
		cout << "|| Select Item To Activate     ||" << endl;
		cout << "---------------------------------" << endl;
		cout << "=================================" << endl;
		cout << "|| Enter any number to go back ||" << endl;
		cout << "=================================" << endl;

		cin >> inv_select;

		if (inv_select == 0) {

			//Adds experience after activating xp booster
			experience = experience + inv.xp_items[inv_select];

			// Removes from inventory
			inv.xp_items.erase(inv.xp_items.begin() + inv_select);

			cout << "Sucsessfully added experience !! " << endl;
			cin >> inv_select;
		}

		if (inv_select == 1) {

			experience = experience + inv.xp_items[inv_select];

			inv.xp_items.erase(inv.xp_items.begin() + inv_select);

			cout << "Sucsessfully added experience !! " << endl;
			cin >> inv_select;

		}

		if (inv_select == 2) {

			experience = experience + inv.xp_items[inv_select];

			inv.xp_items.erase(inv.xp_items.begin() + inv_select);

			cout << "Sucsessfully added experience !! " << endl;
			cin >> inv_select;

		}

		if (inv_select == 3) {

			experience = experience + inv.xp_items[inv_select];

			inv.xp_items.erase(inv.xp_items.begin() + inv_select);

			cout << "Sucsessfully added experience !! " << endl;
			cin >> inv_select;

		}

		if (inv_select == 4) {

			experience = experience + inv.xp_items[inv_select];

			inv.xp_items.erase(inv.xp_items.begin() + inv_select);

			cout << "Sucsessfully added experience !! " << endl;
			cin >> inv_select;

		}

		InventoryMenu();

	}

};


int main() {

	Game loop;

	// Game Loop
	while (loop.running()) {

		system("cls");

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