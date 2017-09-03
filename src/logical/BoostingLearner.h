#pragma once


#include "Interfaces.h"
#include "ECmp.h"
#include "CmpMatrixBuilder.h"
#include "containers.h"
#include "ECmpVotingLearner.h"
//#include "LocalBasisBuilder.h"
#include "Randomizer.h"
#include "math_utils.h"


// ����� �������� ���������
struct BoostingOptions
{
    // ����� ��������
    int iterationsCount;
    
    // �������� Q ����� �������� ������� ������������
    Weight stopQ;

    // ����� ������������� ��������
    int positiveCount;
    
    // ����� ������������� ��������
    Weight positivePart;

    // ����������� ��� ��������������
    Weight minWeight;

    BoostingOptions();
};


// ���������� � ����� ������, �������������� ���������
struct BoostingClassInfo
{
    // ����� ������
    int label;

    // ������������ ������� �� �� ������
    bool complement;

    // ��� �������� ������
    Weight positiveWeight;

    // ��� �������� �� �� ������    
    Weight negativeWeight;

    // ����� ���� ����� ��� ������--�����
    Weight Q;

    // ��������� ���������� ��������������� 
    InformativityCondition informativity;

    Weight GetNormalizedNegativeWeight() const;

    Weight GetNormalizedPositiveWeight() const;

    Weight GetTotalWeight() const;

    // ������������ �������� ���������������, ������� ����� ���������� �� ������
    Weight GetClassWeight() const;

    // ������������ �������� ���������������, ������� ����� ���������� �� ������
    Weight GetClassWeight(Weight threshold) const;

    // �������� �������� ���������� ������
    BoostingClassInfo GetComplement() const;

    BoostingClassInfo(int l = -1, bool c = false);


    Weight NormalizeWeight(Weight w) const;


    // ��������� ��� ��������� �� ����� ������������� ���������� � ������������� ���������� ��������
    Weight GetWeakClassifierWeight(Weight p, Weight n);


    void AddPositiveWeight(Weight w);


    void AddNegativeWeight(Weight w);

};





// �������� ����������� ���������� ������� ��������
class BoostingLearner
    :public IClassifierLearner,
    public IConfigurable,
    private boost::noncopyable
{
    
    // ���������� � ����� ������� � �� �����������
    std::vector<BoostingClassInfo> _weightedClasses;

    // ��������� ������, � ������� ���������� �����
    std::vector<BoostingClassInfo> _selectedClasses;

    // ����� ��������, �� ������� ������ ���������
    ObjectsClassRange _correctPart;
    
    // ����� ��������, �� ������������� ������� ���������� �����������
    ObjectsClassRange _fittingPart;

public:

    // ����� �������� ��������� ��������� ��� ��������� �������� ������
    IBinaryClassifierLearnerPtr positiveLearner;

    // ����� �������� ��������� ��������� ��� ��������� �������� �� �� ������
    IBinaryClassifierLearnerPtr negativeLearner;

    // ������������� ����� �������� � �������������
    BoostingOptions CurrentOptions;
    
    // �������� ���������� ���������
    virtual void Reset();

    // ��������� �� �������
    virtual IClassifierPtr Train(Dataset const& ds);

    // ���������� ����� �� ���������
    virtual void SetDefaultOptions();
        
    // ���������� �����
    virtual void SetOptions( Options const& options );

    // ���������������� ��� � ������� ��� ��������������� �� �����
    static void Register();

    // ������ �����������
    BoostingLearner();
    
private:

    // ��������� ������������� ����� ��������, ����������� ��� ���������� ����������� ���������
    int CalculateIterationCount(Dataset const &ds);

    // ���������������� ��������� ���������� �� �������
    void InitClassesPredicates(Dataset const &ds);
        
    // ������� ���������� � ����� �� �������
    void CollectClassWeightInfo( ObjectsClasses const& classes, Predictions const& predictions, Weight delta);

    // ������� ���������� �����
    BoostingClassInfo SelectClass( Dataset const &ds, Predictions const& predictions, Weight delta);
    
    // ��������� ���� �������� ��� ���������� ������
    void WeightObjects(Dataset const& ds, Predictions const& predictions, BoostingClassInfo const& cls);
    
    // ��������� ��� ��������� �������������� �� �������� ������������� ������������� � ������������� ��������
    Weight WeightBinaryClassifier( BoostingClassInfo &cls, IBinaryClassifierPtr bincls, ObjectPtrList const& positive, ObjectPtrList const& negative ) const;
    
    // ���������������� ����� ��������� � �������� ���������� �������������
    void InitFeatureSelector( Dataset const& ds );

    // �������� ����� ����������� ������������� �������� ��� ��������
    int GetCorrectPositiveObjectsCount(int mk) const;

    // ������������ ������ ���������� �������� ��� �������� ��������� ��������������
    void CollectCorrectObjects(ObjectsClass& clsref, BoostingClassInfo& clsinfo);
    
    void SetupDefaultLearners();
};