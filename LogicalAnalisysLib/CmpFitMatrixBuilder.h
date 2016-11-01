#pragma once
#include "CmpMatrix.h"
#include "ObjectsClass.h"
#include "CoverMatrix.h"
#include "Configurable.h"


struct CmpFitMatrixBuilderOptions
{
    // ������������ ����� ����������� �����
    int fitHeightLimit;
    
    // ������������ ����� ����� ������� ���������
    int cmpHeightLimit;
    
    // ����� ����� ����������� �����, ��� ������� ���������� ����������� �������
    int fitHeightThreshold;

    // ����� ����� ����� ������� ���������, ��� ������� ���������� ����������� �������
    int cmpHeightThreshold;

    // ����������� �� ����� ������ ��������
    int coverLimit;

    // ����� ����� ��������, ��� ������� ���� �������� ������
    int coverThreshold;

    // ������������ ����� �������� ����������
    int iterationLimit;

    // ����������� �� ����� ����������� ��������
    int fitObjectLimit;

    CmpFitMatrixBuilderOptions()
    {
        fitHeightLimit = 20;
        fitHeightThreshold = 50;
        fitObjectLimit = 200;
        
        cmpHeightLimit = 20;
        cmpHeightThreshold = 50;
        
        coverLimit = 5;
        coverThreshold = 500;
        iterationLimit = 100000;
    }
};

struct DualCallback;

// ���������� ���������� ������� ��������� � ����������� �������
class CmpFitMatrixBuilder
    :public IConfigurable
{
    // ������� ���������
    CmpMatrix _cmpMatrix;

    // ����������� �������
    FitMatrix _fitMatrix;

    // ������� � ����������
    CoverMatrix _coverMatrix;

public:

    // ����� ���������� ������ � ������ �� ��������
    CmpFitMatrixBuilderOptions Options;

    CoverMatrix& GetCoverMatrix()
    {
        return _coverMatrix;
    }

    // ���������� ������������
    void SetComparer(IComparerPtr comparer);

    // �������� ������� ��������� � ���������
    void Build(ObjectsClassRange const& correct, ObjectsClassRange const& fitting);

    // ����� �������� ������� ���������
    void FindCovers();
    
    // ���������� �����
    virtual void SetOptions(::Options const& options );

    // ���������� ����� �� ���������
    virtual void SetDefaultOptions();

private:

    void RestMostCovers();

    void RestMostCovers(int thres, int limit);
    
    void MergeFitMatrixRows(int thres, int limit);

    void MergeCmpMatrixRows(int thres, int limit);

    Weight GetCoverWeight(bit_chunk const& cover) const;

    friend DualCallback;
};