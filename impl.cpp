#include "types.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>


FIELD field_from_int(const int i)
{
	return static_cast<FIELD>(i);
}

int field_value(const FIELD& f)
{
	switch (f)
	{
		case FIELD::CANNIBALS	: return -2;	break;
		case FIELD::DESERT		: return 0;		break;
		case FIELD::FOREST		: return 3;		break;
		case FIELD::GOLD_MINE	: return 5;		break;
		case FIELD::GRASSLAND	: return 2;		break;
		case FIELD::IRON		: return 2;		break;
		case FIELD::LAKE		: return 3;		break;
		case FIELD::SEA			: return 1;		break;
		case FIELD::SWAMP		: return 1;		break;
		case FIELD::VILLAGE		: return 6;		break;
		case FIELD::WHEAT		: return 3;		break;
		case FIELD::CITY		: return 10;	break;
		default					: return -42;	break;
	}
}

int tile_value(const Tile& f)
{
	return field_value(f.second);
}

bool operator<(const Coordinate& a, const Coordinate& b)
{
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

std::ostream& operator<<(std::ostream& s, const FIELD& f)
{
	switch (f)
	{
		case FIELD::CANNIBALS	: s << "CANNIBALS";		break;
		case FIELD::DESERT		: s << "DESERT";		break;
		case FIELD::FOREST		: s << "FOREST";		break;
		case FIELD::GOLD_MINE	: s << "GOLD_MINE";		break;
		case FIELD::GRASSLAND	: s << "GRASSLAND";		break;
		case FIELD::IRON		: s << "IRON";			break;
		case FIELD::LAKE		: s << "LAKE";			break;
		case FIELD::SEA			: s << "SEA";			break;
		case FIELD::SWAMP		: s << "SWAMP";			break;
		case FIELD::VILLAGE		: s << "VILLAGE";		break;
		case FIELD::WHEAT		: s << "WHEAT";			break;
		case FIELD::CITY		: s << "CITY";			break;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const DIRECTION& d)
{
	switch (d)
	{
		case DIRECTION::NORTH_WEST	: s << "NORTH_WEST";	break;
		case DIRECTION::NORTH		: s << "NORTH";			break;
		case DIRECTION::NORTH_EAST	: s << "NORTH_EAST";	break;
		case DIRECTION::EAST		: s << "EAST";			break;
		case DIRECTION::SOUTH_EAST	: s << "SOUTH_EAST";	break;
		case DIRECTION::SOUTH		: s << "SOUTH";			break;
		case DIRECTION::SOUTH_WEST	: s << "SOUTH_WEST";	break;
		case DIRECTION::WEST		: s << "WEST";			break;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const Coordinate& p)
{
	s << "(" << p.x << "," << p.y << ")";
	return s;
}
std::istream& operator>>(std::istream& s, Coordinate& p)
{
	s >> p.x >> p.y;
	return s;
}

std::ostream& operator<<(std::ostream& s, const Tile& t)
{
	s << t.first << " " << t.second;
	return s;
}

std::istream& operator>>(std::istream& s, Map& m)
{
	for (int i = 0; i < m.rows(); i++)
	{
		std::vector<FIELD> row;
		for (int j = 0; j < m.cols(); j++)
		{
			int c;
			s >> c;
			row.push_back(field_from_int(c));
		}
		m.map_.push_back(row);
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const Map& m)
{
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			s << m.map_[i][j] << " ";
		}
		s << std::endl;
	}
	return s;
}

Map::Map()
{
	rows_ = 0;
	cols_ = 0;
	map_ = std::vector<std::vector<FIELD>>();
}

Map::Map(const int r, const int c)
{
	if (r > 0 && c > 0) {
		rows_ = r;
		cols_ = c;
	}
	else
	{
		rows_ = 0;
		cols_ = 0;
	}
}

int Map::rows() const
{
	return rows_;
}

int Map::cols() const
{
	return cols_;
}

bool Map::in_range(const int x, const int y) const
{
	return ((0 <= x) && (x < rows_)) && ((0 <= y) && (y < cols_));
}

Tile Map::tile_at(const int i, const int j) const
{
	if (in_range(i,j))
	{
		return std::make_pair(Coordinate(i, j), map_[i][j]);
	}
	else
	{
		return std::make_pair(Coordinate(i, j), FIELD::SEA);
	}
}

Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
	int even_shift = 1;
	if (y % 2 != 0) even_shift = 0;

	int odd_shift = 0;
	if (y % 2 != 0) odd_shift = 1;

	switch (d)
	{
		case DIRECTION::NORTH_WEST	: return tile_at(x - even_shift, y - 1);	break;
		case DIRECTION::NORTH		: return tile_at(x - 1, y);					break;
		case DIRECTION::NORTH_EAST	: return tile_at(x - even_shift, y + 1);	break;
		case DIRECTION::EAST		: return tile_at(x, y + 1);					break;
		case DIRECTION::SOUTH_EAST	: return tile_at(x + odd_shift, y + 1);		break;
		case DIRECTION::SOUTH		: return tile_at(x + 1, y);					break;
		case DIRECTION::SOUTH_WEST	: return tile_at(x + odd_shift, y - 1);		break;
		case DIRECTION::WEST		: return tile_at(x - 1, y);					break;
		default						: return tile_at(x, y);						break;
	}
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
	std::set<Tile> s;
	Tile t_0 = tile_at(i, j);
	s.insert(t_0);

	if (r <= 0) return s;

	for (int i = 0; i < r; i++)
	{
		std::set<Tile> tmp;
		for (Tile t : s) {
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::NORTH));
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::NORTH_WEST));
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::NORTH_EAST));
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::SOUTH));
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::SOUTH_EAST));
			tmp.insert(tile_in_direction(t.first.x, t.first.y, DIRECTION::SOUTH_WEST));
		}
		s.insert(tmp.begin(), tmp.end());
	}

	return s;
}

