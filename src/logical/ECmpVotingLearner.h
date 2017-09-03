#pragma once
#include "Object.h"
#include "CmpMatrixBuilder.h"
#include "containers.h"
#include "ECmpVoting.h"
#include "Interfaces.h"
#include "Configurable.h"
#include "GeneticDualizer.h"
#include "Registrator.h"


struct ECmpVotingLearnerOptions
{
    int ecmpCount;
    
    int optionalCount;
    
    int fittingLimit;
    
    ECmpVotingLearnerOptions()
    {
        ecmpCount = 1;
        optionalCount = 5;
        fittingLimit = 100;
    }
};

//////////////////////////////////////////////////////////////////////////
// �������� ����������� �� ���������� ���� $B_{(U,O,G)}$
//////////////////////////////////////////////////////////////////////////
class ECmpVotingLearner
    :public IBinaryClassifierLearner, 
    public IConfigurable,
    public INeedFeatureSelector,
    private boost::noncopyable
{
    
    GeneticDualizer _geneticAlgorithm;

    //CoveredRowsWeightTargetFunc _geneticTarget;

    IFeatureSelectorPtr _featureSelector;

    ObjectPtrList _fittingObjects;

    ObjectPtrList _optionalObjects;

    ObjectsClass _correct;

    ObjectsClass _fitting;

    ECmpSet _localBasis;

public:

    ECmpVotingLearnerOptions CurrentOptions;
        
    static void Register();

    ECmpVotingLearner();

    // ������� �������� ��������
    virtual IBinaryClassifierPtr Train( ObjectsClass const& cls, InformativityCondition const& informativity );

    // ������� �������� ��������
    virtual IBinaryClassifierPtr Train( ObjectsClass const& correct, ObjectsClass const& fitting);

    // �������� ��� ����������� ���������
    virtual void Reset();
    
    // �������� ���������� �����
    //virtual OptionsDescription const& GetOptionsDescription() const;

    // ���������� ����� ��������
    virtual void SetOptions(Options const& options);
    
    // ���������� �������� ���������
    virtual void SetFeatureSelector( IFeatureSelectorPtr selector );

    // �������� ������� �������� ���������
    virtual IFeatureSelectorPtr GetFeatureSelector();
    
    // ������� �������� ����� ���������
    //OptionsDescription CreateOptionsDescription() const;

    virtual void SetDefaultOptions();

private:
    
    // ����� ������������ ���������� ������ ���������
    ECmpSetInfos BuildECmpSets( 
        ObjectsRange positive, 
        ObjectsRange optional,
        ObjectsRange negative,
        ObjectsRange fitting,
        ECmpSet localBasis, 
        int count);
    
    // ��������� ������� ���������
    bit_matrix BuildCmpMatrix( 
        ObjectsRange positive, 
        ObjectsRange optional, 
        ObjectsRange negative,
        ECmpSet const& localBasis, 
        Weights& weights);
    
    void CollectFittingObjects( ObjectsClass const& fitting );
    
    void SelectFeatures( ObjectsClass const& correct );
};