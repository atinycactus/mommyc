#ifndef MOMMY_RESPONSES_H
#define MOMMY_RESPONSES_H

#include <iterator>
#include <random>
#include <string_view>

namespace responses {

enum class Type {
  kPositive,
  kNegative,
};

//clang-format off
struct Chill {
  inline static constexpr std::string_view kPositive[] = {
      "*pets your head*",
      "*gives you scritches*",
      "you're such a smart cookie~",
      "that's a good {AFFECTIONATE_TERM}~",
      "{MOMMYS_ROLE} thinks {MOMMYS_PRONOUN} little {AFFECTIONATE_TERM} earned a big hug~",
      "good {AFFECTIONATE_TERM}~\n{MOMMYS_ROLE}'s so proud of you~",
      "aww, what a good {AFFECTIONATE_TERM}~\n{MOMMYS_ROLE} knew you could do it~",
      "you did it~!",
      "{MOMMYS_ROLE} loves you~",
      "*gives you a sticker*",
  };

  inline static constexpr std::string_view kNegative[] = {
      "{MOMMYS_ROLE} believes in you~",
      "don't forget to hydrate~",
      "aww, you'll get it next time~",
      "do you need {MOMMYS_ROLE}'s help~?",
      "{MOMMYS_ROLE} still loves you no matter what~",
      "oh no did {MOMMYS_ROLE}'s little {AFFECTIONATE_TERM} make a big mess~?",
      "{MOMMYS_ROLE} knows {MOMMYS_PRONOUN} little {AFFECTIONATE_TERM} can do better~",
      "{MOMMYS_ROLE} still loves you~",
      "just a little further, sweetie~",
  };
};
//clang-format on

template <class T>
concept IsMood = requires {
                   std::string_view(T::kPositive[0]);
                   std::string_view(T::kNegative[0]);
                 };

template <class Mood>
  requires IsMood<Mood>
inline static std::string_view Get(Type response_type) {
  std::random_device rd;
  std::mt19937 gen{rd()};

  std::size_t n;
  if (response_type == Type::kPositive) {
    n = std::size(Mood::kPositive);
  } else {
    n = std::size(Mood::kNegative);
  }

  std::uniform_int_distribution<std::size_t> dis{0, n - 1};

  if (response_type == Type::kPositive) {
    return Mood::kPositive[dis(gen)];
  } else {
    return Mood::kNegative[dis(gen)];
  }
}

}  // namespace responses

#endif  // MOMMY_RESPONSES_H
