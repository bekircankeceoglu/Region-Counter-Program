#include <iostream>
#include <vector>
#include "MapInterface.h"
#include "ZoneCounterInterface.h"

namespace Bekircan
{
    class Map : public MapInterface
    {
    public:
        // sample test map
        std::vector<std::vector<int>> mapTest = {   {0,0,0,0,0,1,0,0,0,0,0,0},
                                                    {1,1,0,0,0,1,0,0,0,0,0,0},
                                                    {0,0,1,1,0,1,1,1,1,0,0,0},
                                                    {0,0,0,0,1,0,1,0,0,1,0,0},
                                                    {0,0,0,1,0,0,1,0,0,0,1,0},
                                                    {0,0,1,0,0,0,1,0,0,1,0,1},
                                                    {0,1,0,0,0,0,1,0,1,0,0,0},
                                                    {1,0,0,0,0,0,1,1,0,0,0,0},
                                                    {0,0,0,0,0,0,1,0,0,0,0,0}
                                                   };
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

        // init map and get width/height
        void Init(MapInterface* map)
        {
            Map mapObj;
            mapInput = mapObj.mapTest;

            // get map sizes as X and Y
            map->GetSize(X, Y);
        }

        // calculate total number of regions
        int Solve()
        {
            for (int i = 0; i < X; i++)
            {
                for (int j = 0; j < Y; j++)
                {
                    // check if not visited or not border
                    if (mapInput[j][i] == 0)
                    {
                        // count as region if any area is found
                        if (areaCheck(i, j) >= 1)
                        {
                            totalArea++;
                        }
                    }
                }
            }
            std::cout << totalArea;

            return totalArea;
        }

        // check neighbour areas recursively
        int areaCheck(int x, int y) {
            // check if area is out of range, border or already visited area
            if ((y < 0) || (y >= Y) || (x < 0) || (x >= X)  || (mapInput[y][x] == 1) || (mapInput[y][x] == 2))
            {
                return 0;
            }

            // set as visited area
            mapInput[y][x] = 2;

            // check 1- west, 2- east, 3- south, 4-north
            int areaSize = 1 + areaCheck(x, y - 1) + areaCheck(x, y + 1) + areaCheck(x - 1, y) + areaCheck(x + 1, y) ;
            return areaSize;
        }
    };
    
}