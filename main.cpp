// transp.cpp -- uses structures with functions and vector!


#include "Header.h"








std::ostream& operator << (std::ostream &o, person &p)
{
	o << "Name::" << p.name << std::endl;
	o << "Id::" << p.id << std::endl;
	o << "Adress::" << p.adress.street << "," << p.adress.zip << " city:: " << p.adress.city << std::endl;

	return o;
}


std::istream& operator >> (std::istream &in, person &p)
{

	getline(in, p.name);
	transform(p.name.begin(), p.name.end(), p.name.begin(), tolower);
	getline(in, p.id);
	string line;
	string line2;
	string line3;
	string line4;



	getline(in, line);


	p.adress.street = line.substr(0, line.find(","));
	line.erase(0, line.find(",") + 1); //klar


	line2 = line.substr(0, 8);
	std::string temp_zip;

	temp_zip = line.substr(0, 8);
	temp_zip.erase(std::remove_if(temp_zip.begin(), temp_zip.end(), isspace), temp_zip.end());// stal från osc
	p.adress.zip = atoi(temp_zip.c_str()); // stoi verkar intee funka på visual studio c++ 

	line3 = line.erase(0, 9);
	if (line3.find(" ") != string::npos) {


		line4 = line3;

		p.adress.city = line4;

		transform(p.adress.city.begin(), p.adress.city.end(), p.adress.city.begin(), tolower);
		int first_letter = p.adress.city.length() - 1;
		while (p.adress.city[first_letter] == ' ')//tills den hittar första bokstav
		{
			first_letter--;
		}
		p.adress.city = p.adress.city.substr(0, first_letter + 1);
	}




	return in;
}




int main()
{
	//Nedanstående 2 rader är endast till för att svenska tecken skall visas i DOS.
	UINT oldcodepage = GetConsoleOutputCP();
	SetConsoleOutputCP(28591);
	std::locale::global(std::locale(""));

	system("chcp 1252");
	
	

	vector<person>me;
	
	string filen = "test.txt";
	me=read_file(filen);

	vector<person>cityplace;
	string city;

	

	char x;
	
	do {

		std::cout << "----------" << endl;
		std::cout << "|meny|" << endl;
		std::cout << "-------------" << endl;
		std::cout << "(1).Sök del av personnamn |" << endl;
		std::cout << "(2).Sök städer |" << endl;
		std::cout << "(3).Exit    |" << endl;
		std::cout << "-------------" << endl;
		
		cin >> x;

		string find;
		size_t name;
		switch (x) {

		case '1':

			while (x != '0') {
				std::cout << "Search name" << endl;
				cin >> find;

				transform(find.begin(), find.end(), find.begin(), tolower);
				name = find_in_names(me, find);

				std::cout << name << endl;
				std::cout << "again ?" << endl;
				std::cout << "If yes click[1] and If no click[0]" << endl;
				cin >> x;
				if (x == '0') {
					break;
				}
			}


		case '2':

			while (x != '0') {
				std::cout << "Search city" << endl;
				cin >> city;
				transform(city.begin(), city.end(), city.begin(), tolower);
				cityplace = find_person_from_city(me, city);

				for (int i = 0; i < cityplace.size(); i++)
				{
					transform(cityplace[i].adress.city.begin(), cityplace[i].adress.city.end(), cityplace[i].adress.city.begin(), toupper);
					cout << cityplace[i].name << " , " << cityplace[i].adress.city << endl;

				}

				std::cout << "again ?" << endl;
				std::cout << "If yes click[1] and If no click[0]" << endl;
				cin >> x;

				if (x == '0') {
					break;
				}
			}







		case '3':



		break;



		}

		} while (x != '3');

	
	system("pause");
	return 0;
}





std::vector<person> read_file(string filename)
{

	std::vector<person>my;
	person record;
	ifstream file; //opens filefile.
	file.open(filename);

	if (file)
	{
		while (file >> record) {


			my.push_back(record);
		}



	}
	else
	{

		cout << "Cannot open file\n";


	}

	file.close();


	if (my.empty()) {

		std::cout << "it's emty" << endl;

	}






	return my;


}
size_t find_in_names(vector<person> persons, string name_part) {



	size_t search = 0;
	string temp;
	for (int i = 0; i < persons.size(); i++)
	{
		temp = (persons[i].name);
		if (temp.find(name_part) != string::npos) // Så länge som strängen inte är tom så ökar matching.
		{
			search++;
		}
	}
	return search;




}

vector<person> find_person_from_city(vector<person>haystack, string city) {



	vector<person>city_lock;



	string temp;

	for (int i = 0; i < haystack.size(); i++) {

		temp = haystack[i].adress.city;

		if (temp == city) // Om den inlästa staden är lika med temp, så sparas en personstruct i city_lock
		{

			city_lock.push_back(haystack[i]);
		}
	}
	return city_lock;



}
