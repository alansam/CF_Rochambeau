//  @see: https://en.wikipedia.org/wiki/Rock_paper_scissors

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <initializer_list>
#include <map>
#include <random>

using namespace std::literals::string_literals;

enum rps : uint8_t {
  rock, paper, scissors, lizard, spock,
};
static
std::array<std::string, 5> const choices {
  "rock"s, "paper"s, "scissors"s,
  "lizard"s, "spock"s,
};

enum wtl : uint8_t { win, tie, loss, };
static
std::array<std::string, 3> result {
  "win"s, "tie"s, "loss"s,
};

enum game : uint8_t { Short = 3u, Long = 5u, };

// . : r p x l s
// r : o - + + -
// p : + o - - +
// x : - + o + -
// l : - + - o +
// s : + - + - o
static
std::map<rps, std::array<wtl, 5ul>> const rules {
//    rock.      paper.     scissors.  lizard.    spock.
  {rps::rock,
    { wtl::tie , wtl::loss, wtl::win , wtl::win , wtl::loss, }},
  {rps::paper,
    { wtl::win , wtl::tie , wtl::loss, wtl::loss, wtl::win , }},
  {rps::scissors,
    { wtl::loss, wtl::win , wtl::tie , wtl::win , wtl::loss, }},
  {rps::lizard,
    { wtl::loss, wtl::win , wtl::loss, wtl::tie , wtl::win , }},
  {rps::spock,
    { wtl::win , wtl::loss, wtl::win , wtl::loss, wtl::tie , }},
};

/*
 *  MARK:  computer_says()
 */
auto computer_says(game gamesz = game::Long) -> rps {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> dist(0u, gamesz - 1);

  return static_cast<rps>(dist(gen));
}

/*
 *  MARK:  player_says()
 */
auto player_says(game gamesz = game::Long) -> rps {
  auto choice { rps::scissors };
  return static_cast<rps>(choice);
}

/*
 *  MARK:  winner()
 */
auto winner(rps computer_said, rps player_said) -> wtl const {
  auto const & rule { rules.at(player_said) };
  auto const rzlt = rule.at(computer_said);

  return rzlt;
}

/*
 *  MARK:  test_winner()
 */
auto test_winner(game gamesz = game::Long) -> void {
  auto graph = [](wtl rzlt) -> char {
    auto gc { 'o' };
    switch (rzlt) {
      case wtl::win:
        gc = '+';
        break;
      case wtl::loss:
        gc = '-';
        break;
      case wtl::tie:
        [[fallthrough]];
      default:
        gc = 'o';
        break;
    }
    return gc;
  };

  std::initializer_list<rps> const v_rpxls {
    rps::rock, rps::paper, rps::scissors, rps::lizard, rps::spock, 
  };
  std::initializer_list<rps> const v_rpx {
    rps::rock, rps::paper, rps::scissors,
  };
  std::vector<rps> v_rpsx;

  v_rpsx = (gamesz == game::Long ? v_rpxls : v_rpx);

  std::cout << std::setw(8) << std::string(8, '.')
            << (gamesz == game::Long
               ? ":   r  p  x  l  s\n"s
               : ":   r  p  x\n"s);
  for (auto const & computer : v_rpsx) {
    std::cout << std::setw(8) << choices.at(computer) << ": "s;
    for (auto const & player : v_rpsx) {
      auto const rzlt = winner(player, computer);
      std::cout << std::setw(3) << graph(rzlt);
    }
    std::cout << std::endl;
  }

  return;
}

/*
 * MARK: main()
 */
int main(int argc, char const * argv[]) {

  std::cout << std::string(60, '.') << '\n';
  for (size_t i_ = 0ul; i_ < 10ul; ++i_) {
    auto computer_said = computer_says();
    auto player_said = player_says();
    auto const rzlt = winner(computer_said, player_said);
    std::cout << "Computer said: "s << choices.at(computer_said) << '\n';
    std::cout << "  Player said: "s << choices.at(player_said) << '\n';
    std::cout << std::setw(3) << static_cast<uint16_t>(rzlt) << ", "s << result[rzlt] << '\n';
    std::cout << std::endl;
  }

  test_winner();

  std::cout << std::string(60, '.') << '\n';
  for (size_t i_ = 0ul; i_ < 10ul; ++i_) {
    auto computer_said = computer_says(game::Short);
    auto player_said = player_says();
    auto const rzlt = winner(computer_said, player_said);
    std::cout << "Computer said: "s << choices.at(computer_said) << '\n';
    std::cout << "  Player said: "s << choices.at(player_said) << '\n';
    std::cout << std::setw(3) << static_cast<uint16_t>(rzlt) << ", "s << result[rzlt] << '\n';
    std::cout << std::endl;
  }

  test_winner(game::Short);

  return 0;
}
