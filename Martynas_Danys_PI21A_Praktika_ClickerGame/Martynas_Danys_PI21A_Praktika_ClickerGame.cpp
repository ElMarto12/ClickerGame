#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class ContentGenerator {
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

			// Conversion from string to integer
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

	private:

		void TraverseVector() {
			
			// Traverses through all Vector elements, despite data type || !! Data in Vector, at this point, not nessisarily can be integer or any other type !! ||
			for (auto itr : Data) {

				cout << itr << " ";
			}

		}


};





int main() {

	ContentGenerator Gen;

}



