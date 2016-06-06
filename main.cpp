#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <algorithm>
using namespace std;

int digits(double x) {
  int ans = 0;
  x = abs(x * pow(10, 7));
  for (x; x >= 1; x = x/10) ans++;
  return ans;
}

struct Point
{
  double x, y;

  void operator=(const Point & a) {
    x = a.x;
    y = a.y;
  }

  bool operator<(const Point& a) const{
    if (abs(x - a.x) < 0.0000001) return y < a.y;
    return x < a.x;
  }

  bool operator==(const Point& a) const {
    return (abs(x  - a.x) < 0.0000001) && (abs(y - a.y) < 0.0000001);
  }

  string toString() const {
    ostringstream oss;
    oss << setprecision(digits(x)) << "(" << x << ", " << setprecision(digits(y)) << y << ")";
    return oss.str();
  }
  
};

struct PointPair
{
  Point x, y;

  bool operator<(const PointPair& a) const {
    if (x == a.x) return y < a.y;
    return x < a.x;
  }

  bool operator==(const PointPair& a) const {
    if (x == a.x) return y == a.y;
    else if (x == a.y) return y == a.x;
    else return false;
  }

  string toString() const {
    ostringstream oss;
    oss << x.toString() << " " << y.toString();
    return oss.str();
  }
};

ostream& operator<<(ostream &outs, const PointPair& pp) {
  return outs << pp.toString();
}

bool pCompare(const struct Point & a, const struct Point & b) {
  if (abs(a.x - b.x) < 0.0000001) return a.y < b.y;
  return a.x < b.x;
}

bool pCompare2(const struct Point & a, const struct Point & b) {
  if (abs(a.y - b.y) < 0.0000001) return a.x < b.x;
  return a.y < b.y;
}

bool pCompare3(const struct PointPair &a, const struct PointPair &b) {
  return a < b;
}

double distance(const struct Point &a, const struct Point &b) {
  return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void brutealg(const vector<Point> &v) {
  double minDistance = DBL_MAX;
  vector<PointPair> ans;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i+1; j < v.size(); j++) {
      double tempDistance = distance(v[i], v[j]); 
      if (abs(tempDistance - minDistance) < 0.0000001) {
	double xx = round(v[i].x * pow(10, 7))/pow(10, 7);
	double xy = round(v[i].y * pow(10, 7))/pow(10, 7);
	double yx = round(v[j].x * pow(10, 7))/pow(10, 7);
	double yy = round(v[j].y * pow(10, 7))/pow(10, 7);
	Point x, y;
	x.x = xx;
	x.y = xy;
	y.x = yx;
	y.y = yy;
	PointPair pp;
	if (x < y) {
	  pp.x = x;
	  pp.y = y;
	}
	else {
	  pp.x = y;
	  pp.y = x;
	}
	bool flag = false;
	for (auto & ppp: ans) {
	  if (pp ==  ppp) flag = true;
	  if (flag) break;
	}
	if (flag) {}
	else ans.push_back(pp);
      }
      else if (tempDistance < minDistance) {
	minDistance = tempDistance;
	ans.clear();
        double xx = round(v[i].x * pow(10, 7))/pow(10, 7);
        double xy = round(v[i].y * pow(10, 7))/pow(10, 7);
        double yx = round(v[j].x * pow(10, 7))/pow(10, 7);
        double yy = round(v[j].y * pow(10, 7))/pow(10, 7);
        Point x, y;
        x.x = xx;
        x.y = xy;
        y.x = yx;
        y.y = yy;
	PointPair pp;
	if (x < y) {
	  pp.x = x;
	  pp.y = y;
	}
	else {
	  pp.x = y;
	  pp.y = x;
	}
        bool flag = false;
        for (auto & ppp: ans) {
          if (pp ==  ppp) flag = true;
          if (flag) break;
        }
        if (flag) {}
        else ans.push_back(pp);
      }
    }
  }
  minDistance = round(minDistance * pow(10, 7))/ pow(10, 7);
  cout << setprecision(digits(minDistance)) << "closest pair distance: " << minDistance << endl;
  sort(ans.begin(), ans.end(), pCompare3);
  for (const auto & pp: ans) cout << pp << endl;
}

