#include "Coordinate.h"

CollisionType Collision::BoxToBox(Rect& _a, Rect& _b)
{
    // 충돌안하면 0
    // 겹치면 1
    // 완전포함 2
    float fMinX; float fMaxX;
    float fMinY; float fMaxY;
    //float fMinZ; float fMaxZ;
    fMinX = _a.x0 < _b.x0 ? _a.x0 : _b.x0;
    fMinY = _a.y0 < _b.y0 ? _a.y0 : _b.y0;
    //fMinZ = _a.v_ctPoint.z < _b.v_ctPoint.z ? _a.v_ctPoint.z : _b.v_ctPoint.z;

    fMaxX = _a.x1 > _b.x1 ? _a.x1 : _b.x1;
    fMaxY = _a.y1 > _b.y1 ? _a.y1 : _b.y1;
    //fMaxZ = _a.v_edPoint.z > _b.v_edPoint.z ? _a.v_edPoint.z : _b.v_edPoint.z;

    // 가로판정
    if ((_a.xSize + _b.xSize) >= (fMaxX - fMinX) && (_a.ySize + _b.ySize) >= (fMaxY - fMinY))
    {
        Vector2D vMin, vMax;
        Rect Intersect;
        vMin.x = _a.x0 > _b.x0 ? _a.x0 : _b.x0;
        vMin.y = _a.y0 > _b.y0 ? _a.y0 : _b.y0;
        //vMin.z = _a.v_ctPoint.z > _b.v_ctPoint.z ? _a.v_ctPoint.z : _b.v_ctPoint.z;

        vMax.x = _a.x1 < _b.x1 ? _a.x1 : _b.x1;
        vMax.y = _a.y1 < _b.y1 ? _a.y1 : _b.y1;
        //vMax.z = _a.v_edPoint.z < _b.v_edPoint.z ? _a.v_edPoint.z : _b.v_edPoint.z;
        Intersect = { vMin.x, vMin.y, vMax.x - vMin.x, vMax.y - vMin.y };
        /*if (Intersect == _a || Intersect == _b)
        {
            return CollisionType::BoxIn;
        }*/
        return CollisionType::BoxOverLap;
    }
    return CollisionType::BoxOut;

}

