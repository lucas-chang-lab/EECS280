// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

int count(vector<double> v) {
    return (int) v.size();
}

double sum(vector<double> v) {
    double sum = 0;
    for (int i = 0; i < (int)v.size(); i++) {
      sum += v[i];
    }
    return sum;
}

double mean(vector<double> v) {
    return sum(v) / (double) count(v);
}

double median(vector<double> v) {
    sort(v.begin(), v.end());
    return count(v) % 2 ? v[count(v) / 2] : (v[count(v) / 2] + v[count(v) / 2 + 1]) / 2.0;
}

double min(vector<double> v) {
    sort(v.begin(), v.end());
    return v[0];
}

double max(vector<double> v) {
    sort(v.begin(), v.end());
    return v[count(v) - 1];
}

double stdev(vector<double> v) {
    double cnt = 0;
    for (int i = 0; i < count(v); i++) {
        cnt += (v[i] - mean(v)) * (v[i] - mean(v));
    }
    cnt /= (count(v) - 1);
    return sqrt(cnt);
}

double percentile(vector<double> v, double p) {
    sort(v.begin(), v.end());
    double rank = p * (count(v) - 1) + 1;
    int k = (int)rank;
    double d = rank - k;
    double vp = v[k - 1] + d * (v[k] - v[k - 1]);
    return vp;
}

vector<double> filter(vector<double> v, vector<double> criteria,
                      double target) {
    vector<double> result;
    for (int i = 0; i < (int) v.size(); i++) {
        if (criteria[i] == target) {
            result.push_back(v[i]);
        }
    }
    return result;
}