vector<Point> recursive(const vector<Point> & p) {
  if (p.size() < 3) return p;
  int mid = p.size()/2;
  vector<Point> a;
  vector<Point> b;
  for (int i = 0; i < mid; i++) a.push_back(p[i]);
  for (int j = mid; j < p.size(); j++) b.push_back(p[j]);
  double minDistance = DBL_MAX;
  vector<Point> left = recursive(a);
  vector<Point> right = recursive(b);
  vector<Point> ans;
  if (left.size() >= 2) {
    double tempDistance = distance(left[0], left[1]);
    if (abs(tempDistance - minDistance) < 0.0000001) {}
    else if (tempDistance < minDistance) { 
      minDistance = tempDistance;
      ans = left;
    }
  }
  if (right.size() >= 2) {
    double tempDistance = distance(right[0], right[1]);
    if (abs(tempDistance - minDistance) < 0.0000001) {
      for (const auto & point : right) ans.push_back(point);
    }
    else if (tempDistance < minDistance) {
      minDistance = tempDistance;
      ans = right;
    }
  }
  vector<Point> strip;
  double lowerbound = p[mid].x - minDistance;
  double upperbound = p[mid].x + minDistance;
  for (const auto & point: p) {
    if (point.x >= lowerbound && point.x <= upperbound) strip.push_back(point);
  }
  sort(strip.begin(), strip.end(), pCompare2);
  for (int i = 0; i < strip.size(); i++) {
    for (int j = i+1; j < strip.size(); j++) {
      if (strip[i].y >= (strip[j].y - minDistance) && strip[i].y <= (strip[j].y + minDistance)) {
	double tempDistance = distance(strip[i], strip[j]);
	if (abs(tempDistance - minDistance) < 0.0000001) {
	  if (strip[i] < strip[j]) {
	    ans.push_back(strip[i]);
	    ans.push_back(strip[j]);
	  }
	  else {
	    ans.push_back(strip[j]);
	    ans.push_back(strip[i]);
	  }
	}
	else if (tempDistance < minDistance) {
	  minDistance = tempDistance;
	  ans.clear();
	  if (strip[i] < strip[j]) {
	    ans.push_back(strip[i]);
	    ans.push_back(strip[j]);
	  }
	  else {
	    ans.push_back(strip[j]);
	    ans.push_back(strip[i]);
	  }
	}
      }
    }
  }
  return ans;
}

void basicalg(vector<Point> & v) {
  vector<Point> points;
  sort(v.begin(), v.end(), pCompare);
  points = recursive(v);
  double tempDistance = distance(points[0], points[1]);
  vector<PointPair> ans;
  for (int i = 0; i < points.size(); i += 2) {
    double xx = round(points[i].x * pow(10, 7))/pow(10, 7);
    double xy = round(points[i].y * pow(10, 7))/pow(10, 7);
    double yx = round(points[i+1].x * pow(10, 7))/pow(10, 7);
    double yy = round(points[i+1].y * pow(10, 7))/pow(10, 7);
    Point x, y;
    x.x = xx;
    x.y = xy;
    y.x = yx;
    y.y = yy;
    PointPair pp;
    if (x < y) {
      pp.x = x;
      pp.y = y;
    }
    else {
      pp.x = y;
      pp.y = x;
    }
    bool flag = false;
    for (auto & ppp: ans) {
      if (pp ==  ppp) flag = true;
      if (flag) break;
    }
    if (flag) {}
    else ans.push_back(pp);
  }
  double minDistance = round(tempDistance * pow(10, 7))/ pow(10, 7);
  cout << setprecision(digits(minDistance)) << "closest pair distance: " << minDistance << endl;
  sort(ans.begin(), ans.end(), pCompare3);
  for (const auto & pp: ans) cout << pp << endl;
}

vector<Point> recursive2(const vector<Point> & p, const vector<Point> & q) {
  if (p.size() < 3) return p;
  int mid = p.size()/2;
  vector<Point> a;
  vector<Point> b;
  vector<Point> c;
  vector<Point> d;
  for (int i = 0; i < mid; i++) a.push_back(p[i]);
  for (int j = mid; j < p.size(); j++) b.push_back(p[j]);
    for (int i = 0; i < q.size(); i++) {
    if (q[i] < p[mid]) c.push_back(q[i]);
    else d.push_back(q[i]);
   }
  double minDistance = DBL_MAX;
  vector<Point> left = recursive2(a,c);
  vector<Point> right = recursive2(b,d);
  vector<Point> ans;
  if (left.size() >= 2) {
    double tempDistance = distance(left[0], left[1]);
    if (abs(tempDistance - minDistance) < 0.0000001) {}
    else if (tempDistance < minDistance) {
      minDistance = tempDistance;
      ans = left;
    }
  }
  if (right.size() >= 2) {
    double tempDistance = distance(right[0], right[1]);
    if (abs(tempDistance - minDistance) < 0.0000001) {
      for (const auto & point : right) ans.push_back(point);
    }
    else if (tempDistance < minDistance) {
      minDistance = tempDistance;
      ans = right;
    }
  }
  vector<Point> strip;
  double lowerbound = p[mid].x - minDistance;
  double upperbound = p[mid].x + minDistance;
  for (const auto & point: q) {
    if (point.x >= lowerbound && point.x <= upperbound) strip.push_back(point);
  }
  for (int i = 0; i < strip.size(); i++) {
    for (int j = i+1; j < strip.size(); j++) {
      if (strip[i].y >= (strip[j].y - minDistance) && strip[i].y <= (strip[j].y + minDistance)) {
        double tempDistance = distance(strip[i], strip[j]);
        if (abs(tempDistance - minDistance) < 0.0000001) {
          if (strip[i] < strip[j]) {
            ans.push_back(strip[i]);
            ans.push_back(strip[j]);
          }
          else {
            ans.push_back(strip[j]);
            ans.push_back(strip[i]);
          }
        }
        else if (tempDistance < minDistance) {
          minDistance = tempDistance;
          ans.clear();
          if (strip[i] < strip[j]) {
            ans.push_back(strip[i]);
            ans.push_back(strip[j]);
          }
          else {
            ans.push_back(strip[j]);
            ans.push_back(strip[i]);
          }
        }
      }
    }
  }
  return ans;
}

