#pragma once
#include <algorithm>
#include <boost\random\uniform_real.hpp>
#include <boost\random.hpp>

#include "Object.h"
#include "containers.h"
#include <map>

// ���������� � ��������� ������ ��� ��� ����������
struct SelectedClassInfo
{
    int label;  // ����� ������
    Weight weight;  // ��������� ��� ������� ������
    bool negative; // ��� ����� ��� ��� ����������

    SelectedClassInfo(int l, Weight w, bool neg)
    {
        label = l;
        weight = w;
        negative = neg;
    }
};


// ����������� ��� ������ � ������ ��������
class SamplesWeighter
{

    // �������, ����������� ����� � ����� ��� ��������
    typedef std::map<int, Weight> ClassWeightMap;
    
    // ������� � ������
    ObjectPtrList _objects;

    // ������� ����� �����
    Weight _sumWeight;

    //////////////////////////////////////////////////////////////////////////
    // ���������� ��������� �����
    //////////////////////////////////////////////////////////////////////////
    typedef boost::minstd_rand stdrand;
    typedef boost::uniform_real<Weight> uni_dist;
    typedef boost::variate_generator<stdrand, uni_dist> uni_generator;

    // ��������� ��������� �����, ����������� �� [0,1]
    mutable uni_generator _rand;

    // ���� �������
    ClassWeightMap _classWeights;

private:

    void OnUpdateWeight(ObjectPtr const& o);

    void OnUpdateWeights(ObjectPtrList const& objects);

    void OnUpdateWeights();


public:

    SamplesWeighter():_rand(stdrand(), uni_dist()){};

    // �������� ���� �������
    ClassWeightMap const& GetClassWeights() const;

    // ���������� �������
    void SetObjects(ObjectPtrList objects);

    // �������� ��������� ���
    void UpdateWeightSum();

    // �������� �������� ����� �����
    void ResetWeightSum()
    {
        _sumWeight = 0;
    }

    // �������� �������
    ObjectPtrList const& GetObjects() const;
    
    // ���������� ���������� ���
    void SetWeight(Weight w);

    // �������� ����� �����
    Weight GetWeightSum() const;

    // ����������� ����, ����� �� ����� ���� ���������
    void NormalizeWeights();

    // ���������� � ��������� �������
    void RandomShuffle();

    // ������� n ��������� ��������
    ObjectPtrList GetRandomSamples(int n) const;

    // ������� n ��������� �������� ���������� ������
    ObjectPtrList GetRandomSamples(int n, SelectedClassInfo const& cls) const;

    // ������� �������� ��������� ������, ��������� ���� ��� ������������� ������������
    ObjectPtr GetRandomSample() const;

    // ����������� ������� �� ����������� �����
    void OrderSamples();

    // ����������� ������� �� �������� �����
    void OrderSamplesDescend();

    // ������� ������� ���������
    void RemoveNull();
    
    // ������� ������ � ��������� ����� ������ delta
    void UpdateClassWeights();


    // ������� ��������� ����� ��� ��� ���������, � �������� ��� ������ delta
    SelectedClassInfo SelectRandomClass(Weight delta);

    // ����� ������� ������ � ��� ����������
    void PartitionByClass(int label, ObjectPtrList& positive, ObjectPtrList& negative);

    // ������� ����������� ������ ������������� � ������������� �����������,
    // ������� ���������� ��������� ���������
    SelectedClassInfo SelectPositiveNegativeSamples(
        Weight epsilon, 
        Weight delta, 
        ObjectPtrList& positive, 
        ObjectPtrList& negative);

    private:

        // ����������, ����������� 
        Weight Delta(Weight posw, Weight negw, Weight epsilon);
};