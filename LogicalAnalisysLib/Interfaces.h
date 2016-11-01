#pragma once

#include <boost/program_options.hpp>

#include "Predictions.h"
#include "Object.h"
#include "Dataset.h"
#include "ECmp.h"
#include "InformativityCondition.h"

//////////////////////////////////////////////////////////////////////////
// �������� ������������� ��������
//////////////////////////////////////////////////////////////////////////
struct IBinaryClassifier
{
    virtual Estimate Apply(Object const& o) const = 0;

    virtual ~IBinaryClassifier(){};
};

typedef std::shared_ptr<IBinaryClassifier> IBinaryClassifierPtr;


//////////////////////////////////////////////////////////////////////////
// ���������� �� ������ �� ���� �������
// ��� �������� ��������� ��������������
//////////////////////////////////////////////////////////////////////////
/*struct ClassTrainInfo
{
    // �������, ��� ������� ���������� �������� ���������� ���������
    ObjectPtrList correctObjects;
    // �������, �� ������� ������������ ����� ���� ��������
    ObjectPtrList optionalObjects;
    // �������, �� ������� ������������ �������� �� ����� �� �����
    ObjectPtrList fittingObjects;

    ClassTrainInfo(){};

    void Clear()
    {
        correctObjects.clear();
        fittingObjects.clear();
        optionalObjects.clear();
    }

    UTILITY_MOVE_DEFAULT_MEMBERS(ClassTrainInfo, (correctObjects)(fittingObjects)(optionalObjects));
};*/



//////////////////////////////////////////////////////////////////////////
// ������ �������� ��������� ��������������
//////////////////////////////////////////////////////////////////////////
struct IBinaryClassifierLearner
{
    
    virtual IBinaryClassifierPtr Train(
        ObjectsClassRange const& correct,
        ObjectsClassRange const& fitting) = 0;

    virtual void Reset() = 0;

    virtual ~IBinaryClassifierLearner(){};
};

typedef std::shared_ptr<IBinaryClassifierLearner> IBinaryClassifierLearnerPtr;


//////////////////////////////////////////////////////////////////////////
// ������������� �������� �� ��������� �������
//////////////////////////////////////////////////////////////////////////
struct IClassifier
{
    virtual Prediction Apply(Object const& o) const = 0;

    virtual Predictions ApplyMany(ObjectsRange const& objects) const = 0;

    virtual ~IClassifier(){};
};

typedef std::shared_ptr<IClassifier> IClassifierPtr;

//////////////////////////////////////////////////////////////////////////
// ��������� ���������� ��������� �������������
//////////////////////////////////////////////////////////////////////////
struct IClassifierLearner
{
	virtual IClassifierPtr Train(Dataset const& ds) = 0;

    virtual void Reset() = 0;
    	
    virtual ~IClassifierLearner(){};
};

typedef std::shared_ptr<IClassifierLearner> IClassifierLearnerPtr;

struct IFeatureSelector;

typedef std::shared_ptr<IFeatureSelector> IFeatureSelectorPtr;

// ��������� ����������� �����������, ������� ��������� � 
// ������ ��������� � �� �������� � �������� ��������
struct INeedFeatureSelector
{
    // ���������� �������� ���������
    virtual void SetFeatureSelector(IFeatureSelectorPtr selector) = 0;

    // �������� ������� �������� ���������
    virtual IFeatureSelectorPtr GetFeatureSelector() = 0;

    virtual ~INeedFeatureSelector(){};
};


typedef std::vector<int> Features;

//////////////////////////////////////////////////////////////////////////
// ���������� ������ ���������, ��� �������--��������, ������� ��.��. �
// ������� ��.��. � �����������
//////////////////////////////////////////////////////////////////////////
struct IFeatureSelector
{
    virtual ~IFeatureSelector(){};

    // ����� ���� ����������
    virtual void Reset() = 0;
        
    // ������������� � �������������� �������� �������
    virtual void Init(Dataset const& ds) = 0;

    // �������� �������� �� ���������� � ����������� ������
    virtual void Select(
        ObjectsClassRange const& correct, 
        ObjectsClassRange const& fitting) = 0;

    // �������� �������� ��� ���������� �������� ������
    virtual void Select(ObjectsClassRange const& cls) = 0;

    // �������� ��������, ���������� ��� ���������� ������� ��������� ��������
    virtual Features const& GetFeatures() const = 0;

    // �������� ��.��. � �����������, ���������� ��� ���������� ������� ��������� ��������
    virtual ECmpSet const& GetECmpSet() const = 0;

};

typedef std::shared_ptr<IFeatureSelector> IFeatureSelectorPtr;


//////////////////////////////////////////////////////////////////////////
// ������� ���������� ����� ������� ���������� ��������� �������������
//////////////////////////////////////////////////////////////////////////
class ClassifierBase
    :public IClassifier
{
public:

    virtual Predictions ApplyMany( ObjectsRange const& objects ) const
    {
        Predictions predictions;
        predictions.reserve(objects.size());

        for(auto& o:objects)
        {
            predictions.push_back(Apply(*o));
        }

        return std::move(predictions);

    }

};




inline bool CheckCorrectness(IBinaryClassifierPtr bincls, 
                            ObjectPtrList const& positive,
                            ObjectPtrList const& negative)
{
    for(auto po: positive)
        if (bincls->Apply(*po) <= 0)
            return false;
    for(auto no: negative)
        if (bincls->Apply(*no) > 0)
            return false;

    return true;
}


// ��������, ���������� �� ����������� �� ��.��.
struct IECVoting
{
    // ���� ��.��., �� ������� �������������� �������������
    virtual void GetECSet(ECSet& ecset) = 0;

    virtual ~IECVoting(){};
};