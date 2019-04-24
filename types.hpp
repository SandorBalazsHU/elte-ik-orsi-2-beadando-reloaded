#ifndef TYPES_HPP
#define TYPES_HPP

#include <array>
#include <cstdint>
#include <iosfwd>
#include <set>
#include <tuple>
#include <vector>
#include <atomic>

enum class FIELD : uint8_t
{
    CANNIBALS,
    DESERT,
    FOREST,
    GOLD_MINE,
    GRASSLAND,
    IRON,
    LAKE,
    SEA,
    SWAMP,
    VILLAGE,
    WHEAT,
	CITY
};

enum class DIRECTION : uint8_t
{
    NORTH_WEST,
    NORTH,
    NORTH_EAST,
    EAST, //not used here
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST //not used here
};

struct Coordinate{
    int x, y;
    Coordinate() : x(0), y(0){}
    Coordinate(int x_, int y_) : x(x_), y(y_){}
    
    Coordinate(const Coordinate&) = default;
    Coordinate& operator=(const Coordinate&) = default;
};
bool operator<(const Coordinate& a, const Coordinate& b);

using Tile = std::pair<Coordinate, FIELD>;

FIELD field_from_int(const int i);

int field_value(const FIELD& f);
int tile_value(const Tile& f);


std::ostream& operator<<(std::ostream& s, const Coordinate& p);
std::ostream& operator<<(std::ostream& s, const DIRECTION& d);
std::ostream& operator<<(std::ostream& s, const FIELD& f);
std::ostream& operator<<(std::ostream& s, const Tile& t);
std::istream& operator>>(std::istream& s, Coordinate& p);

/**
  * new things for 2nd assignment
  */
using City = Coordinate;
using FlightPath = std::pair<City, City>;
//end of new things

class Map{
    int rows_, cols_;
    std::vector<std::vector<FIELD>> map_;
	
	/**
	  * new things for 2nd assignment
	  */
	std::set<City> cities_;
	double get_length(const FlightPath& p) const;
	double get_distance(const City& a, const City& b) const;
	void find_cities();
	FlightPath find_shortest(const std::vector<City>& x_cities, const std::vector<City>& y_cities) const;
	FlightPath closest_brute_force(const std::vector<City>& cities) const;
public:

	FlightPath get_shortest_flightpath() const;
	std::set<City> get_cities() const;
	//end of new things

    bool in_range(const Coordinate& p) const
    {
        return in_range(p.x, p.y);
    }
    
    bool in_range(const int x, const int y) const;

    Map();
    Map(const int r, const int c);

    Map(const std::vector<std::vector<FIELD>>& map) : rows_(map.size()), cols_(map[0].size()), map_(map)
    {
		find_cities();
    }
    
    Map& operator=(const Map&) = default;
    Map& operator=(Map&&) = default;
    Map(const Map&) = default;
    Map(Map&&) = default;
    ~Map() = default;
    
    int rows() const;

    int cols() const;

    Tile tile_at(const Coordinate& p) const
    {
        return tile_at(p.x, p.y);
    }

    Tile tile_at(const int i,const int j) const;
    
    void set_tile(const Tile& t)
    {
        set_tile(std::get<0>(t).x, std::get<0>(t).x, std::get<1>(t));
    }

    void set_tile(const Coordinate p, const FIELD f)
    {
        set_tile(p.x, p.y, f);
    }
    void set_tile(const int i, const int j, const FIELD f);

    Tile tile_in_direction(const Tile& t, const DIRECTION d) const
    {
        return tile_in_direction(std::get<0>(t), d);
    }

    Tile tile_in_direction(const Coordinate& p, const DIRECTION d) const
    {
        return tile_in_direction(p.x, p.y, d);
    }

    //"odd-q" vertical layout, odd columns shoved down
    Tile tile_in_direction(int x, int y, const DIRECTION d) const;
    
    std::set<Tile> get_tiles_in_radius(const Tile& t, const int r) const
    {
        return get_tiles_in_radius(std::get<0>(t).x, std::get<0>(t).y, r);
    }
    
    std::set<Tile> get_tiles_in_radius(const Coordinate& p, const int r) const
    {
        return get_tiles_in_radius(p.x, p.y, r);
    }
    
    std::set<Tile> get_tiles_in_radius(const int i, const int j, const int r) const;
    
    friend std::istream& operator>>(std::istream& s, Map& m);
    friend std::ostream& operator<<(std::ostream& s, const Map& m);
};



#endif
