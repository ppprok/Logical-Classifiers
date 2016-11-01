#pragma once
#include "ECmpByRankFeatureSelector.h"
#include "BoostingLearner.h"
#include "BinaryClassifierVoter.h"


// ���� ��.��. ����� ���������� ��������� ����������� �� ��.��.
class InitECFeatureSelector
    :public FeatureSelectorBase, public IConfigurable
{
    // �������� ��������
    IClassifierLearnerPtr _learner;    

    // ��������� ��.��.
    ECSet _ecset;

public:
    
    InitECFeatureSelector(void);    
    
    virtual void Reset();
        
    virtual void Init( Dataset const& ds );
    
    virtual void SetDefaultOptions();
    
    virtual void SetOptions( ::Options const& options );

    static void Register();

    virtual void Select( ObjectsClassRange const& cls );

    virtual void Select( ObjectsClassRange const& correct, ObjectsClassRange const& fitting );

private:

    void SetupDefaultLearner();

};

