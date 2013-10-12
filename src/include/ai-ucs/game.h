#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <vector>
#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::vector<int> player_vector;

class Game {
  public:
    Game();

  	Game(int w, int h, int x1, int y1, int x2, int y2);

    Game(Game &g);

    enum Move { RIGHT, LEFT, DOWN, UP };
    enum Heuristic { EUCLIDIAN, CANBERRA, KNIGHT };

    static boost::shared_ptr<std::vector<boost::shared_ptr<Game> > >
    load(std::string filename);

    bool
    move(Move m);

    int
    move_cost(Move m);

    bool
    is_game_won() const;

    int
    w() const;

    int
    h() const;

    int
    x1() const;

    double
    x1d() const;

    int
    y1() const;

    double
    y1d() const;

    int
    x2() const;

    double
    x2d() const;

    int
    y2() const;

    double
    y2d() const;

    //std::vector<boost::shared_ptr<player_vector> >
    //history();

    bool
    state_in_history(int x1, int y1, int x2, int y2);

    int
    cost();

    void
    save(std::string filename);

    std::string
    path_to_string();

    void
    save_no_solution(std::string filename);

    double
    euclidian_distance();

    double
    canberra_distance();

    int
    knight_distance();

    double
    astar(Heuristic h);

    bool
    operator ==(const Game &other) const;
  private:
    int _w, _h;

    player_vector
    _players[2];

    std::vector<boost::shared_ptr<player_vector> >
    _history[2];

    int _cost;

    bool
    move_player(int player, Move m);

    void
    save_to_history();
};

class GameComparison {
  bool _reverse;
public:
  GameComparison(const bool& revparam=false);

  bool operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const;
};

class EuclidianComparison {
  bool _reverse;
public:
  EuclidianComparison(const bool& revparam=false);

  bool operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const;
};

class CanberraComparison {
  bool _reverse;
public:
  CanberraComparison(const bool& revparam=false);

  bool operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const;
};

class KnightComparison {
  bool _reverse;
public:
  KnightComparison(const bool& revparam=false);

  bool operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const;
};

class GameSetComparator {
public:
    bool operator() (const boost::shared_ptr<Game>& lhs, const boost::shared_ptr<Game>& rhs) const;
};

typedef std::priority_queue<boost::shared_ptr<Game>, std::vector<boost::shared_ptr<Game> >, GameComparison> game_priority_queue;
typedef std::priority_queue<boost::shared_ptr<Game>, std::vector<boost::shared_ptr<Game> >, EuclidianComparison> euclidian_priority_queue;
typedef std::priority_queue<boost::shared_ptr<Game>, std::vector<boost::shared_ptr<Game> >, CanberraComparison> canberra_priority_queue;
typedef std::priority_queue<boost::shared_ptr<Game>, std::vector<boost::shared_ptr<Game> >, KnightComparison> knight_priority_queue;

#endif /* _GAME_H */