void optimalalg(vector<Point> & v) {
  vector<Point> p;
  vector<Point> q;
  vector<Point> points;
  for (const auto & point : v) {
    p.push_back(point);
    q.push_back(point);
  }
  sort(p.begin(), p.end(), pCompare);
  sort(q.begin(), q.end(), pCompare2);
  points = recursive2(p, q);
  double tempDistance = distance(points[0], points[1]);
  vector<PointPair> ans;
  for (int i = 0; i < points.size(); i += 2) {
    double xx = round(points[i].x * pow(10, 7))/pow(10, 7);
    double xy = round(points[i].y * pow(10, 7))/pow(10, 7);
    double yx = round(points[i+1].x * pow(10, 7))/pow(10, 7);
    double yy = round(points[i+1].y * pow(10, 7))/pow(10, 7); 
    Point x, y;
    x.x = xx;
    x.y = xy;
    y.x = yx;
    y.y = yy;
    PointPair pp;
    if (x < y) {
      pp.x = x;
      pp.y = y;
    }
    else {
      pp.x = y;
      pp.y = x;
    }
    bool flag = false;
    for (auto & ppp: ans) {
      if (pp ==  ppp) flag = true;
      if (flag) break;
    }
    if (flag) {}
    else ans.push_back(pp);
  }
  double minDistance = round(tempDistance * pow(10, 7))/ pow(10, 7);
  cout << setprecision(digits(minDistance)) << "closest pair distance: " << minDistance << endl;
  sort(ans.begin(), ans.end(), pCompare3);
  for (const auto & pp: ans) cout << pp << endl;

}

vector<Point> parse() {
  string s;
  vector<Point> ans;
  int i = 0;
  while (getline(cin, s)) {
    stringstream strstr(s);
    istream_iterator<string> it(strstr);
    istream_iterator<string> end;
    vector<string> results(it, end);
    if (results.size() != 2) {}
    else {
      char *p;
      char *q;
      strtod(results[0].c_str(), &p);
      strtod(results[1].c_str(), &q);
      if ( *p == 0 && *q == 0) {
	Point a;
	a.x = stod(results[0], NULL);
	a.y = stod(results[1], NULL);
	bool flag = false;
	for (auto & point: ans) {
	  if (point == a) flag = true;
	  if (flag) break;
	}
	if (flag) {}
	else ans.push_back(a);
      }
    }
  }	
  if (ans.size() < 2) {
    cout << "Two or more points are required" << endl;
    exit(0);
  }
  return ans;
}

int main(int argc, char *argv[]) {
  char closestPair[] = "./closestPair";
  char brute[] = "brute";
  char basic[] = "basic";
  char optimal[] = "optimal";
  if (argc == 2 && strcmp(argv[0], closestPair) == 0) {
    if (strcmp(argv[1], brute) == 0) {
      vector<Point> v = parse();
      brutealg(v);
    }
    else if (strcmp(argv[1], basic) == 0) {
      vector<Point> v = parse();
      basicalg(v);
    }
    else if (strcmp(argv[1], optimal) == 0) {
      vector<Point> v = parse();
      optimalalg(v);
    }
    else {
      cout << "usage is ./closestPair [brute|basic|optimal]" << endl;
      exit(0);
    }
  }
  else {
    cout << "usage is ./closestPair [brute|basic|optimal]" << endl;
    exit(0);
  }
}
  
