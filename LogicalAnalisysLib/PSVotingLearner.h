#pragma once
#include "Interfaces.h"
#include "FTVotingLearner.h"

// ����������� �� ���������������� �������
class PSVotingLearner
    : public FTVotingLearner
{
protected:

    // ��������� ������ ��� �������� ���������������� �������
    ECSet _ecset;
    
    // ��������� ������ ��� �������� ���������� ����������� ��������
    ObjectPtrList _excluded;
        
    // ���������� ���������� ��.��. � �������������� �� ����
    void MergeCollectedECSet();

    // ������� ���������������� ������
    void CollectECSet(ObjectsRange const& objects);

    // ������� ���������������� ������
    void CollectECSet(ObjectsRange const& objects, OptionalObjects& oo, ComparersComposer& cc);

public:

    virtual IBinaryClassifierPtr Train(ObjectsClassRange const& correct, ObjectsClassRange const& fitting);
        
    static void Register();    
};