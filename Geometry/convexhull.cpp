struct Point{
    ll x, y;
};

Point p0;

int orientation(Point p1, Point p2, Point p3){
    ll val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool cmp(Point p1, Point p2){
    int x = orientation(p0, p1, p2);
    if (!x) {
        if (p1.y == p2.y)
            return p1.x < p2.x;
        return p1.y < p2.y;
    }
    return (x == 2) ? true : false;
}

vector<Point> convexHull(vector<Point>&points){
    int n = points.size();
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[0].y || (points[i].y == points[0].y && points[i].x < points[0].x)) 
            swap(points[0], points[i]);
    }
    p0 = points[0];
    sort(points.begin()+1, points.end(), cmp);
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i+1 < n && (!orientation(p0, points[i], points[i+1])))
            i++;
        points[m++] = points[i];
    }
    if (m < 3) return {};
    vector<Point>res;
    res.pb(points[0]); res.pb(points[1]); res.pb(points[2]);
    for (int i = 3; i < m; i++) {
        while (res.size() > 1 && orientation(res[res.size()-2] , res.back(), points[i]) != 2)
            res.pop_back();
        res.pb(points[i]);
    }
    return res;
}
