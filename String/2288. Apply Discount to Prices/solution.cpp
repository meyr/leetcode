/*
 *  time  : O(N)
 *  space : O(N)
 *
 */
class Solution {
public:
    string discountPrices(string sentence, int discount) {
        istringstream iss(sentence);
        string word, rtn{};
        double disc = (100 - discount) / 100.0;
        while(iss >> word) {
            // check whether the word is price or not
            bool isInteger{true};
            if(word[0] == '$') {
                if(word.size() == 1) {
                    isInteger = false;
                } else {
                    for(int i = 1; i < word.size(); ++i) {
                        if(!isdigit(word[i])) {
                            isInteger = false;
                            break;
                        }
                    }
                }
            } else isInteger = false;

            if(isInteger) {
                double val = stod(&word[1]);
                val *= disc;
                long ival = (long)val;
                double dval = val - ival + 0.005;
                rtn += '$' + to_string(ival) + '.';
                for(int i = 0; i < 2; ++i) {
                    dval *= 10.0;
                    rtn += to_string((int)dval);
                    dval -= (int)dval;
                }
                rtn += " ";
            } else
                rtn += word + " ";
        }
        rtn.pop_back();
        return rtn;
    }
};
