#include "stdafx.h"
#include "CppUnitTest.h"
#include "Dataset.h"
//#include "ECmpVotingLearner.h"
#include "logging_utils.h"
#include "MultiByBinaryLearner.h"
#include "AlgorithmEstimator.h"
#include "BoostingLearner.h"
#include "ECmpByRankFeatureSelector.h"
#include "FTVotingLearner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicalAnalysisLibTest
{		
    TEST_CLASS(ECmpVotingTests)
    {
    public:

        TEST_METHOD(ECmpVotingCorrect)
        {
            Dataset ds;
            ds.Load("../ao.test/datasets/iris.txt");

            auto parts = ds.Split(0.8f, 0.2f);
            parts.first.CollectClasses();
            parts.second.CollectClasses();

            FTVotingLearner ecv;
            ecv.SetFeatureSelector(std::make_shared<ECmpByRankFeatureSelector>());
            ecv.GetFeatureSelector()->Init(parts.first);

            auto& correct = parts.first.classes[1];
            auto& fitting = parts.second.classes[1];

            auto cls = ecv.Train(correct, fitting);

            for (auto& p:correct.positive)
            {
                LOG_SEV(trace) << "p:correct.positive: " << cls->Apply(*p);
                Assert::IsTrue(cls->Apply(*p) > 0);
            }

            for (auto& p:fitting.positive)
            {
                LOG_SEV(trace) << "p:fitting.positive: " << cls->Apply(*p);
            }

            for (auto& p:fitting.negative)
            {
                LOG_SEV(trace) << "p:fitting.negative: " << cls->Apply(*p);
            }

            for (auto& no:correct.negative)
            {
                Assert::IsTrue(cls->Apply(*no) == 0);
            }
        }

        TEST_METHOD(MbyBforIris)
        {
            auto e = CheckMultiByBinaryLearner("../datasets/iris.int");
            Assert::IsTrue(e == 0);
        }

        TEST_METHOD(MbyBforSoybean)
        {
            auto e = CheckMultiByBinaryLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e  == 0);
        }

        TEST_METHOD(MbyBforBalanceScale)
        {
            auto e = CheckMultiByBinaryLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e == 0);
        }

        TEST_METHOD(BoostingForIris)
        {
            auto e = CheckBoostingLearner("../datasets/iris.int");
            Assert::IsTrue(e == 0);
        }

        TEST_METHOD(BoostingForSoybean)
        {
            auto e = CheckBoostingLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e == 0);
        }

        TEST_METHOD(BoostingForBalanceScale)
        {
            auto e = CheckBoostingLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e == 0);
        }

        TEST_METHOD(CVMbyBforIris)
        {
            auto e = CVMultiByBinaryLearner("../datasets/iris.int");
            Assert::IsTrue(e < 0.4);
        }

        TEST_METHOD(CVMbyBforSoybean)
        {
            auto e = CVMultiByBinaryLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e < 0.3);
        }

        TEST_METHOD(CVMbyBforBalanceScale)
        {
            auto e = CVMultiByBinaryLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e < 0.9);
        }


        TEST_METHOD(CVBoostingForIris)
        {
            auto e = CVBoostingLearner("../datasets/iris.int");
            Assert::IsTrue(e < 0.1);
        }

/*        TEST_METHOD(CVBoostingForSoybean)
        {
            auto e = CVBoostingLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e < 0.1);
        }*/

        TEST_METHOD(CVBoostingForBalanceScale)
        {
            auto e = CVBoostingLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e < 0.25);
        }


    private:

        Estimate CheckMultiByBinaryLearner(std::string const& dataset)
        {
            BOOST_LOG_NAMED_SCOPE("CheckMultiByBinaryLearner");

            Dataset ds;
            ds.Load(dataset);

            MultiByBinaryLearner mbbc;    
            mbbc.CurrentOptions.correctPart = 1;
            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->SetFeatureSelector(std::make_shared<ECmpByRankFeatureSelector>());
//            ecv->CurrentOptions.ftCount = 10;
            mbbc.SetPositiveBinaryLearner(ecv);

            auto a = mbbc.Train(ds);

            GroupedPredictions gp;
            gp.groups.push_back(a->ApplyMany(ds.objects));
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e;
            return e;
        }

        Estimate CheckBoostingLearner(std::string const& dataset)
        {
            BOOST_LOG_NAMED_SCOPE("CheckBoostingLearner");

            Dataset ds;
            ds.Load(dataset);

            BoostingLearner boosting;    
            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->SetFeatureSelector(std::make_shared<ECmpByRankFeatureSelector>());
//            ecv->CurrentOptions.ftCount = 5;
            boosting.positiveLearner = ecv;

            auto a = boosting.Train(ds);

            GroupedPredictions gp;
            gp.groups.push_back(a->ApplyMany(ds.objects));
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e;
            return e;
        }

        Estimate CVMultiByBinaryLearner(std::string const& dataset)
        {
            BOOST_LOG_NAMED_SCOPE("CVMultiByBinaryLearner");

            Dataset ds;
            ds.Load(dataset);

            auto mbbc = std::make_shared<MultiByBinaryLearner>();    

            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->SetFeatureSelector(std::make_shared<ECmpByRankFeatureSelector>());
//            ecv->CurrentOptions.ftCount = 10;
            mbbc->SetPositiveBinaryLearner(ecv);

            AlgorithmEstimator ae;
            ae.CurrentOptions.randomSeed = 777;
            GroupedPredictions gp = ae.FoldsCrossValidation(ds, mbbc);
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e;
            return e;
        }

        Estimate CVBoostingLearner(std::string const& dataset)
        {
            BOOST_LOG_NAMED_SCOPE("CVBootingLearner");

            Dataset ds;
            ds.Load(dataset);

            auto boosting = std::make_shared<BoostingLearner>();    
            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->SetFeatureSelector(std::make_shared<ECmpByRankFeatureSelector>());
//            ecv->CurrentOptions.ftCount = 5;
            boosting->positiveLearner = ecv;
            //boosting->negativeLearner = ecv;

            GroupedPredictions gp = AlgorithmEstimator().FoldsCrossValidation(ds, boosting);
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e;
            return e;
        }
    };
}