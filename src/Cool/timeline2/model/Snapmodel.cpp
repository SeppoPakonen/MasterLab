/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Snapmodel.hpp"
#include <climits>
#include <cstdlib>

NAMESPACE_UPP

SnapModel::SnapModel() {
}

SnapModel::~SnapModel() {
}

void SnapModel::AddPoint(int position) {
    int idx = snaps.Find(position);
    if (idx < 0) {
        snaps.Add(position, 1);
    } else {
        snaps[idx]++;
    }
}

void SnapModel::RemovePoint(int position) {
    int idx = snaps.Find(position);
    if (idx >= 0) {
        if (snaps[idx] <= 1) {
            snaps.Remove(idx);
        } else {
            snaps[idx]--;
        }
    }
}

int SnapModel::GetClosestPoint(int position) const {
    if (snaps.IsEmpty()) return -1;
    
    int idx = snaps.FindLowerBound(position);
    int prev = (idx > 0) ? snaps.GetKey(idx - 1) : -1;
    int next = (idx < snaps.GetCount()) ? snaps.GetKey(idx) : -1;
    
    if (prev == -1) return next;
    if (next == -1) return prev;
    
    if (abs(position - prev) < abs(position - next)) {
        return prev;
    }
    return next;
}

int SnapModel::GetNextPoint(int position) const {
    if (snaps.IsEmpty()) return position;
    
    int idx = snaps.FindLowerBound(position + 1);
    return (idx < snaps.GetCount()) ? snaps.GetKey(idx) : position;
}

int SnapModel::GetPreviousPoint(int position) const {
    if (snaps.IsEmpty()) return 0;
    
    int idx = snaps.FindLowerBound(position);
    return (idx > 0) ? snaps.GetKey(idx - 1) : 0;
}

void SnapModel::Ignore(const Vector<int>& points) {
    ignored_points <<= points;
    for (int pt : points) {
        RemovePoint(pt);
    }
}

void SnapModel::UnIgnore() {
    for (int pt : ignored_points) {
        AddPoint(pt);
    }
    ignored_points.Clear();
}

END_UPP_NAMESPACE
