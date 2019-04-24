#include "types.hpp"
#include <iostream>


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

void Map::set_tile(const int i, const int j, const FIELD f)
{
	if (in_range(i, j))
	{
		map_[i][j] = f;
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

// Halmazbővítéses megoldás
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

double Map::get_length(const FlightPath& p) const
{
	return 0.0;
}

double Map::get_distance(const City& a, const City& b) const
{
	return 0.0;
}

FlightPath Map::closest_brute_force(const std::vector<City>& cities) const
{
	return {{0,0}, {0,0}};	
}

FlightPath Map::find_shortest(const std::vector<City>& x_cities, const std::vector<City>& y_cities) const
{
	return brute_force(x_cities);
}

std::set<City> Map::get_cities() const
{
	return cities_;
}

FlightPath Map::get_shortest_flightpath() const
{	
	std::vector<City> v;
	return find_shortest(v, v);
}