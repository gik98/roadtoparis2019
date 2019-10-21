#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> dd;

double euclidean_distance(dd a, dd b) {
  return sqrt((b.first-a.first)*(b.first-a.first)+(b.second-a.second)*(b.second-a.second));
}

double to_radiant(double angle) {
  return (angle*M_PI)/180.0;
}

int main(void) {
  int n;
  for(;;) {
    cin >> n;
    if(n==0) {
      break;
    }

    vector<dd> end_points;
    double av_x = 0.0;
    double av_y = 0.0;
    string line;
    getline(cin, line);
    for(int i = 0; i < n; i++) {
      getline(cin, line);
      std::istringstream iss(line);

      double pos_x, pos_y, angle;
      string command;
      iss >> pos_x >> pos_y >> command >> angle;
      angle -= (360.0*floor(angle/360.0));

      double val;
      while(iss >> command) {
        iss >> val;
        if(command == "walk") {
          pos_x += val*cos(to_radiant(angle));
          pos_y += val*sin(to_radiant(angle));
        }
        else {
          angle += val;
          angle -= (360.0*floor(angle/360.0));
        }
      }

      av_x += pos_x;
      av_y += pos_y;
      end_points.push_back(dd(pos_x, pos_y));
    }

    av_x /= (double)end_points.size();
    av_y /= (double)end_points.size();

    dd av(av_x, av_y);
    double bad_distance = -1.0;
    for(auto p: end_points) {
      bad_distance = max(bad_distance, euclidean_distance(av, p));
    }

    cout << av_x << " " << av_y << " " << bad_distance << endl;
  }
  return 0;
}
