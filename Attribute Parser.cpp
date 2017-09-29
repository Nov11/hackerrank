#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
class Parser {
	struct Node {
		string name;
		map<string, string> kv;
		vector<Node*> children;
	};
	struct Param {
		vector<string> v;
		string att;
	};
	Param extract(string& str) {
		Param result;
		auto pos = -1;
		while (true) {
			auto ret = str.find('.', pos + 1);
			if (ret == string::npos) {
				ret = str.find('~', pos + 1);
				if (ret == string::npos) {
					result.v = {};
					return result;
				}
			}
			result.v.push_back(str.substr(pos + 1, ret - pos - 1));
			pos = ret;
			if (str[ret] == '~') {
				result.att = str.substr(ret + 1);
				break;
			}
		}
		return result;

	}
	Node* findChild(Node* root, string name) {
		for (auto item : root->children) {
			if (item->name == name) { return item; }
		}
		return nullptr;
	}
	void search(Node* root, Param p, void(*func)(string val, bool found)) {
		if (p.v.empty()) { func("", false); return; }
		Node* parent = root;
		for (int i = 0; i < p.v.size(); i++) {
			auto ret = findChild(parent, p.v[i]);
			if (!ret) { func("", false); return; }
			parent = ret;
		}
		auto& ref = parent->kv;
		if (ref.find(p.att) == ref.end()) {
			func("", false); return;
		}
		func(ref[p.att], true);
	}
	bool fillAttribute(string& s, size_t& pos, Node* result) {
		while (pos < s.size() && s[pos] == ' ') { pos++; }
		if (pos == s.size() || s[pos] == '>') { return false; }
		string key;
		while (pos < s.size() && s[pos] != ' ') { key.push_back(s[pos]); pos++; }
		pos += 3;
		string value;
		pos++;
		while (pos < s.size() && s[pos] != '"') { value.push_back(s[pos]); pos++; }
		result->kv[key] = value;
		pos++;
		return true;
	}
	Node* parse(string line) {
		Node* result = new Node;
		auto blank = line.find(' ', 0);
		if (blank == string::npos) {
			result->name = line.substr(1, line.size() - 2);
			return result;
		}
		result->name = line.substr(1, blank - 1);
		auto pos = blank + 1;
		while (fillAttribute(line, pos, result));
		return result;
	}
	int n;

	Node* work(string line) {
		Node* result = parse(line);
		while (true) {
			string tmp;
			getline(cin, tmp);
			n--;
			if (tmp[1] == '/') {
				return result;
			}

			auto ret = work(tmp);
			result->children.push_back(ret);
		}
	}
	Node* work() {
		string tmp;
		getline(cin, tmp);
		n--;
		return work(tmp);
	}
	Node* root = nullptr;
public:
	void build(int lineOfInput) {
		n = lineOfInput;
		root = new Node;
		while (n > 0) {
			root->children.push_back(work());
		}
	}

	void searchAttribute(string param, void(*func)(string val, bool found)) {
		auto p = extract(param);
		search(root, p, func);
	}
};
void callback(string val, bool found) {cout << (found ? val : "Not Found!") << endl;  }
int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	Parser p;
	int n, q;
	cin >> n >> q;
	getchar();

	p.build(n);

	for (int i = 0; i < q; i++) {
		string tmp;
		getline(cin, tmp);
		p.searchAttribute(tmp, callback);
	}
	return 0;
}