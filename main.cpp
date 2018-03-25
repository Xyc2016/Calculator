#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>


using namespace std;


vector<string> convert_to_postfix(string s) {
    if (s[0] == '-' || s[0] == '+')
        s = string() + '0' + s;
    stack<string> stk0;
    vector<string> vct;
    string n;
    for (int pos = 0; pos < s.size(); pos++) {
        auto &ch = s[pos];
        if (ch == '(') {
            if (s[pos + 1] == '+' || s[pos + 1] == '-')
                vct.push_back("0");
            stk0.push(string() + ch);
        } else if (ch == ')') {
            if (n.size())
                vct.push_back(n);
            n.clear();
            while (stk0.size() && stk0.top() != "(") {
                vct.push_back(stk0.top());
                stk0.pop();
            }
            stk0.pop();
        } else if (ch == '+' || ch == '-') {
            if (n.size()) {
                vct.push_back(n);
                n.clear();
            }
            while (stk0.size() && (stk0.top() == "*" || stk0.top() == "/" || stk0.top() == "+" || stk0.top() == "-")) {
                vct.push_back(stk0.top());
                stk0.pop();
            }
            stk0.push(string() + ch);
        } else if (ch == '*' || ch == '/') {
            if (n.size()) {
                vct.push_back(n);
                n.clear();
            }
            while (stk0.size() && (stk0.top() == "*" || stk0.top() == "/")) {
                vct.push_back(stk0.top());
                stk0.pop();
            }


            stk0.push(string() + ch);
        } else if (isdigit(ch)) {
            n += ch;
        }

    }

    if (n.size())
        vct.push_back(n);
    while (stk0.size()) {
        vct.push_back(stk0.top());
        stk0.pop();
    }
    return vct;

}

double calculate_postfix(vector<string> vct) {
    stack<double> stk0;
    for (auto s:vct) {
        if (isdigit(s[0])) {
            stk0.push(stod(s));
            continue;
        }
        auto a0 = stk0.top();
        stk0.pop();
        auto a1 = stk0.top();
        stk0.pop();
        if (s == "+")
            stk0.push(a1 + a0);
        else if (s == "-")
            stk0.push(a1 - a0);
        else if (s == "*")
            stk0.push(a1 * a0);
        else stk0.push(a1 / a0);
    }
    return stk0.top();
}

double calculate(string s) {
    return calculate_postfix(convert_to_postfix(s));
}

int main(int argc, char **argv) {
    if(argc==2){
        cout << calculate(argv[1]) << endl;
    }
    return 0;


}