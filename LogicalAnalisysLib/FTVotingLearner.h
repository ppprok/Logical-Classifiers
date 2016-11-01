#pragma once

#include "bit_chunk.h"
#include "Dataset.h"
#include "Object.h"
#include "Interfaces.h"
#include "Configurable.h"
#include "GeneticDualizer.h"
#include "Registrator.h"
#include "FTVoting.h"
#include "CmpMatrix.h"
#include "CmpFitMatrixBuilder.h"


// ����� �������� ��������� ���������
class FTVotingLearner
    :
    public IBinaryClassifierLearner,
    public IConfigurable,
    public INeedFeatureSelector
{
protected:
    
    // ����� ���������
    IFeatureSelectorPtr _featureSelector;

    // ��������� ������� ��������� � � ��������
    CmpFitMatrixBuilder _cmpFitMatrixBuilder;

    // ��������� ���������
    std::shared_ptr<FeatureComparer> _featureComparer;

    // ��������� ������ ��� �������� ���������� ���������
    Features _features;

    // ��������� �� ��.��.
    std::shared_ptr<ECmpSetComparer> _ecmpSetComparer;

    // ��������� ������ ��� �������� ���������� ��.��. � �����������
    ECmpSet _ecmpSet;
        
public:
        
    FTVotingLearner();

    static void Register();

    virtual void SetDefaultOptions();
        
    virtual void SetOptions( Options const& options );
    
    virtual void Reset();

    virtual IBinaryClassifierPtr Train( ObjectsClassRange const& correct, ObjectsClassRange const& fitting);

    IBinaryClassifierPtr DoTrainECmp( ObjectsClassRange const &correct, ObjectsClassRange const& fitting );
    
    IBinaryClassifierPtr DoTrainFT( ObjectsClassRange const &correct, ObjectsClassRange const& fitting );
    
    virtual void SetFeatureSelector( IFeatureSelectorPtr selector );

    virtual IFeatureSelectorPtr GetFeatureSelector();

    // �������� ������ � ����� ���������� ������� ��������� � � ��������
    CmpFitMatrixBuilderOptions& GetOptions()
    {
        return _cmpFitMatrixBuilder.Options;
    }

private:
    
    IBinaryClassifierPtr DoTrain( ObjectsClassRange const& correct, ObjectsClassRange const& fitting);

protected:

    void InitFeatureComparer();
    
    void InitECmpSetComparer();
    
};

