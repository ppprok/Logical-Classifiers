#pragma once
#include "Interfaces.h"

#undef max

// ������������ � ������������� ������, ������������ ���������������
class BinaryClassifierNormalizer
    :public IBinaryClassifier, public IECVoting
{

    // �������� �������������
    IBinaryClassifierPtr _classifier;
    
    // �����
    Estimate _shrink;
    
    // �������
    Estimate _scale;

public:

    // ������������� 
    BinaryClassifierNormalizer(IBinaryClassifierPtr classifier_);

    // ���������� �� �������, ������������ �� �����������
    void Normalize(ObjectPtrList const& objects, Estimate from = 0, Estimate to = 1);

    // ���������� (e + shrink) * scale, ��� e --- ������ ����������� ��������������
    virtual Estimate Apply( Object const& o ) const;

    Estimate GetScale() const
    {
        return _scale;
    }

    // ��������� �������
    void Scale(Estimate s)
    {
        _scale *= s;
    }

    // ��������� �����
    void Shrink(Estimate d)
    {
        _shrink += d;        
    }

    // ���������� �������������
    IBinaryClassifierPtr GetInner() const
    {
        return _classifier;
    }

    template<typename T>
    std::shared_ptr<T> GetInner() const
    {
        return std::dynamic_pointer_cast<T>(_classifier);
    }

    virtual void GetECSet( ECSet& ecset );
};

typedef std::shared_ptr<BinaryClassifierNormalizer> BinaryClassifierNormalizerPtr;