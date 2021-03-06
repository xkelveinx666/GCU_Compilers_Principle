#pragma once
#include <vector>
#include "LexicalCode.h"
#include "TypeCode.h"
#define LexicalCodeList LexicalCodeListClass*
using namespace std;

class LexicalCodeListClass {
   public:
    void add(LexicalCode l) { this->vec.push_back(l); }
    void addLexicalCode(string original, int typeCode) {
        LexicalCode lc = new LexicalCodeClass();
        lc->setOriginal(original);
        lc->setTypeCode(typeCode);
        lc->setType(getTypeByTypeCode(typeCode));
        lc->setOutPut(getValue(original, typeCode));
        this->add(lc);
    }
    void show() {
        int index = 0;
        vector<LexicalCode>::iterator begin = this->vec.begin();
        vector<LexicalCode>::iterator end = this->vec.end();
        while (begin != end) {
            index++;
            (*begin)->showLexicalCode();
            begin++;
        }
    }

   private:
    vector<LexicalCode> vec;
};