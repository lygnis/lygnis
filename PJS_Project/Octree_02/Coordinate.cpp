#include "Coordinate.h"

CollisionType Collision::BoxToBox(Coor& _a, Coor& _b)
{
    // 충돌안하면 0
    // 겹치면 1
    // 완전포함 2
    float fMinX; float fMaxX;
    float fMinY; float fMaxY;
    float fMinZ; float fMaxZ;
    fMinX = _a.v_ctPoint.x < _b.v_ctPoint.x ? _a.v_ctPoint.x : _b.v_ctPoint.x;
    fMinY = _a.v_ctPoint.y < _b.v_ctPoint.y ? _a.v_ctPoint.y : _b.v_ctPoint.y;
    fMinZ = _a.v_ctPoint.z < _b.v_ctPoint.z ? _a.v_ctPoint.z : _b.v_ctPoint.z;

    fMaxX = _a.v_edPoint.x > _b.v_edPoint.x ? _a.v_edPoint.x : _b.v_edPoint.x;
    fMaxY = _a.v_edPoint.y > _b.v_edPoint.y ? _a.v_edPoint.y : _b.v_edPoint.y;
    fMaxZ = _a.v_edPoint.z > _b.v_edPoint.z ? _a.v_edPoint.z : _b.v_edPoint.z;

    // 가로판정
    if ((_a.v_Size.x + _b.v_Size.x) >= (fMaxX - fMinX) && (_a.v_Size.y + _b.v_Size.y) >= (fMaxY - fMinY)
        && (_a.v_Size.z + _b.v_Size.z) >= (fMaxZ - fMinZ))
    {
        Vector3D vMin, vMax;
        Coor Intersect;
        vMin.x = _a.v_ctPoint.x > _b.v_ctPoint.x ? _a.v_ctPoint.x : _b.v_ctPoint.x;
        vMin.y = _a.v_ctPoint.y > _b.v_ctPoint.y ? _a.v_ctPoint.y : _b.v_ctPoint.y;
        vMin.z = _a.v_ctPoint.z > _b.v_ctPoint.z ? _a.v_ctPoint.z : _b.v_ctPoint.z;

        vMax.x = _a.v_edPoint.x < _b.v_edPoint.x ? _a.v_edPoint.x : _b.v_edPoint.x;
        vMax.y = _a.v_edPoint.y < _b.v_edPoint.y ? _a.v_edPoint.y : _b.v_edPoint.y;
        vMax.z = _a.v_edPoint.z < _b.v_edPoint.z ? _a.v_edPoint.z : _b.v_edPoint.z;
        Intersect.SetPosition(vMin, vMax - vMin);
        if (Intersect == _a || Intersect == _b)
        {
            return CollisionType::BoxIn;
        }
        return CollisionType::BoxOverLap;
    }
    return CollisionType::BoxOut;

}

bool Coor::operator==(Coor& _coor)
{
    if (v_ctPoint == _coor.v_ctPoint && v_Size == _coor.v_Size)
    {
        return true;
    }
    return false;
}
