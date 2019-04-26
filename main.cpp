/*
	Második beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
	Készítette: Sándor Balázs
	Neptun: AZA6NL
	git: https://github.com/SandorBalazsHU/elte-ik-orsi-2-beadando-reloaded (A határidő lejárta után lesz publikus)
*/

//Run Kara Run

#include <iostream>
#include <fstream>
#include "types.hpp"

class Mission {
	private:
		Map map;
		FlightPath path;
	public:
		Mission(std::string input_file);
		void compute();
		void write_out(std::string input_file);
};

int main()
{
	Mission mission("world.map");
	mission.compute();
	mission.write_out("output.txt");
}

Mission::Mission(std::string input_file)
{
	std::fstream file(input_file);
	if (!file.good()) std::cout << "The input file dosen't exist!" << std::endl;

	int n, m;
	file >> n >> m;
	map = Map(n, m);
	file >> map;
}

void Mission::compute()
{
	path = map.get_shortest_flightpath();
}

void Mission::write_out(std::string input_file)
{
	std::ofstream myfile;
	myfile.open(input_file);
	myfile << "From: (" << path.first.x << "," << path.first.y << ")" << std::endl;
	myfile << "To: (" << path.second.x << "," << path.second.y << ")" << std::endl;
	myfile.close();
}