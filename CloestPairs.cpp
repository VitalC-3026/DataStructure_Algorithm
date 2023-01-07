/* 最邻近点对 */
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Point {
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Point() {
        this->x = 0;
        this->y = 0;
    }

};

bool compare_x(Point p1, Point p2) {
    return p1.x < p2.x;
}

bool compare_y(Point p1, Point p2) {
    return p1.y < p2.y;
}

double dist(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double closest_pair(int n, Point* points) {
    // 3个点之内的比较情况
    if (n <= 1) {
        return -1;
    }
    if (n == 2) {
        return dist(points[0], points[1]);
    }
    if (n == 3) {
        double dist1 = dist(points[0], points[1]);
        double dist2 = dist(points[1], points[2]);
        double dist3 = dist(points[0], points[2]);
        double dis[3] = { dist1, dist2, dist3 };
        sort(dis, dis + 3);
        return dis[0];
    }

    // 首先根据x坐标进行所有节点的排序
    sort(points, points + n, compare_x);
    int middle = n / 2;

    // 分治法，将结点一分为二存入数组中，递归调用
    Point* left = new Point[middle];
    Point* right = new Point[n - middle];
    for (int j = 0; ; j++) {
        if (j < middle) {
            left[j] = points[j];
        }
        if (j + middle < n) {
            right[j] = points[j + middle];
        }
        if (j >= middle && j + middle >= n) {
            break;
        }
    }

    double left_dist = closest_pair(middle, left);
    double right_dist = closest_pair(n - middle, right);
    double min0;

    // 比较得到递归结束后左半区和右半区得到的最小距离中的较小者
    if (left_dist < right_dist) {
        min0 = left_dist;
    }
    else{
        min0 = right_dist;
    }

    // 将中间交叉区域的结点以y轴进行排序，然后得到中间交叉区域最短距离点对
    float middle_x = left[middle - 1].x;
    Point* y_points = new Point[n];
    int t = 0;
    for (int i = 0; i < n; i++) {
        if (points[i].x > middle_x - min0 && points[i].x < middle_x + min0) {
            y_points[t++] = points[i];
        }
    }
    sort(y_points, y_points + t, compare_y);
    double min = 10000000;
    for (int i = 0; i < t; i++) {
        for (int j = i + 1; j < 15 && j < t; j++) {
            double middle_dist = dist(y_points[i], y_points[j]);
            if (middle_dist < min) {
                min = middle_dist;
            }
        }
    }

    delete[] left;
    delete[] right;

    // 中间区域最临近点对距离与左右半区最临近点对距离进行比较，返回最小值
    if (min < min0) {
        return min;
    }
    else {
        return min0;
    }

}

int main() {
    int n;
    cin >> n;
    Point* points = new Point[n];
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    double res = closest_pair(n, points);
    cout << setiosflags(ios::fixed) << setprecision(2) << res;

}
