/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_SnapModel_h_
#define _Cool_SnapModel_h_

#include <Core/Core.h>

NAMESPACE_UPP

class SnapInterface {
public:
    virtual ~SnapInterface() {}
    virtual void AddPoint(int position) = 0;
    virtual void RemovePoint(int position) = 0;
};

class SnapModel : public SnapInterface {
public:
    SnapModel();
    virtual ~SnapModel();

    virtual void AddPoint(int position) override;
    virtual void RemovePoint(int position) override;

    int GetClosestPoint(int position) const;
    int GetNextPoint(int position) const;
    int GetPreviousPoint(int position) const;

    void Ignore(const Vector<int>& points);
    void UnIgnore();

private:
    // Sorted list of snap points (position -> count)
    VectorMap<int, int> snaps;
    Vector<int> ignored_points;
};

END_UPP_NAMESPACE

#endif
