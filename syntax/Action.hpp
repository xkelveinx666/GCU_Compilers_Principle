#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include "Operation.hpp"
#include "../string/StrToNumber.h"
#include "../string/Split.hpp"
#include <iostream>

#define ActionTable ActionTableClass *
using namespace std;

class ActionTableClass {
public:
    void readTableFromText(string file) {
        ifstream infile, inLength;
        infile.open(file.data());
        inLength.open(file.data());
        assert(infile.is_open());

        string s;
        int row = 0, col = 0;
        bool isFirstRow = true;
        bool isFirstColumn;
        int rowLen = 0;
        int colLen = 0;
        while (getline(inLength, s)) {
            this->status.push_back(rowLen);
            rowLen++;
        }
        while (getline(infile, s)) {
            isFirstColumn = true;
            vector<string> result = split(s, " ");
            if (result.size() == 0) {
                break;
            }
            OperationList operationList = new vector<Operation>();
            for (col = 0; col < result.size(); col++) {
                if (isFirstRow) {
                    if (isFirstColumn) {
                        isFirstColumn = false;
                        continue;
                    }
                    this->nonTerminators.push_back(result[col]);
                } else if (isFirstColumn) {
                    isFirstColumn = false;
                } else {
                    Operation operation;
                    if (result[col].at(0) == 's') {
                        operation = new OperationClass();
                        operation->setIsOperation(true);
                        operation->setIsMove(true);
                        string numStr = result[col].substr(1);
                        operation->setNumber(strToInt(numStr));
                    } else if (result[col].at(0) == 'r') {
                        operation = new OperationClass();
                        operation->setIsOperation(true);
                        operation->setIsMove(false);
                        string numStr = result[col].substr(1);
                        operation->setNumber(strToInt(numStr));
                    } else if (result[col] == "ACC") {
                        operation = new OperationClass();
                        operation->setIsOperation(true);
                        operation->setIsACC(true);
                    } else {
                        operation = new OperationClass();
                    }
                    operationList->push_back(operation);
                }
            }
            isFirstRow = false;
            this->action.push_back(operationList);
        }
        infile.close();
    }

    void show() {
        auto begin = this->action.begin();
        auto end = this->action.end();
        while (begin != end) {
            for (int j = 0; j < (*begin)->size(); j++) {
                cout << (*(*begin))[j]->getNumber() << " ";
            }
            cout << endl;
            begin++;
        }
    }

private:
    vector<string> nonTerminators;
    vector<int> status;
    vector<OperationList> action;
};