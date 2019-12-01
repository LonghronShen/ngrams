#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <ngram/char_ngrams.h>
#include <ngram/text2wfreq.h>

/**
 * display help information
 */
void Text2wfreq::showHelp() {
  printf("\nUsage: ngrams [options]\n");
  printf("Compute all the word/char frequencies for the given text file.\n");
  printf("Options:\n");
  printf("--n=N			Number of ngrams, the default is %d-grams.\n",
         Config::DEFAULT_NGRAM_N);
  printf("--type=T		character, word or byte, the default is %s.\n",
         (int)Config::DEFAULT_NGRAM_TYPE == (int)Config::WORD_NGRAM
             ? "word"
             : (int)Config::DEFAULT_NGRAM_TYPE == (int)Config::CHAR_NGRAM
                   ? "character"
                   : "byte");
  printf("--in=training files	default to stdin.\n");
  printf("--out=output file	default to stdout. ( currently stdout only "
         ")\n\n");
}

int main(int argc, char *argv[]) {
  time_t startTime;
  time(&startTime);
  Text2wfreq tf;

  if (tf.getOptions(argc, argv)) {
    // tf.printOptions();
  } else {
    tf.showHelp();
    return 0;
  }
  INgrams *ngrams = NULL;
  if (tf.getNgramType() == Config::WORD_NGRAM) { // word ngrams
    ngrams = new WordNgrams(tf.getNgramN(), tf.getInFileName().c_str(),
                            tf.getOutFileName().c_str());
  } else if (tf.getNgramType() == Config::CHAR_NGRAM) { // char ngrams
    ngrams = new CharNgrams(tf.getNgramN(), tf.getInFileName().c_str(),
                            tf.getOutFileName().c_str());
  } else if (tf.getNgramType() == Config::BYTE_NGRAM) { // byte ngrams
    ngrams = new ByteNgrams(tf.getNgramN(), tf.getInFileName().c_str(),
                            tf.getOutFileName().c_str());
  }

  time_t midTime;
  time(&midTime);
  fprintf(stderr, "ngrams have been generated, start outputing.\n");
  if (ngrams) {
    ngrams->output();
    delete ngrams;
    ngrams = NULL;
  }
  time_t endTime;
  time(&endTime);

  fprintf(stderr, "\nSubtotal: %ld seconds for generating ngrams.\n",
          midTime - startTime);
  fprintf(stderr, "Subtotal: %ld seconds for outputing ngrams.\n",
          endTime - midTime);
  fprintf(stderr, "Total %ld seconds.\n", endTime - startTime);
}
