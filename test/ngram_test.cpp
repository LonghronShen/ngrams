#include <ngram/char_ngrams.h>
#include <ngram/word_ngrams.h>
#include <ngram/byte_ngrams.h>
#include <ngram/text2wfreq.h>

#include "lest.hpp"

using namespace std;

const lest::test specification[] = {
    CASE("hello world!") {
        auto hw = "Hello, world!";
        EXPECT(hw == hw);
    },
};

int main (int argc, char *argv[]) {
  return lest::run(specification, argc, argv);
}
