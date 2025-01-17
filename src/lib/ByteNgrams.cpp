/*******************************************************************
C++ Package of  ngrams
Copyright (C) 2006  Zheyuan Yu

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Read full GPL at http://www.gnu.org/copyleft/gpl.html

Email me at jerryy@gmail.com if you have any question or comment
WebSite: http://www.cs.dal.ca/~zyu

*************************************************************************/

#include <ngram/byte_ngrams.h>

ByteNgrams::ByteNgrams(int newNgramN, const char *newInFileName,
                       const char *newOutFileName, const char *newDelimiters,
                       const char *newStopChars)
    : Ngrams(newNgramN, newInFileName, newOutFileName, newDelimiters,
             newStopChars) {
  addTokens();
}

ByteNgrams::~ByteNgrams() {}

void ByteNgrams::addTokens() {
  // get token string from input file
  auto &inFileName = getInFileName();
  FILE *fp = inFileName.length() > 0 ? fopen(inFileName.c_str(), "rb") : stdin;

  if (fp == NULL) {
    printf("ByteNgrams:addTokens - failed to open file %s\n",
           inFileName.c_str());
  } else {

    int count = 0;
    char c[3];
    c[1] = 0;
    c[2] = 0;
    unsigned char buffer[1024 * 32];

    while (true) {
      size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);

      for (size_t i = 0; i < bytesRead; i++) {
        sprintf(c, "%02x", buffer[i]);
        addToken(c);
        count++;
      }

      if (bytesRead == 0) {
        break;
      }
    }
    // special processing need to be done, if less than NGRAM_N tokens in the
    // whole input text.
    if (count < this->getN()) {
      preParse(count);
    }

    fclose(fp);
  }
}

void ByteNgrams::preParse(int count) {
  TokenNode *p, *newHead;
  p = newHead = head;
  utf8_string ngram;
  ngram.reserve(64);
  while (newHead) {
    p = newHead;
    ngram.empty();
    for (int i = 0; i < count; i++) {
      ngram += p->token;
      // printf("%d ngram %s.\n", i, ngram.c_str() );
      this->addNgram(ngram.c_str(), i + 1);
      if (p == tail) {
        break;
      }
      p = p->next;
    }
    newHead = newHead->next;
  }
}
void ByteNgrams::parse() {
  TokenNode *p, *newHead;
  p = newHead = head;
  utf8_string ngram;
  ngram.reserve(64);
  while (newHead) {
    int n = 0;
    p = newHead;
    ngram.empty();
    while (p) {
      ngram += p->token;
      n++;
      p = p->next;
    }
    // printf("%d ngram %s.\n", n, ngram.c_str() );
    if (n > 0) {
      this->addNgram(ngram.c_str(), n);
    }
    newHead = newHead->next;
  }
}

void ByteNgrams::output() {
  int ngramN = this->getN();

  printf("BEGIN OUTPUT BYTE NGRAMS\n");
  printf("Total %d unique ngrams in %d ngrams.\n", this->count(),
         this->total());
  fprintf(stderr, "Total %d unique ngrams in %d ngrams.\n", this->count(),
          this->total());

  for (int i = 1; i <= ngramN; i++) {
    // Get sorted item list
    ngram_vector<NgramToken *> ngram_vector;
    this->getNgrams(ngram_vector, i);

    printf("\n%d-GRAMS ( Total %d unique ngrams in %d grams )\n", i,
           this->count(i), this->total(i));
    fprintf(stderr, "\n%d-GRAMS ( Total %d unique ngrams in %d grams )\n", i,
            this->count(i), this->total(i));
    printf("------------------------\n");

    size_t count = ngram_vector.count();
    ngram_vector.sort(INgrams::compareFunction);
    for (unsigned j = 0; j < count; j++) {
      NgramToken *ngramToken = ngram_vector[j];

      printf("%s\t%d\n", ngramToken->ngram.c_str(),
             ngramToken->value.frequency);

      delete ngramToken;
    }
  }
}

void ByteNgrams::getNgrams(ngram_vector<NgramToken *> &ngram_vector, int n) {
  // Get sorted item list
  // ngram_vector<string> & keyngram_vector = getKeys( );
  // ngram_vector<NgramValue> & valuengram_vector = getValues( );
  auto &item_vector = getItems();
  size_t count = item_vector.count();
  for (unsigned i = 0; i < count; i++) {
    auto item = item_vector[i];
    if (item && item->value.n == n) {
      ngram_vector.add(new NgramToken(item->key, item->value));
      // ngram_vector.add( NgramToken( item->key, item->value ) );
    }
  }
}
