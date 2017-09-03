#pragma once

#include "Object.h"
#include "Predictions.h"
#include "containers.h"

// ������������ �������������
struct EC
{
    FeatureValues featureValues;

    Weight weight;

    UTILITY_MOVE_DEFAULT_MEMBERS(EC, (featureValues)(weight));

    EC(Weight w = 0)
        :weight(w)
    {
    }

    EC(FeatureValues fv, Weight w = 0)
        :weight(w), featureValues(std::move(fv))
    {
    }

    // ������������ ��.��.
    EC(FeatureValue fv, Weight w = 0)
        :weight(w), featureValues(1, fv)
    {
    }

    EC(Features const& features, Values const& values, Weight w = 0)
    {
        weight = w;
        featureValues.reserve(features.size());
        for (auto j : features)
            if (inside(values, j))
                featureValues.emplace_back(j, values[j]);
        unique(featureValues);
    }


    // ���������� ��.��. � �������
    bool Apply(Object const& o) const
    {
        for (auto& fv:featureValues)
        {
            if (! fv.Apply(o))
                return false;
        }

        return true;
    }

    Estimate ApplySum(ObjectPtrList const& objects)
    {
        Estimate e = 0;
        for (auto& o : objects)
        {
            Estimate w = o->weight;
            if (w && Apply(*o))
                e +=w;
        }
        return e;
    }

    // ���������� ��.��. � ������ ��������
    void Apply(ObjectPtrList const& objects, Positions& positions)
    {
        positions.clear();
        int n = objects.size();
        for(int i = 0; i < n; ++i)
        {
            if (Apply(*objects[i]))
                positions.push_back(i);
        }
    }

    // ���� ��.��.
    int GetRank() const
    {
        return featureValues.size();
    }

    // �������������� ��.��. 
    // ������� ������������ �����, ����� ��������--�������� � � ��������� ������� ����
    bool operator <(EC const& ec) const
    {
        if (GetRank() == ec.GetRank())
        {
            if (less(featureValues, ec.featureValues))
                return true;

            if (weight <= ec.weight)
                return false;

            return equal(featureValues, ec.featureValues);
        }        
        return GetRank() < ec.GetRank();
    }

    // ��������� ��.��. �� ������������
    bool operator == (EC const& ec) const
    {
        return weight == ec.weight && equal(featureValues, ec.featureValues);
    }
};


