#pragma once
#include "Dataset.h"
#include "Interfaces.h"
#include "blob.h"
#include "Configurable.h"

struct AlgorithmEstimatorOptions
{
    std::string validationMethod;

    float trainPart;

    int times;

    int randomSeed;

    AlgorithmEstimatorOptions()
    {
        validationMethod = "CV";
        times = 5;
        trainPart = 0.9f;
        randomSeed = 777;
    }
};

// ���������� ������� ������ �������� ����������
class AlgorithmEstimator
    :public IConfigurable
{
        
public:

    Dataset trainDataset;

    Dataset testDataset;

    IClassifierLearnerPtr algorithm;

    GroupedPredictions result;

    AlgorithmEstimatorOptions CurrentOptions;
    
    AlgorithmEstimator(void);

    // �������������� � ���������� �� �����
    GroupedPredictions FoldsCrossValidation( 
        Dataset ds, 
        IClassifierLearnerPtr a, 
        float trainPart = 0.9, 
        int count =1 );
    
    // �������������� �� ��������� ����������
    GroupedPredictions RandomSplitCrossValidation(
        Dataset ds, 
        IClassifierLearnerPtr a, 
        float trainPart = 0.9,
        int count = 1);

    // �������������� � ��������� �� ������� ��� ������ �������
    GroupedPredictions LeaveOneOutCrossValidation(Dataset ds, 
        IClassifierLearnerPtr a);

    // �������������� ������������ ��������� �� ��������� �������
    Predictions TestCorrectness(Dataset const& ds, IClassifierLearnerPtr a);

    // �������� �������� ������ �� �������� ������� ���������,
    // ���������� �� ������� �������
    Predictions ValidateByTestDataset(Dataset const& train, Dataset const& test, IClassifierLearnerPtr a);

    void Run();
    
    virtual void SetDefaultOptions();

    //virtual OptionsDescription const& GetOptionsDescription() const;

    virtual void SetOptions( Options const& options );
    
    //OptionsDescription CreateOptionsDescription() const;
};

