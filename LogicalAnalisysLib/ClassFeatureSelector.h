#pragma once

#include <map>
#include "FeatureSelectorBase.h"
#include "Registrator.h"
#include "BinaryECFeatureSelector.h"

// ����� ��������� �� �������
class ClassFeatureSelector
    :public FeatureSelectorBase, public IConfigurable
{
    typedef std::map<int, IFeatureSelectorPtr> FeatureSelectorMap;

    // ������� �� ������ �������
    FeatureSelectorMap _featureSelectors;

    // ��������� �� ������������
    IFeatureSelectorPtr _lastfeatureSelector;

    // ����� ������ ���������
    ::Options _featureSelectorOptions;

public:

    ClassFeatureSelector();

    static void Register();

    virtual void Reset();

    virtual void Select( ObjectsClassRange const& correct, ObjectsClassRange const& fitting );

    virtual void Select( ObjectsClassRange const& cls );

    IFeatureSelectorPtr GetFeatureSelector( int label);

    virtual Features const& GetFeatures() const;

    virtual ECmpSet const& GetECmpSet() const;

    virtual void Init( Dataset const& ds );

    virtual void SetOptions( ::Options const& options );

    virtual void SetDefaultOptions();

public:

    IFeatureSelectorPtr CreateFeatureSelector();

};