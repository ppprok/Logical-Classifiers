#pragma once

#include <map>

#include "IMLAlgorithm.h"
#include "ECmp.h"
#include "ECmpSetPredicate.h"
#include "SamplesWeighter.h"
#include "CmpMatrixBuilder.h"
#include "containers.h"
#include "ECmpSetPredicateBuilder.h"
#include "LocalBasisBuilder.h"
#include "Randomizer.h"
#include "math_utils.h"


// �������� ����������� ���������� ������� ��������
class BoostingLogicalCorrector
    :public MLAlgorithmBase
{

public:

    // ����� �������������
    enum Mode
    {
        // ������� �����
        Basis,
        // ���������� �����
        Additive,
    };

    // ���������� � ���� ������
    struct ClassWeightInfo
    {
        // ����� ������
        int label;
        // ������������ ������� �� �� ������
        bool complement;
        // ��� �������� ������
        Weight positiveWeight;
        // ��� �������� �� �� ������
        Weight negativeWeight;
        // ��������������� ����� ���� ����� ��� ������ -- �����
        Weight Q;

        ClassWeightInfo(int l, bool c = false)
        {
            label = l;
            complement = c;
            positiveWeight = 0;
            negativeWeight = 0;
            Q = 0;
        }

		// �������� ����� ��� ������, ����������� �� ����� ����� ������������� � ������������� ���������� �������� 
        Weight GetDelta(Weight p, Weight n, Weight eps) const
        {
            return (GetTotalWeight() / Q) * psi2(n, p, eps);
        }

		// ����� �������� ������� ����� ������� ��������� ����� � ����������� ���������
		// ����������, ����� ���� ���������� ��� ������ ����
		Weight GetDeltaDiff(Weight p, Weight n, Weight eps, Weight delta) const
		{
			return psi(p, n, eps) - sqrt(delta * Q / GetTotalWeight());
		}

		// ������������ ������� ����� � ����������, ���������� ��� ������ 
		Weight GetMaxDelta(Weight eps) const
		{
			return GetDelta(GetNormalizedPositiveWeight(), 0, eps);
		}

		Weight GetTotalWeight() const
		{
			return positiveWeight + negativeWeight;
		}

		Weight GetNormalizedPositiveWeight() const
		{
			return GetTotalWeight() != 0 ? positiveWeight / GetTotalWeight() : 0;
		}

		Weight GetNormalizedNegativeWeight() const
		{
			return GetTotalWeight() != 0 ? negativeWeight / GetTotalWeight() : 0;
		}

		static Weight psi2(Weight p, Weight n, Weight eps)
		{
			return sqr(psi(p, n, eps));
		}

		static Weight psi(Weight p, Weight n, Weight eps)
		{
			return sqrt(p) - sqrt(n+eps);
		}
    };

    // ����� �������� � �������������
    struct Options
    {
        // ����� ��������
        int iterationsCount;

        // ��������� �����
        ECmpSet localBasis;

        // ����� �������������� ��������
        int optionalObjectsCount;

        // �������� ���������� ���� ���������
        Weight epsilon;

        // ����� �������������
        Mode mode;

		// �������� Q ����� �������� ������� ������������
		Weight stopQ;

        Options()
        {
            mode = Basis;
            optionalObjectsCount = 0;
            iterationsCount = 0;
            epsilon = 0;
			stopQ = 0;
        }

        UTILITY_MOVE_DEFAULT_MEMBERS(Options, 
            (mode)(optionalObjectsCount)(iterationsCount)(localBasis)(epsilon)(stopQ));

        //Options(Dataset const& ds);
    };

private:

    typedef std::map<int, ECmpSetPredicates> PredicatesMap;

    // ���������, ����������� � �����������
    PredicatesMap _predicates;

    // ������� ����� �������� � ������������
    Options _currentOptions;

    Randomizer _randomizer;

public:

    // �������������� ����� �������� � �������������
    Options RecommendedOptions;
    
    // �������� ���������� ���������
    virtual void Reset();

    // ��������� �� �������
    virtual void Train(Dataset const& ds);


    // ��������� ������������� � �������
    virtual Prediction Apply(Object const& o) const;

private:

    // ���������� ������ ���������� ������������� � ������������� ��������, 
    // �� ������� ������������ ��������������� ���������
 /*   void AssignWeightedObjects(Dataset const &ds, SelectedClassInfo &cls, 
        ECmpSetPredicateBuilder::TrainInfo &positive, 
        ECmpSetPredicateBuilder::TrainInfo &negative);

    // ������� ��������� ����������� �������
    void SelectOptionalPositiveObjects(
        SamplesWeighter &weighter, 
        SelectedClassInfo cls, int count,
        ECmpSetPredicateBuilder::TrainInfo &positive);

    // ��������� ���� �������� �� ��������
    void CalculateWeightsByMargins(Dataset const &ds, Predictions &predictions);*/

    // ���������������� ��������� ���������� �� �������
    void InitClassesPredicates(Dataset const &ds);
        
    // ��������������� ������� ����� �� ��������� �������
    Options CreateCurrentOptions(Dataset const& ds);

    
    // ������� ���������� � ����� �� �������
    std::vector<ClassWeightInfo> CollectClassWeightInfo(
        Classes const& classes,
        Predictions const& predictions, Weight eps);

    // ������� ���������� �����
    ClassWeightInfo SelectClass(Dataset const &ds, Predictions const& predictions, Weight delta, Weight eps);

    // ��������� ���� �������� ��� ���������� ������
    void WeightObjects(Dataset const& ds, Predictions const& predictions, ClassWeightInfo const& cls);
    
    // ������� ������� ��� ��������
    void SelectTrainObjects(Dataset const& ds, BoostingLogicalCorrector::ClassWeightInfo const& cls, ECmpSetPredicateBuilder::TrainInfo& positive, ECmpSetPredicateBuilder::TrainInfo& negative, Weight delta, Weight epsilon, int optionalObjectsCount);

	// ������� ������� ��� ��������
	void SelectTrainObjectsByIncrease(Dataset const& ds, BoostingLogicalCorrector::ClassWeightInfo const& cls, ECmpSetPredicateBuilder::TrainInfo& positive, ECmpSetPredicateBuilder::TrainInfo& negative, Weight delta, Weight epsilon, int optionalObjectsCount);

	int CollectOptionalObjects(int optionalObjectsCount, ECmpSetPredicateBuilder::TrainInfo &positive);

};