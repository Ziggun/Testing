#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

struct line {
  Point p1, p2;
};

bool onLine(line l1, Point p)
{
  if (p.x <= max(l1.p1.x, l1.p2.x)
    && p.x <= min(l1.p1.x, l1.p2.x)
    && (p.y <= max(l1.p1.y, l1.p2.y)
      && p.y <= min(l1.p1.y, l1.p2.y)))
    return true;

  return false;
}

int direction(Point a, Point b, Point c)
{
  int value = (b.y - a.y) * (c.x - b.x)
    - (b.x - a.x) * (c.y - b.y);

  if (value == 0)
    return 0;

  else if (value < 0)
    return 2;

  return 1;
}

bool isIntersect(line l1, line l2)
{
  int dir1 = direction(l1.p1, l1.p2, l2.p1);
  int dir2 = direction(l1.p1, l1.p2, l2.p2);
  int dir3 = direction(l2.p1, l2.p2, l1.p1);
  int dir4 = direction(l2.p1, l2.p2, l1.p2);

  if (dir1 != dir2 && dir3 != dir4)
    return true;

  if (dir1 == 0 && onLine(l1, l2.p1))
    return true;

  if (dir2 == 0 && onLine(l1, l2.p2))
    return true;

  if (dir3 == 0 && onLine(l2, l1.p1))
    return true;

  if (dir4 == 0 && onLine(l2, l1.p2))
    return true;

  return false;
}

bool checkInside(Point poly[], int n, Point p)
{

  if (n < 3)
    return false;

  line exline = { p, { 9999, p.y } };
  int count = 0;
  int i = 0;
  do {

    line side = { poly[i], poly[(i + 1) % n] };
    if (isIntersect(side, exline)) {

      if (direction(side.p1, p, side.p2) == 0)
        return onLine(side, p);
      count++;
    }
    i = (i + 1) % n;
  } while (i != 0);

  return count & 1;
}

int main()
{
  setlocale(LC_ALL, "ru");
  Point polygon[] = { { 4, 16 }, { 8, 20 }, { 10,12 }, { 20, 8 }, {14,4}, {6,10} };
  Point p, p1, p2, p3, rA, rB, rC, rD;
  int  rX, rY, rL, rW;
  cout << "Введите координаты точки x и y , а затем длину и ширину прямоугольника" << endl;
  cin >> rX >> rY >> rL >> rW;

  // нахождение координат углов, от центральной точки прямоугольника.
  rA.x = rX - (rL / 2);
  rA.y = rY - (rW / 2);
  rB.x = rX - (rL / 2);
  rB.y = rY + (rW / 2);
  rC.x = rX + (rL / 2);
  rC.y = rY + (rW / 2);
  rD.x = rX + (rL / 2);
  rD.y = rY - (rW / 2);

  Point rec [] = { { rA.x, rA.y }, { rB.x, rB.y  }, { rC.x, rC.y}, { rD.x, rD.y } };
  
  int n = sizeof(polygon) / sizeof(polygon[0]);
  bool isInside = true;

  for (int i = 0; i < sizeof(rec) / sizeof(rec[0]); i++)
  {
    if (checkInside(polygon, n, rec[i])) {
      cout << "Point is inside." << endl;
    }
    else {
      cout << "Point is outside." << endl;
      isInside = false;
      break;
    }
  }
  
  if (isInside) cout << "Rectangle within a polygon";
  else cout << "Rectangle not in polygon";
  
  return 0;
}