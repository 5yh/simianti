#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
struct Point
{
    int index;
    double x, y, z;
};
struct Cell2D
{
    int indexPoint1, indexPoint2, indexPoint3;
};
struct Cell3D
{
    int indexPoint1, indexPoint2, indexPoint3, indexPoint4;
};
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
    cout << surfacePoints[274353].x << endl;

    // 读取surfaceFile三角面片个数
    getline(inputSurfaceFile, line);
    int surfaceCellNumber = readSingleIntInString(line);
    cout << "surfaceCellNumber为：" << surfaceCellNumber << endl;

    // 将三角面片放入surfaceCells中
    surfaceCells.resize(surfaceCellNumber);
    for (int i = 0; i < surfaceCellNumber; i++)
    {
        getline(inputSurfaceFile, line);
        int num1, num2, num3;
        // Point *tmpPoint = new Point;
        Cell2D tmpCell;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3)
        {
            // 将三个int添加到tmpPoint中
            // cout << num1 << num2 << num3 << endl;
            tmpCell.indexPoint1 = num1;
            tmpCell.indexPoint2 = num2;
            tmpCell.indexPoint3 = num3;
            surfaceCells[i] = tmpCell;
        }
        else
        {
            std::cerr << "cant parse line：" << line << std::endl;
        }
    }
    cout << surfaceCells[485100].indexPoint1 << endl;
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
    for (int i = 0; i < volumeCellNumber; i++)
    {
        getline(inputVolumFile, line);
        int num1, num2, num3, num4;
        // Point *tmpPoint = new Point;
        Cell3D tmpCell3D;
        std::istringstream iss(line);
        if (iss >> num1 >> num2 >> num3 >> num4)
        {
            // 将4个double添加到tmpPoint中
            // cout << num1 << num2 << num3 << endl;
            if (num1 == 3)
                continue;
            if (num2 > SurfacePointNumber || num3 > SurfacePointNumber || num4 > SurfacePointNumber)
                continue;
            tmpCell3D.indexPoint1 = num1;
            tmpCell3D.indexPoint1 = num2;
            tmpCell3D.indexPoint1 = num3;
            tmpCell3D.indexPoint1 = num4;
            volumeCells[i] = tmpCell3D;
            cout << num1 << ' ' << num2 << ' ' << num3 << ' ' << num4 << endl;
        }
    }
    inputVolumFile.close();
    // return true;
}

int main()
{
    // cout << "hello";
    check_Steiner("Patch_Array_Antenna_surface_mesh.vtk", "Patch_Array_Antenna_volume_mesh.vtk");
}