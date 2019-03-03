#pragma once
#include <vector>
#include <unordered_map>
#include <bits/unordered_set.h>

#include "move_default.h"

typedef float Estimate;

// ������������ �� ��������� ������� � ������
struct ClassPrediction
{
    int label;            // ����� ������
    Estimate estimate;    // ������ �� �����
    //Estimate margin;      // ������

    ClassPrediction(int l = -1)
        :label(l), estimate(0)
    {
        //margin = 0;
    }
};

typedef std::vector<ClassPrediction> ClassPredictions;

typedef std::unordered_map<int, ClassPrediction> ClassPredictionsMap;

// ������������ ��� �������
class Prediction
{

public:

    int label;

    ClassPredictions predictions;

    Prediction(int l = -1);

    Prediction(ClassPredictionsMap const& p, int l = -1);

    UTILITY_MOVE_DEFAULT_MEMBERS(Prediction, (label)(predictions));

    // ����� ������ ��� ����������� ������
    int PosByLabel(int l) const;

    // �������� ������ �� �����
    Estimate EstimateByLabel(int l) const;

    // �������� ������ ��� ������ � ��������� ������
    ClassPrediction& GetByLabel(int l);

    // ��������� ������� �� �������
/*    void CalculateMargins()
    {
        ClassPredictions cp(predictions.size());
        
        int r = predictions.size();
        for (int i = 0; i < r; ++i)
        {
            bool nan = true;
            Estimate max = 0;
            for (int t = 0; t < r; ++t)
            {
                if (t != i)
                {
                    if (nan || max < predictions[t].estimate)
                    {
                        max = predictions[t].estimate;
                        nan = false;
                    }
                }
            }

            cp[i].estimate = predictions[i].estimate - max;
            cp[i].label = predictions[i].label;
        }

        predictions = std::move(cp);
    }*/

    // �������� ����� � ������������� ��������
    /*int LabelByMargins() const
    {
        for(auto p:predictions)
            if (p.estimate > 0)
                return p.label;
        return -1;
    }*/

    // �������� ����� � ������������ �������
    int LabelByEstimates() const;
};


typedef std::vector<Prediction> Predictions;

// ��������������� ������������ ��� ������������ �������
class GroupedPredictions
{
public:	

    std::vector<Predictions> groups;

    GroupedPredictions();

    GroupedPredictions(Predictions predictions);

    UTILITY_MOVE_DEFAULT_MEMBERS(GroupedPredictions, (groups));

    // �������� ������� ������� ������
    Estimate GetMeanError() const;

    // �������� ������� ������� ������, ��������� ������ �� �������������
    Estimate GetMeanErrorIgnoreRejections();
};