/**
  * new functions for 2nd assignment
  */

void Map::find_cities()
{
	for(int i = 0; i < rows_; i++)
	{
		for(int j = 0; j < cols_; j++)
		{
			Tile tile = tile_at(i,j);
			if(tile.second == FIELD::CITY) cities_.insert((City) tile.first);
		}
	}
}

std::set<City> Map::get_cities() const
{
	return cities_;
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
	if (in_range(i, j))
	{
		Tile current_tile = tile_at(i,j);
		if(current_tile.second == FIELD::CITY && f != FIELD::CITY)
		{
			cities_.erase(current_tile.first);
		}
		else
		{
			cities_.insert(current_tile.first);
		}
		map_[i][j] = f;
	}
}

double Map::get_length(const FlightPath& p) const
{
	return (double) get_distance(p.first, p.second);
}

double Map::get_distance(const City& a, const City& b) const
{
	return (double) std::sqrt(std::pow(a.x-b.x, 2)+std::pow(a.y-b.y, 2));;
}

FlightPath Map::closest_brute_force(const std::vector<City>& cities) const
{
	std::pair<std::pair<City, City>, double> closest;
	closest.second = 0.0;
	for(size_t i = 0; i < cities.size(); i++)
	{
		for(size_t j = 0; j < cities.size(); j++)
		{
			double d = get_distance(cities[i], cities[j]);
			if(d >= closest.second)
			{
				closest.first.first = cities[i];
				closest.first.second = cities[j];
				closest.second = d;
			}
		}
		
	}
	return std::pair<City, City>(closest.first.first, closest.first.second);
}

bool coordinate_y_order(const Coordinate& a, const Coordinate& b)
{
	if (a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

// TODO: Rendezés ellenőrzése
FlightPath Map::get_shortest_flightpath() const
{
	std::vector<City> x,y;
	std::copy(cities_.begin(), cities_.end(), std::back_inserter(x));
	y=x;
	std::sort(y.begin(), y.end(), coordinate_y_order);
	return find_shortest(x,y);
}

// TODO: Felezés ellenőrzése + Páratlan esetben kerüljön a jobb oldalhoz a plusz elem!
FlightPath Map::find_shortest(const std::vector<City>& x_cities, const std::vector<City>& y_cities) const
{
	if(x_cities.size()>4) return closest_brute_force(x_cities);

	std::size_t const half_size = x_cities.size() / 2;
	std::vector<City> on_left_x(x_cities.begin(), x_cities.begin() + half_size-1);
	std::vector<City> on_right_x(x_cities.begin() + half_size, x_cities.end());

	City middle_X = on_right_x[0];

	std::vector<City> on_left_y, on_right_y;
	for (size_t i = 0; i < y_cities.size(); i++)
	{
		if(y_cities[i].x<=middle_X.x)
		{
			on_left_y.push_back(y_cities[i]);
		}
		else
		{
			on_right_y.push_back(y_cities[i]);
		}
	}

	FlightPath path_a = find_shortest(on_left_x, on_left_y);
	FlightPath path_b = find_shortest(on_right_x, on_right_y); //Külön szálon!

	FlightPath min_path = (get_length(path_a)<get_length(path_b)) ? path_a : path_b;
	
}