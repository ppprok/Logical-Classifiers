#include "stdafx.h"
#include "CppUnitTest.h"
#include "Dataset.h"
#include "FTVotingLearner.h"
#include "logging_utils.h"
#include "MultiByBinaryLearner.h"
#include "AlgorithmEstimator.h"
#include "BoostingLearner.h"
#include "BinaryClassifierNormalizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicalAnalysisLibTest
{		
    TEST_CLASS(FTVotingTests)
    {
    public:

        TEST_METHOD(FTVotingCorrect)
        {
            Dataset ds;
            ds.Load("../datasets/dermatology.int");

            auto parts = ds.Split(0.3f, 0.7f);
            parts.first.CollectClasses();
            parts.second.CollectClasses();

            FTVotingLearner ecv;
            ecv.GetFeatureSelector()->Init(ds);

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
                LOG_SEV(trace) << "no:correct.negative: " << cls->Apply(*no);
                Assert::AreEqual(0.0f, cls->Apply(*no));
            }

            
            auto norm = std::make_shared<BinaryClassifierNormalizer>(cls);
            norm->Normalize(ds.objects);
            cls = norm;

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
                LOG_SEV(trace) << "no:correct.negative: " << cls->Apply(*no);
                Assert::AreEqual(0.0f, cls->Apply(*no));
            }


        }

        
        TEST_METHOD(FTVotingCorrect2)
        {
            Dataset ds;
            ds.Load("../datasets/iris.int");

            ObjectsClass fitting;

            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->GetFeatureSelector()->Init(ds);


            auto& correct = ds.classes[0];
            
            auto cls = ecv->Train(correct, fitting);

            for (auto& po:correct.positive)
            {
                LOG_SEV(trace) << "p:correct.positive: " << cls->Apply(*po);
                Assert::IsTrue(cls->Apply(*po) > 0);
            }

            for (auto& no:correct.negative)
            {
                LOG_SEV(trace) << "no:correct.negative: " << cls->Apply(*no);
                Assert::AreEqual(0.0f, cls->Apply(*no));
            }


            correct = ds.classes[1];

            //ecv = std::make_shared<FTVotingLearner>();
            ecv->Reset();
            cls = ecv->Train(correct, fitting);

            for (auto& po:correct.positive)
            {
                LOG_SEV(trace) << "p:correct.positive: " << cls->Apply(*po);
                Assert::IsTrue(cls->Apply(*po) > 0);
            }

            for (auto& no:correct.negative)
            {
                LOG_SEV(trace) << "no:correct.negative: " << cls->Apply(*no);
                Assert::AreEqual(0.0f, cls->Apply(*no));
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
            Assert::IsTrue(e == 0);
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
            Assert::IsTrue(e < 0.2);
        }

        TEST_METHOD(CVMbyBforSoybean)
        {
            auto e = CVMultiByBinaryLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e < 0.3);
        }

        TEST_METHOD(CVMbyBforBalanceScale)
        {
            auto e = CVMultiByBinaryLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e < 0.95);
        }


        TEST_METHOD(CVBoostingForIris)
        {
            auto e = CVBoostingLearner("../datasets/iris.int");
            Assert::IsTrue(e < 0.05);
        }

        TEST_METHOD(CVBoostingForSoybean)
        {
            auto e = CVBoostingLearner("../datasets/soybean-large.int");
            Assert::IsTrue(e < 0.15);
        }

        TEST_METHOD(CVBoostingForBalanceScale)
        {
            auto e = CVBoostingLearner("../datasets/balance-scale.int");
            Assert::IsTrue(e < 0.25);
        }

        TEST_METHOD(LOOBoostingForSoybeanSmall)
        {
            auto e = LOOBoostingLearner("../datasets/soybean-small.int");
            Assert::IsTrue(e < 0.03);
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
            ecv->GetOptions().coverLimit = 100;
            ecv->GetOptions().cmpHeightThreshold = 200;
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
            mbbc->CurrentOptions.correctPart = 1;

            auto ecv = std::make_shared<FTVotingLearner>();
            ecv->GetOptions().coverLimit = 100;
            ecv->GetOptions().cmpHeightThreshold = 200;

            mbbc->SetPositiveBinaryLearner(ecv);

            GroupedPredictions gp = AlgorithmEstimator().FoldsCrossValidation(ds, mbbc);
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
            boosting->positiveLearner = ecv;
            //boosting->negativeLearner = ecv;

            GroupedPredictions gp = AlgorithmEstimator().FoldsCrossValidation(ds, boosting);
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e << "; MErrNR=" << gp.GetMeanErrorIgnoreRejections();
            return e;
        }


        Estimate LOOBoostingLearner(std::string const& dataset)
        {
            BOOST_LOG_NAMED_SCOPE("CVBootingLearner");
            
            Dataset ds;
            ds.Load(dataset);

            auto boosting = std::make_shared<BoostingLearner>();    
            boosting->CurrentOptions.stopQ = 0.5f;
            auto ecv = std::make_shared<FTVotingLearner>();
            boosting->positiveLearner = ecv;

            GroupedPredictions gp = AlgorithmEstimator().LeaveOneOutCrossValidation(ds, boosting);
            auto e = gp.GetMeanError();
            LOG << "MeanError=" << e << "; MErrNR=" << gp.GetMeanErrorIgnoreRejections();
            return e;
        }

    };
}