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

#ifdef ENABLE_LEWD
struct Thirsty {
  inline static constexpr std::string_view kPositive[] = {
    "*tugs your leash*\nthat's a VERY good {affectionate_term}~",
    "*runs {pronoun} fingers through your hair* good {affectionate_term}~ keep going~",
    "*smooches your forehead*\ngood job~",
    "*nibbles on your ear*\nthat's right~\nkeep going~",
    "*pats your butt*\nthat's a good {affectionate_term}~",
    "*drags {pronoun} nail along your cheek*\nsuch a good {affectionate_term}~",
    "*bites {pronoun} lip*\nmhmm~",
    "give {role} a kiss~",
    "*heavy breathing against your neck*",
  };

  inline static constexpr std::string_view kNegative[] = {
    "you're so cute when you're flustered~",
    "do you think you're going to get a reward from {role} like that~?",
    "*grabs your hair and pulls your head back*\nyou can do better than that for {role} can't you~?",
    "if you don't learn how to code better, {role} is going to put you in time-out~",
    "does {role} need to give {pronoun} little {affectionate_term} some special lessons~?",
    "you need to work harder to please {role}~",
    "gosh you must be flustered~",
    "are you just keysmashing now~?\ncute~",
    "is {role}'s little {affectionate_term} having trouble reaching the keyboard~?",
  };
};

struct Yikes {
  inline static constexpr std::string_view kPositive[] = {
    "keep it up and {role} might let you cum you little {denigrating_term}~",
    "good {denigrating_term}~\nyou've earned five minutes with the buzzy wand~",
    "mmm~ come taste {role}'s {part}~",
    "*slides {pronoun} finger in your mouth*\nthat's a good little {denigrating_term}~",
    "you're so good with your fingers~\n{role} knows where {pronoun} {denigrating_term} should put them next~",
    "{role} is getting hot~",
    "that's a good {denigrating_term}~",
    "yes~\nyes~~\nyes~~~",
    "{role}'s going to keep {pronoun} good little {denigrating_term}~",
    "open wide {denigrating_term}. you've earned {role}'s {part}~",
    "do you want {role}'s {part}? Keep this up and you'll earn it~",
    "oooh~ what a good {denigrating_term} you are.~",
  };

  inline static constexpr std::string_view kNegative[] = {
    "you filthy {denigrating_term}~\nyou made a mess, now clean it up~\nwith your tongue~",
    "*picks you up by the throat*\npathetic~",
    "*drags {pronoun} claws down your back*\ndo it again~",
    "*brandishes {pronoun} paddle*\ndon't make me use this~",
    "{denigrating_term}.\n{denigrating_term}~\n{denigrating_term}~~",
    "get on your knees and beg {role} for forgiveness you {denigrating_term}~",
    "{role} doesn't think {pronoun} little {denigrating_term} should have permission to wear clothes anymore~",
    "never forget you belong to {role}~",
    "does {role} need to put you in the {denigrating_term} wiggler~?",
    "{role} is starting to wonder if you should just give up and become {pronoun} breeding stock~",
    "on your knees {denigrating_term}~",
    "oh dear. {role} is not pleased",
    "one spank per error sounds appropriate, don't you think {denigrating_term}?",
    "no more {part} for you {denigrating_term}",
  };
};
#endif
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
