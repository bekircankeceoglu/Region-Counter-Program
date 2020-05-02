#include "RegionCounter.h"

int main()
{
    MapInterface *obj;
    Bekircan::Map m;
    obj = &m;
    obj->Show();
    
    ZoneCounterInterface* zone;
    Bekircan::Counter counterObj;
    zone = &counterObj;
    zone->Init(obj);

    zone->Solve();
}

