#pragma once
#include "Interfaces.h"
#include "Configurable.h"
#include "Registrator.h"


struct MultiByBinaryLearnerOptions
{
    // ����� �������, ��� ������� �� ������ ���� ����������
    float correctPart;

    // ����� ��������
    int iterationCount;

    MultiByBinaryLearnerOptions()
        :iterationCount(0), correctPart(0.7f)
    {
    }

};


//////////////////////////////////////////////////////////////////////////
// �������������, �������� ��� ������� ������ ����� �������� ���������������,
// ���������� �� �� �������� ����������� ����������
//////////////////////////////////////////////////////////////////////////
class MultiByBinaryLearner
    :public IClassifierLearner,
    public IConfigurable,
    private boost::noncopyable
{

    // ����� �������� �������� ��������������� ��� ��������� �������� ������
    IBinaryClassifierLearnerPtr _positiveLearner;

    // ����� �������� �������� ��������������� ��� ��������� �������� �� �� ������
    IBinaryClassifierLearnerPtr _negativeLearner;

private:

    void InitFeatureSelector( Dataset const& ds );

public:

    MultiByBinaryLearnerOptions CurrentOptions;
    
    MultiByBinaryLearner();

    static void Register();

    void SetPositiveBinaryLearner(IBinaryClassifierLearnerPtr pos);
        
    void SetNegativeBinaryLearner(IBinaryClassifierLearnerPtr neg);

    virtual IClassifierPtr Train( Dataset const& ds );
    
    virtual void Reset();

    virtual void SetDefaultOptions();

    //virtual OptionsDescription const& GetOptionsDescription() const;

    virtual void SetOptions( Options const& options );
    
    //OptionsDescription CreateOptionsDescription() const;
};

