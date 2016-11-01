#pragma once
#include "Interfaces.h"
#include "Configurable.h"



// ������� ����� ��� ������ ���������
class FeatureSelectorBase
    :public IFeatureSelector
{
protected:

    Features _features;

    ECmpSet _ecmpSet;



public:
        
    virtual void Reset();
        
    
    
    virtual void Select( ObjectsClassRange const& correct, ObjectsClassRange const& fitting )
    {};

    virtual void Select( ObjectsClassRange const& cls )
    {};
    
    virtual Features const& GetFeatures() const;

    virtual ECmpSet const& GetECmpSet() const;

    virtual void Init( Dataset const& ds );



//////////////////////////////////////////////////////////////////////////
// ��������������� ������ ������ ���������
//////////////////////////////////////////////////////////////////////////
public:

    // ���������, �������� �� ����� ��.��. ���� ����� ����������� �� ������� ������ �����������
    static bool AnyDefectPairs(IFeatureSelector const& fs, ObjectsRange const& positive, ObjectsRange const& negative);

    // ��������� ����� ��������
    static int CountDefectPairs(IFeatureSelector const& fs, ObjectsRange const& positive, ObjectsRange const& negative, int maxc = -1);

    // ��������� ������������� ��� ��������� ���
    static Weight WeightDefectPairs(IFeatureSelector const& fs, ObjectsRange const& positive, ObjectsRange const& negative);

    // ���������, ����������� �� ��� ������� ����������� ������� ��.��. � �����������
    static bool IsDefectPair(IFeatureSelector const& fs, Object const& po, Object const& no);

    

};