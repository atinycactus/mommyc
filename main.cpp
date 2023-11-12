#include <fmt/args.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <new>
#include <optional>
#include <random>
#include <ranges>
#include <string_view>
#include <vector>

#include "responses.h"

namespace {

inline constexpr auto kDefaultLittle{"girl"};
inline constexpr auto kDefaultRoles{"mommy"};
inline constexpr auto kDefaultPronouns{"her"};
inline constexpr auto kDefaultEmotes{"❤️/💖/💗/💓/💞"};

std::optional<const char*> GetEnv(const char* var) noexcept {
  if (auto v = std::getenv(var)) {
    return v;
  }

  return std::nullopt;
}

int Subprocess(const char* file, char** argv) noexcept {
  auto pid{::fork()};
  if (pid < 0) {
    std::perror("fork");
    return EXIT_FAILURE;
  } else if (pid == 0) {
    // child
    ::execvp(file, argv);
    ::_exit(EXIT_FAILURE);
  } else {
    // parent
    int s;
    do {
      ::waitpid(pid, &s, WUNTRACED);
    } while (!WIFEXITED(s) && !WIFSIGNALED(s));
    return s;
  }
}

std::string_view Choose(std::string_view choices) {
  const std::size_t n(std::ranges::count(choices, '/'));
  if (n == 0) {
    return choices;
  }

  using std::operator""sv;
  auto split{std::views::split(choices, "/"sv)};

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<std::size_t> dis{0, n};

  const auto pick{dis(gen)};
  std::string_view ret{choices};
  for (std::size_t i = 0; auto r : split) {
    if (i++ == pick) {
      ret = std::string_view{r.begin(), r.end()};
    }
  }

  return ret;
}

}  // namespace

int main(int argc, char** argv) {
  // this assertion makes life easier for lazy people (me!)
  if (argc == 0) {
    // TODO: mommy error message~
    fmt::print(stderr, "environment sucks!!!!\n");
    return EXIT_FAILURE;
  }

  const auto littles{GetEnv("MOMMYS_LITTLE").value_or(kDefaultLittle)};
  const auto pronouns{GetEnv("MOMMYS_PRONOUNS").value_or(kDefaultPronouns)};
  const auto roles{GetEnv("MOMMYS_ROLES").value_or(kDefaultRoles)};
  const auto emotes{GetEnv("MOMMYS_EMOTES").value_or(kDefaultEmotes)};

  std::string_view program_name{argv[0]};

  const char* compiler;
  if (program_name.ends_with("cxx") || program_name.ends_with("c++")) {
    compiler = GetEnv("MOMMY_CXX").value_or("c++");
  } else {
    compiler = GetEnv("MOMMY_CC").value_or("cc");
  }

  const auto compiler_len{std::strlen(compiler) + 1};

  auto argv0{std::make_unique<char[]>(compiler_len)};
  std::strncpy(argv0.get(), compiler, compiler_len);

  argv[0] = argv0.get();

  int ret{Subprocess(compiler, argv)};

  responses::Type resp_type;
  fmt::text_style style{};
  if (ret == EXIT_SUCCESS) {
    resp_type = responses::Type::kPositive;
  } else {
    resp_type = responses::Type::kNegative;
    style = fmt::fg(fmt::terminal_color::red);
  }

  // for now we'll hard-code the chill mood~
  auto resp{responses::Get<responses::Chill>(resp_type)};

  const auto chosen_little{Choose(littles)};
  const auto chosen_pronouns{Choose(pronouns)};
  const auto chosen_role{Choose(roles)};
  const auto chosen_emote{Choose(emotes)};

  auto msg{fmt::format(fmt::runtime(resp),
                       fmt::arg("AFFECTIONATE_TERM", chosen_little),
                       fmt::arg("MOMMYS_ROLE", chosen_role),
                       fmt::arg("MOMMYS_PRONOUN", chosen_pronouns))};

  fmt::print(stderr, "{} {}\n", fmt::styled(msg, style), chosen_emote);

  return ret;
}
