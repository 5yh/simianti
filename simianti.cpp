#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
int inline max3(int num1, int num2, int num3)
{
    return (num1 > num2) ? ((num1 > num3) ? num1 : num3) : ((num2 > num3) ? num2 : num3);
}
int inline min3(int num1, int num2, int num3)
{
    return (num1 < num2) ? ((num1 < num3) ? num1 : num3) : ((num2 < num3) ? num2 : num3);
}

struct Point
{
    int index;
    double x, y, z;
};
struct Cell2D
{
    int indexPoint1, indexPoint2, indexPoint3;
    bool operator==(const Cell2D &other) const
    {
        return (indexPoint1 == other.indexPoint1) && (indexPoint2 == other.indexPoint2) && (indexPoint3 == other.indexPoint3);
    }
};
struct Cell3D
{
    int indexPoint1, indexPoint2, indexPoint3, indexPoint4;
};
bool compareDescending(int a, int b)
{
    return a > b;
}
bool compareCell2dDescending(Cell2D a, Cell2D b)
{
    if (a.indexPoint1 != b.indexPoint1)
    {
        return a.indexPoint1 > b.indexPoint1;
    }
    else if (a.indexPoint2 != b.indexPoint2)
    {
        return a.indexPoint2 > b.indexPoint2;
    }
    else if (a.indexPoint3 != b.indexPoint3)
    {
        return a.indexPoint3 > b.indexPoint3;
    }
    return true;
}
int readSingleIntInString(string line)
{
    istringstream iss(line);
    string token;
    int number = 0;
    // 依次读取分词
    while (iss >> token)
    {
        // 读取本行单个number
        if (istringstream(token) >> number)
        {
            break; // 当找到一个整数后停止
        }
    }
    return number;
}
bool check_Steiner(std::string surfaceFilePath, std::string volumFilePath)
{
    // cout << surfacefile << volumfile;
    vector<Point> surfacePoints;
    vector<Cell2D> surfaceCells;
    ifstream inputSurfaceFile, inputVolumFile;
    inputSurfaceFile.open(surfaceFilePath);

    if (!inputSurfaceFile.is_open())
    {
        cerr << "cant open surface file" << endl;
        exit(1);
    }

    string line;
    // 逐行读取前四行，丢弃
    for (int i = 0; i < 4; i++)
    {
        getline(inputSurfaceFile, line);
    }

    // 读取surfaceFile点的个数
    getline(inputSurfaceFile, line);
    int SurfacePointNumber = readSingleIntInString(line);
    surfacePoints.resize(SurfacePointNumber);
    cout << "surface点的个数为:" << SurfacePointNumber << endl;

    // 将surface点添加到surfacePoints中
    for (int i = 0; i < SurfacePointNumber; i++)
    {
        getline(inputSurfaceFile, line);
        double num1, num2, num3;
        // Point *tmpPoint = new Point;
        Point tmpPoint;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3)
        {
            // 将三个double添加到tmpPoint中
            // cout << num1 << num2 << num3 << endl;
            tmpPoint.index = i;
            tmpPoint.x = num1;
            tmpPoint.y = num2;
            tmpPoint.z = num3;
            surfacePoints[i] = tmpPoint;
        }
        else
        {
            std::cerr << "无法解析行：" << line << std::endl;
        }
    }
    // cout << surfacePoints[240000].x << endl;

    // 读取surfaceFile三角面片个数
    getline(inputSurfaceFile, line);
    int surfaceCellNumber = readSingleIntInString(line);
    cout << "surfaceCellNumber为：" << surfaceCellNumber << endl;

    // 将三角面片放入surfaceCells中
    surfaceCells.resize(surfaceCellNumber);
    for (int i = 0; i < surfaceCellNumber; i++)
    {
        getline(inputSurfaceFile, line);
        int num1, num2, num3, num4;
        // Point *tmpPoint = new Point;
        Cell2D tmpCell;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3 >> num4)
        {
            // 将三个int添加到tmpPoint中
            int maxx = max3(num2, num3, num4);
            int minn = min3(num2, num3, num4);
            int midd = num2 + num3 + num4 - maxx - minn;
            tmpCell.indexPoint1 = maxx;
            tmpCell.indexPoint2 = midd;
            tmpCell.indexPoint3 = minn;
            // cout<<maxx<<' '<<midd<<' '<<minn<<endl;
            surfaceCells[i] = tmpCell;
        }
        else
        {
            std::cerr << "cant parse line：" << line << std::endl;
        }
    }
    // cout << surfaceCells[484000].indexPoint1 << endl;
    // 274559 759684
    // 关闭文件,现在有surfacePoints存surface点，surfaceCells存surface三角形面片
    inputSurfaceFile.close();
    // --------------------------------------------------------------------------
    vector<Point> volumePoints;
    vector<Cell3D> volumeCells;
    inputVolumFile.open(volumFilePath);
    if (!inputVolumFile.is_open())
    {
        cerr << "cant open volume file" << endl;
        exit(1);
    }
    // 逐行读取前四行，丢弃
    for (int i = 0; i < 4; i++)
    {
        getline(inputVolumFile, line);
    }
    getline(inputVolumFile, line);
    int volumePointNumber = readSingleIntInString(line);
    volumePoints.resize(volumePointNumber);
    cout << "volume点的个数为:" << volumePointNumber << endl;
    for (int i = 0; i < volumePointNumber; i++)
    {
        getline(inputVolumFile, line);
        double num1, num2, num3;
        // Point *tmpPoint = new Point;
        Point tmpPoint;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3)
        {
            // 将三个double添加到tmpPoint中
            // cout << num1 << num2 << num3 << endl;
            tmpPoint.index = i;
            tmpPoint.x = num1;
            tmpPoint.y = num2;
            tmpPoint.z = num3;
            volumePoints[i] = tmpPoint;
        }
        else
        {
            std::cerr << "无法解析行：" << line << std::endl;
        }
    }

    // 读取volumeFile四面体个数

    getline(inputVolumFile, line);
    int volumeCellNumber = readSingleIntInString(line);
    cout << "volumeCellNumber为：" << volumeCellNumber << endl;
    volumeCells.resize(volumeCellNumber);
    int j = 0;
    for (int i = 0; i < volumeCellNumber; i++)
    {
        getline(inputVolumFile, line);
        int num1, num2, num3, num4, num5;
        // Point *tmpPoint = new Point;
        Cell3D tmpCell3D;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3 >> num4 >> num5)
        {
            // 将4个double添加到tmpPoint中
            // cout << num1 << num2 << num3 << endl;
            // volume里的三角形不要
            if (num1 == 3)
                continue;
            // 删掉一些必没有面片的四面体
            if (num2 >= SurfacePointNumber && num3 >= SurfacePointNumber && num4 >= SurfacePointNumber && num5 >= SurfacePointNumber)
                continue;
            tmpCell3D.indexPoint1 = num2;
            tmpCell3D.indexPoint2 = num3;
            tmpCell3D.indexPoint3 = num4;
            tmpCell3D.indexPoint4 = num5;
            volumeCells[j++] = tmpCell3D;
        }
    }
    cout << "存入的四面体个数为:" << j << endl;

    vector<Cell2D> volumeCells3DTo2D(j * 4);
    vector<int> tmpnums(4);
    int k = 0;
    for (int i = 0; i < j; i++)
    {
        tmpnums[0] = volumeCells[i].indexPoint1;
        tmpnums[1] = volumeCells[i].indexPoint2;
        tmpnums[2] = volumeCells[i].indexPoint3;
        tmpnums[3] = volumeCells[i].indexPoint4;
        sort(tmpnums.begin(), tmpnums.end(), compareDescending);
        if (tmpnums[0] < SurfacePointNumber && tmpnums[1] < SurfacePointNumber && tmpnums[2] < SurfacePointNumber)
        {
            volumeCells3DTo2D[k].indexPoint1 = tmpnums[0];
            volumeCells3DTo2D[k].indexPoint2 = tmpnums[1];
            volumeCells3DTo2D[k++].indexPoint3 = tmpnums[2];
        }
        if (tmpnums[0] < SurfacePointNumber && tmpnums[1] < SurfacePointNumber && tmpnums[3] < SurfacePointNumber)
        {
            volumeCells3DTo2D[k].indexPoint1 = tmpnums[0];
            volumeCells3DTo2D[k].indexPoint2 = tmpnums[1];
            volumeCells3DTo2D[k++].indexPoint3 = tmpnums[3];
        }

        if (tmpnums[0] < SurfacePointNumber && tmpnums[1] < SurfacePointNumber && tmpnums[3] < SurfacePointNumber)
        {
            volumeCells3DTo2D[k].indexPoint1 = tmpnums[0];
            volumeCells3DTo2D[k].indexPoint2 = tmpnums[1];
            volumeCells3DTo2D[k++].indexPoint3 = tmpnums[3];
        }
        if (tmpnums[1] < SurfacePointNumber && tmpnums[2] < SurfacePointNumber && tmpnums[3] < SurfacePointNumber)
        {
            volumeCells3DTo2D[k].indexPoint1 = tmpnums[1];
            volumeCells3DTo2D[k].indexPoint2 = tmpnums[2];
            volumeCells3DTo2D[k++].indexPoint3 = tmpnums[3];
        }
    }
    cout << "将四面体四个面分别存入volumeCells3DTo2D中，个数为：" << k << endl;
    volumeCells3DTo2D.resize(k);
    // 这里有bug，存的时候因为筛除了一些，所以这里vector长度大于实际存的，排序爆了
    sort(volumeCells3DTo2D.begin(), volumeCells3DTo2D.end(), compareCell2dDescending);
    cout << "volumeCells3DTo2D降序排序,大小为" << volumeCells3DTo2D.size() << endl;
    sort(surfaceCells.begin(), surfaceCells.end(), compareCell2dDescending);
    cout << "surfaceCells降序排序,大小为" << surfaceCells.size() << endl;
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << i << ' ' << volumeCells3DTo2D[i].indexPoint1 << ' ' << volumeCells3DTo2D[i].indexPoint2 << ' ' << volumeCells3DTo2D[i].indexPoint3 << endl;
    // }
    // cout << "---------------------------------------------------" << endl;
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << i << ' ' << surfaceCells[i].indexPoint1 << ' ' << surfaceCells[i].indexPoint2 << ' ' << surfaceCells[i].indexPoint3 << endl;
    // }
    int ii = 0, jj = 0;
    while (jj < volumeCells3DTo2D.size())
    {
        if (surfaceCells[ii] == volumeCells3DTo2D[jj])
        {
            ii++, jj++;
            continue;
        }
        else
        {
            jj++;
        }
    }
    if (ii != surfaceCells.size())
    {
        cout << "有不在volume的三角形" << endl;
        // 38 242435 242430 228182
        cout << "不在volume中的序号为:" << ii << endl;
        return false;
    }
    else
    {
        cout << "所有三角形都在volume中" << endl;
        cout << ii;
        return true;
    }
    inputVolumFile.close();
    // return true;
}

int main()
{
    // cout << "hello";
    check_Steiner("Patch_Array_Antenna_surface_mesh.vtk", "Patch_Array_Antenna_volume_mesh.vtk");
}