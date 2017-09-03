#pragma once

#include "Interfaces.h"
#include "BinaryClassifierNormalizer.h"


typedef std::vector<IBinaryClassifierPtr> BinaryClassifiers;

typedef std::map<int, BinaryClassifiers> BinaryClassifiersMap;

// ����������� �� �������� ���������������, ��������� � ������������ ������� �������
class BinaryClassifierVoter
    : public ClassifierBase, public IECVoting
{

    // ��������������, ��������������� �� �������
    BinaryClassifiersMap _classifiers;

public:

    BinaryClassifiersMap const& GetClassifiers() const 
    { 
        return _classifiers; 
    }

    // ���������������� ������ ������ ��������������� ��� ������� ������
    void Init(Dataset const& ds, int reserve = 0);

    // �������� �������������
    BinaryClassifierNormalizerPtr AddClassifier(int label, IBinaryClassifierPtr classifier, Weight w = 1);

    // �������� ������������� � �������� ������ �� ��������� ����������� � �������
    BinaryClassifierNormalizerPtr AddClassifierAndUpdateEstimates( 
        int label, 
        IBinaryClassifierPtr cls, 
        ObjectPtrList const &objects, 
        Predictions& predictions,
        Weight w = 1);
   

    // ��������� ������ ��� �������
    virtual Prediction Apply( Object const& o ) const;
    
    virtual void GetECSet( ECSet& ecset );
};
