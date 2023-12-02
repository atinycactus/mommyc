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
    "that's a good {affectionate_term}~",
    "{role} thinks {pronoun} little {affectionate_term} earned a big hug~",
    "good {affectionate_term}~\n{role}'s so proud of you~",
    "aww, what a good {affectionate_term}~\n{role} knew you could do it~",
    "you did it~!",
    "{role} loves you~",
    "*gives you a sticker*",
    "*boops your nose*",
    "*wraps you in a big hug*",
    "well done~!\n{role} is so happy for you~",
    "what a good {affectionate_term} you are~",
    "that's {role}'s clever little {affectionate_term}~",
    "you're doing so well~!",
    "you're making {role} so happy~",
    "{role} loves {pronoun} cute little {affectionate_term}~",
  };

  inline static constexpr std::string_view kNegative[] = {
    "{role} believes in you~",
    "don't forget to hydrate~",
    "aww, you'll get it next time~",
    "do you need {role}'s help~?",
    "everything's gonna be ok~",
    "{role} still loves you no matter what~",
    "oh no did {role}'s little {affectionate_term} make a big mess~?",
    "{role} knows {pronoun} little {affectionate_term} can do better~",
    "{role} still loves you~",
    "{role} thinks {pronoun} little {affectionate_term} is getting close~",
    "it's ok, {role}'s here for you~",
    "oh, darling, you're almost there~",
    "does {role}'s little {affectionate_term} need a bit of a break~?",
    "oops~! {role} loves you anyways~",
    "try again for {role}, {affectionate_term}~",
    "don't worry, {role} knows you can do it~",
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
