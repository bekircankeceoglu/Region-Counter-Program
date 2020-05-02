#include <iostream>
#include <vector>
#include "MapInterface.h"
#include "ZoneCounterInterface.h"

namespace Bekircan
{
    class Map : public MapInterface
    {
    public:

        std::vector<std::vector<int>> mapTest = { {0,0,1,0,0,0},
                                                  {0,1,0,1,1,1},
                                                  {1,1,0,1,0,0},
                                                  {0,1,0,0,1,0},
                                                  {0,0,1,1,1,0},
                                                  {0,0,0,0,1,0} };
        // Creates a map of given size.
        virtual void SetSize(const int width, const int height)
        {
            mapTest.resize(height);
            for (int i = 0; i < height; i++)
            {
                mapTest[i].resize(width);
            }
        }
        // Returns size of map to solve.
        void GetSize(int& width, int& height)
        {
            height = mapTest.size();
            width = mapTest[0].size();
        }
        // Sets border at given point.
        void SetBorder(const int x, const int y)
        {
            mapTest[y][x] = 1;
        }
        // Clears border at given point.
        void ClearBorder(const int x, const int y)
        {
            mapTest[y][x] = 0;
        }
        // Checks if there is a border at given point.
        bool IsBorder(const int x, const int y)
        {
            if (mapTest[y][x] == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // Show map contents.
        void Show()
        {
            for (int i = 0; i < mapTest.size(); i++)
            {
                for (int j = 0; j < mapTest[i].size(); j++)
                {
                    std::cout << mapTest[i][j];
                }
                std::cout << std::endl;
            }
        }
    };
    class Counter : public ZoneCounterInterface
    {
    public:
        std::vector<std::vector<int>> mapInput;
        int X = 0, Y = 0;
        int totalArea = 0;
        void Init(MapInterface* map)
        {
            Map mapObj;
            mapInput = mapObj.mapTest;

            map->GetSize(X, Y);
        }

        int Solve()
        {
            for (int i = 0; i < X; i++)
            {
                for (int j = 0; j < Y; j++)
                {
                    if (mapInput[j][i] == 0)
                    {
                        if (blank(i, j) >= 1)
                        {
                            totalArea++;
                        }
                    }
                }
            }
            std::cout << totalArea;

            return totalArea;
        }

        int blank(int x, int y) {
            if ((x < 0) || (x >= X) || (y < 0) || (y >= Y) || (mapInput[y][x] == 1))
                return 0;

            mapInput[y][x] = 1;

            int areaSize = 1 + blank(x - 1, y) + blank(x + 1, y) + blank(x, y - 1) + blank(x, y + 1);
            return areaSize;
        }
    };
    ZoneCounterInterface* getZoneCounter()
    {
        return new Counter();
    }
}